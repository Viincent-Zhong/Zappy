/*
** EPITECH PROJECT, 2022
** B-YEP-410-PAR-4-1-zappy-pierre-alexandre.delgado-arevalo
** File description:
** PersoData
*/

using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PersoData : MonoBehaviour
{
    public static List<Perso> PersoList;
}

public class Perso
{
    public Vector3 position;
    public int level = 0;
    public int id = 0;
    public int inventory = 0;
    public string team;
    public int orientation = 0;
    public int died = 0;
}
