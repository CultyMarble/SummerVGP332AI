#pragma once
#include "pch.h"
#include "raylib.h"

#include "SystemManager.h"
#include "DrawManager.h"

extern const int screenWidth = 720;
extern const int screenHeight = 720;

int startX = 1;
int startY = 1;

int main(void)
{
    /*==================================================================================
        INITIALIZATION
    ==================================================================================*/
    // Window & Devices
    InitWindow(screenWidth, screenHeight, "VGP332 - AI");
    SetTargetFPS(144);

    /*==================================================================================
        LOAD RESOURCES
    ==================================================================================*/
    // Texture
    Texture2D Texture_Atlas = LoadTexture("resources/link_master_atlas.png");

    // Map
    assert(LoadResource::LoadVectorToMap("map.txt"));

    /*==================================================================================
        GAME OBJECT
    ==================================================================================*/

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        /*==================================================================================
            UPDATE GAME FRAME
        ==================================================================================*/
        if (IsKeyDown(KEY_ONE))
        {
            path = TilemapManager::Get()->FindPathBFS(startX, startY, 5, 5);
        }

        if (IsKeyDown(KEY_TWO))
        {
            path = TilemapManager::Get()->FindPathBFS(startX, startY, 8, 8);
        }

        if (IsKeyDown(KEY_THREE))
        {
            path = TilemapManager::Get()->FindPathDFS(startX, startY, 5, 5);
        }

        if (IsKeyDown(KEY_FOUR))
        {
            path = TilemapManager::Get()->FindPathDFS(startX, startY, 8, 8);
        }

        //if (IsKeyDown(KEY_FIVE))
        //{
        //    path = TilemapManager::Get()->FindPathDijkstra(startX, startY, 8, 8);
        //}

        //if (IsKeyDown(KEY_SEVEN))
        //{
        //    path = TilemapManager::Get()->FindPathAStar(startX, startY, 5, 5);
        //}

        /*==================================================================================
            UPDATE DRAW FRAME
        ==================================================================================*/
        BeginDrawing();
        ClearBackground(BLACK);

        draw::TileMap(Texture_Atlas);

        EndDrawing();
    }

    // De-Initialization
    UnloadTexture(Texture_Atlas);
    CloseWindow();

    return EXIT_SUCCESS;
}