#include "XPSHelper/XPSHelper.hpp"
#include "Board/Board.hpp"

#include <iostream>

int main(int argc, char* argv[]) {
	XPSHelper xpsHelper(argv[1]);

	const int K = std::stoi(argv[2]);
	int verticalBoundsCount = std::stoi(argv[3]);
	int gorizontalBoundsCount = std::stoi(argv[4]);

	std::vector<int> verticalBounds,
					 gorizontalBounds;

	int xpsWidth  = xpsHelper.GetXPSWidth(),
		xpsHeight = xpsHelper.GetXPSHeight();

	std::cout << xpsWidth << " " << xpsHeight << std::endl;

	int dBlockVertical   = xpsHeight / (gorizontalBoundsCount + 1);
	int dBlockGorizontal = xpsWidth  / (verticalBoundsCount   + 1);

	int curBoundVertical = dBlockGorizontal;
	do {
		verticalBounds.push_back(curBoundVertical);
		curBoundVertical += dBlockGorizontal;
	} while (curBoundVertical <= xpsWidth);
	verticalBounds.pop_back();
	verticalBounds.push_back(xpsWidth);

	int curBoundGorizontal = dBlockVertical;
	do {
		gorizontalBounds.push_back(curBoundGorizontal);
		curBoundGorizontal += dBlockVertical;
	} while (curBoundGorizontal <= xpsHeight);
	gorizontalBounds.pop_back();
	gorizontalBounds.push_back(xpsHeight);

	std::cout << "gorizontalBounds" << std::endl;
	for (int i = 0; i < gorizontalBounds.size(); ++i)
		std::cout << gorizontalBounds[i] << " ";

	std::cout << std::endl;
	std::cout << std::endl;

	std::cout << "verticalBounds" << std::endl;
	for (int i = 0; i < verticalBounds.size(); ++i)
		std::cout << verticalBounds[i] << " ";

	std::cout << std::endl;
	std::cout << std::endl;

	Board board(gorizontalBounds, verticalBounds, xpsHelper);

	auto blocks = board.GetBlocks();
	for (int i = 0; i < blocks.size(); ++i) {
		auto geom = blocks[i].GetGeometry();

		for (int j = 0; j < geom.size(); ++j) {
			for (int k = 0; k < geom[j].size(); ++k)
				std::cout << geom[j][k] << " ";
			std::cout << std::endl;
		}

		std::cout << std::endl;
		std::cout << std::endl;
	}

	return 0;
}