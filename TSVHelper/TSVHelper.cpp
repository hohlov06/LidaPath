#include "TSVHelper.hpp"

using namespace LidaPath;

TSVHelper::TSVHelper(const XPSHelper& xpsHelper, int K) :
	xpsHelper_(xpsHelper),
	K_(K)
{}

void TSVHelper::AddBoard(const Board& board, int verticalBoundsCount, int gorizontalBoundsCount) {
	for (int i = 0; i < board.GetPaths().size(); ++i) {
		for (int j = 0; j < board.GetSnakeVariations().size(); ++j) {
			blockPaths_.push_back(board.GetPaths()[i]);
			paths_.push_back(board.GetSnakePaths()[i * board.GetPaths().size() + j]);
			snakeVariations_.push_back(board.GetSnakeVariations()[j]);
			verticalBoundsCount_.push_back(verticalBoundsCount);
			gorizontalBoundsCount_.push_back(gorizontalBoundsCount);

			int curSimSum = 0;
			std::vector<RArea> days(paths_.back().size() / K_ + 1);

			for (int k = 0; k < paths_.back().size(); ++k)
				days[k / (K_ + (k < paths_.back().size() % K_))] = Merge(days[k / (K_ + (k < paths_.back().size() % K_))], xpsHelper_.GetWellCoat(paths_.back()[k]));

			for (int k = 1; k < days.size(); ++k)
				curSimSum += IntersectionSize(days[k-1], days[k]);
			simSums_.push_back(curSimSum);
		}
	}

	std::cout << board.GetPaths().size() << " OK" << std::endl;
}

void TSVHelper::WriteTSV(std::ofstream& out) {
	out << "PathNumber\t" << "K\t" << "Vertical Bounds Count\t" << "Gorizontal Bounds Count\t" << "Block Path\t" << "Snake Variant\t" << "Perekldka\n";

	std::cout << blockPaths_.size() << std::endl;

	for (int i = 0; i < blockPaths_.size(); ++i) {
		out << i << "\t";

		out << K_ << "\t";

		out << verticalBoundsCount_[i] << "\t";

		out << gorizontalBoundsCount_[i] << "\t";

		for (int j = 0; j < blockPaths_[i].size(); ++j)
			out << blockPaths_[i][j];
		out << "\t";

		for (int j = 0; j < snakeVariations_[i].size(); ++j)
			out << (bool)snakeVariations_[i][j];
		out << "\t";

		out << simSums_[i] << "\n";
	}
}