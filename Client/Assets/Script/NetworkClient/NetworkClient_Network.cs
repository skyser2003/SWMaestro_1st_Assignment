using System;
using System.Collections.Generic;
using System.Reflection;
using UnityEngine;
using System.IO;

public partial class NetworkClient {
    private List<byte> receiveBuffer;
    private Dictionary<int, MethodInfo> receiveHandlerList;
    private Dictionary<int, MethodInfo> parserList;
    private Dictionary<Type, int> sendPacketIDList;

    private PacketHeader receiveHeader;

    private void InitPacketReceive()
    {
        receiveBuffer = new List<byte>();
        receiveHandlerList = new Dictionary<int, MethodInfo>();
        parserList = new Dictionary<int, MethodInfo>();

        receiveHeader = new PacketHeader();

        // Enum
        Dictionary<string, int> enumNameList = new Dictionary<string, int>();

        List<Array> enumList = new List<Array>();
        enumList.Add(Enum.GetValues(typeof(PKENUM.SCPacketEnum)));

        foreach (var enumArr in enumList) {
            foreach (var val in enumArr) {
                string enumName = val.ToString();
                int enumVal = (int)val;

                if (enumName.EndsWith("END") == false && enumName.EndsWith("BEGIN") == false) {
                    if (enumNameList.ContainsKey(enumName) == true) {
                        Debug.LogError("Something's wrong!  Enum name : " + enumName);
                        continue;
                    }
                    else if (enumNameList.ContainsValue(enumVal) == true) {
                        Debug.LogError("Something's wrong!  Enum val : " + enumVal);
                        continue;
                    }

                    enumNameList.Add(enumName, enumVal);
                }
            }
        }

        // Member method
        List<MethodInfo> packetReceiveHandlerList = new List<MethodInfo>();

        var allMethodInfoList = GetType().GetMethods(BindingFlags.NonPublic | BindingFlags.Instance);
        foreach (var info in allMethodInfoList) {
            if (info.Name == "OnPacketReceive" && info.GetParameters().Length == 1) {
                packetReceiveHandlerList.Add(info);
            }
        }

        // Parser
        var parserOriginal = GetType().GetMethod("Parse", BindingFlags.NonPublic | BindingFlags.Instance);

        foreach (var info in packetReceiveHandlerList) {
            var parameter = info.GetParameters()[0];
            var pksType = parameter.ParameterType;
            var pksTypeName = parameter.ParameterType.Name;

            if (enumNameList.ContainsKey(pksTypeName) == true) {
                var genericMethod = parserOriginal.MakeGenericMethod(pksType);
                parserList.Add(enumNameList[pksTypeName], genericMethod);
            }
        }

        // Receive handler
        foreach (var info in packetReceiveHandlerList) {
            var parameter = info.GetParameters()[0];
            var pksTypeName = parameter.ParameterType.Name;

            if (enumNameList.ContainsKey(pksTypeName) == true) {
                receiveHandlerList.Add(enumNameList[pksTypeName], info);
            }
            else {
                // TODO : Some error message?
            }
        }
    }

    private void InitPacketSend()
    {
        sendPacketIDList = new Dictionary<Type, int>();
        
        Dictionary<string, int> enumNameList = new Dictionary<string, int>();

        List<Array> enumList = new List<Array>();
        enumList.Add(Enum.GetValues(typeof(PKENUM.CSPacketEnum)));

        foreach (var enumArr in enumList) {
            foreach (var val in enumArr) {
                string enumName = val.ToString();
                int enumVal = (int)val;

                if (enumName.EndsWith("END") == false && enumName.EndsWith("BEGIN") == false) {
                    if (enumNameList.ContainsKey(enumName) == true) {
                        Debug.LogError("Something's wrong!  Enum name : " + enumName);
                        continue;
                    }
                    else if (enumNameList.ContainsValue(enumVal) == true) {
                        Debug.LogError("Something's wrong!  Enum val : " + enumVal);
                        continue;
                    }

                    enumNameList.Add(enumName, enumVal);
                }
            }
        }

        // Packet type to id
        foreach (var pair in enumNameList) {
            string enumName = pair.Key;
            int enumVal = pair.Value;
            var type = Type.GetType("PKS." + enumName);

            if (type == null) {
                Debug.LogError("Something's wrong!  Enum name : " + enumName);
                continue;
            }

            sendPacketIDList[type] = enumVal;
        }
    }

    private void ParsePacket()
    {
        lock (receiveBuffer) {
            while (true) {
                if (receiveHeader.packetID == -1 && PacketHeader.Size <= receiveBuffer.Count) {
                    receiveHeader.Deserialize(receiveBuffer.ToArray());
                    receiveBuffer.RemoveRange(0, 8);
                }
                else if (receiveHeader.packetID != -1 && receiveHeader.length <= receiveBuffer.Count) {
                    MethodInfo parser;
                    MethodInfo handler;

                    if (parserList.TryGetValue(receiveHeader.packetID, out parser) == true &&
                        receiveHandlerList.TryGetValue(receiveHeader.packetID, out handler) == true) {
                        var data = new byte[receiveHeader.length];
                        Buffer.BlockCopy(receiveBuffer.ToArray(), 0, data, 0, receiveHeader.length);

                        var pks = parser.Invoke(this, new object[] { data });
                        handler.Invoke(this, new object[] { pks });
                    }

                    receiveBuffer.RemoveRange(0, receiveHeader.length);
                    receiveHeader.Init();
                }
                else {
                    break;
                }
            }
        }
    }

    private Message Parse<Message>(byte[] data)
        where Message : ProtoBuf.IExtensible
    {
        using (var ms = new MemoryStream(data)) {
            return ProtoBuf.Serializer.Deserialize<Message>(ms);
        }
    }

    private void ReceiveHandler(byte[] data)
    {
        lock (receiveBuffer) {
            receiveBuffer.AddRange(data);
        }
    }

    private void Send<Message>(Message pks)
        where Message : ProtoBuf.IExtensible
    {
        int id;
        if(sendPacketIDList.TryGetValue(pks.GetType(), out id) == true) {
            Send(id, pks);
        }
    }

    private void Send<Message>(int packetID, Message pks)
        where Message : ProtoBuf.IExtensible
    {
        if (client == null) {
            return;
        }

        using (var ms = new MemoryStream()) {
            ProtoBuf.Serializer.Serialize(ms, pks);

            var buffer = new byte[PacketHeader.Size + ms.Length];

            var header = new PacketHeader();
            header.packetID = packetID;
            header.length = (int)ms.Length;

            Buffer.BlockCopy(header.Serialize(), 0, buffer, 0, PacketHeader.Size);
            Buffer.BlockCopy(ms.ToArray(), 0, buffer, PacketHeader.Size, buffer.Length - PacketHeader.Size);

            client.Send(buffer);
        }
    }
}