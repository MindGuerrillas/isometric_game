/* 
 * File:   CFontsManager.h
 * Author: alan
 *
 * Created on March 19, 2013, 3:33 PM
 */

#ifndef CFONTSMANAGER_H
#define	CFONTSMANAGER_H

#include <SDL.h>
#include "SDL_ttf.h"
#include <string>
#include <tr1/unordered_map>

#define STANDARD_FONT           "./fonts/verdana.ttf"
#define STANDARD_FONT_BOLD      "./fonts/verdanab.ttf"

typedef std::tr1::unordered_map  <std::string, TTF_Font*> FontsMap;

class CFontsManager
{
    public:
        CFontsManager();
        
        static CFontsManager    FontsManager;
        
        bool            Initialize();        
        bool            Load(std::string File, int PointSize);            
        TTF_Font*       GetFont(std::string File, int PointSize);
        
        void    Tidy();
       
    private:
        FontsMap       Fonts;
};

#endif	/* CFONTSMANAGER_H */

