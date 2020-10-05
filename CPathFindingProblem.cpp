#include "CPathFindingProblem.h"
#include "CMap.h"

CPathFindingProblem::CPathFindingProblem(CPathFindingStateSpace* StartState, CPathFindingStateSpace* GoalState)
{
    Start = StartState;
    Goal = GoalState;
    Unit = StartState->UnitID;
}

CPathFindingProblem::CPathFindingProblem(CUnit* Unit, int GoalID)
{
    Start = new CPathFindingStateSpace(Unit, Unit->Location->ID); 
    Goal = new CPathFindingStateSpace(Unit, GoalID);    
    this->Unit = Unit;
}

CPath* CPathFindingProblem::FindPath()
{
    // Don't bother searching if Goal is known to be Impassable
    if (!CMap::Map.GetTileByID(Goal->StateID)->isPassable())
        return NULL;
    
    // get List of State Spaces
    vector<CStateSpace*> results = AStar(this, Manhatten, false);
    
    CMap::Map.PathCalculated = true;
    
    // Build CPath object from results
    CPath* NewPath = new CPath;
    
    for (int x = 0, len = results.size(); x < len; x++)
    {
        CTile* tile = CMap::Map.GetTileByID(results[x]->StateID);   
        NewPath->Prepend(tile);                
    }
    
    if (NewPath->Length == 0)
        return NULL;
    else
        return NewPath;
}

int Manhatten(CProblem* problem, CStateSpace* state)
{
    CTile* from =  CMap::Map.GetTileByID(state->StateID);    
    CTile* to =  CMap::Map.GetTileByID(problem->GetGoalState()->StateID);
    
    return STRAIGHT_MOVE * (abs(from->XGridPos - to->XGridPos) + abs(from->YGridPos - to->YGridPos));
}

bool CPathFindingProblem::IsGoalState(CStateSpace* state)
{    
    return Goal->StateID == state->StateID;            
}

std::vector<Successor> CPathFindingProblem::GetSuccessors(CStateSpace* state)
{   
    CTile* CurrentTile = CMap::Map.GetTileByID(state->StateID);
  
    std::vector<Successor> results;
    
    for (int direction = 0; direction < NUMBER_OF_DIRECTIONS; direction++)
    {
        CTile* tile = CMap::Map.GetTileByDirection(CurrentTile, direction);

        if (tile == NULL)
            continue;
        
        if (!tile->isPassable())
            continue;
        
        Successor node;
        node.State = new CPathFindingStateSpace(this->Unit, tile->ID);        
        node.Direction = direction;

        // Basic Movement Cost
        node.Cost = (direction % 2 == 0) ? STRAIGHT_MOVE : DIAGONAL_MOVE;

        // Additional Costs
        node.Cost += tile->TerrainCost();

        node.Parent = state;
        
        results.push_back(node);        
    }
    
    return results;
}