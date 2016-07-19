using System.Collections.Generic;
using UnityEngine;
using ProtoBuf;
using System;

public partial class NetworkClient : MonoBehaviour {
    System.Random rand = new System.Random();

    private TCPClient client;

    private string serverIP = "localhost";

    // Use this for initialization
    void Start()
    {
        InitPacketReceive();
        InitPacketSend();

        client = new TCPClient();
        client.ReceiveHandler = ReceiveHandler;
        client.ConnectHandler = ServerConnectHandler;
        client.Init(serverIP, 3999);
        client.Connect();

        Debug.Log("Try connect");
    }

    // Update is called once per frame
    void Update()
    {
        ParsePacket();
    }

    void OnDestroy()
    {
        client.Disconnect();
    }

    void FixedUpdate()
    {
    }

    private void ServerConnectHandler()
    {
        Debug.Log("Connect success");
    }
}