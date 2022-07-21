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

			Angle curAngle = Angle::LEFT_UP;

			for (int k = 0; k < blocks_.size(); ++k) {
				Angle after = SnakeRunBlock(res, blocks_[paths_[i][k]], snakeVariations_[j][k], curAngle);

				if (k + 1 < blocks_.size()) {
					int curBlockNum   = paths_[i][k];
					int nextBlockNum  = paths_[i][k + 1];

					if (nextBlockNum == curBlockNum + 1) {

						if (after == Angle::LEFT_UP || after == Angle::RIGHT_UP)
							curAngle = Angle::LEFT_UP;
						else
							curAngle = Angle::LEFT_DOWN;

					} else if (nextBlockNum == curBlockNum - 1) {

						if (after == Angle::LEFT_UP || after == Angle::RIGHT_UP)
							curAngle = Angle::RIGHT_UP;
						else
							curAngle = Angle::RIGHT_DOWN;

					} else if (nextBlockNum > curBlockNum) {
						if (after == Angle::LEFT_UP || after == Angle::LEFT_DOWN)
							curAngle = Angle::LEFT_UP;
						else
							curAngle = Angle::RIGHT_UP;
					} else if (nextBlockNum < curBlockNum) {
						if (after == Angle::LEFT_UP || after == Angle::LEFT_DOWN)
							curAngle = Angle::LEFT_DOWN;
						else
							curAngle = Angle::RIGHT_DOWN;
					}
				}
			}

			ret.push_back(res);
		}
	}

	return ret;
}

Angle Snake::SnakeRunBlock(std::vector<int>& res, const Block& block, SnakeType snakeType, 
						   Angle start)
{
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

	int x = 0,
		y = 0;

	switch(start) {
		case Angle::LEFT_UP:
			x = 0;
			y = 0;
			break;

		case Angle::LEFT_DOWN:
			y = geom.size() - 1;
			x = 0;
			break;

		case Angle::RIGHT_UP:
			x = geom.front().size() - 1;
			y = 0;
			break;

		case Angle::RIGHT_DOWN:
			x = geom.front().size() - 1;
			y = geom.size() - 1;
			break;
	}

	while (true) {
		if (geom[y][x] != -1)
			res.push_back(geom[y][x]);
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

	if (x == 0 && y == 0)
		return Angle::LEFT_UP;
	else if (x == 0 && y == geom.size()-1)
		return Angle::LEFT_DOWN;
	else if (x == geom.front().size()-1 && y == 0)
		return Angle::RIGHT_UP;

	return Angle::RIGHT_DOWN;
}