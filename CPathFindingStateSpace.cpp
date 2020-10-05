#include "CPathFindingStateSpace.h"

CPathFindingStateSpace::CPathFindingStateSpace(CUnit* Unit, int TileID)
{
    this->UnitID = Unit;
    this->StateID = TileID;
    CStateSpace();
}
