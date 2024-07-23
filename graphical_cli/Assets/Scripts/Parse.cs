using System.Collections;
using System.Collections.Generic;
using System;
using UnityEngine;

public class Parse : MonoBehaviour
{

    private void Start()
    {
        // Execute execute;

        // execute = new Execute();
        // execute.initPersoData();
    }

    public static void InterpretToGame(string data)
    {
        CoreParse(data);
    }

    public static void CoreParse(string arg)
    {
        List<List<String>> array = convert_string(arg);

        for (int i = 0; i < array.Count; i++) {
            if (array[i][0] == "bct")
                bct(array[i]);
            if (array[i][0] == "msz")
                Mapnb(array[i]);
            if (array[i][0] == "plv")
                plv(array[i]);
            if (array[i][0] == "pin")
                pin(array[i]);
            if (array[i][0] == "pdi")
                pid(array[i]);
            if (array[i][0] == "ppm")
                ppm(array[i]);
            if (array[i][0] == "seg")
                Int16.Parse(array[i][1]);
            if (array[i][0] == "pnw")
                NewPlayer(array[i]);
        }
    }

    private static void NewPlayer(List<String> str)
    {
        int IndexPlayer = Int16.Parse(str[1]);
        int x = Int16.Parse(str[2]);
        int y = Int16.Parse(str[3]);
        int o = Int16.Parse(str[4]);
        int lvl = Int16.Parse(str[5]);
        string team = str[6];

        Execute execute = new Execute();
        execute.newPerso(IndexPlayer, x, y, o, lvl, team);
    }

    private static void pid(List<String> str)
    {
        int id = Int16.Parse(str[1]);

        Execute execute = new Execute();
        execute.hideCharacter(id);
    }

    private static void ppm(List<String> str) 
    {
        int x = Int16.Parse(str[2]);
        int y = Int16.Parse(str[3]);
        int o = Int16.Parse(str[4]);
        int id = Int16.Parse(str[1]);
        
        Execute execute = new Execute();
        execute.movePerso(id, x, y, o);
    }

    private static void plv(List<String> str) 
    {
        //print("je plv");
        int lvl = Int16.Parse(str[2]);
        int IndexPlayer = Int16.Parse(str[1]);

    }
    
    private static void pin(List<String> str) 
    {
        //print("je pin");
        int IndexPlayer = Int16.Parse(str[1]);
        int[] tab_nb = new int[6];
        int index = 0;
        for (int i = 3; i < str.Count - 1; i++) {
            tab_nb[index] = Int16.Parse(str[i]);
            index += 1;
        }
    }

    private static void Mapnb(List<String> str) 
    {
        Execute execute = new Execute();
        MapData.map_size_x = Int16.Parse(str[1]);
        MapData.map_size_y = Int16.Parse(str[2]);
        execute.initMapData();
    }

    private static void bct(List<String> array)
    {
        //print("je bct");
        int x = Int16.Parse(array[1]);
        int y = Int16.Parse(array[2]);
        int[] tab_nb = new int[7];
        TileData data = new TileData();
        int index = 0;
        for (int i = 3; i < array.Count; i++) {
            tab_nb[index] = Int16.Parse(array[i]);
            index += 1;
        }
        data.qTab = tab_nb;
        MapData.TileList[x][y] = data;
    }

    public static List<List<String>> convert_string(string data)
    {
        string[] tmp = data.Split("\n");
        string[] tmp2;
        int size_j = tmp.Length - 1;
        int size_i = 0;
        int len_tmp = 0;
        List<List<String>> matrix= new List<List<String>>(); //Creates new nested List
    
        for (int i = 0; i < tmp.Length; i++) {
            tmp2 = tmp[i].Split(" ");
            len_tmp = tmp2.Length;
            if (size_i < len_tmp)
                size_i = len_tmp;
        }
        for (int i = 0; i < size_j; i++)
            matrix.Add(new List<String>()); //Adds new sub List
        for (int j = 0; j < size_j; j++) {
            tmp2 = tmp[j].Split(" ");
            size_i = tmp2.Length;
            for (int i = 0; i < size_i; i++) {
                matrix[j].Add(tmp2[i]);
            }
        }
        return matrix;
    }
}