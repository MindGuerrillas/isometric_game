/* 
 * File:   CMap.h
 * Author: alan
 *
 * Created on March 4, 2013, 2:51 PM
 */

#ifndef CMAP_H
#define	CMAP_H

#include "SDL.h"
#include <vector>
#include <string>
#include "CPath.h"

enum {
    NORTH,
    NORTH_EAST,
    EAST,
    SOUTH_EAST,
    SOUTH,
    SOUTH_WEST,
    WEST,
    NORTH_WEST
};

#define NUMBER_OF_DIRECTIONS    8
#define TILESET_GFX             "./gfx/tilesets/tiles.png"
#define OVERLAYS_GFX            "./gfx/tilesets/overlays.png"
#define MOUSEMAP_GFX            "./gfx/tilesets/mousemap.gif"
#define GRID_GFX                "./gfx/tilesets/grid.png"
#define PATH_ARROWS             "./gfx/tilesets/patharrows.png"
#define TILE_CONNECTIONS_GFX    "./gfx/tilesets/tileconnections.png"
#define TERRAIN_TREES_GFX       "./gfx/tilesets/trees.png"
#define TERRAIN_HILLS_GFX       "./gfx/tilesets/hills.png"
#define TERRAIN_MOUNTAINS_GFX   "./gfx/tilesets/mountains.png"
#define TERRAIN_RIVERS_GFX      "./gfx/tilesets/rivers.png"
#define RIVER_MOUTHS_GFX        "./gfx/tilesets/rivermouths.png"

#define TILE_HIGHLIGHT_GFX      "./gfx/tilesets/tilehighlight.png"


#define NUMBER_TERRAIN_TILES    16

class CTile;

class CMap
{
    public:
        CMap();
        
        static  CMap    Map;
        
        SDL_Surface*    SMap;
        
        void    Render(int MapX, int MapY);
        void    RenderPath(int MapX, int MapY);
        void    RenderBorders(int MapX, int MapY);
        
        void    Load(std::string Map);
        int     Width();
        int     Height();
        void    Tidy();
        
        CTile*                  GetTileByCoord(int X, int Y) ;
        CTile*                  GetTileByGridPos(int X, int Y);
        CTile*                  GetTileByDirection(CTile* Tile, int Direction);
        CTile*                  GetTileByID(int ID);
        int                     GetTileIDFromGridPos(int X, int Y);        
        int                     GetDirectionToTile(CTile* From , CTile* To);        
        int                     GetNumberOfTiles();        
        std::vector<CTile*>     GetTilesWithinDistanceFrom(CTile* From, int Distance, bool BorderOnly = false);

        void    GenerateAutoBorders();
        
        bool    PathCalculated;
        CPath*  CurrentPath;
        
        bool    ShowGrid;
        bool    AutoCoast;
        
        CTile*  MouseOverTile;
        
    private:
        
        std::vector<CTile>      TileList;
        
        int     MapHeight;
        int     MapWidth;
        
        int     red, green, blue, yellow, white;
        
        void    GenerateAutoCoast(CTile* Tile); 
        void    GenerateAutoTerrain(CTile* Tile); // Calculates & sets Tile.TileTerrainIndex          
        
};

#endif	/* CMAP_H */

