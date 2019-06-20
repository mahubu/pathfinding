#pragma once

#include <array>
#include <pathfinding/model/Cell.hpp>
#include <pathfinding/model/Grid.hpp>

namespace pathfinding
{

	/**
	* Check whether given cell (row, column) is valid or not into a given grid.
	*
	* @param grid the grid.
	* @param row the cell row.
	* @param column the cell column.
	*
	* @return whether (or not) the cell is valid.
	**/
	inline bool isValid(const Grid& grid, int row, int column)
	{
		return row >= 0 && (unsigned)row < grid.rows && column >= 0 && (unsigned)column < grid.columns;
	}

	/**
	* Check whether given cell (row, column) is blocked or not into a given grid.
	*
	* @param grid the grid.
	* @param row the cell row.
	* @param column the cell column.
	*
	* @return whether (or not) the cell is blocked.
	**/
	inline bool isAccessible(const Grid& grid, int row, int column)
	{
		return grid.cells[row][column];
	}

	/**
	* Check whether the destination has been reached or not, given a cell (row, column).
	*
	* @param row the cell row.
	* @param column the cell column.
	* @param destination the destination.
	*
	* @return whether (or not) the destination has been reached.
	**/
	inline bool isDestination(int row, int column, const Cell& destination)
	{
		return row == destination.row && column == destination.column;
	}

	/**
	* Calculate the Chebyshev (aka 'chessboard') distance from a cell (row, column) to a targeted cell.
	*
	* @param row the cell row.
	* @param column the cell column.
	* @param target the target.
	*
	* @return the euclidean distance.
	**/
	inline double distance(int row, int column, const Cell& target)
	{
		int dr = abs(row - target.row);
		int dc = abs(column - target.column);
		return (double)(dr + dc - std::min(dr, dc));
	}

	/**
	* Calculate the heuristic from a cell (row, column) to a destination.
	*
	* @param row the cell row.
	* @param column the cell column.
	* @param destination the destination.
	*
	* @return the heuristic.
	**/
	inline double heuristic(int row, int column, const Cell& destination)
	{
		// Chebyshev distance is used in this example.
		return distance(row, column, destination);
	}

}