#include "DrawingFunctions.h"
#include "CSurface.h"
#include <cmath>

void WriteText(SDL_Surface* Surf_Dest, const char* text, TTF_Font* font, SDL_Color color, int X, int Y)
{
    SDL_Surface* fontsurface = TTF_RenderText_Blended(font, text, color);
    CSurface::Draw(Surf_Dest, fontsurface, X, Y);    
    SDL_FreeSurface(fontsurface);
}

void DrawLine(SDL_Surface* screen, int x1, int y1, int x2, int y2, unsigned int color)
{
    double x = x2 - x1;
    double y = y2 - y1;
    double length = sqrt( x*x + y*y );

    double addx = x / length;
    double addy = y / length;

    x = x1;
    y = y1;

    for(double i = 0; i < length; i += 1)
    {
      CSurface::putpixel(screen,(int)x, (int)y, color );
      x += addx;
      y += addy;
    }
}