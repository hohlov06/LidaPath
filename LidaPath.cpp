#include "XPSHelper/XPSHelper.hpp"
#include "Board/Board.hpp"
#include "PathHelper/PathHelper.hpp"

#include <iostream>

int main(int argc, char* argv[]) {
    LidaPath::XPSHelper xpsHelper(argv[1]);

    LidaPath::PathHelper pathHelper(xpsHelper);

    const int K = std::stoi(argv[2]);
    int verticalBoundsCountMax = std::stoi(argv[3]);
    int gorizontalBoundsCountMax = std::stoi(argv[4]);

    for (int verticalBoundsCount = 0; verticalBoundsCount <= verticalBoundsCountMax; ++verticalBoundsCount) {
        for (int gorizontalBoundsCount = 0; gorizontalBoundsCount <= gorizontalBoundsCountMax; ++gorizontalBoundsCount) {
            std::vector<int> verticalBounds,
                             gorizontalBounds;

            int xpsWidth  = xpsHelper.GetXPSWidth(),
                xpsHeight = xpsHelper.GetXPSHeight();

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

            LidaPath::Board board(gorizontalBounds, verticalBounds, xpsHelper, K);
            pathHelper.AddPaths(board.GetSnakePaths());

            std::cout << verticalBoundsCount << " " << gorizontalBoundsCount << " OK" << std::endl;
        }
    }

    auto resPaths = pathHelper.CreateXPSPaths();
    std::cout << "Results paths count: " << resPaths.size() << std::endl;

    return 0;
}