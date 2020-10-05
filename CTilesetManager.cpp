#include <string>
#include <sstream>
#include "CTile.h"
#include "CTilesetManager.h"
#include "CDebugLogging.h"
#include "CSurfaceManager.h"
#include "CUnit.h"

CTilesetManager   CTilesetManager::TilesetManager;

CTilesetManager::CTilesetManager()
{

}

bool CTilesetManager::Initialize()
{   
    
    return true;
}

SDL_Rect CTilesetManager::LookupTilesetDimensions(std::string tileset)
{
    SDL_Rect rect = {0, 0, TILE_WIDTH, TILE_HEIGHT};
    
    if (tileset == UNITS_GFX)    
        rect = {0, 0, UNITS_TILE_WIDTH, UNITS_TILE_HEIGHT};
    
    if (tileset == UNIT_HIGHLIGHT_GFX)    
        rect = {0, 0, UNIT_HIGHLIGHT_WIDTH, UNIT_HIGHLIGHT_HEIGHT};
    
    return rect;
}

// Load a specified Surface
bool CTilesetManager::Load(std::string File, bool alpha)
{    
    SDL_Rect tilesize = LookupTilesetDimensions(File);
    
    // Load Tileset image
    Tileset set;
    set.Surface = CSurfaceManager::SurfaceManager.GetSurface(File, alpha);
    
    // Load in the details of the tileset's tiles
    int TilesetWidth  = set.Surface->w / tilesize.w;
    int TilesetHeight = set.Surface->h / tilesize.h;
    int ID = 0;
    
    set.Width = TilesetWidth;
    set.Height = TilesetHeight;
    
    int DitherOffsets[4][2] = {{tilesize.w / 2, 0}, {tilesize.w / 2, tilesize.h / 2}, {0, tilesize.h / 2}, {0, 0}};
    
    for (int y=0; y < TilesetHeight; y++)
    {
        for (int x=0; x < TilesetWidth; x++)
        {
            int TilesetX = (ID % TilesetWidth) * tilesize.w;
            int TilesetY = (ID / TilesetWidth) * tilesize.h;
            
            TileDetails tDetail;
            tDetail.X = TilesetX;
            tDetail.Y = TilesetY;
            
            // Load Tile to Surface Manager
            SDL_Rect rect;
            rect.x = TilesetX;
            rect.y = TilesetY;
            rect.w = tilesize.w;
            rect.h = tilesize.h;
            
            SDL_Surface*   currentTile = CSurface::GetRectFromSurface(set.Surface, rect);
            
            std::stringstream tilename;
            tilename << File << "_" << x << "_" << y;
            
            CSurfaceManager::SurfaceManager.LoadExistingSurface(tilename.str(), currentTile);
            
            // Create a dithered version of Tile
            SDL_Surface* ditheredTile = CSurface::mask_surface(currentTile, CSurfaceManager::SurfaceManager.GetSurface(DITHER_GFX), 0, 0);
            tilename << "_DITHER";
            
            CSurfaceManager::SurfaceManager.LoadExistingSurface(tilename.str(), ditheredTile);
            
            // Split Dither Tile into quarters
            for (int dir = 0; dir < 4; dir++)
            {
                std::stringstream surfacename;
                surfacename << tilename.str() << dir;
                
                SDL_Rect rect = {DitherOffsets[dir][0], DitherOffsets[dir][1], tilesize.w / 2, tilesize.h / 2};
                SDL_Surface*   ditherQuarter = CSurface::GetRectFromSurface(ditheredTile, rect);
                
                CSurfaceManager::SurfaceManager.LoadExistingSurface(surfacename.str(), ditherQuarter);
                
                tDetail.Blending[dir] = ditherQuarter;
            }
            
            tDetail.STileNormal = currentTile;
            tDetail.STileDither = ditheredTile;
            
            set.Tiles.push_back(tDetail);
            
            ID++;
        }
    }
    
    Tilesets[File] = set;
    
    return true;
}

void CTilesetManager::Tidy()
{
    Tilesets.clear();
}

SDL_Surface* CTilesetManager::GetSurface(std::string ID, bool alpha)
{    
    // Check is requested surface is already loaded. If not, do so
    if (Tilesets[ID].Surface == NULL)
        if (Load(ID, alpha) == false) return NULL;
       
    return Tilesets[ID].Surface;
}

TileDetails* CTilesetManager::GetTileDetails(std::string ID, int tileID)
{
    // Check is requested surface is already loaded. If not, do so
    if (Tilesets[ID].Surface == NULL)
        if (Load(ID) == false) return NULL;
    
    return &Tilesets[ID].Tiles[tileID];
}

TileDetails* CTilesetManager::GetTileDetailsByRowCol(std::string ID, int X, int Y)
{
    // Check is requested surface is already loaded. If not, do so
    if (Tilesets[ID].Surface == NULL)
        if (Load(ID) == false) return NULL;
    
    if (X >= Tilesets[ID].Width) X = Tilesets[ID].Width;
    if (Y >= Tilesets[ID].Height) Y = Tilesets[ID].Height;
    
    int tileID = (Y * Tilesets[ID].Width) + X;
    
    return &Tilesets[ID].Tiles[tileID];
}

SDL_Surface* CTilesetManager::GetTileSurface(std::string ID, int tileID, bool Dithered, int DitherSector)
{
    // Check is requested surface is already loaded. If not, do so
    if (Tilesets[ID].Surface == NULL)
        if (Load(ID) == false) return NULL;

    if (Dithered)
    {
        if (DitherSector >= 0)
            return Tilesets[ID].Tiles[tileID].Blending[DitherSector];
        else
            return Tilesets[ID].Tiles[tileID].STileDither;
    }
    else
        return Tilesets[ID].Tiles[tileID].STileNormal;
}

SDL_Surface* CTilesetManager::GetTileSurfaceByRowCol(std::string ID, int X, int Y, bool Dithered, int DitherSector)
{
    // Check is requested surface is already loaded. If not, do so
    if (Tilesets[ID].Surface == NULL)
        if (Load(ID) == false) return NULL;
    
    int tileID = (Y * Tilesets[ID].Width) + X;
   
    if (Dithered)
    {
        if (DitherSector >= 0)
            return Tilesets[ID].Tiles[tileID].Blending[DitherSector];
        else
            return Tilesets[ID].Tiles[tileID].STileDither;
    }
    else
        return Tilesets[ID].Tiles[tileID].STileNormal;
}