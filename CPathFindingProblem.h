/* 
 * File:   CPathFindingProblem.h
 * Author: alan
 *
 * Created on 29 May 2013, 13:45
 */

#ifndef CPATHFINDINGPROBLEM_H
#define	CPATHFINDINGPROBLEM_H

#include "AI.h" // Include the AI library

#include "CPathFindingStateSpace.h"
#include "CPath.h"

#define STRAIGHT_MOVE   10
#define DIAGONAL_MOVE   14

class CPathFindingProblem : public CProblem
{
    public:
        CPathFindingProblem(CPathFindingStateSpace* StartState, CPathFindingStateSpace* GoalState);
        CPathFindingProblem(CUnit* Unit, int GoalID);
        
        CPath* FindPath();
        
        bool                    IsGoalState(CStateSpace* state);         
        std::vector<Successor>  GetSuccessors(CStateSpace* state);   
        
        CUnit*  Unit;
};

// Custom heuristic function
int Manhatten(CProblem* problem, CStateSpace* state);

#endif	/* CPATHFINDINGPROBLEM_H */

