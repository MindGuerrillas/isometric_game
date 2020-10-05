#include "CMap.h"
#include "CSurfaceManager.h"
#include "CCamera.h"
#include "CTilesetManager.h"
#include <fstream>
#include <sstream>
#include "CTile.h"
#include "CGame.h"
#include "DrawingFunctions.h"

CMap    CMap::Map;

CMap::CMap()
{
    AutoCoast = true;
    ShowGrid = true;
    MapHeight = 0;
    MapWidth = 0;   
    PathCalculated = false;
}

void CMap::Load(std::string Map)
{
    // Read & Load Map file
    std::string line;
    std::ifstream  mapfile (Map.c_str());
    
    if (!mapfile.is_open())
        return;
    
    int TileCounter = 0;
    
    while(getline(mapfile, line))
    {
        // split line by ' ' SPACE
        std::stringstream ss(line);        
        std::string tiledata;
        
        while(getline(ss,tiledata, ' '))
        {
            // Split data by : into Tile Type & Special Terrain
            
            std::stringstream sstile(tiledata); 
            std::string tiletype;
            std::string tilespecialterrain;
            
            getline(sstile,tiletype,':');
            getline(sstile,tilespecialterrain,':');
            
            // Load Tile
            CTile tile;
            tile.TileType = atoi(tiletype.c_str());
            tile.SpecialTerrain = atoi(tilespecialterrain.c_str());
            
            tile.ID = TileCounter;             
            tile.Seed = rand() % 3;
            tile.TileTerrainIndex = rand() % NUMBER_TERRAIN_TILES;
            
            TileList.push_back(tile);
            
            TileCounter++;
            
            if (MapHeight == 0)
                MapWidth++;
        }
                
        MapHeight++;
    }
               
    // Calculate X & Y positions for Tiles
    for (int id=0, len=TileList.size(); id < len; id++)
    {
        int X = id % MapWidth;
        int Y = id / MapWidth;
        int XOffSet;
        
        // Offset row by TILE_WIDTH/2 on even rows        
        if (Y % 2 == 0) // it's EVEN       
            XOffSet = 0;                                  
        else // it's ODD        
            XOffSet = TILE_WIDTH / 2;
                
        int tileX = (X * TILE_WIDTH) + XOffSet;
        int tileY = Y * TILE_HEIGHT/2;
        
        TileList[id].X = tileX;
        TileList[id].Y = tileY;
        TileList[id].XGridPos = X;
        TileList[id].YGridPos = Y;
    }
        
    // Generate AutoCoast & AutoTerrain Info for Tiles;
    for (int id=0, len=TileList.size(); id < len; id++)
    {
        GenerateAutoCoast(&TileList[id]);                
        GenerateAutoTerrain(&TileList[id]);        
    }
    
    mapfile.close();    
}

void CMap::Render(int MapX, int MapY)
{ 
    SDL_Rect Rect;
    Rect.x = 0;
    Rect.y = 0;
    Rect.w = MAP_WIDTH;
    Rect.h = MAP_HEIGHT;

    // Clear display
    SDL_FillRect(SMap, &Rect, 0x000000);
        
    int ID = 0;

    for (int y = 0; y < MapHeight; y++)
    {
        for (int x = 0; x < MapWidth; x++)
        {                
            // Get Current Tile
            CTile* tile = GetTileByID(ID);
            
            tile->Render(SMap, MapX, MapY);
            
            ID++;
        }
    }
    
    RenderBorders(MapX, MapY);
    RenderPath(MapX, MapY);
    
    PathCalculated = false;
}

void CMap::RenderBorders(int MapX, int MapY)
{
    int BorderOffsets[4][2] = {{TILE_WIDTH / 2, 0}, {TILE_WIDTH / 2, TILE_HEIGHT / 2}, {0, TILE_HEIGHT / 2}, {0, 0}};
    
    // Draw Borders
    for (int x = 0, len = TileList.size(); x < len; x++)
    {
        CTile* Tile = GetTileByID(x);
        
        if (Tile == NULL)
            continue;
        
        if (CCamera::Camera.OnScreen(Tile->X, Tile->Y))
        {
            int screen_tileX = MapX + Tile->X;
            int screen_tileY = MapY + Tile->Y;
        
            if (Tile->Borders > 0)
            {        
                int counter = 0;
                
                for (int dir = 1; dir <= 8; dir <<= 1)
                {
                    if (Tile->Borders & dir)
                    {
                        // draw border
                        CSurface::Draw( SMap, CSurfaceManager::SurfaceManager.GetSurface(BORDER_GFX), 
                                    screen_tileX + BorderOffsets[counter][0], screen_tileY + BorderOffsets[counter][1],
                                    BorderOffsets[counter][0], BorderOffsets[counter][1], TILE_WIDTH / 2, TILE_HEIGHT /2);
                    }
                    
                    counter++;
                }
            }    
        }
    }
}

void CMap::RenderPath(int MapX, int MapY)
{
    // Display any currently calculated path
    if (CurrentPath)
    {
        // Display Path
        CPathNode* currentNode = CurrentPath->GetNextNode();

        while (currentNode)
        {                
            CPathNode* nextNode = currentNode->Next;

            if (nextNode)
            {
                int TileX = (MapX + currentNode->Tile->X) + (TILE_WIDTH / 2);
                int TileY = (MapY + currentNode->Tile->Y) + (TILE_HEIGHT / 2);

                int nextTileX = (MapX + nextNode->Tile->X) + (TILE_WIDTH / 2);
                int nextTileY = (MapY + nextNode->Tile->Y) + (TILE_HEIGHT / 2);

                DrawLine(SMap, TileX, TileY, nextTileX, nextTileY, 0xff0000); 

            }

            currentNode = nextNode;
        }
    }      
}

int CMap::Height()
{
    return MapHeight;
}

int CMap::Width()
{
    return MapWidth;
}

void CMap::Tidy()
{
    TileList.clear();
    CTilesetManager::TilesetManager.Tidy();
    
    SDL_FreeSurface(SMap);
}

int CMap::GetTileIDFromGridPos(int X, int Y)
{
    return (MapWidth * Y) + X;
}

CTile* CMap::GetTileByCoord(int X, int Y) 
{
    SDL_Surface* MouseMap = CSurfaceManager::SurfaceManager.GetSurface(MOUSEMAP_GFX);
    
    static bool ColoursLoaded = false;
    
    if (!ColoursLoaded)
    {
        red = SDL_MapRGB(MouseMap->format, 255, 0, 0);
        yellow = SDL_MapRGB(MouseMap->format, 255, 255, 0);
        white = SDL_MapRGB(MouseMap->format, 255, 255, 255);
        green = SDL_MapRGB(MouseMap->format, 0, 255, 0);
        blue = SDL_MapRGB(MouseMap->format, 0, 0, 255);
        ColoursLoaded = true;
    }
    
    int MapX = X + CCamera::Camera.GetX();
    int MapY = Y + CCamera::Camera.GetY();;
    
    int RegionX = MapX / TILE_WIDTH;
    int RegionY = (MapY / TILE_HEIGHT) * 2;    
    
    int MouseMapX = MapX % TILE_WIDTH;
    int MouseMapY = MapY % TILE_HEIGHT;
 
    // Get Colour in MouseMap @ MouseMapX,MouseMapY
    int PixelColour = CSurface::getpixel(MouseMap, MouseMapX, MouseMapY);

    int RegionDX = 0;
    int RegionDY = 0;
 
    if (PixelColour == red)
    {
        RegionDX = -1;
        RegionDY = -1;
    }else if (PixelColour == yellow)
    {
        RegionDX = 0;
        RegionDY = -1;
    }else if (PixelColour == white)
    {
        RegionDX = 0;
        RegionDY = 0;
    }else if (PixelColour == green)
    {
        RegionDX = -1;
        RegionDY = 1;
    }else if (PixelColour == blue)
    {
        RegionDX = 0;
        RegionDY = 1;
    }
    
    unsigned int ID = (MapWidth * (RegionY + RegionDY)) + (RegionX + RegionDX);
    
    if(ID < 0 || ID >= TileList.size())
    	return NULL;
    
    return &TileList[ID];
}

CTile* CMap::GetTileByGridPos(int X, int Y)
{
    int ID = GetTileIDFromGridPos(X, Y);
    
    if (ID >= TileList.size())
        return NULL;
    else
        return &TileList[ID];
}

CTile* CMap::GetTileByID(int ID)
{
    if (ID < 0 || ID > GetNumberOfTiles())
        return NULL;
    
    return &TileList[ID];
}

int CMap::GetDirectionToTile(CTile* From, CTile* To)
{        
    for (int x = 0; x < NUMBER_OF_DIRECTIONS; x++)
        if (GetTileByDirection(From, x) == To)
            return x;
    
    return -1;
}

CTile* CMap::GetTileByDirection(CTile* Tile, int Direction)
{
    int TileY, TileX;
    
    switch(Direction)
    {
        case NORTH:
            TileX = Tile->XGridPos;
            TileY = Tile->YGridPos - 2;
            break;
            
        case NORTH_EAST: // if EVEN
            TileX = Tile->XGridPos + ((Tile->YGridPos % 2 == 0) ? 0 : 1);
            TileY = Tile->YGridPos - 1;
            break;
            
        case EAST:
            TileX = Tile->XGridPos + 1;
            TileY = Tile->YGridPos;
            break;
            
        case SOUTH_EAST: // if EVEN
            TileX = Tile->XGridPos + ((Tile->YGridPos % 2 == 0) ? 0 : 1);
            TileY = Tile->YGridPos + 1;
            break;
            
        case SOUTH:
            TileX = Tile->XGridPos;
            TileY = Tile->YGridPos + 2;
            break;
            
        case SOUTH_WEST: // if EVEN
            TileX = Tile->XGridPos + ((Tile->YGridPos % 2 == 0) ? -1 : 0);
            TileY = Tile->YGridPos + 1;
            break;

        case WEST:
            TileX = Tile->XGridPos - 1;
            TileY = Tile->YGridPos;
            break;
            
        case NORTH_WEST: // if EVEN
            TileX = Tile->XGridPos + ((Tile->YGridPos % 2 == 0) ? -1 : 0);
            TileY = Tile->YGridPos - 1;
            break;                   
    }
    
    if (TileX < 0 || TileY < 0)
        return NULL;
    
    return GetTileByGridPos(TileX, TileY);
}

void CMap::GenerateAutoCoast(CTile* Tile)
{
    if (Tile == NULL)
        return;
    
    // Is this Tile an Ocean Tile. If so find if it is next to land. If so, in which direction   
    if (Tile->TileType != TILE_TYPE_WATER)
        return;
    
    // Split Tile into 4 (N,S,E,W) & Check each for Land
    
    int ID = 0;
    int counter  = 0;
    bool LandFound = false;
        
    for (int direction = 0; direction < NUMBER_OF_DIRECTIONS; direction +=2)
    {
        ID = 0;
        counter = 0;
        
        for (int d2 = (direction - 1); d2 <= (direction + 1); d2++)
        {
            int d3 = (d2 < 0) ? NUMBER_OF_DIRECTIONS - 1: d2;
            
            CTile* nextTile = NULL;
            nextTile = GetTileByDirection(Tile, d3);
            
            if (nextTile)                                        
                if (nextTile->TileType != TILE_TYPE_WATER)
                {
                   ID |= 1 << counter;
                   LandFound = true;
                }
            
            counter++;
        }  
      
        Tile->CoastMap[direction / 2] = ID;
    }
    
    // River Mouths
    if (LandFound)
    {
        // Check for Rivers on diagonals
        counter = 0;
        for (int x = 1; x < NUMBER_OF_DIRECTIONS; x += 2)
        {
            CTile* nextTile = GetTileByDirection(Tile, x);
            
            if (nextTile == NULL)
                continue;
            
            if (nextTile->SpecialTerrain == RIVER_TILE)
            {
                Tile->RiverMouth = counter;
                break;
            }
            
            counter++;
        }
    }
    
    Tile->HasCoast = LandFound;    
}

int CMap::GetNumberOfTiles()
{
    return MapWidth * MapHeight;
}

void CMap::GenerateAutoTerrain(CTile* Tile)
{
    // Check Diagonal Tiles for Tiles of same terrain Type. 
    // Calculate a number from 0 -> 15
    
    int ID = 0;
    int counter = 0;
    
    for (int x = 1; x < NUMBER_OF_DIRECTIONS; x += 2)
    {
        CTile* checkTile = NULL;
        checkTile = GetTileByDirection(Tile,x);
        
        if (checkTile != NULL) // No Tile Available so set to 0 (ignore it);  
        {
            // Tile Blending Info
            if (checkTile->TileType == Tile->TileType || Tile->TileType == TILE_TYPE_WATER)
                Tile->SurroundingTiles[counter] = -1;  // No blending needed
            else if (checkTile->TileType == TILE_TYPE_WATER)
                Tile->SurroundingTiles[counter] = TILE_TYPE_GRASS;
            else
                Tile->SurroundingTiles[counter] = checkTile->TileType;
            
            // RIVERS
            if (Tile->SpecialTerrain == RIVER_TILE)
            {                
                if ((Tile->SpecialTerrain == checkTile->SpecialTerrain) || (checkTile->TileType == TILE_TYPE_WATER))
                    ID |= 1 << counter;
                           
            }else if (Tile->TileType == checkTile->TileType)
                ID |= 1 << counter;
        }else
            Tile->SurroundingTiles[counter] = -1;
        
        counter++;
    }
      
    Tile->TileTerrainIndex = ID;
}

void CMap::GenerateAutoBorders()
{
    for (int id=0, len=TileList.size(); id < len; id++)
    {
        CTile* Tile = GetTileByID(id);
        
        if (Tile == NULL)
            continue;

        // If this tile isn't controlled by someone ignore it - no borders
        if (Tile->ControlledBy == NULL)
            continue;

        int counter = 0;
        int borders = 0;

        for (int direction = 1; direction < NUMBER_OF_DIRECTIONS; direction +=2)
        {            
            CTile* nextTile = GetTileByDirection(Tile, direction);

            if (nextTile)                                        
                if (nextTile->ControlledBy != Tile->ControlledBy)
                   borders |= 1 << counter;

            counter++;       
        }

        Tile->Borders = borders;    
    }
}

std::vector<CTile*> CMap::GetTilesWithinDistanceFrom(CTile* From, int Distance, bool BorderOnly)
{
    std::vector<CTile*> TileList;
    
    int Multiplier;
    int Counter = 2;
    
    if (From->YGridPos % 2)
        Multiplier = -1;
    else
        Multiplier = 1;
    
    for (int xSteps = 0, len = 1 + (Distance * 2); xSteps < len; xSteps++)
    {
        if (Counter == 0)  // Reduce Distance every 2 passes
        {
            Distance--;  
            if (Distance < 0) Distance = 0;
            Counter = 2;
        }
        
        int currentX = From->XGridPos + (Distance * Multiplier);
        
        for (int y = -xSteps; y <= xSteps; y++)
        {
            CTile* tile = CMap::Map.GetTileByGridPos(currentX, From->YGridPos + y);
            
            if (tile)
            {
                // Do Stuff                 
                if (BorderOnly) // Return only the border tiles
                {
                    if ((y < (-xSteps + 2)) || (y > xSteps - 2))
                        TileList.push_back(tile);
                }else
                    TileList.push_back(tile);
            }
        }
        
        Counter--;
        Multiplier = -Multiplier;        
    }  
    
    return TileList;
}