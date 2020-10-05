/* 
 * File:   CTile.h
 * Author: alan
 *
 * Created on March 4, 2013, 2:55 PM
 */

#ifndef CTILE_H
#define	CTILE_H

#include <SDL.h>

#include "CCity.h"

#define TILE_WIDTH      64
#define TILE_HEIGHT     32

#define RIVER_TILE      999
#define RIVER_MOUTH     998

#define COAST_GFX       "./gfx/tilesets/coast.png"
#define DITHER_GFX      "./gfx/tilesets/dither.png"
#define BORDER_GFX      "./gfx/tilesets/borders.png"

#define MAXIMUM_CIVILIZATIONS  5

class CTile;
class CUnit;
class CCivilization;

struct TileVisibility
{
    bool    Known;
    bool    Fogged;
};

class CTile
{
    public:
        
        CTile();
    
        int     X;
        int     Y;
        int     XGridPos;
        int     YGridPos;
        int     ID; 
        
        int     TileType; // Grass, Plains, Hill, Mountain etc..
        int     SpecialTerrain; // furs, buffalo, corn, gold, etc        
        int     TileImprovement; // Farm, mine, irrigation etc        
        int     TileTerrainIndex;  // Stores index of image to display for tile
        int     RiverMouth; // End of river. Number is for which direction mouth goes in;
        
        CCivilization*  ControlledBy; // The Civ that owns this tile
        int             Borders; // Number to indicate direction of borders
        
        int     Seed; // Random value to smooth out tiled effect
        bool    HasCoast;         
        int     CoastMap[4]; // Stores a number between 0 - 7 (000 - 111)           
        int     SurroundingTiles[4]; // Stores TileType of surrounding Tiles in N, E, S, W;
        
        struct  TileVisibility    VisibleTo[MAXIMUM_CIVILIZATIONS];
        
        CUnit*  Unit; // Pointer to unit that is in this square
        CCity*  City; // Pointer to city in this square
        
        int     TerrainCost();
        
        void    Render(SDL_Surface* SDisplay, int MapX, int MapY);
        void    RenderCoast(SDL_Surface* SDisplay);
        bool    isPassable();
        
        int     GetGold();
        int     GetFood();
        int     GetShields();
};


#endif	/* CTILE_H */

