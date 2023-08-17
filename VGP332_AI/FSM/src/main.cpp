#pragma once
#include <iostream>
#include <stdio.h>

#include "AI.h"

#include "raylib.h"

int main(void)
{
    /*==================================================================================
        INITIALIZATION
    ==================================================================================*/
    // Window & Devices
    const int screenWidth = 720;
    const int screenHeight = 720;

    InitWindow(screenWidth, screenHeight, "VGP332 - AI");
    SetTargetFPS(144);

    /*==================================================================================
        LOAD RESOURCES
    ==================================================================================*/


    /*==================================================================================
        GAME OBJECT
    ==================================================================================*/

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        /*==================================================================================
            UPDATE GAME FRAME
        ==================================================================================*/

        /*==================================================================================
            UPDATE DRAW FRAME
        ==================================================================================*/
        BeginDrawing();
        ClearBackground(GRAY);

        EndDrawing();
    }

    /*==================================================================================
        DE-INITIALIZATION
    ==================================================================================*/


    CloseWindow();
    return EXIT_SUCCESS;
}