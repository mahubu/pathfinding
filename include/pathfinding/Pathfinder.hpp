#pragma once

#include <set>
#include <vector>
#include <pathfinding/model/Cell.hpp>
#include <pathfinding/model/Grid.hpp>

namespace pathfinding
{
	/**
	* A path finder.
	**/
	class Pathfinder
	{
	public:
		Pathfinder(const Grid& grid, const Cell& source, const Cell& destination);

		/**
		* Find the path through the grid, from the source to the destination.
		**/
		void find();

		/**
		* Trace the found path, if it exists.
		**/
		void trace();

	private:
		void initialize();
		bool next(const int relativeRow, const int relativeColumn, const Cell& current);

		const Grid grid_;
		Cell source_;
		Cell destination_;
		/*
		* Open list and closed list from Dijkstra Algorithm :
		* - Closed list (closedList_) contains already processed cells.
		* - Open list (openList_ & openPaths_) contains candidate cells to final path.
		*/
		std::vector<std::vector<bool>> closedList_;
		std::set<std::pair<double, Cell>> openList_;
		std::vector<std::vector<Cell>> openPaths_;

	};

}