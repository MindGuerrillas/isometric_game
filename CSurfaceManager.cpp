#include <string>

#include "CSurfaceManager.h"
#include "CDebugLogging.h"

CSurfaceManager   CSurfaceManager::SurfaceManager;

CSurfaceManager::CSurfaceManager()
{

}

bool CSurfaceManager::Initialize()
{   
    
    return true;
}

// Load a specified Surface
bool CSurfaceManager::Load(std::string File, bool alpha)
{    
    SDL_Surface* TempSurface = NULL;

    // Load Surface
    if((TempSurface = CSurface::Load(File, alpha)) == NULL)
        return false;
    
    Surfaces[File] = TempSurface;

    char msg[255];
    sprintf(msg,"Loading Surface: %s", File.c_str());  
    CDebugLogging::DebugLogging.Log(msg,0);
    
    return true;
}

bool CSurfaceManager::LoadExistingSurface(std::string ID, SDL_Surface* Src)
{
    if (Src == NULL)
        return false;
    
    Surfaces[ID] = Src;
    
    char msg[255];
    sprintf(msg,"Loading Surface: %s", ID.c_str());  
    CDebugLogging::DebugLogging.Log(msg,0);
    
    return true;
}

void CSurfaceManager::Tidy()
{
    for (SurfaceMap::const_iterator it = Surfaces.begin(); it != Surfaces.end(); ++it)
        SDL_FreeSurface(it->second);
    
    Surfaces.clear();
}

SDL_Surface* CSurfaceManager::GetSurface(std::string ID, bool alpha)
{    
    // Check is requested surface is already loaded. If not, do so
    if (Surfaces[ID] == NULL)
        if (Load(ID, alpha) == false) return NULL;
       
    return Surfaces[ID];
}
