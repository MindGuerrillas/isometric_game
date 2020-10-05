/* 
 * File:   CCivilization.h
 * Author: alan
 *
 * Created on March 12, 2013, 1:09 PM
 */

#ifndef CCIVILIZATION_H
#define	CCIVILIZATION_H

#include <string>
#include <vector>
#include "CUnit.h"
#include "CCity.h"

class CCivilization
{
    public:
        
        CCivilization();
        
        // PROPERTIES
        int             ID;
        std::string     Name;
        
        int Food;
        int Shields;
        int Gold;
        
        std::vector<CUnit*>      Units;          // List of Units
        std::vector<CCity*>      Cities;         // List of Cities
        
        CUnit*  SelectedUnit;
        CCity*  SelectedCity;
        
        // LOGIC
        void    Loop();      // Run all end of turn processes
        void    Render(SDL_Surface* SDisplay);
        void    Tidy();
        
        CUnit*  CreateUnit(UNIT_TYPE type, CCity* Home = NULL);
        CCity*  CreateCity(CTile* Tile);
        
        void    HarvestAndPay();
        
    private:
    
};



#endif	/* CCIVILIZATION_H */

