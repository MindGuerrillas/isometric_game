/* 
 * File:   CPathFindingStateSpace.h
 * Author: alan
 *
 * Created on 29 May 2013, 13:17
 */

#ifndef CPATHFINDINGSTATESPACE_H
#define	CPATHFINDINGSTATESPACE_H

#include "AI.h"
#include "CUnit.h"

class CPathFindingStateSpace : public CStateSpace
{
    public:
        CPathFindingStateSpace();
        CPathFindingStateSpace(CUnit* Unit, int TileID);
        
        // This state space stores only a pointer to the moving Unit
        CUnit*     UnitID;
};

#endif	/* CPATHFINDINGSTATESPACE_H */

