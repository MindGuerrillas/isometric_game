/* 
 * File:   CPathFinding.h
 * Author: alan
 *
 * Created on March 9, 2013, 9:39 AM
 */

#ifndef CPATHFINDING_H
#define	CPATHFINDING_H

#include "CBinaryHeap.h"
#include "CMap.h"
#include "CPath.h"

#define OPEN_LIST       1
#define CLOSED_LIST     2

#define STRAIGHT_MOVE   10
#define DIAGONAL_MOVE   14

bool    PathFindingBHPush(int a, int b);
bool    PathFindingBHPop(int node, int arraysize, int val, int targetvalue);
        
class CPathFinding
{
    public:
        
        CPathFinding();
        
        CPath* FindPath(int startX, int startY, int targetX, int targetY);
        
    private:
        CBinaryHeap OpenList;
        
        int     ArraySize; // Total number of available tiles;       
        
        int*    ClosedList;
        int     ClosedListSize;
        
        void    AddToClosedList(CTile* Tile);
        void    AddToOpenList(CTile* Tile);        
};


#endif	/* CPATHFINDING_H */

