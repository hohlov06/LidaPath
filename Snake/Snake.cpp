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
	int startWellNum = -1;

	if (lastWellNum == -1) {
		for (int i = 0; i < geom.size(); ++i) {
			if (startWellNum != -1)
				break;

			for (int j = 0; j < geom[i].size(); ++j)
				if (geom[i][j] != -1) {
					startWellNum = geom[i][j];
					break;
				}
		}
	} else {
		for (int i = 0; i < geom.size(); ++i)
			for (int j = 0; j < geom[i].size(); ++j) {
				if (geom[i][j] == -1)
					continue;

				if (xpsHelper_.IsNeighbours(geom[i][j], lastWellNum))
					startWellNum = geom[i][j];
			}

		if (startWellNum == -1) {
			for (int i = 0; i < geom.size(); ++i)
				for (int j = 0; j < geom[i].size(); ++j) {
					if (geom[i][j] == -1)
						continue;

					if (xpsHelper_.GetWellCoords(geom[i][j]).first == xpsHelper_.GetWellCoords(lastWellNum).first || 
						xpsHelper_.GetWellCoords(geom[i][j]).second == xpsHelper_.GetWellCoords(lastWellNum).second)
					{
						startWellNum = geom[i][j];
					}
				}
		}
	}

	if (startWellNum == -1)
		return -1;

	int x = -1,
		y = -1;

	for (int i = 0; i < geom.size(); ++i)
		for (int j = 0; j < geom[i].size(); ++j)
			if (geom[i][j] == startWellNum) {
				x = j;
				y = i;
			}

	std::vector<std::pair<int, int>> verticalDirs   = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
	std::vector<std::pair<int, int>> gorizontalDirs = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}}; 

	std::vector<std::pair<int, int>> dirs;

	if (snakeType == SnakeType::VERTICAL) {
		dirs = verticalDirs;
	} else {
		dirs = gorizontalDirs;
	}

	auto canGo = [&](std::pair<int, int> well, std::pair<int, int> d) {
		if (well.first + d.first >= geom.size() || well.first + d.first < 0)
			return false;

		if (well.second + d.second >= geom[0].size() || well.second + d.second < 0)
			return false;

		if (geom[well.first + d.first][well.second + d.second] == -1)
			return false;

		return true;
	};

	std::set<int> snaked;

	int last = startWellNum;
	do {
		res.push_back(last);
		snaked.insert(last);

		bool isNext = false;
		for (auto dir : dirs) {
			if (canGo(std::make_pair(y, x), dir) && 
				!snaked.count(geom[y + dir.first][x + dir.second]))
			{
				isNext = true;
				y += dir.first;
				x += dir.second;
				break;
			}
		}

		if (isNext)
			last = geom[y][x];
		else
			break;

	} while (true);

	return last;
}