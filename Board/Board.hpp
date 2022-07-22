#pragma once

#include "../XPSHelper/XPSHelper.hpp"
#include "../Block/Block.hpp"
#include "../Snake/Snake.hpp"

#include <vector>

namespace LidaPath {
    class Board {
    public:
        Board(std::vector<int> gorizontalBounds, std::vector<int> verticalBounds,
              const XPSHelper& xpsHelper, const int K);

        void WritePaths(int count);

        const std::vector<Block>& GetBlocks() const;
        const std::vector<std::vector<int>>& GetAdjList() const;
        const std::vector<std::vector<int>>& GetPaths() const;
        const std::vector<std::vector<int>>& GetSnakePaths() const;
        const std::vector<std::vector<SnakeType>>& GetSnakeVariations() const;

    private:
        void CreateBlocks();

        const XPSHelper& xpsHelper_;
        const int K_;

        std::vector<int> verticalBounds_,
                         gorizontalBounds_;

        std::vector<Block> blocks_;

        std::vector<std::vector<int>> adjList_;
        std::vector<std::vector<int>> paths_;

        std::vector<std::vector<int>> snakePaths_;

        std::vector<std::vector<SnakeType>> snakeVariations_;
    };
}