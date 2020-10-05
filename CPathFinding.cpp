#include "CPathFinding.h"

CPathFinding::CPathFinding()
{
    ArraySize = CMap::Map.GetNumberOfTiles();
    
    // Allocate Array
    ClosedList = new int[ArraySize];
    ClosedListSize = 0;
    
    OpenList.Initialize(ArraySize);
}

void CPathFinding::AddToClosedList(CTile* Tile)
{
    Tile->PathInfo.WhichList = CLOSED_LIST;
    ClosedList[ClosedListSize] = Tile->ID;
    ClosedListSize++;
}

void CPathFinding::AddToOpenList(CTile* Tile)
{
    Tile->PathInfo.WhichList = OPEN_LIST;
    OpenList.PushNode(Tile->ID, PathFindingBHPush);
}

/*
 * A* Path Finding Function
 */
CPath* CPathFinding::FindPath(int startX, int startY, int targetX, int targetY)
{
    if (!ClosedList)
        ClosedList = new int[ArraySize];
        
    CTile* TargetTile = CMap::Map.GetTileByGridPos(targetX, targetY);
    CTile* StartTile = CMap::Map.GetTileByGridPos(startX, startY);
    
    CTile* CurrentTile = StartTile;
    
    // 1. Add Starting Square to Open List
    
    CurrentTile->PathInfo.G = 0;
    CurrentTile->PathInfo.F = 0;
    CurrentTile->PathInfo.H = 0;
    CurrentTile->PathInfo.Parent = NULL;
    CurrentTile->PathInfo.WhichList = 0;
    
    AddToOpenList(CurrentTile);

    do
    {
        // Look for Lowest F on Open List - Add it To Closed List        
        CurrentTile = CMap::Map.GetTileByID(OpenList.PopNode(PathFindingBHPop));
        
        if (CurrentTile == NULL)
            continue;
        
        AddToClosedList(CurrentTile);

        // 2. Calculate F, G & H for 8 adjacent tiles    
        for (int direction = 0; direction < NUMBER_OF_DIRECTIONS; direction++)
        {
            CTile* tile = CMap::Map.GetTileByDirection(CurrentTile, direction);
            
            if (tile == NULL)
                continue;
            
            // 3. If valid tile and not already on Closed List - ELSE Ignore it
            if (tile->isPassable() && tile->PathInfo.WhichList != CLOSED_LIST)
            {
                if (tile->PathInfo.WhichList != OPEN_LIST)
                {
                    // 4. Set Parent to current Tile;
                    tile->PathInfo.Parent = CurrentTile;

                    // 5. Calculate & Record F, G & H                
                    tile->PathInfo.G = (direction % 2 == 0) ? CurrentTile->PathInfo.G + STRAIGHT_MOVE : CurrentTile->PathInfo.G + DIAGONAL_MOVE;
                    tile->PathInfo.G += tile->TerrainCost();
                    
                    // Calculate H - estimated distance to Target using Manhatten method (straight lines)
                    tile->PathInfo.H = STRAIGHT_MOVE * (abs(tile->XGridPos - targetX) + abs(tile->YGridPos - targetY));

                    tile->PathInfo.F = tile->PathInfo.G + tile->PathInfo.H;                

                    // 6. Add to Open List            
                    AddToOpenList(tile);
                }else // 7. If already on Open List
                {                
                    // 8. Check if Path from Start to this square is better going through Current Tile - Use G to calculate this
                    int NewG = (direction % 2 == 0) ? CurrentTile->PathInfo.G + STRAIGHT_MOVE : CurrentTile->PathInfo.G + DIAGONAL_MOVE;
                    NewG += tile->TerrainCost();
                    
                    if (NewG < tile->PathInfo.G)
                    {
                        // 9. If so, Change Parent to Current Tile
                        tile->PathInfo.Parent = CurrentTile;
                        
                        // 10. Recalculate F & G            
                        tile->PathInfo.G = NewG;
                        tile->PathInfo.F = tile->PathInfo.G + tile->PathInfo.H;
                    }
                }
            }
        }
        
    // 11. Stop when target Square is added to Closed List        
    } while (TargetTile->PathInfo.WhichList != CLOSED_LIST && OpenList.GetSize() > 0);
    
    CMap::Map.PathCalculated = true;
    
    // Tidy Up
    if (ClosedList)
    {
        delete [] ClosedList;
        ClosedList = NULL;
    }
    
    if (OpenList.GetSize() == 0)
    {
        OpenList.Tidy();
        return NULL;
    }
    else
    {        
        // Read Path back and store in Path structure (Doubly-linked List)
        
        CPath* NewPath = new CPath;
        
        CTile*  currentNode = TargetTile;
        
        while (currentNode)
        {
            // Create New Node - don't add 1st tile
            
            if (currentNode != StartTile)
                NewPath->Prepend(currentNode);
            
            // Get Next Node
            currentNode = currentNode->PathInfo.Parent;            
        }
        
        OpenList.Tidy();
        
        return NewPath;
    }
        
}

bool PathFindingBHPush(int a, int b)
{
    CTile* tile1 = CMap::Map.GetTileByID(a);
    CTile* tile2 = CMap::Map.GetTileByID(b);
    
    return (tile1->PathInfo.F < tile2->PathInfo.F);
}

bool PathFindingBHPop(int node, int arraysize, int val, int targetvalue)
{
    CTile* tile1 = CMap::Map.GetTileByID(val);
    CTile* tile2 = CMap::Map.GetTileByID(targetvalue);    
    
    return ((node <= arraysize) && tile1->PathInfo.F < tile2->PathInfo.F);
}