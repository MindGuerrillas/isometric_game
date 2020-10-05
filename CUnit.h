/* 
 * File:   CUnit.h
 * Author: alan
 *
 * Created on March 12, 2013, 1:14 PM
 */

#ifndef CUNIT_H
#define	CUNIT_H

#include "CTile.h"
#include "CPathFinding.h"
#include "DataSetup.h"

#define UNITS_GFX           "./gfx/tilesets/units.png"
#define UNITS_TILE_WIDTH    48
#define UNITS_TILE_HEIGHT   36

#define UNIT_HIGHLIGHT_GFX      "./gfx/tilesets/unithighlight.png"
#define UNIT_HIGHLIGHT_WIDTH    60
#define UNIT_HIGHLIGHT_HEIGHT   24

// Forward declare Civilization class as it's needed here (avoids circular reference)
class CCivilization;

class CUnit
{
    public:

        CUnit();

        // PROPERTIES
        CCivilization*  Civilization;
        UNIT_TYPE       Type;
        CTile*          Location;
        
        int             Moves_Left;
        int             HP;
        ACTION          Performing_Action;
        
        CPath*          Path;
        
        bool            Dead;
        
        //Path            UnitPath;
        
        void            PerformAction(ACTION action);
        bool            MoveToTile(CTile* Tile);
        bool            MoveInDirection(int direction);
        void            FollowPath();
        
        void            Render(SDL_Surface* SDisplay);
        
        void            DiscoverMap();
        
    private:

        // ACTIONS
        bool    BuildCity();
        bool    BuildFarm();
        

};

#endif	/* CUNIT_H */

