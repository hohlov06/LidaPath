#include "Board.hpp"

Board::Board(std::vector<int> gorizontalBounds, std::vector<int> verticalBounds,
			 const XPSHelper& xpsHelper) :
	xpsHelper_(xpsHelper)
{
	gorizontalBounds_ = gorizontalBounds;
	verticalBounds_   = verticalBounds;

	CreateBlocks();
	BlockGraph graph_(blocks_, xpsHelper_);

	adjList_ = graph_.GetAdjList();
	paths_ = graph_.GetAllPaths(0);
}

void Board::CreateBlocks() {
	blocks_.clear();

	for (int i = 0; i < verticalBounds_.size(); ++i)
		for (int j = 0; j < gorizontalBounds_.size(); ++j) {
			std::vector<int> curBlockWellNums;

			for (int xCoord = (i == 0) ? 0 : verticalBounds_[i-1]; xCoord < verticalBounds_[i]; ++xCoord)
				for (int yCoord = (j == 0) ? 0 : gorizontalBounds_[j-1]; yCoord < gorizontalBounds_[j]; ++yCoord) {
					try {
						curBlockWellNums.push_back(xpsHelper_.GetWellNum(std::make_pair(xCoord, yCoord)));
					} catch(...) {}
				}

			blocks_.push_back(Block(curBlockWellNums, xpsHelper_));
		}
}

const std::vector<Block>& Board::GetBlocks() const {
	return blocks_;
}

const std::vector<std::vector<int>>& Board::GetAdjList() const {
	return adjList_;
}

const std::vector<std::vector<int>>& Board::GetPaths() const {
	return paths_;
}