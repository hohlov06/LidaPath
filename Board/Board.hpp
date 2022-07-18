#pragma once

#include "../XPSHelper/XPSHelper.hpp"
#include "../Block/Block.hpp"

#include <vector>

class Board {
public:
	Board(std::vector<int> gorizontalBounds, std::vector<int> verticalBounds,
		  const XPSHelper& xpsHelper);

	const std::vector<Block>& GetBlocks() const;

private:
	void CreateBlocks();

	const XPSHelper& xpsHelper_;

	std::vector<int> verticalBounds_,
					 gorizontalBounds_;

	std::vector<Block> blocks_;
};