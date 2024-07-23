using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using System;
using System.Net;
using System.Net.Sockets;
using System.Text;

public class buttonControl : MonoBehaviour
{
    public static Client instance;
    public static int dataBufferSize = 4096;

    public string ip = "10.41.177.42";
    public int port = 4242;
    public int myId = 0;
    // Start is called before the first frame update
    void Start()
    {
    }

    // Update is called once per frame
    void Update()
    {
        
    }

    public void Connect()
    {
        IPHostEntry ipHost = Dns.GetHostEntry(Dns.GetHostName());
        IPAddress ipAddr = ipHost.AddressList[0];
        IPEndPoint localEndPoint = new IPEndPoint(ipAddr, 4242);

        Socket sender = new Socket(ipAddr.AddressFamily,
                   SocketType.Stream, 0);

        sender.Connect(localEndPoint);
        byte[] messageSent = Encoding.ASCII.GetBytes("hello client!");
        sender.Send(messageSent);
    }
}
