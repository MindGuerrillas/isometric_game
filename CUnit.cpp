#include <string>

#include "CUnit.h"
#include "CTile.h"
#include "CCivilization.h"
#include "CCamera.h"
#include "CTilesetManager.h"
#include "CGame.h"
#include "CFramerate.h"

CUnit::CUnit()
{
    Dead = false;
    Civilization = NULL;
    Path = NULL;
    Location = NULL;
    Performing_Action = NOTHING;
    
}

void CUnit::Render(SDL_Surface* SDisplay)
{
    if (Dead)
        return;
    
    // Only render if actually on screen
    if (!CCamera::Camera.OnScreen(Location->X, Location->Y))
        return;
    
    // Is Tile Visible To Current Civ?
    if (!Location->VisibleTo[Civilization->ID].Known)
        return;
    
    int screen_tileX = -CCamera::Camera.GetX() + Location->X;
    int screen_tileY =  -CCamera::Camera.GetY() + Location->Y;
    
    // If Selected Unit, show highlight
    if (Civilization->SelectedUnit == this)
        CSurface::Draw(SDisplay, CTilesetManager::TilesetManager.GetTileSurface(UNIT_HIGHLIGHT_GFX, 1), screen_tileX + 5, screen_tileY + 5);
    
    screen_tileX += UnitSpecs[Type].XOffset;
    screen_tileY += UnitSpecs[Type].YOffset;
    
    CSurface::Draw( SDisplay, CTilesetManager::TilesetManager.GetTileSurface(UNITS_GFX, UnitSpecs[Type].Gfx), screen_tileX, screen_tileY); 
    
}

void CUnit::PerformAction(ACTION action)
{
    CFramerate::FPSControl.ScreenIsDirty = true;
    
    if (Type == SETTLER)
    {
        switch (action)
        {
            case BUILD_CITY:
                BuildCity();
                break;           
        }
    }
    
    if (Type == WORKER)
    {
        switch (action)
        {
            case BUILD_ROAD:
                
                break;
                
            case FARM:
                BuildFarm();
                break;
            
            case IRRIGATE:
                
                break;
                
            case MINE:
                
                break;                
        }        
    }
    
}

bool CUnit::BuildCity()
{
    CCity* builtcity = Civilization->CreateCity(Location);
    
    if (builtcity)
    {
        // Kill the Settler Unit
        CMap::Map.CurrentPath = NULL;
        Dead = true;
        
        return true;
    }else
        return false;
}

bool CUnit::BuildFarm()
{
    // Can only build on own land
    if (Location->ControlledBy != Civilization)
        return false;
    
    if (Location->TileImprovement == TILE_IMPROVEMENT_FARM)
        return false;
    
    Location->TileImprovement = TILE_IMPROVEMENT_FARM;
    
    return true;
}

bool CUnit::MoveInDirection(int direction)
{
    if (direction < 0)
        return false;
    
    CTile* nextTile = CMap::Map.GetTileByDirection(Location, direction);
    
    if (nextTile)
        return MoveToTile(nextTile);
    else
        return false;
}

bool CUnit::MoveToTile(CTile* Tile)
{
    if (Tile->isPassable())
    {
        Location = Tile;
        Tile->Unit = this;    

        // Reduce movement
        Moves_Left -= TerrainSpecs[Tile->TileType].MoveCost;

        DiscoverMap();    
        
        return true;
    }else
    {
        // Stop Movement & Clear any Path
        Path->Tidy();
        Path = NULL;
        
        return false;
    }
}

void CUnit::FollowPath()
{    
    while (Moves_Left > 0 && Path)
    {
        CPathNode* node = Path->GetNextNode();

        if (MoveInDirection(CMap::Map.GetDirectionToTile(Location, node->Tile)))
        {
            Path->CompletedStep();

            if (Path->Length == 0) // Path Completed
                Path = NULL;
        }
    }
}

/*
 Look at surrounding tiles and mark as Known
 */
void CUnit::DiscoverMap()
{
    int ViewDistance = UnitSpecs[Type].Vision_Radius;    
    
    std::vector<CTile*> TileList = CMap::Map.GetTilesWithinDistanceFrom(Location, ViewDistance);
    
    for (int x = 0; x < TileList.size(); x++)
    {
        TileList[x]->VisibleTo[Civilization->ID].Fogged = false;
        TileList[x]->VisibleTo[Civilization->ID].Known = true; 
    }
   
    // Tidy up
    TileList.clear();
    
    CFramerate::FPSControl.ScreenIsDirty = true;
}
