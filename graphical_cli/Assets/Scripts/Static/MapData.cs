/*
** EPITECH PROJECT, 2022
** graphical_cli
** File description:
** Map
*/

using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MapData : MonoBehaviour
{
    public static int position;
    
    public static int map_size_x;
    public static int map_size_y;

    public static List<List<TileData>> TileList;
}

public class TileData
{
    public int[] qTab;
}