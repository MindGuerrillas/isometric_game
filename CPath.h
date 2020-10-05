/* 
 * File:   CPath.h
 * Author: alan
 *
 * Created on March 15, 2013, 2:55 PM
 */

#ifndef CPATH_H
#define	CPATH_H

// Doubly-Linked List storing Path info

#include "CTile.h"

class CPathNode
{
    public:
        CPathNode();

        CTile*          Tile;
        CPathNode*      Previous;
        CPathNode*      Next;     
};

class CPath
{
    public:
        
        CPath();
        ~CPath();
                
        int     Length;
        
        CTile*          GetNextTile();
        CPathNode*      GetNextNode();
        CPathNode*      NewNode(CTile*  Tile);
        void            Prepend(CTile*  Tile);

        void            CompletedStep(); // Removes 1st node from list
        void            Tidy();
        
    private:
        CPathNode*      First;    
};

#endif	/* CPATH_H */

