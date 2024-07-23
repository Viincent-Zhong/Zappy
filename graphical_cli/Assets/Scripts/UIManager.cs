using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using TMPro;

public class UIManager : MonoBehaviour
{
    public static UIManager instance;

    public GameObject startMenu;
    public TMP_InputField portField;
    public TMP_InputField machineField;

    public void ConnectToServer()
    {
        startMenu.SetActive(false);
        Client.instance.ConnectToServer();
    }

    public void setPort()
    {
        try {
            ParamsData.port = int.Parse(portField.text);
        } catch (System.FormatException e) {
            ParamsData.port = 4242;
        }
    }

    public void setMachine()
    {
        ParamsData.machine = machineField.text;
        if (ParamsData.machine == null || ParamsData.machine == "")
            ParamsData.machine = "127.0.0.1";
    }
}