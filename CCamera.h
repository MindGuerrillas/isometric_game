
#ifndef _CCAMERA_H_
    #define _CCAMERA_H_

#include <SDL.h>
#include "Define.h"
#include "CMap.h"

#define CAMERA_SCROLL_INC       2

enum 
{
    TARGET_MODE_NORMAL = 0,
    TARGET_MODE_CENTER
};

class CCamera 
{
    public:
        static CCamera Camera;
        int TargetMode;         
        
    private:
        int X;
        int Y;

        float* TargetX;
        float* TargetY;

        CTile*     ScrollTo;       
        
    public:
        CCamera();
        
        bool OnMove(int MoveX, int MoveY);
        
        int GetX();
        int GetY();
        void SetPos(int X, int Y);
        void SetTarget(float* X, float* Y);
        
        void            ScrollToTarget(CTile* target);
        CTile*          GetScrollTarget();        
        
        bool OnScreen(int objX, int objY);        
};

#endif
