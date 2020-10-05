#include "CPath.h"

CPath::CPath()
{    
    Length = 0;
    First = NULL;
}

CPathNode::CPathNode()
{
    Next = NULL;
    Previous = NULL;
    Tile = NULL;
}

CPath::~CPath()
{
    // Free any list
    while (First != NULL)
    {
        CPathNode* next = First->Next;
        delete First;
        First = next;
    }   
}

void CPath::Tidy()
{       
    // Free any list
    while (First != NULL)
    {
        CPathNode* next = First->Next;
        delete First;
        First = next;
    }
}


void CPath::CompletedStep()
{
    // Remember Next node
    CPathNode*  nextNode = First->Next;
    
    // Remove 1st Node
    if (First)
        delete First;
    
    First = nextNode;
    
    if (First)
        First->Previous = NULL;
    
    Length--;
}

CPathNode* CPath::NewNode(CTile* Tile)
{
    CPathNode* node = new CPathNode;
    node->Tile = Tile;
    
    node->Next = NULL;
    node->Previous = NULL;
	
    return node;        
}

void CPath::Prepend(CTile* Tile)
{
    CPathNode* ptr = NewNode(Tile);
    
    if (First)
    {
        First->Previous = ptr;
        ptr->Next = First;
    }
    First = ptr;  
    
    Length++;
}

CTile*  CPath::GetNextTile()
{
    return First->Tile;
}

CPathNode* CPath::GetNextNode()
{
    return First;
}