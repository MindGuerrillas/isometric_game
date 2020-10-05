#include "CCivilization.h"
#include <sstream>

CCivilization::CCivilization()
{
    SelectedUnit = NULL;
    SelectedCity = NULL;
}

void CCivilization::Loop()
{
    
}

void CCivilization::Render(SDL_Surface* SDisplay)
{
    // Print Units
    for (int unit = 0, len = Units.size(); unit < len; unit++)
        Units[unit]->Render(SDisplay);
    
    // Print Cities
    for (int city = 0, len = Cities.size(); city < len; city++)
        Cities[city]->Render(SDisplay);
}

CUnit* CCivilization::CreateUnit(UNIT_TYPE type, CCity* Home)
{
    // Can Unit be afforded
    if (Gold < UnitSpecs[type].Build_Cost)
        return NULL;
    else
        Gold -= UnitSpecs[type].Build_Cost;
    
    CUnit* unit = new CUnit;
    
    unit->Civilization = this;
    unit->Type = type;
    unit->Moves_Left = UnitSpecs[type].Moves;
    
    // Set to random location or Home City if Set
    if (Home)
        unit->Location = Home->Location; // Should set to a random tile
    else
    {
        CTile* Tile = NULL;
        
        while (!Tile)
        {            
            int RandomTileID = rand() % CMap::Map.GetNumberOfTiles();        
            Tile = CMap::Map.GetTileByID(RandomTileID);
            
            if (Tile)
                if (Tile->TileType == TILE_TYPE_WATER)
                    Tile = NULL;
        }
        
        unit->Location = Tile;
    }

    unit->Location->Unit = unit;
    
    unit->DiscoverMap();
    
    Units.push_back(unit);
    
    //CUnit* NewUnit = NULL;
    //NewUnit = &Units.back();
    
    return unit;
}

CCity* CCivilization::CreateCity(CTile* Tile)
{
        // Check for valid terrain
    if (Tile->TileType == TILE_TYPE_MOUNTAINS)
        return NULL;
    
    // Create a New City
    std::stringstream   Cityname;
    Cityname << "City " << Cities.size();
    
    CCity* City = new CCity;
    
    City->CityName = Cityname.str();
    City->Location = Tile;
    City->Civilization = this;
    City->Population = 100;

    // Claim all the tiles for your civilization
    std::vector<CTile*> land  = CMap::Map.GetTilesWithinDistanceFrom(Tile,City->Territory);
    
    for (int x = 0; x < land.size(); x++)
        land[x]->ControlledBy = this;
    
    land.clear();
    
    
    City->Location->City = City;
    
    Cities.push_back(City);
    
    // Recalculate City Borders
    CMap::Map.GenerateAutoBorders();
    
    return City;
}

void CCivilization::HarvestAndPay()
{
    // Per City
    for (int city = 0; city < Cities.size(); city++)
    {
        // Collect resources from surrounding tiles
        std::vector<CTile*> tiles = CMap::Map.GetTilesWithinDistanceFrom(Cities[city]->Location, Cities[city]->Territory);
        
        for (int tile = 0; tile < tiles.size(); tile++)
        {
            // Harvest Surrounding Tiles
            Gold += tiles[tile]->GetGold();
            Food += tiles[tile]->GetFood();
            Shields += tiles[tile]->GetShields();
        }
        
        tiles.clear();        
    }    
    
    // Pay for Units
    for (int unit = 0; unit < Units.size(); unit++)
    {
        Gold -= UnitSpecs[Units[unit]->Type].Upkeep_Cost_Gold;
        Shields -= UnitSpecs[Units[unit]->Type].Upkeep_Cost_Shields;
        Food -= UnitSpecs[Units[unit]->Type].Upkeep_Cost_Food;           
    }    
}

void CCivilization::Tidy()
{
    // Tidy Units
    for (std::vector<CUnit*>::iterator b = Units.begin(); b != Units.end();) 
    {        
        delete (*b);
        b = Units.erase( b ); // reseat iterator to a valid value post-erase                   
    } 
    
    // Tidy Cities
    for (std::vector<CCity*>::iterator b = Cities.begin(); b != Cities.end();) 
    {        
        delete (*b);
        b = Cities.erase( b ); // reseat iterator to a valid value post-erase                   
    }     
    
}