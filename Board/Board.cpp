#include "Board.hpp"

#include "../BlockGraph/BlockGraph.hpp"
#include "../Snake/Snake.hpp"

#include <fstream>
#include <string>
#include <algorithm>

using namespace LidaPath;

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

    snakeVariations_ = snake.GetSnakeVariations();
}

void Board::WritePaths(int count) {
    system("mkdir paths");

    std::vector<std::pair<int, std::vector<int>*>> simSumPaths;
    for (int i = 0; i < snakePaths_.size(); ++i) {
        int curSimSum = 0;

        std::vector<RArea> days(snakePaths_[i].size() / K_ + 1);

        for (int j = 0; j < snakePaths_[i].size(); ++j)
            days[j / (K_ + (j < snakePaths_[i].size() % K_))] = Merge(days[j / (K_ + (j < snakePaths_[i].size() % K_))], xpsHelper_.GetWellCoat(snakePaths_[i][j]));
        
        for (int j = 1; j < days.size(); ++j)
            curSimSum += IntersectionSize(days[j-1], days[j]);

        simSumPaths.push_back({curSimSum, &snakePaths_[i]});

        std::cout << i << std::endl;
    }

    std::cout << "SimSumPaths OK" << std::endl;

    std::sort(simSumPaths.begin(), simSumPaths.end(), [](std::pair<int, std::vector<int>*> lhs, std::pair<int, std::vector<int>*> rhs) {
        return lhs.first < rhs.first;
    });

    std::cout << "Sort OK" << std::endl;

    for (int i = 0; i < count; ++i) {
        std::ofstream out(std::string() + "paths\\path" + std::to_string(i) + ".txt", std::ios::out);

        for (int j = 0; j < simSumPaths[i].second->size(); ++j)
            out << xpsHelper_.GetOldCoords((*simSumPaths[i].second)[j]).first << " "
                << xpsHelper_.GetOldCoords((*simSumPaths[i].second)[j]).second << " "
                << j / (K_ + (j < snakePaths_[i].size() % K_)) << "\n";

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

const std::vector<std::vector<SnakeType>>& Board::GetSnakeVariations() const {
    return snakeVariations_;
}