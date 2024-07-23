/*
** EPITECH PROJECT, 2022
** B-YEP-410-PAR-4-1-zappy-pierre-alexandre.delgado-arevalo
** File description:
** Execute
*/

using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class Execute
{
    public void initMapData()
    {
        TileData tile = new TileData();
        tile.qTab = new int[7] {1, 1, 1, 1, 1, 1, 1};

        MapData.TileList = new List<List<TileData>>();
        for (int i = 0; i < 10; i++) {
            MapData.TileList.Add(new List<TileData>());
        }
        for (int j = 0; j < MapData.map_size_x; j++) {
            for (int i = 0; i < MapData.map_size_y; i++) {
                MapData.TileList[j].Add(tile);
            }
        }
    }

    public void initPersoData()
    {
        PersoData.PersoList = new List<Perso>();

        Perso perso = new Perso();

        perso.position = new Vector3(0, 0, 0);
        perso.level = 0;
        perso.id = 0;
        perso.team = "";
        perso.inventory = 0;
    }

    public void newPerso(int id, int x, int y, int o, int lvl, string team)
    {
        Perso perso = new Perso();

        perso.position = new Vector3((MapData.map_size_x - 1) - (MapData.map_size_x - 1 - x), 0, (MapData.map_size_y - 1) - y);
        perso.level = lvl;
        perso.id = id;
        perso.team = team;
        perso.inventory = 0;
        PersoData.PersoList.Add(perso);
    }

    public void addPerso(int id)
    {
        Perso perso = new Perso();

        perso.position = new Vector3(0, 0, 0);
        perso.level = 0;
        perso.id = id;
        perso.team = "";
        perso.inventory = 0;
        PersoData.PersoList.Add(perso);
    }

    public void removePerso(int id)
    {
        for (int i = 0; i < PersoData.PersoList.Count; i++) {
            if (PersoData.PersoList[i].id == id) {
                PersoData.PersoList.RemoveAt(i);
                return;
            }
        }
    }

    public void levelUpPerso(int id)
    {
        for (int i = 0; i < PersoData.PersoList.Count; i++) {
            if (PersoData.PersoList[i].id == id) {
                PersoData.PersoList[i].level += 1;
                return;
            }
        }
    }

    public void movePerso(int id, int X, int Y, int O)
    {
        Vector3 vector = new Vector3((MapData.map_size_x - 1) - (MapData.map_size_x - 1 - X), 0, (MapData.map_size_y - 1) - Y);

        for (int i = 0; i < PersoData.PersoList.Count; i++) {
            if (PersoData.PersoList[i].id == id) {
                PersoData.PersoList[i].orientation = O;
                PersoData.PersoList[i].position = vector;
                return;
            }
        }
    }

    public void hideCharacter(int id)
    {
        for (int i = 0; i < PersoData.PersoList.Count; i++) {
            if (PersoData.PersoList[i].id == id) {
                PersoData.PersoList[i].died = 1;
                return;
            }
        }
    }

    public void setTeamName(int id, string name)
    {
        for (int i = 0; i < PersoData.PersoList.Count; i++) {
            if (PersoData.PersoList[i].id == id) {
                PersoData.PersoList[i].team = name;
                return;
            }
        }
    }
}
