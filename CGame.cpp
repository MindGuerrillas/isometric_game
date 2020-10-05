#include "CGame.h"
#include <string>
#include "CDebugLogging.h"
#include "CStateManager.h"
#include "CFramerate.h"
#include "CMap.h"
#include "DrawingFunctions.h"
#include "CFontsManager.h"

CGame CGame::Instance;

CGame::CGame()
{
    
}

void CGame::Render() 
{
    if (CFramerate::FPSControl.Framerate_Control())
    {  
        SDL_Rect Rect;
        Rect.x = 0;
        Rect.y = 0;
        Rect.w = WINDOW_WIDTH;
        Rect.h = WINDOW_HEIGHT;

        // Clear display
        SDL_FillRect(SDisplay, &Rect, 0x333333);
        
        // Print map to display
        CMap::Map.Render(-CCamera::Camera.GetX(), -CCamera::Camera.GetY());        
        
        // Print Civilizations to display
        for (int civs = 0, len = Civilizations.size(); civs < len; civs++)
            Civilizations[civs]->Render(CMap::Map.SMap);
        
        // Print UI
        UpdateUI();
        
        CSurface::Draw(SDisplay, CMap::Map.SMap, 0, 0);
        CSurface::Draw(SDisplay, SSidePanel, MAP_WIDTH, 0);
    }
}

void CGame::Tidy() 
{
    // Tidy Civs
    for (std::vector<CCivilization*>::iterator b = Civilizations.begin(); b != Civilizations.end();) 
    { 
        (*b)->Tidy();

        delete (*b);

        b = Civilizations.erase( b ); // reseat iterator to a valid value post-erase                   
    } 
    
    
    // Logging
    CDebugLogging::DebugLogging.Log("Game Closing - Tidying", 1); 

    CMap::Map.Tidy();
    
    SDL_FreeSurface(SSidePanel);
    
    // Close Debug Log if open
    CDebugLogging::DebugLogging.Tidy();
}

void CGame::Reset()
{    
    //InitializeEntities();
    
    CSoundManager::SoundManager.StopMusic();
    
    CDebugLogging::DebugLogging.Log("Game Reset", 1);    
}

CGame* CGame::GetInstance()
{
    return &Instance;
}

void CGame::GameOver()
{    
    CSoundManager::SoundManager.Play(FX_GAME_OVER);
    
    // Switch States and Show Level Transition Screen
    CStateManager::SetAppState(STATE_GAME_OVER, SDisplay);    
}

void CGame::GameComplete()
{    
    // Switch States and Show Level Transition Screen
    CStateManager::SetAppState(STATE_GAME_COMPLETE, SDisplay);    
}

int CGame::GetNumberOfCivilizations()
{
    return Civilizations.size();
}

void CGame::EndOfTurn()
{
    // Run Other Civs AI

    // Start a new turn
    BeginNewTurn();
}

void CGame::BeginNewTurn()
{    
    CFramerate::FPSControl.ScreenIsDirty = true;
    
    for (int x = 0, len = Civilizations.size(); x < len; x++)
    {
        CCivilization* civ = Civilizations[x];
        
        // Harvest & Pay
        civ->HarvestAndPay();
   
        // Update Display
        printf("GOLD: %d  FOOD: %d  SHIELDS: %d\n", civ->Gold, civ->Food, civ->Shields);
        
        // Reset all movement allowances           
        for (int y = 0, len2 = civ->Units.size(); y < len2; y++)
        {
            CUnit* cUnit = civ->Units[y];
            cUnit->Moves_Left = UnitSpecs[cUnit->Type].Moves;
            
            cUnit->FollowPath();                        
        }
        
    }
}

void CGame::UnitActions(ACTION action)
{
    if (CurrentCivilization->SelectedUnit)
    {
        CurrentCivilization->SelectedUnit->PerformAction(action);
    }
}

void CGame::UpdateUI()
{
    SDL_Rect Rect;
    Rect.x = 0;
    Rect.y = 0;
    Rect.w = SSidePanel->w;
    Rect.h = SSidePanel->h;

    // Clear display
    SDL_FillRect(SSidePanel, &Rect, 0x333333);
        
    TTF_Font* smallFont = CFontsManager::FontsManager.GetFont(STANDARD_FONT_BOLD, 12);    
    SDL_Color Color = {255, 255, 0};
    
    char gold[20];
    sprintf(gold,"GOLD: %d", CurrentCivilization->Gold);        
    WriteText(SSidePanel, gold, smallFont, Color, 10, 10);
    
    char shields[20];
    sprintf(shields,"SHIELDS: %d", CurrentCivilization->Shields);        
    WriteText(SSidePanel, shields, smallFont, Color, 10, 30);
    
    char food[20];
    sprintf(food,"FOOD: %d", CurrentCivilization->Food);        
    WriteText(SSidePanel, food, smallFont, Color, 10, 50);
    
    CFramerate::FPSControl.ScreenIsDirty = true;
}

