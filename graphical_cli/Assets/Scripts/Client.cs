/*
** EPITECH PROJECT, 2022
** B-YEP-410-PAR-4-1-zappy-pierre-alexandre.delgado-arevalo
** File description:
** Client
*/

using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.Net;
using System.Text;
using System;
using UnityEngine.SceneManagement;
using System.Threading;
using System.IO;
using System.Net.Sockets;

public class Client : MonoBehaviour
{
    public static Client instance;
    private Thread _rec;
    private Socket _sender;

    private void Awake()
    {
        if (instance == null)
        {
            instance = this;
        }
        else if (instance != this)
        {
            Debug.Log("Instance already exists, destroying object!");
            Destroy(this);
        }
    }

    private void Start()
    {
        _rec = new Thread(ReceiveServer);
    }

    private void ReceiveServer()
    {
        byte[] messageReceived = new byte[1024];
        byte[] tmp = new byte[1];
        int offset = 0;
        int byteRecv = 0;

        while (1 == 1) {
            byteRecv = _sender.Receive(tmp, 1, SocketFlags.None);
            if (byteRecv <= 0) {
                InfoData.finito = true;
                _sender.Shutdown(SocketShutdown.Both); 
                _sender.Close();
                return;
            }

            if (Encoding.ASCII.GetString(tmp, 0, 1)[0] == '\n') {
                messageReceived[offset] = tmp[0];
                offset += 1;
                Parse.InterpretToGame(Encoding.ASCII.GetString(messageReceived, 0, offset));
                Array.Clear(messageReceived, 0, messageReceived.Length);
                offset = 0;
            } else {
                messageReceived[offset] = tmp[0];
                offset += 1;
            }
        }
    }

    public void ConnectToServer()
    {
        IPAddress ipAddr = IPAddress.Parse(ParamsData.machine);
        IPEndPoint localEndPoint = new IPEndPoint(ipAddr, ParamsData.port);

        _sender = new Socket(ipAddr.AddressFamily,
        SocketType.Stream, 0);
        _sender.Connect(localEndPoint);

        byte[] messageReceived = new byte[1024];
        int byteRecv = _sender.Receive(messageReceived); 
        print(Encoding.ASCII.GetString(messageReceived, 0, byteRecv));

        byte[] msg = Encoding.ASCII.GetBytes("GRAPHIC\n"); 
        int byteSent = _sender.Send(msg);
        Execute execute;

        execute = new Execute();
        execute.initPersoData();
        _rec.Start();
    }

    public void StartGame()
    {
        SceneManager.LoadScene("Game");
    }

    public void Exit()
    {
        Application.Quit();
    }

    void Update()
    {
    }

}