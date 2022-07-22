#include "Block.hpp"

#include <set>

using namespace LidaPath;

Block::Block(std::vector<int> wellNums,
             const XPSHelper& xpsHelper)
{
    std::set<int> xCoords;
    for (auto wellNum : wellNums)
        xCoords.insert(xpsHelper.GetWellCoords(wellNum).first);
    int width = xCoords.size();

    std::set<int> yCoords;
    for (auto wellNum : wellNums)
        yCoords.insert(xpsHelper.GetWellCoords(wellNum).second);
    int height = yCoords.size();

    int minX = INT_MAX;
    for (auto wellNum : wellNums)
        minX = std::min(minX, xpsHelper.GetWellCoords(wellNum).first);

    int minY = INT_MAX;
    for (auto wellNum : wellNums)
        minY = std::min(minY, xpsHelper.GetWellCoords(wellNum).second);

    blockGeometry_.resize(height, std::vector<int>(width, -1));
    for (auto wellNum : wellNums) {
        blockGeometry_[xpsHelper.GetWellCoords(wellNum).second - minY][xpsHelper.GetWellCoords(wellNum).first - minX] = wellNum;
    }
}

const std::vector<std::vector<int>>& Block::GetGeometry() const {
    return blockGeometry_;
}