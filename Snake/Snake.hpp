#pragma once

#include "../XPSHelper/XPSHelper.hpp"
#include "../Block/Block.hpp"

#include <vector>

enum SnakeType {
	VERTICAL,
	GORIZONTAL
};

enum Angle {
	LEFT_UP,
	RIGHT_UP,

	LEFT_DOWN,
	RIGHT_DOWN
};

class Snake {
public:
	Snake(const std::vector<Block>& blocks, const XPSHelper& xpsHelper, const std::vector<std::vector<int>>& paths);

	std::vector<std::vector<int>> GetSnakePaths();

private:
	Angle SnakeRunBlock(std::vector<int>& res, const Block& block, SnakeType snakeType, 
						Angle start);
	std::vector<std::vector<SnakeType>> snakeVariations_;

	const std::vector<Block>& blocks_;
	const XPSHelper xpsHelper_;
	const std::vector<std::vector<int>>& paths_;
};