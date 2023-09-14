#pragma once
#include "raylib.h"
#include "AI.h"

#include "SCV.h"


int main(void)
{
    /*==================================================================================
        INITIALIZATION
    ==================================================================================*/
    // Window & Devices
    const int screenWidth = 860;
    const int screenHeight = 200;

    InitWindow(screenWidth, screenHeight, "VGP332 - AI");
    SetTargetFPS(144);

    /*==================================================================================
        LOAD RESOURCES
    ==================================================================================*/

    /*==================================================================================
        GAME OBJECT
    ==================================================================================*/
    SCV testSCV;

    /*==================================================================================
        GAME INIT
    ==================================================================================*/
    testSCV.Initialize();

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        /*==================================================================================
            UPDATE GAME FRAME
        ==================================================================================*/
        if (IsKeyPressed(KEY_SPACE))
        {
            testSCV.Update();
        }

        if (IsKeyPressed(KEY_ENTER))
        {
            testSCV.ToggleIsInDanger();
        }

        /*==================================================================================
            UPDATE DRAW FRAME
        ==================================================================================*/
        BeginDrawing();
        ClearBackground(BLACK);

        DrawText("Note: Please Keep this window active and press space to update the SCV behavior!", 10, 10, 20, RED);
        DrawText("Behaviour Summary:", 10, 30, 20, WHITE);
        DrawText("SCV will continously mine for mineral and contruct building", 30, 50, 20, GRAY);
        DrawText("if there are at least 200 mineral in command center.", 30, 70, 20, GRAY);
        DrawText("Press Enter to Toggle In Danger Mode", 30, 90, 20, GRAY);
        DrawText("While In Danger: SCV will drop all tasks and run away forever!", 30, 110, 20, GRAY);
        DrawText("When out of Danger Mode: SCV will continuous the prior task which it dropped!", 30, 130, 20, GRAY);
        DrawText("All Behaviour is output in window console. Please read carefully!!!", 30, 150, 20, GRAY);

        EndDrawing();
    }

    /*==================================================================================
        DE-INITIALIZATION
    ==================================================================================*/
    testSCV.Terminate();

    CloseWindow();
    return EXIT_SUCCESS;
}