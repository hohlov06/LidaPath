#pragma once

#include "../Block/Block.hpp"
#include "../XPSHelper/XPSHelper.hpp"

#include <vector>

namespace LidaPath {
    class BlockGraph {
    public:
        BlockGraph(const std::vector<Block>& blocks, const XPSHelper& xpsHelper);
        std::vector<std::vector<int>> GetAllPaths(int startBlockNum) const;

        const std::vector<std::vector<int>>& GetAdjList() const;
        const XPSHelper& GetXPSHelper() const;
        const std::vector<Block>& GetBlocks() const;

    private:

        void dfs(int v, std::vector<std::vector<int>>& res, std::vector<bool>& used, std::vector<int>& cur) const;

        bool IsEdge(int lhs, int rhs) const;

        std::vector<std::vector<int>> adjList_;

        const XPSHelper& xpsHelper_;
        const std::vector<Block>& blocks_; 
    };
}