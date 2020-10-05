#include "CFindTileTypeProblem.h"
#include "CMap.h"

CTile* CFindTileTypeProblem::FindForest()
{    
    // get List of State Spaces
    vector<CStateSpace*> results = BFS(this, false);
    
    if (results.size() == 0)
        return NULL;
    else
    {
        CTile* tile;
        
        int tileID = results.front()->StateID;
        
        tile = CMap::Map.GetTileByID(tileID);
        
        return tile;
    }    
}

bool CFindTileTypeProblem::IsGoalState(CStateSpace* state)
{    
    CTile* tile = CMap::Map.GetTileByID(state->StateID);
    
    return tile->TileType == Goal->StateID;
}