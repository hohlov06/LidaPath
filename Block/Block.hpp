#pragma once

#include "../XPSHelper/XPSHelper.hpp"

#include <vector>

class Block {
public:
	Block(std::vector<int> wellNums,
		  const XPSHelper& xpsHelper_);
private:
	std::vector<std::vector<int>> blockGeometry_;
};