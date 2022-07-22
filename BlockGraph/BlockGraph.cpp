#include "BlockGraph.hpp"

using namespace LidaPath;

BlockGraph::BlockGraph(const std::vector<Block>& blocks, const XPSHelper& xpsHelper) :
    blocks_(blocks),
    xpsHelper_(xpsHelper)
{
    adjList_.resize(blocks_.size());

    for (int i = 0; i < blocks_.size(); ++i)
        for (int j = 0; j < blocks_.size(); ++j) {
            if (i == j)
                continue;

            if (IsEdge(i, j))
                adjList_[i].push_back(j);
        }
}

bool BlockGraph::IsEdge(int lhs, int rhs) const {
    auto lhsGeom = blocks_[lhs].GetGeometry();
    auto rhsGeom = blocks_[rhs].GetGeometry();

    for (int i1 = 0; i1 < lhsGeom.size(); ++i1)
        for (int j1 = 0; j1 < lhsGeom[i1].size(); ++j1)
            for (int i2 = 0; i2 < rhsGeom.size(); ++i2)
                for (int j2 = 0; j2 < rhsGeom[i2].size(); ++j2) {
                    if (lhsGeom[i1][j1] == -1 || rhsGeom[i2][j2] == -1)
                        continue;

                    if (xpsHelper_.IsNeighbours(lhsGeom[i1][j1], rhsGeom[i2][j2]))
                        return true;
                }

    return false;
}

const std::vector<std::vector<int>>& BlockGraph::GetAdjList() const {
    return adjList_;
}

const XPSHelper& BlockGraph::GetXPSHelper() const {
    return xpsHelper_;
}

const std::vector<Block>& BlockGraph::GetBlocks() const {
    return blocks_;
}

void BlockGraph::dfs(int v, std::vector<std::vector<int>>& res, std::vector<bool>& used, std::vector<int>& cur) const {
    used[v] = true;
    cur.push_back(v);

    bool isEnd = true;
    for (int to : adjList_[v]) {
        if (used[to])
            continue;

        isEnd = false;
        dfs(to, res, used, cur);
    }

    if (isEnd && cur.size() == adjList_.size())
        res.push_back(cur);

    used[v] = false;
    cur.pop_back();
}

std::vector<std::vector<int>> BlockGraph::GetAllPaths(int startBlockNum) const {
    std::vector<std::vector<int>> ret;
    std::vector<bool> used(adjList_.size(), false);
    std::vector<int> cur;

    dfs(startBlockNum, ret, used, cur);

    return ret;
}