/*
** EPITECH PROJECT, 2022
** graphical_cli
** File description:
** Loading
*/

using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class Loading : MonoBehaviour
{
    // Start is called before the first frame update
    void Start()
    {
        // int position = Int16.Parse(RawData.raw_data);
        // MapData.position = position;
        // Perso perso1;
        // perso1.position_x = 3;
        // perso1.position_y = 4;
        // PersoData.persos[0].position_x = 4;
        PersoData.PersoList = new List<Perso>();
        // Perso perso1 = new Perso();
        // perso1.position = new Vector3(0, 0, 9);
        // PersoData.PersoList.Add(perso1);
        // Perso perso2 = new Perso();
        // perso2.position = new Vector3(3, 0, 4);
        // PersoData.PersoList.Add(perso2);
        // Perso perso3 = new Perso();
        // perso3.position = new Vector3(5, 0, 2);
        // PersoData.PersoList.Add(perso3);
        // PersoData.persos[0].position_y = 3;
        // Execute execute = new Execute();
        // execute.initMapData();
        SceneManager.LoadScene("Game");

        // TileData tile = new TileData();
        // tile.qTab = new int[7];
        // tile.qTab[0] = 0;
        // tile.qTab[1] = 1;
        // tile.qTab[2] = 1;
        // tile.qTab[3] = 1;
        // tile.qTab[4] = 0;
        // tile.qTab[5] = 1;
        // tile.qTab[6] = 1;
        // List<TileData> myList = new List<TileData>();
        // myList.Add(tile);
        // MapData.TileList = new List<List<TileData>>();
        // MapData.TileList.Add(myList);
        // print(MapData.TileList[0].Count);
        // print(MapData.TileList.Count);
    }

    // Update is called once per frame
    void Update()
    {
        
    }
}
