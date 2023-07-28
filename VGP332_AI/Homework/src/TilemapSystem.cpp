#include "TilemapSystem.h"

using namespace AI;

extern const int screenWidth;
extern const int screenHeight;

namespace
{
    inline void UpdateIndex(int& x, int& y)
    {
        x++;
        if (x % 10 == 0)
        {
            x = 0;
            y++;
        }
    }

    inline int ToIndex(int x, int y)
    {
        return x + (y * 10);
    }
}

namespace tms
{
    TilemapManager* TilemapManager::_instance = nullptr;

    TilemapManager::TilemapManager() {}

    TilemapManager* TilemapManager::Get()
    {
        if (_instance == nullptr)
            _instance = new TilemapManager;

        return _instance;
    }

    TilemapManager::~TilemapManager() { delete _instance; }

    void TilemapManager::LoadMapData(std::vector<char>& TileDataVector)
    {
        TileData _tileData = {};

        int x = {};
        int y = {};
        float size = static_cast<float>(TILESIZE); //64

        //Calculate offset to push map to the right
        int offsetX = static_cast<int>(TILESIZE * 6);

        for (char& data : TileDataVector)
        {
            _tileData.SetCollisionBox({ (size * x + 40), (size * y + 40), size, size });

            if (data == '0')
            {
                _tileData.SetIDx(0);
                _tileData.SetIDy(2);
                _tileData.SetPassable(false);
            }
            else if (data == '1')
            {
                _tileData.SetIDx(1);
                _tileData.SetIDy(2);
                _tileData.SetPassable(false);
            }
            else if (data == '2')
            {
                _tileData.SetIDx(2);
                _tileData.SetIDy(2);
                _tileData.SetPassable(false);
            }
            else if (data == '3')
            {
                _tileData.SetIDx(3);
                _tileData.SetIDy(2);
                _tileData.SetPassable(false);
            }
            else if (data == '4')
            {
                _tileData.SetIDx(0);
                _tileData.SetIDy(1);
                _tileData.SetPassable(false);
            }
            else if (data == '5')
            {
                _tileData.SetIDx(1);
                _tileData.SetIDy(1);
                _tileData.SetPassable(false);
            }
            else if (data == '6')
            {
                _tileData.SetIDx(2);
                _tileData.SetIDy(1);
                _tileData.SetPassable(false);
            }
            else if (data == '7')
            {
                _tileData.SetIDx(3);
                _tileData.SetIDy(1);
                _tileData.SetPassable(false);
            }
            else if (data == '9')
            {
                _tileData.SetIDx(4);
                _tileData.SetIDy(0);
                _tileData.SetPassable(false);
            }
            else if (data == 'a')
            {
                _tileData.SetIDx(0);
                _tileData.SetIDy(0);
                _tileData.SetPassable(true);
            }
            else if (data == 'b')
            {
                _tileData.SetIDx(1);
                _tileData.SetIDy(0);
                _tileData.SetPassable(true);
            }
            else if (data == 'c')
            {
                _tileData.SetIDx(2);
                _tileData.SetIDy(0);
                _tileData.SetPassable(true);
            }
            else if (data == 'd')
            {
                _tileData.SetIDx(3);
                _tileData.SetIDy(0);
                _tileData.SetPassable(true);
            }

            float xRec = static_cast<float>(_tileData.GetSize() * _tileData.GetIDx());
            float yRec = static_cast<float>(_tileData.GetSize() * _tileData.GetIDy());

            _tileData.SetTextureSource(Rectangle{ xRec, yRec, _tileData.GetSize(), _tileData.GetSize() });

            map.push_back(_tileData);
            UpdateIndex(x, y);
        }

        auto GetNeighbor = [&](int c, int r) -> AI::GridBasedGraph::Node*
        {
            if (GetTileData(c, r).IsPassable())
            {
                return mGraph.GetNode(c, r);
            }

            return nullptr;
        };

        mGraph.Initialize(tilemapColumns, tilemapRows);
        for (int r = 0; r < tilemapRows; ++r)
        {
            for (int c = 0; c < tilemapColumns; ++c)
            {
                if (GetTileData(c, r).IsPassable() == false)
                    continue;

                GridBasedGraph::Node* node = GetNeighbor(c, r);

                node->neighbors[GridBasedGraph::Direction::North] = GetNeighbor(c, r - 1);
                node->neighbors[GridBasedGraph::Direction::South] = GetNeighbor(c, r + 1);
                node->neighbors[GridBasedGraph::Direction::East] = GetNeighbor(c + 1, r);
                node->neighbors[GridBasedGraph::Direction::West] = GetNeighbor(c - 1, r);

                node->neighbors[GridBasedGraph::Direction::NorthEast] = GetNeighbor(c + 1, r - 1);
                node->neighbors[GridBasedGraph::Direction::NorthWest] = GetNeighbor(c - 1, r - 1);
                node->neighbors[GridBasedGraph::Direction::SouthEast] = GetNeighbor(c + 1, r + 1);
                node->neighbors[GridBasedGraph::Direction::SouthWest] = GetNeighbor(c - 1, r + 1);
            }
        }
    }

    const TileData& TilemapManager::GetTileData(int xCoordinate, int yCoordinate)
    {
        int _index = ToIndex(xCoordinate, yCoordinate);

        return map[_index];
    }

    Vector2 TilemapManager::GetPixelPosition(int x, int y) const
    {
        return
        {
            ((x + 0.5f) * 64) + 40,
            ((y + 0.5f) * 64) + 40
        };
    }

    Path TilemapManager::FindPathBFS(int startX, int startY, int endX, int endY)
    {
        Path path;
        BFS bfs;

        if (bfs.Run(mGraph, startX, startY, endX, endY))
        {
            const auto& closedList = bfs.GetClosedList();
            auto node = closedList.back();

            while (node != nullptr)
            {
                path.push_back(GetPixelPosition(node->column, node->row));
                node = node->parent;
            }

            std::reverse(path.begin(), path.end());
        }

        return path;
    }

    Path TilemapManager::FindPathDFS(int startX, int startY, int endX, int endY)
    {
        Path path;
        DFS dfs;

        if (dfs.Run(mGraph, startX, startY, endX, endY))
        {
            const auto& closedList = dfs.GetClosedList();
            auto node = closedList.back();

            while (node != nullptr)
            {
                path.push_back(GetPixelPosition(node->column, node->row));
                node = node->parent;
            }

            std::reverse(path.begin(), path.end());
        }

        return path;
    }

    Path TilemapManager::FindPathDijkstra(int startX, int startY, int endX, int endY)
    {
        Path path;
        Dijkstra dijkstra;

        auto getCost = [](const GridBasedGraph::Node* node, const GridBasedGraph::Node* neighbor)->float
        {
            // if neighbor >>
            if (node->column != neighbor->column && node->row != neighbor->row)
            {
                return 2.1f;
            }

            return 1.0f;
        };

        if (dijkstra.Run(mGraph, startX, startY, endX, endY, getCost))
        {
            const auto& closedList = dijkstra.GetClosedList();
            auto node = closedList.back();

            while (node != nullptr)
            {
                path.push_back(GetPixelPosition(node->column, node->row));
                node = node->parent;
            }

            std::reverse(path.begin(), path.end());
        }

        return path;
    }

    Path TilemapManager::FindPathAStar(int startX, int startY, int endX, int endY)
    {
        Path path;
        AStar aStar;

        auto getCost = [](const GridBasedGraph::Node* node, const GridBasedGraph::Node* neighbor)->float
        {
            // if neighbor >>
            if (node->column != neighbor->column && node->row != neighbor->row)
            {
                return 1.14f;
            }

            return 1.0f;
        };

        auto getHeuristic = [](const GridBasedGraph::Node* neighbor, const GridBasedGraph::Node* endNode)->float
        {
            float D = 1.0f;
            float dx = abs(neighbor->column - endNode->column);
            float dy = abs(neighbor->row - endNode->row);

            return D * (dx + dy);
        };

        if (aStar.Run(mGraph, startX, startY, endX, endY, getCost, getHeuristic))
        {
            const auto& closedList = aStar.GetClosedList();
            auto node = closedList.back();

            while (node != nullptr)
            {
                path.push_back(GetPixelPosition(node->column, node->row));
                node = node->parent;
            }

            std::reverse(path.begin(), path.end());
        }

        return path;
    }
}