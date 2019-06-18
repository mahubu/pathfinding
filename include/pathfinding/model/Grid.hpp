#pragma once

#include <vector>

namespace pathfinding
{
	/**
	* A grid of cells.
	* '0' cells are blocking cells.
	* '1' cells are walkable cells.
	**/
	struct Grid
	{
		std::vector<std::vector<int>> cells{ {0} };
		size_t rows{ 0 };
		size_t columns{ 0 };
	};
}