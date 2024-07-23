using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PersoMo : MonoBehaviour
{
    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        if (Input.GetKeyDown(KeyCode.LeftArrow)){
            transform.Translate(new Vector3(-1.1f,0,0));
        }
        if (Input.GetKeyDown(KeyCode.RightArrow)){
            transform.Translate(new Vector3(1.1f,0,0));
        }
        if (Input.GetKeyDown(KeyCode.UpArrow)){
            transform.Translate(new Vector3(0,0,1.1f));
        }
        if (Input.GetKeyDown(KeyCode.DownArrow)){
            transform.Translate(new Vector3(0,0,-1.1f));
        }
    }
}
