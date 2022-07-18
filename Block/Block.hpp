#pragma once

#include "../XPSHelper/XPSHelper.hpp"

#include <vector>

class Block {
public:
	Block(std::vector<int> wellNums,
		  const XPSHelper& xpsHelper_);

	Block() = default;

	const std::vector<std::vector<int>>& GetGeometry() const;
private:
	std::vector<std::vector<int>> blockGeometry_;
};