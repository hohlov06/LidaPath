#include "Block.hpp"

#include <set>

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

	blockGeometry_.resize(height, std::vector<int>(width));
	for (auto wellNum : wellNums)
		blockGeometry_[xpsHelper.GetWellCoords(wellNum).first - minX][xpsHelper.GetWellCoords(wellNum).second - minY] = wellNum;
}