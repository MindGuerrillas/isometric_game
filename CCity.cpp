#include "CCity.h"
#include "CCivilization.h"
#include "CCamera.h"
#include "CTilesetManager.h"
#include "CSurfaceManager.h"

CCity::CCity()
{
    CityName = "";
    Civilization = NULL;
    Location = NULL;
    Population = 0;
    Size = 1;
    Territory = 1;
}


void CCity::Render(SDL_Surface* SDisplay)
{
    // Only render if actually on screen
    if (!CCamera::Camera.OnScreen(Location->X, Location->Y))
        return;
    
    // Is Tile Visible To Current Civ?
    if (!Location->VisibleTo[Civilization->ID].Known)
        return;
    
    int screen_tileX = -CCamera::Camera.GetX() + Location->X;
    int screen_tileY =  -CCamera::Camera.GetY() + Location->Y;
    
    // If Selected Unit, show highlight
    if (Civilization->SelectedCity == this)        
        HighlightTiles(SDisplay);
            
    screen_tileY += -10;
    
    CSurface::Draw( SDisplay, CTilesetManager::TilesetManager.GetTileSurface(CITIES_GFX, Size - 1), screen_tileX, screen_tileY);     
}

int CCity::GetFood()
{
    // Count Food produced by City
    int Food = 0;
    
    std::vector<CTile*> tiles = CMap::Map.GetTilesWithinDistanceFrom(Location, Territory);
    
    for (int x = 0; x < tiles.size(); x++)
        Food += tiles[x]->GetFood();
    
    return Food;
}

int CCity::GetShields()
{
    // Count Shield produced by City
    int Shields = 0;
    
    std::vector<CTile*> tiles = CMap::Map.GetTilesWithinDistanceFrom(Location, Territory);
    
    for (int x = 0; x < tiles.size(); x++)
        Shields += tiles[x]->GetShields();
    
    return Shields;    
}

int CCity::GetGold()
{
    // Count Gold produced by City
    int Gold = 0;
    
    std::vector<CTile*> tiles = CMap::Map.GetTilesWithinDistanceFrom(Location, Territory);
    
    for (int x = 0; x < tiles.size(); x++)
        Gold += tiles[x]->GetGold();
    
    return Gold;    
}

void CCity::HighlightTiles(SDL_Surface* SDisplay)
{    
    std::vector<CTile*> tiles = CMap::Map.GetTilesWithinDistanceFrom(Location, Territory);
    
    for (int x = 0; x < tiles.size(); x++)
    {
        int screen_tileX = -CCamera::Camera.GetX() + tiles[x]->X;
        int screen_tileY =  -CCamera::Camera.GetY() + tiles[x]->Y;
        
        CSurface::Draw(SDisplay, CSurfaceManager::SurfaceManager.GetSurface(CITIES_TILE_HIGHLIGHT), screen_tileX, screen_tileY);
    }
}