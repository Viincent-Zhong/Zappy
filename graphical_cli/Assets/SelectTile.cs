using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.Text.RegularExpressions;

public class SelectTile : MonoBehaviour
{
    public GameObject _obj;

    void OnMouseDown()
    {
        string[] digits= Regex.Split(_obj.name, @"\D+");
        int x = 0;
        int y = 0;
        TileData elements;

        try {
            x = int.Parse(digits[1]);
            y = int.Parse(digits[2]);
        } catch (System.FormatException e) {
            return;
        }
        elements = MapData.TileList[x][y];
        InfoData.elements = elements.qTab;
        Debug.Log("Food" + elements.qTab[0] + " linemate" + elements.qTab[1] + " deraumere" + elements.qTab[2] + " sibur" + elements.qTab[3] + " mendiane" + elements.qTab[4] + " phiras" + elements.qTab[5] + " thystame" + elements.qTab[6]);
    }
}
