/* 
 * File:   CTilesetManager.h
 * Author: alan
 *
 * Created on March 5, 2013, 1:20 PM
 */

#ifndef CTILESETMANAGER_H
#define	CTILESETMANAGER_H

#include <SDL.h>
#include "CSurface.h"
#include <tr1/unordered_map>
#include <vector>

struct TileDetails
{
    int X;
    int Y;
    SDL_Surface*    STileNormal;
    SDL_Surface*    STileDither;
    SDL_Surface*    Blending[4]; // Stores dithered tile split into 4 for N, E, S, W
};

struct Tileset
{
    SDL_Surface*                Surface;
    std::vector<TileDetails>    Tiles;
    int                         Width;
    int                         Height;
};

typedef std::tr1::unordered_map  <std::string, Tileset> TilesetMap;

class CTilesetManager
{
    public:
        CTilesetManager();
        
        static CTilesetManager    TilesetManager;
        
        bool            Initialize();            
        void            Tidy();
        SDL_Surface*    GetSurface(std::string ID, bool alpha = true);
        
        TileDetails*   GetTileDetails(std::string ID, int tileID);
        TileDetails*   GetTileDetailsByRowCol(std::string ID, int X, int Y);
        
        SDL_Surface*   GetTileSurface(std::string ID, int tileID, bool Dithered = false, int DitherSector = -1);
        SDL_Surface*   GetTileSurfaceByRowCol(std::string ID, int X, int Y, bool Dithered = false, int DitherSector = -1);
        
    private:
        bool            Load(std::string File, bool alpha = true);        
        
        TilesetMap      Tilesets;    
        SDL_Rect        LookupTilesetDimensions(std::string tileset);
};

#endif	/* CTILESETMANAGER_H */

