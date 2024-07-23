using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SelectPlayer : MonoBehaviour
{
    public GameObject _obj;

    void OnMouseDown()
    {
        Debug.Log(_obj.name);
    }
}
