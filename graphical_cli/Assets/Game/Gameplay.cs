/*
** EPITECH PROJECT, 2022
** B-YEP-410-PAR-4-1-zappy-pierre-alexandre.delgado-arevalo
** File description:
** Gameplay
*/

using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Gameplay : MonoBehaviour
{
    int _nbrPlayers = 0;

    void Start()
    {
        createTileClone(MapData.map_size_y, MapData.map_size_x);
    }

    Vector3 GetOrientation(int direction)
    {
        int orientation = 0;

        switch (direction) {
            case 1:
                orientation = 0;
                break;
            case 2:
                orientation = 90;
                break;
            case 3:
                orientation = 180;
                break;
            case 4:
                orientation = 270;
                break;
        };
        return new Vector3(0, orientation, 0);
    }

    void createTileClone(int nb_j, int nb_i)
    {
        GameObject tileOriginal = GameObject.Find("tileOriginal");
        GameObject Map = GameObject.Find("Map");

        for (int j = 0; j < nb_j; j++) {
            for (int i = 0; i < nb_i; i++) {
                GameObject tileClone = Instantiate(tileOriginal, new Vector3(i * 1.1f, tileOriginal.transform.position.y, j * 1.1f), tileOriginal.transform.rotation);
                tileClone.transform.parent = Map.transform;
                tileClone.name = "Case[" + j +"]" + "[" + i +"]";
            }
        }
    }

    void createPersoClone(int nb)
    {
        GameObject persoOriginal = GameObject.Find("persoOriginal");
        GameObject Persos = GameObject.Find("Persos");
        Vector3 mult = new Vector3(1.1f, 0, 1.1f);
        int i = _nbrPlayers;

        GameObject persoClone = Instantiate(persoOriginal, VectorMult(mult, PersoData.PersoList[i].position), persoOriginal.transform.rotation);
        persoClone.transform.parent = Persos.transform;
        persoClone.transform.eulerAngles = GetOrientation(PersoData.PersoList[i].orientation);
        persoClone.name = "Perso [" + nb +"]";
        _nbrPlayers++;
    }

    void AddNewPersoClone(int i)
    {
        GameObject persoOriginal = GameObject.Find("persoOriginal");
        GameObject Persos = GameObject.Find("Persos");
        Vector3 mult = new Vector3(1.1f, 0, 1.1f);

        GameObject persoClone = Instantiate(persoOriginal, mult, persoOriginal.transform.rotation);
        persoClone.transform.parent = Persos.transform;
        persoClone.name = "Perso [" + i +"]";
    }

    // void createRessourceClonePerTile(int nb)
    // {
    //     GameObject ressourceOriginal = GameObject.Find("Ressource [0]");
    //     GameObject Ressources = GameObject.Find("Ressources");
    //     Vector3 mult = new Vector3(1.1f, 2f, 1.1f);

    //     for (int i = 1; i < nb; i++) {
    //         GameObject ressourceClone = Instantiate(ressourceOriginal, VectorMult(mult, PersoData.PersoList[i].position), ressourceOriginal.transform.rotation);
    //         ressourceClone.transform.parent = Ressources.transform;
    //         ressourceClone.name = "Ressource [" + i +"]";
    //     }
    // }

    void Update()
    {
        if (InfoData.finito == true)
            Application.Quit();

        GameObject Perso;
        string tmp;
        Vector3 mult = new Vector3(1.1f, 1.0f, 1.1f);
        int nbPerso = PersoData.PersoList.Count;

        if (_nbrPlayers != nbPerso)
            createPersoClone(PersoData.PersoList[_nbrPlayers].id);
        for (int i = 0; i < nbPerso; i++) {
            tmp = "Perso [" + PersoData.PersoList[i].id +"]";
            Perso = GameObject.Find(tmp);
            if (Perso == null) {
                continue;
            }
            if (PersoData.PersoList[i].died == 1) {
                Debug.Log("perso mort");
                Perso.SetActive(false);
                Destroy(Perso, 0.0f);
                continue;
            }
            Perso.transform.position = VectorMult(mult, PersoData.PersoList[i].position);
            Perso.transform.eulerAngles = GetOrientation(PersoData.PersoList[i].orientation);
        }
        for (int j = 0; j < MapData.TileList.Count; j++) {
            for (int i = 0; i < MapData.TileList[j].Count; i++) {
                setRessourceActiveOrNot(MapData.TileList[j][i], j, i);
            }
        }
        
    }

    void setRessourceActiveOrNot(TileData tile, int j, int i)
    {
        string toSearch = "Case[" + j +"]" + "[" + i +"]";
        GameObject myTile = GameObject.Find(toSearch);
        int qTabSize = 7;

        for (int k = 0; k < qTabSize; k++) {
            toSearch = "q" + k;
            myTile.transform.Find(toSearch).gameObject.SetActive((tile.qTab[k] != 0));
        }
    }

    Vector3 VectorMult(Vector3 v1, Vector3 v2) {
        return new Vector3(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z);
    }

}