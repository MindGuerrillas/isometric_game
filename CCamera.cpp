
#include "CCamera.h"
#include "CMap.h"
#include "CFramerate.h"
#include "CTile.h"

CCamera CCamera::Camera;

CCamera::CCamera() 
{
    X = TILE_WIDTH / 2;
    Y = TILE_HEIGHT / 2;

    TargetX = NULL;
    TargetY = NULL;

    TargetMode = TARGET_MODE_NORMAL;
      
    ScrollTo = NULL;
}

// Moves camera by MoveX & MoveY
bool CCamera::OnMove(int MoveX, int MoveY) 
{
    CFramerate::FPSControl.ScreenIsDirty = true;
    
    int MapWidthPixels = CMap::Map.Width() * TILE_WIDTH;
    int MapHeightPixels = CMap::Map.Height() / 2 * TILE_HEIGHT;
    
    // don't move for small maps
    if ((MapWidthPixels < MAP_WIDTH) || (MapHeightPixels < MAP_HEIGHT))
        return false;
    
    X += MoveX;
    Y += MoveY;

    bool XMovePossible = true;
    bool YMovePossible = true;
    
    // Prevent seeing off screen    
    if (X < TILE_WIDTH / 2) X = TILE_WIDTH / 2, XMovePossible = false;
    if (Y < TILE_HEIGHT / 2) Y = TILE_HEIGHT / 2, YMovePossible = false;;
    if (X > (MapWidthPixels - MAP_WIDTH)) X = MapWidthPixels - MAP_WIDTH, XMovePossible = false;;
    if (Y > (MapHeightPixels - MAP_HEIGHT)) Y =  MapHeightPixels - MAP_HEIGHT, YMovePossible = false;;
        
    return XMovePossible && YMovePossible;
}

int CCamera::GetX() 
{
    return X;
}


int CCamera::GetY() 
{
    return Y;
}


void CCamera::SetPos(int X, int Y) 
{
    this->X = X;
    this->Y = Y;
}


void CCamera::SetTarget(float* X, float* Y) 
{
    TargetX = X;
    TargetY = Y;
}

bool CCamera::OnScreen(int objX, int objY)
{
    bool WithinX = false;
    bool WithinY = false;
    
    if (objX > (X - TILE_WIDTH) && objX < X + MAP_WIDTH + TILE_WIDTH)
        WithinX = true;
    
    if (objY > (Y - TILE_HEIGHT) && objY < Y + MAP_HEIGHT + TILE_HEIGHT)
        WithinY = true;
    
    return (WithinX && WithinY);     
}

void CCamera::ScrollToTarget(CTile* target)
{
    ScrollTo = target;
}

CTile* CCamera::GetScrollTarget()
{
    return ScrollTo;
}