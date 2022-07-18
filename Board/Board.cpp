#include "Board.hpp"

Board::Board(std::vector<int> gorizontalBounds, std::vector<int> verticalBounds,
			 const XPSHelper& xpsHelper) :
	xpsHelper_(xpsHelper)	
{
	gorizontalBounds_ = gorizontalBounds;
	verticalBounds_   = verticalBounds;
}