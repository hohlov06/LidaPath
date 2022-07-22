#include "PathHelper.hpp"

void PathHelper::AddPaths(const std::vector<std::vector<int>>& newPaths) {
	for (int i = 0; i < newPaths.size(); ++i)
		paths_.push_back(newPaths[i]);
}

PathHelper::PathHelper(const XPSHelper& xpsHelper) :
	xpsHelper_(xpsHelper)
{}

std::vector<std::vector<std::pair<int, int>>> PathHelper::CreateXPSPaths() {
	std::vector<std::vector<std::pair<int, int>>> ret;

	for (int i = 0; i < paths_.size(); ++i) {
		std::vector<std::pair<int, int>> toAdd;
		for (int j = 0; j < paths_[i].size(); ++j) {
			toAdd.push_back(xpsHelper_.GetOldCoords(paths_[i][j]));
		}

		ret.push_back(toAdd);
	}

	return ret;
}