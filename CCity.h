/* 
 * File:   CCity.h
 * Author: alan
 *
 * Created on March 12, 2013, 1:12 PM
 */

#ifndef CCITY_H
#define	CCITY_H

#include "SDL.h"
#include <string>

class CTile;
class CCivilization;

#define CITIES_GFX           "./gfx/tilesets/cities.png"
#define CITIES_TILE_WIDTH    62
#define CITIES_TILE_HEIGHT   43

#define CITIES_HIGHLIGHT_GFX      "./gfx/tilesets/unithighlight.png"
#define CITIES_HIGHLIGHT_WIDTH    60
#define CITIES_HIGHLIGHT_HEIGHT   24

#define CITIES_TILE_HIGHLIGHT   "./gfx/tilesets/borders_white.png"

class CCity
{
    public:
        
        CCity();
        
        // PROPERTIES
        CCivilization*  Civilization;
        std::string     CityName;
        CTile*          Location;
        int             Population;
        int             Size;
        int             Territory; // Number of tiles in each direction claimed by city;
        
        void    Render(SDL_Surface* SDisplay);
        
        int     GetShields();
        int     GetGold();
        int     GetFood();
        
        void    HighlightTiles(SDL_Surface* SDisplay);
        
    private:

    
};

#endif	/* CCITY_H */

