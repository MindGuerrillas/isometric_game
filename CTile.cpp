#include "CTile.h"
#include "CMap.h"
#include "CSurfaceManager.h"
#include "CCamera.h"
#include "CTilesetManager.h"
#include "CGame.h"

CTile::CTile()
{
    TileImprovement = -1;
    TileTerrainIndex = 0;
    RiverMouth = -1;
    SpecialTerrain = -1;
    HasCoast = false;
    Borders = 0;
    
    ControlledBy = NULL;
    Unit = NULL;
    City = NULL;
    
    // Clear PatternMap array
    for (int x=0; x < 4; x++)
        CoastMap[x] = -1;
    
    // Clear Visibility data
    for (int civ = 0, len = CGame::GetInstance()->GetNumberOfCivilizations(); civ < len ; civ++)
    {
        VisibleTo[civ].Fogged = false;
        VisibleTo[civ].Known = false;
    }
    
    for (int x = 0; x < 4; x++)
        SurroundingTiles[x] = -1;
}

void CTile::Render(SDL_Surface* SDisplay, int MapX, int MapY)
{
    int DitherOffsets[4][2] = {{TILE_WIDTH / 2, 0}, {TILE_WIDTH / 2, TILE_HEIGHT / 2}, {0, TILE_HEIGHT / 2}, {0, 0}};
    
    int screen_tileX = MapX + X;
    int screen_tileY = MapY + Y;
    
    // Is Tile Visible To Current Civ?
    if (VisibleTo[CGame::GetInstance()->CurrentCivilization->ID].Known)
    {                                
        if (CCamera::Camera.OnScreen(X, Y))
        {
            // Draw tile to surface                
            CSurface::Draw( SDisplay, CTilesetManager::TilesetManager.GetTileSurfaceByRowCol(TILESET_GFX, Seed, TileType), screen_tileX, screen_tileY);

            // Draw any needed Dither to Tile
            for (int dir = 0; dir < 4; dir++)
            {
                if (SurroundingTiles[dir] >= 0)
                {
                    // Dither Required
                    CSurface::Draw( SDisplay, CTilesetManager::TilesetManager.GetTileSurfaceByRowCol(TILESET_GFX, 0, SurroundingTiles[dir], true, dir), 
                                    screen_tileX + DitherOffsets[dir][0], screen_tileY + DitherOffsets[dir][1]);

                }
            }

            // Overlay Coast Map
            RenderCoast(SDisplay);

             // Show Grid                
            if (CMap::Map.ShowGrid)
               CSurface::Draw(SDisplay, CSurfaceManager::SurfaceManager.GetSurface(GRID_GFX), screen_tileX, screen_tileY); 
 
            // add any terrain - for Forests, Hills, Mountains
            if (TileType >= TILE_TYPE_FORESTS && TileType <= TILE_TYPE_MOUNTAINS)
            {
                std::string tileset;

                switch (TileType)
                {
                    case TILE_TYPE_MOUNTAINS:
                        tileset = TERRAIN_MOUNTAINS_GFX;
                        break;

                    case TILE_TYPE_HILLS:
                        tileset = TERRAIN_HILLS_GFX;
                        break;

                    case TILE_TYPE_FORESTS:
                        tileset = TERRAIN_TREES_GFX;
                        break;
                }

                CSurface::Draw( SDisplay, CTilesetManager::TilesetManager.GetTileSurface(tileset, TileTerrainIndex), screen_tileX, screen_tileY);   
            }

            // add any special terrain
            if (SpecialTerrain >= 0)
            {
                if (SpecialTerrain == RIVER_TILE)                    
                    CSurface::Draw(SDisplay, CTilesetManager::TilesetManager.GetTileSurface(TERRAIN_RIVERS_GFX, TileTerrainIndex), screen_tileX, screen_tileY);                       
                 else
                    CSurface::Draw(SDisplay, CTilesetManager::TilesetManager.GetTileSurface(OVERLAYS_GFX, SpecialTerrain), screen_tileX, screen_tileY);
            }

            // add an improvement
            if (TileImprovement >= 0)
                CSurface::Draw(SDisplay, CTilesetManager::TilesetManager.GetTileSurface(OVERLAYS_GFX, TileImprovement), screen_tileX, screen_tileY);

        }
    }

    // Draw Tile Highlight
    if (CMap::Map.MouseOverTile == this)
        CSurface::Draw(SDisplay, CSurfaceManager::SurfaceManager.GetSurface(TILE_HIGHLIGHT_GFX), screen_tileX, screen_tileY);
    
}

void CTile::RenderCoast(SDL_Surface* SDisplay)
{
    if (HasCoast && CMap::Map.AutoCoast)
    {
        SDL_Surface* coast = CSurfaceManager::SurfaceManager.GetSurface(COAST_GFX);

        int StartX = -CCamera::Camera.GetX() + X;
        int StartY = -CCamera::Camera.GetY() + Y;
        
        int offsets[4][2] = { 
            {StartX + (TILE_WIDTH / 4), StartY},   
            {StartX + (TILE_WIDTH / 2), StartY + (TILE_HEIGHT / 4)},
            {StartX + (TILE_WIDTH / 4), StartY + (TILE_HEIGHT / 2)},
            {StartX, StartY + (TILE_HEIGHT / 4)}
        };
        
        for (int c=0; c < 4; c++)
        { 
            if (CoastMap[c] > 0)
            {
                CSurface::Draw(SDisplay, coast, offsets[c][0], offsets[c][1], CoastMap[c] * (TILE_WIDTH/2), c * (TILE_HEIGHT/2), TILE_WIDTH/2, TILE_HEIGHT/2);
            }
        }

        if (RiverMouth >= 0)
        {
            int screen_tileX = -CCamera::Camera.GetX() + X;
            int screen_tileY = -CCamera::Camera.GetY() + Y;
            
            TileDetails* tPosRiver = CTilesetManager::TilesetManager.GetTileDetails(RIVER_MOUTHS_GFX,RiverMouth);

            CSurface::Draw(SDisplay, CTilesetManager::TilesetManager.GetSurface(RIVER_MOUTHS_GFX), 
                                screen_tileX, screen_tileY, tPosRiver->X, tPosRiver->Y, TILE_WIDTH, TILE_HEIGHT);            
        }
    }    
}

bool CTile::isPassable()
{
    bool Passable = true;
    
    // If tile is not Known to Civilization return passable = true
    if (!(VisibleTo[CGame::GetInstance()->CurrentCivilization->ID].Known))
        return true;
   
    if (TileType == TILE_TYPE_WATER)
        Passable = false;
    
    if (TileType == TILE_TYPE_MOUNTAINS)
        Passable = false;
    
    return Passable;
}

int CTile::TerrainCost()
{
    switch (TileType)
    {
        case TILE_TYPE_FORESTS:
            return 5;
        case TILE_TYPE_HILLS:
            return 15;
        case TILE_TYPE_JUNGLE:
            return 10;
        case TILE_TYPE_SWAMP:
            return 10;            
    }
    
    return 0;
}

int CTile::GetFood()
{
    int food = 0;
    
    food += TerrainSpecs[TileType].Food;
    
    if (TileImprovement == TILE_IMPROVEMENT_FARM)
        food += TerrainSpecs[TileType].Food_Improvement;
    
    return food;
}

int CTile::GetGold()
{
    int gold = 0;
    
    gold += TerrainSpecs[TileType].Gold;
    
    if (TileImprovement == TILE_IMPROVEMENT_ROAD)
        gold += TerrainSpecs[TileType].Gold_Improvement;
    
    return gold;    
}

int CTile::GetShields()
{
    int shields = 0;
    
    shields += TerrainSpecs[TileType].Gold;
    
    if (TileImprovement == TILE_IMPROVEMENT_MINE)
        shields += TerrainSpecs[TileType].Shields_Improvement;
    
    return shields;     
}