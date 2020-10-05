/* 
 * File:   CState.h
 * Author: alan
 *
 * Created on December 24, 2012, 2:34 PM
 */

#ifndef CSTATE_H
#define	CSTATE_H

#include "CEvent.h"
#include "CSurface.h"
#include <SDL_ttf.h>

class CState : public CEvent
{
    public:
        CState();

        virtual bool Activate(SDL_Surface* SDisp, int Options[] = NULL) = 0;
        virtual void DeActivate() = 0;
        virtual void Loop() = 0;
        virtual void Render() = 0;
    
};


#endif	/* CSTATE_H */

