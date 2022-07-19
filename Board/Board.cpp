#include "Board.hpp"

#include "../BlockGraph/BlockGraph.hpp"
#include "../Snake/Snake.hpp"

#include <fstream>
#include <string>

Board::Board(std::vector<int> gorizontalBounds, std::vector<int> verticalBounds,
			 const XPSHelper& xpsHelper, const int K) :
	xpsHelper_(xpsHelper),
	K_(K)
{
	gorizontalBounds_ = gorizontalBounds;
	verticalBounds_   = verticalBounds;

	CreateBlocks();
	BlockGraph graph_(blocks_, xpsHelper_);

	adjList_ = graph_.GetAdjList();
	paths_ = graph_.GetAllPaths(0);

	Snake snake(blocks_, xpsHelper_, paths_);
	snakePaths_ = snake.GetSnakePaths();
}

void Board::WritePaths() {
	system("mkdir paths");

	for (int i = 0; i < snakePaths_.size(); ++i) {
		std::ofstream out(std::string() + "paths\\path" + std::to_string(i) + ".txt", std::ios::out);

		for (int j = 0; j < snakePaths_[i].size(); ++j) {
			out << xpsHelper_.GetOldCoords(snakePaths_[i][j]).first  << " " 
				<< xpsHelper_.GetOldCoords(snakePaths_[i][j]).second << " " 
				<< j / K_ << "\n";  
		}

		out.close();
	}
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

const std::vector<std::vector<int>>& Board::GetSnakePaths() const {
	return snakePaths_;
}