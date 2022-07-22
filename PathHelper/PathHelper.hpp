#pragma once

#include "../XPSHelper/XPSHelper.hpp"

#include <vector>

namespace LidaPath {
	class PathHelper {
	public:
		void AddPaths(const std::vector<std::vector<int>>& newPaths);
		PathHelper(const XPSHelper& xpsHelper);

		std::vector<std::vector<std::pair<int, int>>> CreateXPSPaths();
	private:
		std::vector<std::vector<int>> paths_;
		const XPSHelper& xpsHelper_;
	};
}