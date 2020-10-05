#ifndef _CGAME_H_
    #define _CGAME_H_

#include <vector>
#include <string>

#include "CState.h"
#include "Define.h"
#include "CSoundManager.h"
#include "CCamera.h"
#include "CCivilization.h"

class CGame : public CState 
{
    private:
        
        CGame();
        
        static CGame    Instance;
        
        SDL_Surface*    SDisplay;
        
        SDL_Surface*    SSidePanel;
        
        std::vector<CCivilization*>      Civilizations;  // List of Civilizations (players)
        
        void    UpdateUI();
        
    public:
        static CGame* GetInstance();
        
        CCivilization*  CurrentCivilization;
        
        int     GetNumberOfCivilizations();
        
        // EVENT HANDLING
        void    OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode);
        void    OnKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode);
        void    OnUser(Uint8 type, int code, void* data1, void* data2);             
        void    OnLButtonDown(int x, int y);
        void    OnRButtonDown(int x, int y);
        void    OnMouseMove(int mX, int mY, int relX, int relY, bool Left,bool Right,bool Middle);
        
        void    UnitActions(ACTION action);
        
        // GAME LOOP etc..
        bool    Activate(SDL_Surface* SDisp, int Options[] = NULL);
        void    DeActivate();
        void    Loop();
        void    Render();
        void    Tidy();        
        
        void    BeginNewTurn();
        void    EndOfTurn();
        
        // STATE SWITCHING
        void    GameOver();
        void    GameComplete();
        void    Reset();       
};

#endif
