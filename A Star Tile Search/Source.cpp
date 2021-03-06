#include "stdafx.h"
#include "iostream"
#include "PuzzleState.h"
#include "PuzzleMove.h"
#include <string>
#include <list>
#include <iterator>

using namespace std;

bool find_solution(PuzzleState start, PuzzleState goal, list<PuzzleMove> & solution);
void print_solution(list<PuzzleMove> & solution);
list<PuzzleMove>::const_iterator & findNextParent(PuzzleState & state, list<PuzzleMove>::const_iterator & from, list<PuzzleMove>::const_iterator & end, list<PuzzleMove> aMoveList);
bool isMember(PuzzleState element, list<PuzzleMove> & list);

static PuzzleState NullState(3, 3); //Set Default Puzzle State

/*
3 0 1
6 4 2
7 8 5
*/
/*
1 2 5
0 4 8
3 6 7
*/

int main()
{
	int rc;
	list<PuzzleMove> solution;

	cout << "Enter size of tile puzzle (integer greater than 0): ";
	cin >> rc;

	PuzzleState begin(rc, rc);
	cout << "\nEnter Start State row by row (numbers delimited by white space):\n";
	cin >> begin;
	PuzzleState goal(rc, rc);
	cout << "\nEnter Goal State row by row (numbers delimited by white space):\n";
	cin >> goal;
	cout << endl;

	if (find_solution(begin, goal, solution))
	{
		cout << "Solution:\n\n";
		cout << begin << endl;
		print_solution(solution);
	}
	else
		cout << "No Solution Found..." << endl;
	system("pause");
	return 0;
}

//Print final solution with all steps used
void print_solution(list<PuzzleMove> & solution)
{
	list<PuzzleMove>::const_iterator i;
	string move;
	for (i = solution.begin(); i != solution.end(); ++i)
	{
		PuzzleMove pmove = *i;
		switch (pmove.getMoveName())
		{
		case 0: move = "down"; break;
		case 1: move = "left"; break;
		case 2: move = "right"; break;
		case 3: move = "up"; break;
		}
		cout << move << "\n\n";
		cout << pmove.getState() << "\n";
	}
}

//Breath First Search with Manhattan distance as hueristic
bool find_solution(PuzzleState start, PuzzleState goal, list<PuzzleMove> & solution)
{
	list<PuzzleMove> open, closed;
	open.push_back(PuzzleMove(start, NullState, nullMove));
	int manhatDist;
	list<PuzzleMove>::const_iterator best;
	while (!open.empty())
	{
		PuzzleMove current_move = open.front();
		manhatDist = current_move.getState().getManhatDist(goal);
		best = open.begin();
		for (list<PuzzleMove>::const_iterator itr = open.begin(); itr != open.end(); ++itr)
		{
			PuzzleMove pmove = *itr;
			if (pmove.getState().getManhatDist(goal) < manhatDist)
			{
				current_move = *itr;
				manhatDist = current_move.getState().getManhatDist(goal);
				best = itr;
			}
		}
		open.erase(best);
		PuzzleState currentState = current_move.getState();
		if (currentState == goal)
		{
			list<PuzzleMove>::const_iterator lastFoundPosition = closed.begin();
			list<PuzzleMove>::const_iterator end = closed.end();
			PuzzleState parentState = current_move.getParent();
			while (parentState != NullState)
			{
				solution.push_front(current_move);
				currentState = parentState;
				lastFoundPosition = findNextParent(currentState, lastFoundPosition, end, closed);
				current_move = *lastFoundPosition;
				parentState = current_move.getParent();
			}
			return true;
		}
		else
		{
			closed.push_front(current_move);

			/* The order of these does affect the solution time. However optimal solution will be found anyway*/
			if (currentState.canMoveDown())
			{
				currentState.moveBlankDown();
				PuzzleState childState = currentState;
				childState.setDepth(currentState.getDepth() + 1);
				currentState.moveBlankUp();
				if (!isMember(childState, open) && !isMember(childState, closed))
				{
					open.push_back(PuzzleMove(childState, currentState, Down)); //bfs

				}
			}
			if (currentState.canMoveLeft())
			{
				currentState.moveBlankLeft();
				PuzzleState childState = currentState;
				childState.setDepth(currentState.getDepth() + 1);
				currentState.moveBlankRight();
				if (!isMember(childState, open) && !isMember(childState, closed))
				{
					open.push_back(PuzzleMove(childState, currentState, Left)); //bfs
				}
			}
			if (currentState.canMoveUp())
			{
				currentState.moveBlankUp();
				PuzzleState childState = currentState;
				childState.setDepth(currentState.getDepth() + 1);
				currentState.moveBlankDown();
				if (!isMember(childState, open) && !isMember(childState, closed))
				{
					open.push_back(PuzzleMove(childState, currentState, Up)); //bfs
				}
			}
			if (currentState.canMoveRight())
			{
				currentState.moveBlankRight();
				PuzzleState childState = currentState;
				childState.setDepth(currentState.getDepth() + 1);
				currentState.moveBlankLeft();
				if (!isMember(childState, open) && !isMember(childState, closed))
				{
					open.push_back(PuzzleMove(childState, currentState, Right)); //bfs
				}
			}
		}
	}
	return false;
}

list<PuzzleMove>::const_iterator & findNextParent(PuzzleState & state, list<PuzzleMove>::const_iterator & from, list<PuzzleMove>::const_iterator & end, list<PuzzleMove> aMoveList)
{
	list<PuzzleMove>::const_iterator & itr = from;
	for (itr = from; itr != end; ++itr)
	{
		PuzzleMove aMove = *itr;
		if (state == aMove.getState()) break;
	}
	return itr;
}
//is member of found set
bool isMember(PuzzleState element, list<PuzzleMove> & alist)
{
	list<PuzzleMove>::const_iterator it;
	for (it = alist.begin(); it != alist.end(); ++it)
	{
		PuzzleMove pmove = *it;
		if (pmove.getState() == element)
		{
			return true;
		}
	}
	return false;
}