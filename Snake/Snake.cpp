#include "Snake.hpp"

#include <set>

Snake::Snake(const std::vector<Block>& blocks, const XPSHelper& xpsHelper, const std::vector<std::vector<int>>& paths) :
	xpsHelper_(xpsHelper),
	blocks_(blocks),
	paths_(paths)
{
	for (int mask = 0; mask < (1 << blocks.size()); ++mask) {
		std::vector<SnakeType> snakeVariant;

		for (int blockSnakeType = 1; blockSnakeType < (1 << blocks.size()); blockSnakeType <<= 1) {
			SnakeType curSnakeType = ((blockSnakeType & mask) > 0) ? SnakeType::GORIZONTAL : SnakeType::VERTICAL;
			snakeVariant.push_back(curSnakeType);
		}

		snakeVariations_.push_back(snakeVariant);
	}

	std::cout << "Snake Variations Size: " << snakeVariations_.size() << std::endl;
	std::cout << std::endl;
}

std::vector<std::vector<int>> Snake::GetSnakePaths() {
	std::vector<std::vector<int>> ret;

	for (int i = 0; i < paths_.size(); ++i) {
		for (int j = 0; j < snakeVariations_.size(); ++j) {
			std::vector<int> res;

			int lastWellNum = -1;
			for (int k = 0; k < blocks_.size(); ++k)
				lastWellNum = SnakeRunBlock(res, blocks_[paths_[i][k]], snakeVariations_[j][k], lastWellNum);

			ret.push_back(res);
		}
	}

	return ret;
}

int Snake::SnakeRunBlock(std::vector<int>& res, const Block& block, SnakeType snakeType, int lastWellNum) {
	auto geom = block.GetGeometry();
	std::vector<std::pair<int, int>> verticalDirs   = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
	std::vector<std::pair<int, int>> gorizontalDirs = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}}; 

	std::vector<std::pair<int, int>> dirs;

	if (snakeType == SnakeType::VERTICAL) {
		dirs = verticalDirs;
	} else {
		dirs = gorizontalDirs;
	}

	std::vector<std::vector<bool>> used(geom.size(), std::vector<bool>(geom.front().size(), false));

	auto canGo = [&](std::pair<int, int> coord, std::pair<int, int> d) {
		if (coord.first + d.first < 0 || coord.first + d.first >= geom.size())
			return false;

		if (coord.second + d.second < 0 || coord.second + d.second >= geom.front().size())
			return false;

		return (bool)(!used[coord.first + d.first][coord.second + d.second]);
	};

	std::vector<std::pair<int, int>> startWells = {{0, 0},
												   {geom.size()-1, 0},
												   {0, geom.front().size()-1},
												   {geom.size()-1, geom.front().size()-1}};

	std::vector<std::vector<int>> paths;

	for (auto startWell : startWells) {
		for (int i = 0; i < used.size(); ++i)
			used[i].assign(used[i].size(), false);

		int y = startWell.first,
			x = startWell.second;

		std::vector<int> curPath;
		while (true) {
			if (geom[y][x] != -1)
				curPath.push_back(geom[y][x]);
			used[y][x] = true;

			bool isNext = false;
			for (auto dir : dirs) {
				if (canGo({y, x}, dir)) {
					y += dir.first,
					x += dir.second;
					isNext = true;

					break;
				}
			}

			if (!isNext)
				break;
		}

		paths.push_back(curPath);		
	}

	std::vector<int> selectPath;
	if (lastWellNum == -1)
		selectPath = paths.front();
	else {
		int curSimSum = -1;

		for (int i = 0; i < paths.size(); ++i) {
			if (paths[i].size() > 0 && 
				IntersectionSize(xpsHelper_.GetWellCoat(paths[i].front()), xpsHelper_.GetWellCoat(lastWellNum)) > curSimSum)
			{
				curSimSum = IntersectionSize(xpsHelper_.GetWellCoat(paths[i].front()), xpsHelper_.GetWellCoat(lastWellNum));
				selectPath = paths[i];
			}
		}
	}

	int last = lastWellNum;
	if (selectPath.size() > 0) {
		last = selectPath.back();

		for (auto well : selectPath)
			res.push_back(well);
	}

	return last;
}