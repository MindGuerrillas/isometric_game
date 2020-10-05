#include <SDL/SDL_keysym.h>
#include "CGame.h"
#include "CDebugLogging.h"
#include "CMap.h"
#include "CFramerate.h"
#include "CPathFindingProblem.h"
#include "CFindTileTypeProblem.h"

void CGame::OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode) 
{    
    switch(sym) 
    {            
        case SDLK_LEFT:
            // Clear any current scrolling
            CCamera::Camera.ScrollToTarget(NULL);
            CCamera::Camera.OnMove(-CAMERA_SCROLL_INC, 0);            
            break;
            
        case SDLK_RIGHT:
            // Clear any current scrolling
            CCamera::Camera.ScrollToTarget(NULL);
            CCamera::Camera.OnMove(CAMERA_SCROLL_INC, 0);
            break;
            
        case SDLK_UP:
            // Clear any current scrolling
            CCamera::Camera.ScrollToTarget(NULL);
            CCamera::Camera.OnMove(0, -CAMERA_SCROLL_INC);
            break;
            
        case SDLK_DOWN:
            // Clear any current scrolling
            CCamera::Camera.ScrollToTarget(NULL);
            CCamera::Camera.OnMove(0, CAMERA_SCROLL_INC);
            break;
            
        default: {
        }
    }
}

void TestForest()
{
    if (CGame::GetInstance()->CurrentCivilization->SelectedUnit == NULL)
        return;
            
    CUnit* unit = CGame::GetInstance()->CurrentCivilization->SelectedUnit;

    CFindTileTypeProblem* problem2 = new CFindTileTypeProblem(unit, TILE_TYPE_HILLS);
    CTile* tile = problem2->FindForest();
    delete problem2;

    if (tile != NULL)
    {
        CPathFindingProblem* problem = new CPathFindingProblem(unit, tile->ID);            
        CPath* p = problem->FindPath();
        delete problem;

        if (p)
        {
            if (p->Length == 1) // Only moving to an adjacent tile
            {
                unit->Path = NULL;        
                unit->MoveToTile(tile);
            }
            else // Full Path 
            {        
                unit->Path = p;

                // Take 1st steps along Path;
                unit->FollowPath();       
            }
        }                
    }
}

void CGame::OnKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode) 
{
    switch(sym) 
    {
        case SDLK_x: // Find Forest TESTER            
            TestForest();            
            break;
            
        case SDLK_g:
            CMap::Map.ShowGrid = !CMap::Map.ShowGrid;  
            CFramerate::FPSControl.ScreenIsDirty = true;
            break;

        case SDLK_c:
            CMap::Map.AutoCoast = !CMap::Map.AutoCoast;
            CFramerate::FPSControl.ScreenIsDirty = true;
            break;
            
        case SDLK_b:
            UnitActions(BUILD_CITY);            
            break;
            
        case SDLK_f:
            UnitActions(FARM);
            break;

        case SDLK_RETURN:
            EndOfTurn();
            break;
            
        default: {
        }
    }
}

void CGame::OnUser(Uint8 type, int code, void* data1, void* data2) 
{
    // USER EVENTS
   
    switch (code)
    {
        case GAME_EVENT_RESET:
            Reset();
            break;
            
        case GAME_EVENT_LEVEL_COMPLETE:
            //LevelComplete();
            break;
            
        case GAME_EVENT_GAMEOVER:
            GameOver();
            break;
    }
    
}

void CGame::OnLButtonDown(int x, int y)
{
    CTile* Tile = CMap::Map.GetTileByCoord(x,y);
    
    if (Tile == NULL)
        return;
    
    // Select Unit if one exists
    if (Tile->Unit)    
        CurrentCivilization->SelectedUnit = Tile->Unit;
    else
    {
        CurrentCivilization->SelectedUnit = NULL;
        if (CMap::Map.CurrentPath)
        {
            CMap::Map.CurrentPath->Tidy();
            CMap::Map.CurrentPath = NULL;
            CMap::Map.MouseOverTile = NULL;
        }        
    }
    
    // Select City if one exists
    if (Tile->City)
        CurrentCivilization->SelectedCity = Tile->City;
    else
        CurrentCivilization->SelectedCity = NULL;
    
    CCamera::Camera.ScrollToTarget(Tile);
     
    CFramerate::FPSControl.ScreenIsDirty = true;
}

void CGame::OnRButtonDown(int x, int y)
{
    CTile* Tile = CMap::Map.GetTileByCoord(x,y);
    
    if (Tile == NULL)
        return;

    printf("X:%d, Y:%d\n", Tile->XGridPos, Tile->YGridPos);
    
    CUnit* SelectedUnit = CurrentCivilization->SelectedUnit;
    
    if (SelectedUnit)
    {
        // Store Path To Current Tile        
        CPathFindingProblem* problem = new CPathFindingProblem(SelectedUnit, Tile->ID);            
        CPath* p = problem->FindPath();
        delete problem;
                
        if (p)
        {
            if (p->Length == 1) // Only moving to an adjacent tile
            {
                SelectedUnit->Path = NULL;        
                SelectedUnit->MoveToTile(Tile);
            }
            else // Full Path 
            {        
                SelectedUnit->Path = p;

                // Take 1st steps along Path;
                SelectedUnit->FollowPath();       
            }
        }
        
        CurrentCivilization->SelectedUnit = NULL;        
    }
    
    CMap::Map.MouseOverTile = NULL;
    
    if (CMap::Map.CurrentPath)
    {
        CMap::Map.CurrentPath->Tidy();
        CMap::Map.CurrentPath = NULL;
    }
    
    CFramerate::FPSControl.ScreenIsDirty = true;    
}

void CGame::OnMouseMove(int mX, int mY, int relX, int relY, bool Left,bool Right,bool Middle)
{
    // If Unit selected show arrows to current tile;
    if (CurrentCivilization->SelectedUnit == NULL)
        return;
    
    CTile*  CurrentTile = CMap::Map.GetTileByCoord(mX, mY);
    
    if (CurrentTile == CurrentCivilization->SelectedUnit->Location)
        return;
    
    if (CurrentTile && CurrentTile != CMap::Map.MouseOverTile)
    {
        CFramerate::FPSControl.ScreenIsDirty = true;
        
        CMap::Map.MouseOverTile = CurrentTile;
        
        // Calculate New Path
        
        if (CMap::Map.CurrentPath)
            CMap::Map.CurrentPath->Tidy();
       
        CPathFindingProblem* problem = new CPathFindingProblem(CurrentCivilization->SelectedUnit,  CurrentTile->ID);            
        CMap::Map.CurrentPath = problem->FindPath();
        delete problem;
    }
}