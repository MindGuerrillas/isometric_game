
#include "CGame.h"
#include "CEventsManager.h"
#include "CMap.h"
#include "CFramerate.h"

void CGame::Loop() 
{    
    // Run any Managed Events
    CEventsManager::EventsManager.Loop();
   
    for (int civID = 0; civID < Civilizations.size(); civID++)
    {
        CCivilization*  civ = Civilizations[civID];
        
        // Clear any Dead Units    
        for (std::vector<CUnit*>::iterator b = civ->Units.begin(); b != civ->Units.end();) 
        { 
            if ((*b)->Dead == true)
            {
                if (civ->SelectedUnit == (*b))
                {
                    (*b)->Location->Unit = NULL;
                    civ->SelectedUnit = NULL;
                }
                
                delete (*b);
                
                b = civ->Units.erase( b ); // reset iterator to a valid value post-erase
            }else
                ++b;            
        } 
    
        // Move Camera towards target (if set)
        if (CCamera::Camera.GetScrollTarget())
        {
            CFramerate::FPSControl.ScreenIsDirty = true;
            
            int dX = (CCamera::Camera.GetScrollTarget()->X + (TILE_WIDTH / 2) - (MAP_WIDTH / 2)) - CCamera::Camera.GetX() ;
            int dY = (CCamera::Camera.GetScrollTarget()->Y + (TILE_HEIGHT / 2) - (MAP_HEIGHT / 2)) - CCamera::Camera.GetY() ;            
            
            int NewX = 0;
            int NewY = 0;

            if (dX != 0)
                NewX = (dX > 0) ? CAMERA_SCROLL_INC : -CAMERA_SCROLL_INC;

            if  (dY != 0)
                NewY = (dY > 0) ? CAMERA_SCROLL_INC : -CAMERA_SCROLL_INC;
            
            bool moveCompleted = CCamera::Camera.OnMove(NewX, NewY);
            
            // Find Tile in Centre of Screen
            CTile* targetTile = CMap::Map.GetTileByCoord(MAP_WIDTH / 2, MAP_HEIGHT / 2);
            
            // Has target been reached            
            if (targetTile == CCamera::Camera.GetScrollTarget() || !moveCompleted)
                CCamera::Camera.ScrollToTarget(NULL);
            
        }        
    }
    
    // Give some CPU back
    SDL_Delay(1);
}


