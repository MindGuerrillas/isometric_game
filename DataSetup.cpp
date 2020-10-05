#include "DataSetup.h"

UnitSpecification       UnitSpecs[NUMBER_OF_UNIT_TYPES];
TerrainSpecification    TerrainSpecs[TILE_TYPE_MAXIMUM];

void InitializeUnitSpecs()
{
    // Load Unit Details
    
    // WORKER
    UnitSpecs[WORKER].UnitType                  = WORKER;
    UnitSpecs[WORKER].Gfx                       = 54;
    UnitSpecs[WORKER].XOffset                   = 8;
    UnitSpecs[WORKER].YOffset                   = -10;
    UnitSpecs[WORKER].Build_Cost                = 40;  // SHIELDS
    UnitSpecs[WORKER].Upkeep_Cost_Food          = 1;
    UnitSpecs[WORKER].Upkeep_Cost_Shields       = 1;
    UnitSpecs[WORKER].Upkeep_Cost_Gold          = 0;
    UnitSpecs[WORKER].Moves                     = 1;
    UnitSpecs[WORKER].Vision_Radius             = 2;
    UnitSpecs[WORKER].Firepower                 = 1;
    UnitSpecs[WORKER].HP                        = 20;
    
    // SETTLER
    UnitSpecs[SETTLER].UnitType                  = SETTLER;
    UnitSpecs[SETTLER].Gfx                       = 24;
    UnitSpecs[SETTLER].XOffset                   = 8;
    UnitSpecs[SETTLER].YOffset                   = -10;
    UnitSpecs[SETTLER].Build_Cost                = 40;
    UnitSpecs[SETTLER].Upkeep_Cost_Food          = 1;
    UnitSpecs[SETTLER].Upkeep_Cost_Shields       = 1;
    UnitSpecs[SETTLER].Upkeep_Cost_Gold          = 0;
    UnitSpecs[SETTLER].Moves                     = 2;
    UnitSpecs[SETTLER].Vision_Radius             = 2;
    UnitSpecs[SETTLER].Firepower                 = 1;
    UnitSpecs[SETTLER].HP                        = 20;    
}

void InitializeTerrainSpecs()
{
    TerrainSpecs[TILE_TYPE_GRASS].Type          = TILE_TYPE_GRASS;
    TerrainSpecs[TILE_TYPE_GRASS].Food          = 2;
    TerrainSpecs[TILE_TYPE_GRASS].Shields       = 0;
    TerrainSpecs[TILE_TYPE_GRASS].Gold         = 0;
    TerrainSpecs[TILE_TYPE_GRASS].MoveCost      = 1;    
    TerrainSpecs[TILE_TYPE_GRASS].Food_Improvement      = 1;  
    TerrainSpecs[TILE_TYPE_GRASS].Gold_Improvement      = 1;  
    TerrainSpecs[TILE_TYPE_GRASS].Shields_Improvement      = 1;  
    
    
    TerrainSpecs[TILE_TYPE_DESERT].Type          = TILE_TYPE_DESERT;
    TerrainSpecs[TILE_TYPE_DESERT].Food          = 0;
    TerrainSpecs[TILE_TYPE_DESERT].Shields       = 1;
    TerrainSpecs[TILE_TYPE_DESERT].Gold         = 0;
    TerrainSpecs[TILE_TYPE_DESERT].MoveCost      = 1;
    TerrainSpecs[TILE_TYPE_DESERT].Food_Improvement      = 1;  
    TerrainSpecs[TILE_TYPE_DESERT].Gold_Improvement      = 1;  
    TerrainSpecs[TILE_TYPE_DESERT].Shields_Improvement      = 1; 
    
    TerrainSpecs[TILE_TYPE_FORESTS].Type         = TILE_TYPE_FORESTS;
    TerrainSpecs[TILE_TYPE_FORESTS].Food         = 1;
    TerrainSpecs[TILE_TYPE_FORESTS].Shields      = 2;
    TerrainSpecs[TILE_TYPE_FORESTS].Gold        = 0;
    TerrainSpecs[TILE_TYPE_FORESTS].MoveCost     = 2;
    TerrainSpecs[TILE_TYPE_FORESTS].Food_Improvement      = 0;  
    TerrainSpecs[TILE_TYPE_FORESTS].Gold_Improvement      = 0;  
    TerrainSpecs[TILE_TYPE_FORESTS].Shields_Improvement      = 0; 
    
    TerrainSpecs[TILE_TYPE_HILLS].Type         = TILE_TYPE_HILLS;
    TerrainSpecs[TILE_TYPE_HILLS].Food         = 1;
    TerrainSpecs[TILE_TYPE_HILLS].Shields      = 0;
    TerrainSpecs[TILE_TYPE_HILLS].Gold        = 0;
    TerrainSpecs[TILE_TYPE_HILLS].MoveCost     = 2;
    TerrainSpecs[TILE_TYPE_HILLS].Food_Improvement      = 1;  
    TerrainSpecs[TILE_TYPE_HILLS].Gold_Improvement      = 0;  
    TerrainSpecs[TILE_TYPE_HILLS].Shields_Improvement      = 3; 
    
    TerrainSpecs[TILE_TYPE_MOUNTAINS].Type         = TILE_TYPE_MOUNTAINS;
    TerrainSpecs[TILE_TYPE_MOUNTAINS].Food         = 0;
    TerrainSpecs[TILE_TYPE_MOUNTAINS].Shields      = 1;
    TerrainSpecs[TILE_TYPE_MOUNTAINS].Gold        = 0;
    TerrainSpecs[TILE_TYPE_MOUNTAINS].MoveCost     = 3;
    TerrainSpecs[TILE_TYPE_MOUNTAINS].Food_Improvement      = 0;  
    TerrainSpecs[TILE_TYPE_MOUNTAINS].Gold_Improvement      = 0;  
    TerrainSpecs[TILE_TYPE_MOUNTAINS].Shields_Improvement      = 1;   
    
    TerrainSpecs[TILE_TYPE_WATER].Type         = TILE_TYPE_WATER;
    TerrainSpecs[TILE_TYPE_WATER].Food         = 1;
    TerrainSpecs[TILE_TYPE_WATER].Shields      = 0;
    TerrainSpecs[TILE_TYPE_WATER].Gold        = 2;
    TerrainSpecs[TILE_TYPE_WATER].MoveCost     = 0;
    TerrainSpecs[TILE_TYPE_WATER].Food_Improvement      = 0;  
    TerrainSpecs[TILE_TYPE_WATER].Gold_Improvement      = 0;  
    TerrainSpecs[TILE_TYPE_WATER].Shields_Improvement      = 0; 
}