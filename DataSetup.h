/* 
 * File:   DataSetup.h
 * Author: alan
 *
 * Created on March 16, 2013, 3:35 PM
 */

#ifndef DATASETUP_H
#define	DATASETUP_H

enum UNIT_TYPE
{
    SETTLER,
    WORKER,
    WARRIOR,
    
    
    NUMBER_OF_UNIT_TYPES  // Always bigger than maximum number of unit types;
};

enum ACTION
{
    NOTHING,
    FARM,
    IRRIGATE,
    MINE,
    BUILD_ROAD,
    BUILD_CITY
};

struct  UnitSpecification
{
    UNIT_TYPE           UnitType;
    int                 Gfx;    // Tile ID in Units Tile-set
    int                 XOffset;
    int                 YOffset;
    int                 Build_Cost;    
    int                 Upkeep_Cost_Shields;
    int                 Upkeep_Cost_Food;
    int                 Upkeep_Cost_Gold;
    int                 HP;
    int                 Firepower;
    int                 Moves;
    int                 Vision_Radius;
};

enum
{
    TILE_TYPE_WATER,            // 0
    TILE_TYPE_GRASS,            // 1
    TILE_TYPE_DESERT,           // 2
    TILE_TYPE_PRAIRI,           // 3
    TILE_TYPE_FORESTS,
    TILE_TYPE_HILLS,
    TILE_TYPE_MOUNTAINS,
    TILE_TYPE_TUNDRA,           // 7
    TILE_TYPE_ARTIC,
    TILE_TYPE_SWAMP,
    TILE_TYPE_JUNGLE,            // 10
    
    
    TILE_TYPE_MAXIMUM
};

enum
{
    TILE_IMPROVEMENT_IRRIGATED,
    TILE_IMPROVEMENT_FARM,
    TILE_IMPROVEMENT_MINE,
    TILE_IMPROVEMENT_ROAD
};

enum
{
    TILE_TERRAIN_NORMAL,
    TILE_TERRAIN_MOUNTAIN,
    TILE_TERRAIN_RIVER
};

struct  TerrainSpecification
{
    int         Type;
    int         Food;
    int         Shields;
    int         Gold;
    int         MoveCost;
    
    int         Food_Improvement;
    int         Shields_Improvement;
    int         Gold_Improvement;
};

extern UnitSpecification UnitSpecs[NUMBER_OF_UNIT_TYPES];
extern TerrainSpecification TerrainSpecs[TILE_TYPE_MAXIMUM];

void    InitializeUnitSpecs();
void    InitializeTerrainSpecs();

#endif	/* DATASETUP_H */

