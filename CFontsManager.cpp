#include "CFontsManager.h"
#include <string>
#include <sstream>
#include "CDebugLogging.h"

CFontsManager   CFontsManager::FontsManager;

CFontsManager::CFontsManager()
{

}

bool CFontsManager::Initialize()
{
    if (TTF_Init() < 0)
        return false;
    
    CDebugLogging::DebugLogging.Log("Fonts Initialized", 1); 
    
    return true;
}

// Load a specified Font File
bool CFontsManager::Load(std::string File, int PointSize)
{
    TTF_Font* loadedFont;
    
    char msg[255];
    sprintf(msg,"Loading Font: %s at %dpx", File.c_str(), PointSize);  
    CDebugLogging::DebugLogging.Log(msg,0);
    
    if((loadedFont = TTF_OpenFont(File.c_str(),PointSize)) == NULL)
        return false;
 
    std::stringstream HashLabel;
    HashLabel << File << PointSize;
    
    Fonts[HashLabel.str()] = loadedFont;
    
    return true;
}

TTF_Font* CFontsManager::GetFont(std::string File, int PointSize)
{
    std::stringstream HashLabel;
    HashLabel << File << PointSize;
    
     // Check is requested font is already loaded. If not, do so
    if (Fonts[HashLabel.str()] == NULL)
        if (Load(File, PointSize) == false) return NULL;
       
    return Fonts[HashLabel.str()];
}

void CFontsManager::Tidy()
{
    for (FontsMap::const_iterator it = Fonts.begin(); it != Fonts.end(); ++it)
        TTF_CloseFont(it->second);
    
    Fonts.clear(); 
    
    TTF_Quit();
}
