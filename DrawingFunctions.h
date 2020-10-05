/* 
 * File:   DrawingFunctions.h
 * Author: alan
 *
 * Created on March 19, 2013, 4:02 PM
 */

#ifndef DRAWINGFUNCTIONS_H
#define	DRAWINGFUNCTIONS_H

#include "SDL.h"
#include "SDL_ttf.h"

void    WriteText(SDL_Surface* Surf_Dest, const char* text, TTF_Font* font, SDL_Color color, int X, int Y);
void    DrawLine(SDL_Surface *screen, int x1, int y1, int x2, int y2, unsigned int color);

#endif	/* DRAWINGFUNCTIONS_H */

