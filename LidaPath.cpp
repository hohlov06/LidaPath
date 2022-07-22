#include "LidaPath.hpp"


std::vector<std::vector<std::pair<int, int>>> LidaPath::CreateXPSPaths(const std::string& xpsFilePath,
                                                             		   int maxVerticalBounds, int maxGorizontalBounds)
{
    XPSHelper xpsHelper(xpsFilePath.c_str());
    const int K = 1;

    PathHelper pathHelper(xpsHelper);
    int verticalBoundsCountMax = maxVerticalBounds;
    int gorizontalBoundsCountMax = maxGorizontalBounds;

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
        }
    }

    auto resPaths = pathHelper.CreateXPSPaths();
    return resPaths;
}