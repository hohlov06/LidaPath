#include "XPSHelper/XPSHelper.hpp"
#include "Board/Board.hpp"
#include "PathHelper/PathHelper.hpp"

#include <iostream>

namespace LidaPath {
    std::vector<std::vector<std::pair<int, int>>> CreateXPSPaths(const std::string& xpsFilePath,
                                                                 int maxVerticalBounds, int maxGorizontalBounds);
}