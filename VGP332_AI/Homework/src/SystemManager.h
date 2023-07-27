#pragma once
#include "pch.h"
#include "raylib.h"

#include "TilemapSystem.h"

#define MOVE_DISTANCE 64

static int moveTimes;

namespace LoadResource
{
    bool LoadtxtToVector(std::string fileName, std::vector<char>& TileDataList)
    {
        char c;

        // Open the File
        std::ifstream in(fileName.c_str());

        // Check if object is valid
        if (!in)
        {
            std::cerr << "Cannot open the File : " << fileName << std::endl;
            return false;
        }

        std::string str;
        // Read the next line from File untill it reaches the end.
        while (in.get(c))
            TileDataList.push_back(c);

        //Close The File
        in.close();

        return true;
    }

    bool LoadVectorToMap(std::string fileName)
    {
        std::vector<char> TileDataList;

        if (LoadResource::LoadtxtToVector(fileName, TileDataList))
        {
            tms::TilemapManager::Get()->LoadMapData(TileDataList);
            return true;
        }

        return false;
    }
}