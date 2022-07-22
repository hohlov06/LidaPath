#pragma once

#include <vector>
#include <fstream>

#include "../XPSHelper/XPSHelper.hpp"
#include "../Board/Board.hpp"
#include "../Snake/Snake.hpp"
#include "../RArea/RArea.hpp"

namespace LidaPath {
	class TSVHelper {
	public:
		TSVHelper(const XPSHelper& xpsHelper, int K);
		void AddBoard(const Board& board, int verticalBoundsCount, int gorizontalBoundsCount);
		void WriteTSV(std::ofstream& out);

	private:
		const XPSHelper& xpsHelper_;
		const int K_;

		std::vector<std::vector<int>> blockPaths_;
		std::vector<std::vector<int>> paths_;
		std::vector<std::vector<SnakeType>> snakeVariations_;
		std::vector<int> verticalBoundsCount_;
		std::vector<int> gorizontalBoundsCount_;
		std::vector<int> simSums_;
	};
}