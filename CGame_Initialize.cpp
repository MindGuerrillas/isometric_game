#include "CGame.h"
#include "CDebugLogging.h"
#include "CUnit.h"
#include <string>
#include <algorithm>
#include "CFramerate.h"
#include "CMap.h"
#include "CProblem.h"
#include "CPathFindingStateSpace.h"
#include "CPathFindingProblem.h"

bool CGame::Activate(SDL_Surface* SDisp, int Options[]) 
{    
    SDisplay = SDisp;
    
    SSidePanel = SDL_CreateRGBSurface(SDL_HWSURFACE, WINDOW_WIDTH - MAP_WIDTH, WINDOW_HEIGHT, 32,
                                        SDisplay->format->Rmask, SDisplay->format->Gmask, SDisplay->format->Bmask, SDisplay->format->Amask);
    
    // Load Unit Details
    InitializeUnitSpecs();
    InitializeTerrainSpecs();
    
    // Create a 1st Civilization
    CCivilization* Civ = new CCivilization;
    Civ->Name = "Romans";
    Civ->ID = 0;
    
    Civ->Food = 10;
    Civ->Gold = 1000;
    Civ->Shields = 100;
    
    Civilizations.push_back(Civ);
    
    // Get a ref to the new Civ
    CurrentCivilization = Civ;
    
    // Load The Map
    CMap::Map.Load("./maps/newmap.map");
    
    
    // Give Civ a starter unit - Settler
    CurrentCivilization->CreateUnit(SETTLER);
    
    CurrentCivilization->CreateUnit(WORKER);
    
    // Reset the Framerate to avoid big difference in FPS between States
    CFramerate::FPSControl.Reset();
    
    return true;
}

void CGame::DeActivate()
{
    Tidy();
}

