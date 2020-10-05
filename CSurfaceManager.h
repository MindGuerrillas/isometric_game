/* 
 * File:   CSurfaceManager.h
 * Author: alan
 *
 * Created on February 16, 2013, 2:13 PM
 */

#ifndef CSURFACEMANAGER_H
#define	CSURFACEMANAGER_H

#include <SDL.h>
#include "CSurface.h"
#include <tr1/unordered_map>

#define SURFACES_PATH         "./gfx/"

typedef std::tr1::unordered_map  <std::string, SDL_Surface*> SurfaceMap;

class CSurfaceManager
{
    public:
        CSurfaceManager();
        
        static CSurfaceManager    SurfaceManager;
        
        bool            Initialize();            
        void            Tidy();
        SDL_Surface*    GetSurface(std::string ID, bool alpha = true);
        
        bool            LoadExistingSurface(std::string ID, SDL_Surface* Src);
        
    private:
        bool            Load(std::string File, bool alpha);        
        
        SurfaceMap      Surfaces;    
};

#endif	/* CSURFACEMANAGER_H */

