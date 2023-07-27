#pragma once

namespace AI
{
    class GridBasedGraph
    {
    public:
        enum Direction : int
        {
            North,
            South,
            East,
            West,
            NorthEast,
            NorthWest,
            SouthEast,
            SouthWest,
        };

        struct Node
        {
            std::array<Node*, 8> neighbors = {};

            int column = {};
            int row = {};

            // search parameters
            Node* parent = nullptr;
            bool opened = false;
            bool closed = false;

            float cost = 0.0f;
            float heuristic = 0.0f;

            void Reset()
            {
                parent = nullptr;
                opened = false;
                closed = false;

                cost = 0.0f;
                heuristic = 0.0f;
            }
        };

        void Initialize(int column, int row);

        void ResetSearchParameter();

        Node* GetNode(int x, int y);
        const Node* GetNode(int x, int y) const;

        int GetGridColumns() const { return gridColumns; }
        int GetGridRows() const { return gridRows; }

    private:
        std::vector<GridBasedGraph::Node> gridNodes;

        int gridColumns = {};
        int gridRows = {};

        int GetIndex(int x, int y) const;
    };
}