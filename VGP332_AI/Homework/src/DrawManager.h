#include "pch.h"
#include "raylib.h"

#include "TilemapSystem.h"

using namespace tms;

Path path;

namespace draw
{
    void TileMap(const Texture2D& Texture_Atlas)
    {
        // Get map data
        const auto& map = TilemapManager::Get()->GetMap();

        // Get tile size data
        const float& tileSize = map[0].GetSize();

        // Draw each tile
        for (auto& tile : map)
        {
            float xRec = static_cast<float>(tileSize * tile.GetIDx());
            float yRec = static_cast<float>(tileSize * tile.GetIDy());

            DrawTextureRec(Texture_Atlas, tile.GetTextureSource(), tile.GetCollisionBoxPosition(), WHITE);
        }

        // Draw line between tile and its neighbor
        for (int r = 0; r < 10; ++r)
        {
            for (int c = 0; c < 10; ++c)
            {
                const auto node = TilemapManager::Get()->GetTilemapGraph().GetNode(c, r);
                for (const auto neighbor : node->neighbors)
                {
                    if (neighbor == nullptr)
                        continue;

                    const auto a = TilemapManager::Get()->GetPixelPosition(node->column, node->row);
                    const auto b = TilemapManager::Get()->GetPixelPosition(neighbor->column, neighbor->row);

                    DrawLineV(a, b, RED);
                }
            }
        }

        // Draw line between tile and its search parent
        for (int r = 0; r < 10; ++r)
        {
            for (int c = 0; c < 10; ++c)
            {
                const auto node = TilemapManager::Get()->GetTilemapGraph().GetNode(c, r);
                if (node->parent != nullptr)
                {
                    const auto a = TilemapManager::Get()->GetPixelPosition(node->column, node->row);
                    const auto b = TilemapManager::Get()->GetPixelPosition(node->parent->column, node->parent->row);

                    DrawLineV(a, b, YELLOW);
                }
            }
        }

        // Draw line to show path
        if (path.size() == 0)
            return;

        for (int i = 1; i < path.size(); ++i)
        {
            DrawLineV(path[i - 1], path[i], GREEN);
        }
    }
}