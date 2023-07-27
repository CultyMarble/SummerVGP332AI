#pragma once
#include "pch.h"
#include "raylib.h"

#include "AI.h"

using Path = std::vector<Vector2>;

namespace tms
{
    struct TileData
    {
    public:
        Rectangle GetCollisionBox() const { return collisionBox; }
        Vector2 GetCollisionBoxPosition() const { return { collisionBox.x, collisionBox.y }; }
        void SetCollisionBox(Rectangle newCollision) { collisionBox = newCollision; }

        float GetSize() const { return SIZE; }

        int GetIDx() const { return textureIDx; }
        void SetIDx(int newID) { textureIDx = newID; }

        int GetIDy() const { return textureIDy; }
        void SetIDy(int newID) { textureIDy = newID; }

        Rectangle GetTextureSource() const { return textureSource; }
        void SetTextureSource(Rectangle newSource) { textureSource = newSource; }

        bool IsPassable() const { return isPassable; }
        void SetPassable(const bool newBool) { isPassable = newBool; }

    private:
        Rectangle collisionBox = {};
        const float SIZE = 64.0f;

        int textureIDx = {};
        int textureIDy = {};
        Rectangle textureSource = {};

        bool isPassable = {};
    };

    class TilemapManager
    {
    public:
        static TilemapManager* Get();
        virtual ~TilemapManager();

        void LoadMapData(std::vector<char>& TileMapList);
        std::vector<TileData> GetMap() const { return map; };

        const TileData& GetTileData(int xCoordinate, int yCoordinate);

        int GetColumns() const { return tilemapColumns; }
        int GetRows() const { return tilemapRows; }

        // AI add-ons
        const AI::GridBasedGraph& GetTilemapGraph() { return mGraph; }

        Vector2 GetPixelPosition(int x, int y) const;

        Path FindPathBFS(int startX, int startY, int endX, int endY);
        Path FindPathDFS(int startX, int startY, int endX, int endY);
        Path FindPathDijkstra(int startX, int startY, int endX, int endY);
        Path FindPathAStar(int startX, int startY, int endX, int endY);

    private:
        TilemapManager();
        static TilemapManager* _instance;

        static const int MAPSIZE = 100;
        static const int TILESIZE = 64;

        int tilemapColumns = 10;
        int tilemapRows = 10;

        std::vector<TileData> map = {};

        // AI add-ons
        AI::GridBasedGraph mGraph = {};
    };
}