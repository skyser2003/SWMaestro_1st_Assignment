using System;

class PacketHeader {
    public int packetID;
    public int length;

    public static readonly int Size = 8;

    public PacketHeader()
    {
        Init();
    }

    public void Init()
    {
        packetID = -1;
        length = -1;
    }

    public byte[] Serialize()
    {
        var data = new byte[Size];
        Buffer.BlockCopy(BitConverter.GetBytes(packetID), 0, data, 0, 4);
        Buffer.BlockCopy(BitConverter.GetBytes(length), 0, data, 4, 4);

        return data;
    }

    public void Deserialize(byte[] data)
    {
        packetID = BitConverter.ToInt32(data, 0);
        length = BitConverter.ToInt32(data, 4);
    }
}