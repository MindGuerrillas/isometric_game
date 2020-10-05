/* 
 * File:   CFindForestProblem.h
 * Author: alan
 *
 * Created on 01 June 2013, 14:43
 */

#ifndef CFINDTILETYPEPROBLEM_H
#define	CFINDTILETYPEPROBLEM_H

#include "AI.h" // Include the AI library
#include "CTile.h"
#include "CPathFindingProblem.h"

class CFindTileTypeProblem : public CPathFindingProblem
{
    public:
        CFindTileTypeProblem(CUnit* Unit, int TileType) : CPathFindingProblem(Unit, TileType) {}
        
        CTile* FindForest();
        
        bool IsGoalState(CStateSpace* state);         
        
};

#endif	/* CFINDTILETYPEPROBLEM_H */

