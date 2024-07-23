using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CameraSwitch : MonoBehaviour
{
    public Camera GlobalCamera;
    public Camera FpsCamera;

    // Update is called once per frame
    void Update()
    {
        float buf = 0;
        if (Input.GetKeyDown(KeyCode.C))
        {
            buf = GlobalCamera.depth;
            GlobalCamera.depth = FpsCamera.depth;
            FpsCamera.depth = buf;
        }
        
    }
}
