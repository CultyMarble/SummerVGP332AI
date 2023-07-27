#include "pch.h"
#include "GridBasedGraph.h"

namespace AI
{
    // Public
    void GridBasedGraph::Initialize(int columns, int rows)
    {
        gridNodes.clear();
        gridNodes.reserve(columns * rows);

        gridColumns = columns;
        gridRows = rows;

        for (int r = 0; r < rows; ++r)
        {
            for (int c = 0; c < columns; ++c)
            {
                auto& node = gridNodes.emplace_back();

                node.column = c;
                node.row = r;
            }
        }
    }

    void GridBasedGraph::ResetSearchParameter()
    {
        for (auto& node : gridNodes)
        {
            node.Reset();
        }
    }

    GridBasedGraph::Node* GridBasedGraph::GetNode(int x, int y)
    {
        if (x >= 0 && x < gridColumns && y >= 0 && y < gridColumns)
        {
            const int _index = GetIndex(x, y);

            if (_index < gridNodes.size())
            {
                return &gridNodes[_index];
            }
        }

        return nullptr;
    }

    const GridBasedGraph::Node* GridBasedGraph::GetNode(int x, int y) const
    {
        if (x >= 0 && x < gridColumns && y >= 0 && y < gridColumns)
        {
            const int _index = GetIndex(x, y);

            if (_index < gridNodes.size())
            {
                return &gridNodes[_index];
            }
        }

        return nullptr;
    }

    // Private
    int GridBasedGraph::GetIndex(int x, int y) const
    {
        return x + (y * 10);
    }
}