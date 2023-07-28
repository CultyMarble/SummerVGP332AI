#pragma once
#include "pch.h"
#include "raylib.h"

#include "SystemManager.h"
#include "DrawManager.h"

extern const int screenWidth = 720;
extern const int screenHeight = 720;

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

    // Testing Nodes
    int startX = 1;
    int startY = 1;
    int endX = 2;
    int endY = 2;

    /*==================================================================================
        GAME OBJECT
    ==================================================================================*/

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        /*==================================================================================
            UPDATE GAME FRAME
        ==================================================================================*/
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            int x = GetMousePosition().x;
            int y = GetMousePosition().y;

            std::cout << GetMousePosition().x << " " << GetMousePosition().y << std::endl;

            auto node = TilemapManager::Get()->GetClosestNode(x, y);
            if (node != nullptr)
            {
                startX = node->column;
                startY = node->row;
            }
        }
        
        if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
        {
            int x = GetMousePosition().x;
            int y = GetMousePosition().y;

            std::cout << GetMousePosition().x << " " << GetMousePosition().y << std::endl;

            auto node = TilemapManager::Get()->GetClosestNode(x, y);
            if (node != nullptr)
            {
                endX = node->column;
                endY = node->row;
            }

            std::cout << endX << " " << endY << std::endl;
        }

        if (IsKeyPressed(KEY_ONE))
        {
            path = TilemapManager::Get()->FindPathBFS(startX, startY, endX, endY);
        }

        if (IsKeyPressed(KEY_TWO))
        {
            path = TilemapManager::Get()->FindPathDFS(startX, startY, endX, endY);
        }

        if (IsKeyPressed(KEY_THREE))
        {
            path = TilemapManager::Get()->FindPathDijkstra(startX, startY, endX, endY);
        }

        if (IsKeyPressed(KEY_FOUR))
        {
            path = TilemapManager::Get()->FindPathAStar(startX, startY, endX, endY);
        }

        /*==================================================================================
            UPDATE DRAW FRAME
        ==================================================================================*/
        BeginDrawing();
        ClearBackground(BLACK);

        DrawText("KEY 1: BSF | KEY 2: DFS | KEY 3: Dijkstra | KEY 4: AStar", 10, 10, 20, PINK);

        draw::TileMap(Texture_Atlas);

        // Draw startpoint and endpoint
        DrawCircleLines((startX * 64.0f) + 72.0f, (startY * 64.0f) + 72.0f, 10, LIME);
        DrawCircleLines((endX * 64.0f) + 72.0f, (endY * 64.0f) + 72.0f, 10, ORANGE);

        EndDrawing();
    }

    // De-Initialization
    UnloadTexture(Texture_Atlas);
    CloseWindow();

    return EXIT_SUCCESS;
}