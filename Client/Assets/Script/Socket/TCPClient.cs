using System;
using System.Net;
using System.Net.Sockets;

class TCPClient {
    public delegate void ConnectDelegate();
    public delegate void ReceiveDelegate(byte[] data);

    private Socket socket;
    private IPEndPoint hostEndPoint;

    private bool isConnected = false;

    public ConnectDelegate ConnectHandler { private get; set; }
    public ReceiveDelegate ReceiveHandler { private get; set; }

    ~TCPClient()
    {
        Disconnect();
    }

    public void Init(string ip, int port)
    {
        IPHostEntry host = Dns.GetHostEntry(ip);
        IPAddress[] addressList = host.AddressList;

        hostEndPoint = new IPEndPoint(addressList[addressList.Length - 1], port);
        socket = new Socket(hostEndPoint.AddressFamily, SocketType.Stream, ProtocolType.Tcp);
    }

    public void Connect()
    {
        var saea = new SocketAsyncEventArgs();
        saea.RemoteEndPoint = hostEndPoint;
        saea.Completed += OnConnect;

        bool willRaiseEvent = socket.ConnectAsync(saea);
        if (willRaiseEvent == false) {
            OnConnect(this, saea);
        }
    }

    public void Disconnect()
    {
        socket.Disconnect(false);
    }

    public void BeginReceive()
    {
        var token = new TCPReceiveToken();

        var saea = new SocketAsyncEventArgs();
        saea.UserToken = token;
        saea.SetBuffer(new byte[500], 0, 500);
        saea.Completed += OnComplete;

        BeginReceive(saea);
    }

    public void BeginReceive(SocketAsyncEventArgs saea)
    {
        bool willRaiseEvent = socket.ReceiveAsync(saea);
        if (willRaiseEvent == false) {
            OnReceive(this, saea);
        }
    }

    public void Send(byte[] data)
    {
        var token = new TCPSendToken();
        token.length = data.Length;

        var saea = new SocketAsyncEventArgs();
        saea.UserToken = token;
        saea.SetBuffer(data, 0, data.Length);

        Send(saea);
    }

    private void Send(SocketAsyncEventArgs saea)
    {
        var token = saea.UserToken as TCPSendToken;
        int newOffset = saea.Offset + saea.BytesTransferred;
        saea.SetBuffer(newOffset, token.length - newOffset);
        saea.Completed += OnComplete;

        bool willRaiseEvent = socket.SendAsync(saea);
        if (willRaiseEvent == false) {
            OnSend(this, saea);
        }
    }

    // Handlers
    public void OnComplete(object sender, SocketAsyncEventArgs saea)
    {
        switch (saea.LastOperation) {
            case SocketAsyncOperation.Receive: {
                    OnReceive(sender, saea);
                }
                break;

            case SocketAsyncOperation.Send: {
                    OnSend(sender, saea);
                }
                break;

            case SocketAsyncOperation.Disconnect: {
                    OnDisconnect(sender, saea);
                }
                break;
        }
    }

    public void OnConnect(object sender, SocketAsyncEventArgs saea)
    {
        isConnected = (saea.SocketError == SocketError.Success);
        if (isConnected == false) {
            OnDisconnect(sender, saea);
            return;
        }

        if(ConnectHandler != null) {
            ConnectHandler();
        }

        BeginReceive();
    }

    public void OnSend(object sender, SocketAsyncEventArgs saea)
    {
        if (saea.SocketError != SocketError.Success) {
            OnDisconnect(sender, saea);
            return;
        }

        if (saea.LastOperation == SocketAsyncOperation.Send) {
            var token = saea.UserToken as TCPSendToken;
            token.length -= saea.BytesTransferred;

            if (token.length != 0) {
                Send(saea);
            }
            else {
                saea.Dispose();
            }
        }
    }

    public void OnReceive(object sender, SocketAsyncEventArgs saea)
    {
        if (saea.SocketError != SocketError.Success || saea.BytesTransferred == 0) {
            OnDisconnect(sender, saea);
            return;
        }

        if (saea.LastOperation == SocketAsyncOperation.Receive) {

            if (ReceiveHandler != null) {
                var buffer = new byte[saea.BytesTransferred];
                Buffer.BlockCopy(saea.Buffer, 0, buffer, 0, saea.BytesTransferred);

                ReceiveHandler(buffer);
            }

            BeginReceive(saea);
        }
    }

    private void OnDisconnect(object sender, SocketAsyncEventArgs saea)
    {
        isConnected = false;
        socket.Disconnect(false);
    }
}