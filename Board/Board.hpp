#pragma once

#include "../XPSHelper/XPSHelper.hpp"
#include "../Block/Block.hpp"

#include <vector>

class Board {
public:
	Board(std::vector<int> verticalBounds_, std::vector<int> gorizontalBounds_);

private:
	const XPSHelper& xpsHelper_;

	std::vector<int> verticalBounds_,
					 gorizontalBounds_;
};