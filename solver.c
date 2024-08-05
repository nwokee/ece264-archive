// ***
// *** You MUST modify this file
// ***

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "solver.h"
#include "path.h"
#include "mazehelper.h"
#include "maze.h"

char * solveMaze(Maze * m) {
    //An obvious upper bound on the size of the solution path is the number
    //of squares in the maze + 1 (to account for the '\0'). You could make
    //this a tighter bound by accounting for how many walls there are, but
    //this approach is good enough!
	char * retval = malloc(sizeof(char) * ((m->width * m->height) + 1));

	MazePos mp = {.xpos = m->start.xpos, .ypos = m->start.ypos};
	if (!depthFirstSolve(m, mp, retval, 0)) {
		fprintf(stderr, "No solution found!\n");
	} else {
		printf("Solution found: %s\n", retval);
	}
	
	return retval;
}

bool depthFirstSolve(Maze * m, MazePos curpos, char * path, int step) {
	
	//FILL IN YOUR CODE HERE
	if(atEnd(curpos, m))
	{
		path[step] = '\0';
		return true;
	}
	if(!squareOK(curpos, m))
	{
		return false;
	}

	m -> maze[curpos.ypos][curpos.xpos].visited = true;
	char directions[4] = {'N', 'S', 'E', 'W'};
	MazePos steps[4] = {
		{.xpos = curpos.xpos, .ypos = curpos.ypos -1},
		{.xpos = curpos.xpos, .ypos = curpos.ypos +1},
		{.xpos = curpos.xpos +1, .ypos = curpos.ypos},
		{.xpos = curpos.xpos -1, .ypos = curpos.ypos}
	};

	for(int x = 0; x < 4; x++)
	{
		if(depthFirstSolve(m, steps[x], path, step+1))
		{
			path[step] = directions[x];
			return true;
		}
	}
	return false;
}

