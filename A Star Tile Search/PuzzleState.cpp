#include "stdafx.h"
#include <iostream>
#include <vector>
#include "PuzzleState.h"

int PuzzleState::getDepth()
{
	return depth;
}
void PuzzleState::setDepth(int d)
{
	depth = d;
}
//Get Manhatan distance to solution
int PuzzleState::getManhatDist(PuzzleState goal)
{
	int dist = 0;
	for (int i = 0; i < (int)tiles.size(); i++)
	{
		for (int j = 0; j < (int)goal.tiles.size(); j++)
		{
			if (tiles[i] == goal.tiles[j])
			{
				dist += getDist(i, j);
			}
		}
	}
	dist += depth;
	return dist;
}

int PuzzleState::getDist(int a, int b)
{
	int arow = a / rows;
	int acol = a % cols;
	int brow = b / rows;
	int bcol = b % cols;
	return std::abs(arow - brow) + std::abs(acol - bcol);
}

bool PuzzleState::operator==(const PuzzleState & rhs) const
{
	for (int i = 0; i < (int)tiles.size(); i++)
	{
		if (tiles[i] != rhs.tiles[i])
			return false;
	}
	return true;
}
bool PuzzleState::operator!=(const PuzzleState & rhs) const
{
	for (int i = 0; i < (int)tiles.size(); i++)
	{
		if (tiles[i] != rhs.tiles[i])
			return true;
	}
	return false;
}
const PuzzleState & PuzzleState::operator=(const PuzzleState & rhs)
{
	tiles = rhs.tiles;
	blank_position_col = rhs.blank_position_col;
	blank_position_row = rhs.blank_position_row;
	depth = rhs.depth;
	return *this;
}//assignment op

bool PuzzleState::canMoveUp()
{
	return blank_position_row != 0;
	//if 0 is not in row 1
}
bool PuzzleState::canMoveDown()
{
	return blank_position_row < rows - 1;
	//if 0 is not in last row 
}
bool PuzzleState::canMoveLeft()
{
	return blank_position_col != 0;
	//if 0 is not in col 1
}
bool PuzzleState::canMoveRight()
{
	return blank_position_col < cols - 1;
	//if 0 is not in last col
}
PuzzleState PuzzleState::moveBlankUp()
{
	int blankPos = (blank_position_row * rows) + blank_position_col;
	tiles[blankPos] = tiles[blankPos - rows];
	tiles[blankPos - rows] = 0;
	blank_position_row--;
	return *this;
	//swap 0 number above
}
PuzzleState PuzzleState::moveBlankDown()
{
	int blankPos = (blank_position_row * rows) + blank_position_col;
	tiles[blankPos] = tiles[blankPos + rows];
	tiles[blankPos + rows] = 0;
	blank_position_row++;
	return *this;
	//swap 0 number below
}
PuzzleState PuzzleState::moveBlankLeft()
{
	int blankPos = (blank_position_row * rows) + blank_position_col;
	tiles[blankPos] = tiles[blankPos - 1];
	tiles[blankPos - 1] = 0;
	blank_position_col--;
	return *this;
	//swap 0 number left
}
PuzzleState PuzzleState::moveBlankRight()
{
	int blankPos = (blank_position_row * rows) + blank_position_col;
	tiles[blankPos] = tiles[blankPos + 1];
	tiles[blankPos + 1] = 0;
	blank_position_col++;
	return *this;
	//swap 0 number right
}

//Get Puzzle State
void PuzzleState::read(istream & in)
{
	for (int i = 0; i < (int)tiles.size(); i++)
	{
		in >> tiles[i];
		if (tiles[i] == 0)
		{
			blank_position_col = i % cols;
			blank_position_row = i / rows;
		}
	}
}

//Print Puzzle State
void PuzzleState::print(ostream & out)
{
	if (cols != 0)
	{
		for (int i = 0; i < (int)tiles.size(); i++)
		{
			out << tiles[i] << " ";
			if (i%cols == rows - 1)
				out << endl;
		}
	}
	else
		out << "NULLSTATE" << endl;
}

//overload operators
istream & operator>>(istream &  in, PuzzleState & rhs)
{
	rhs.read(in);
	return in;
}
ostream & operator<<(ostream & out, PuzzleState & rhs)
{
	rhs.print(out);
	return out;
}