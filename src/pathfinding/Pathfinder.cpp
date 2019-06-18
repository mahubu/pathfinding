#include <pathfinding/Pathfinder.hpp>
#include <pathfinding/helper/CellHelper.hpp>

#include <iostream>

namespace pathfinding
{

	Pathfinder::Pathfinder(const Grid& grid, const Cell& source, const Cell& destination) : grid_(grid), source_(source), destination_(destination) {
		// Initialize the closed list with 'false' values.
		for (unsigned int r = 0; r < grid_.rows; r++) {
			std::vector<bool> closedRow;
			for (unsigned int c = 0; c < grid_.columns; c++) {
				closedRow.push_back(false);
			}
			closedList_.push_back(closedRow);
		}

		// Initialize the open list with the source, implemented as Red-Black Tree.
		openList_.insert(std::make_pair(source_.f, source_));

		// Initialize the open paths with empty cells.
		for (unsigned int r = 0; r < grid_.rows; r++) {
			std::vector<Cell> path;
			for (unsigned int c = 0; c < grid_.columns; c++) {
				Cell cell;
				path.push_back(cell);
			}
			openPaths_.push_back(path);
		}
		openPaths_[source_.row][source_.column] = source_;
	}

	void Pathfinder::find()
	{
		if (!isValid(grid_, source_.row, source_.column) || !isValid(grid_, destination_.row, destination_.column))
		{
			std::cerr << "Source or destination is invalid." << std::endl;
			return;
		}

		if (!isAccessible(grid_, source_.row, source_.column) || !isAccessible(grid_, destination_.row, destination_.column))
		{
			std::cerr << "Source or destination is blocked." << std::endl;
			return;
		}

		if (isDestination(source_.row, source_.column, destination_))
		{
			std::cerr << "Already at destination." << std::endl;
			return;
		}

		bool reached = false;
		while (!openList_.empty())
		{
			std::pair<double, Cell> node = *openList_.begin();
			// Remove the node from the open list.
			openList_.erase(openList_.begin());

			const Cell cell = node.second;

			// Add the node to the closed list.
			closedList_[cell.row][cell.column] = true;

			// Generating the 8 neighbours of this cell.
			reached |= find(-1, 0, cell); // North: i-1, j
			reached |= find(-1, +1, cell);// N-E:   i-1, j+1
			reached |= find(0, +1, cell); // East:  i  , j+1
			reached |= find(1, 1, cell);  // S-E:   i+1, j+1
			reached |= find(1, 0, cell);  // South: i+1, j
			reached |= find(1, -1, cell); // S-W:   i+1, j-1
			reached |= find(0, -1, cell); // West:  i  , j-1
			reached |= find(-1, -1, cell);// N-W:   i-1, j-1
		}

		if (reached)
		{
			// Update destination's previous cell.
			destination_.previousColumn = openPaths_[destination_.row][destination_.column].previousColumn;
			destination_.previousRow = openPaths_[destination_.row][destination_.column].previousRow;
		}
	}

	void Pathfinder::trace()
	{
		if (!(destination_.previousRow == DEFAULT_COORDINATE && destination_.previousColumn == DEFAULT_COORDINATE))
		{
			// Generate the found path backward from the destination.
			std::vector<Cell> path;
			Cell current = destination_;
			while (!(source_.row == current.row && source_.column == current.column))
			{
				const Cell cell = current;
				path.push_back(cell);
				current = openPaths_[cell.previousRow][cell.previousColumn];
			}
			path.push_back(source_);

			// Trace the found path forward.
			std::cout << "Found path:";
			while (!path.empty())
			{
				const Cell cell = path.back();
				path.pop_back();
				std::cout << " -> (" << cell.row << "," << cell.column << ")";
			}
			std::cout << std::endl;
		}
		else
		{
			std::cout << "No found path." << std::endl;
		}
	}

	bool Pathfinder::find(const int relativeRow, const int relativeColumn, const Cell& current)
	{
		const int row = current.row + relativeRow;
		const int column = current.column + relativeColumn;

		if (isValid(grid_, row, column))
		{
			// If the neighbour is the destination.
			if (isDestination(row, column, destination_))
			{
				openPaths_[row][column].previousRow = current.row;
				openPaths_[row][column].previousColumn = current.column;
				return true;
			}
			// If the neighbour is not on the closed list and is accessible. 
			else if (!closedList_[row][column] && isAccessible(grid_, row, column))
			{
				double g = openPaths_[current.row][current.column].g + distance(row, column, current);
				double h = heuristic(row, column, destination_);
				double f = g + h;
				// If the neighbour is not on the open list (its 'f' value is the default one) or its 'f' value is shorter than the registered one in the open list.
				if (openPaths_[row][column].f == DEFAULT_COST || openPaths_[row][column].f > f)
				{
					// Update the neighbour with all needed informations. 
					openPaths_[row][column].row = row;
					openPaths_[row][column].column = column;
					openPaths_[row][column].f = f;
					openPaths_[row][column].g = g;
					openPaths_[row][column].h = h;
					openPaths_[row][column].previousRow = current.row;
					openPaths_[row][column].previousColumn = current.column;

					openList_.insert(std::make_pair(f, openPaths_[row][column]));
				}
			}
		}

		return false;
	}
}