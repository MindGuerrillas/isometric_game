
// Surface functions

#ifndef _CSURFACE_H_
    #define _CSURFACE_H_

#include <SDL.h>
#include <SDL_image.h>
#include <string>

int pygame_AlphaBlit(SDL_Surface *src, SDL_Rect *srcrect, 
                     SDL_Surface *dst, SDL_Rect *dstrect);

class CSurface 
{
    public:
        CSurface();

    public:
        static SDL_Surface* Load(std::string File, bool alpha);

        static bool             Draw(SDL_Surface* Surf_Dest, SDL_Surface* Surf_Src, int X, int Y);
        static bool             Draw(SDL_Surface* Surf_Dest, SDL_Surface* Surf_Src, int X, int Y, int X2, int Y2, int W, int H);
        static bool             Transparent(SDL_Surface* Surf_Dest, int R, int G, int B);        
        static Uint32           getpixel(SDL_Surface *surface, int x, int y);  
        static void             putpixel(SDL_Surface *surface, int x, int y, Uint32 pixel);
        static SDL_Surface*     mask_surface(SDL_Surface * pSrc, SDL_Surface * pMask, int mask_offset_x, int mask_offset_y);
        static SDL_Surface*     GetRectFromSurface(SDL_Surface* Src, SDL_Rect rect);
};

#endif
