#pragma once

#define NOMINMAX // Getting rid of min/max macros.
#include <limits>

namespace pathfinding
{
	static constexpr int DEFAULT_COORDINATE = -1;
	static constexpr double DEFAULT_COST = std::numeric_limits<double>::max();

	/**
	* A cell into the grid.
	**/
	struct Cell
	{
		int row{ DEFAULT_COORDINATE }; // 'row' coordinate of the cell on the grid.
		int column{ DEFAULT_COORDINATE }; // 'column' coordinate of the cell on the grid.
		int previousRow{ DEFAULT_COORDINATE }; // 'row' coordinate of the previous cell in the generated path.
		int previousColumn{ DEFAULT_COORDINATE }; // 'column' coordinate of the previous cell in the generated path.
		double g{ DEFAULT_COST }; // Cost from the source to a given cell on the grid, following the generated path.
		double h{ DEFAULT_COST }; // Estimated cost from that given cell on the grid to the destination. Often referred to as the 'heuristic'.
		double f{ DEFAULT_COST }; // f = g + h 
	};

	inline bool operator<(const Cell& left, const Cell& right) {
		return left.row < right.row || left.row == right.row && left.column < right.column;
	}
}