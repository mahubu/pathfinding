#include <pathfinding/Pathfinder.hpp>
#include <pathfinding/model/Cell.hpp>
#include <pathfinding/model/Grid.hpp>

#include <iostream>

int main()
{
	std::cout << "Pathfinding." << std::endl;

	std::vector<std::vector<int>> cells =
	{
		{ 1, 0, 1, 1, 1, 1, 0, 1, 1, 1 },
		{ 1, 1, 1, 0, 1, 1, 1, 0, 1, 1 },
		{ 1, 1, 1, 0, 1, 1, 0, 1, 0, 1 },
		{ 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 },
		{ 1, 1, 1, 0, 1, 1, 1, 0, 1, 0 },
		{ 1, 0, 1, 1, 1, 1, 0, 1, 0, 0 },
		{ 1, 0, 0, 0, 0, 1, 0, 0, 0, 1 },
		{ 1, 0, 1, 1, 1, 1, 0, 1, 1, 1 },
		{ 1, 1, 1, 0, 0, 0, 1, 0, 0, 1 }
	};

	pathfinding::Grid grid;
	grid.cells = cells;
	grid.rows = cells.size();
	grid.columns = cells[cells.size() - 1].size();

	pathfinding::Cell source;
	source.row = 8;
	source.column = 0;
	source.g = 0.0;
	source.h = 0.0;
	source.f = 0.0;

	pathfinding::Cell destination;
	destination.row = 0;
	destination.column = 0;

	pathfinding::Pathfinder pathfinder(grid, source, destination);
	pathfinder.find();
	pathfinder.trace();
}
