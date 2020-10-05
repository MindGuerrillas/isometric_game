/* 
 * File:   CBinaryHeap.h
 * Author: alan
 *
 * Created on March 8, 2013, 1:50 PM
 */

#ifndef CBINARYHEAP_H
#define	CBINARYHEAP_H

bool BinaryHeapMinPush(int a, int b); // Default Sort Order
bool BinaryHeapMaxPush(int a, int b);
bool BinaryHeapMinPop(int node, int arraysize, int val, int targetvalue); // Default Sort Order
bool BinaryHeapMaxPop(int node, int arraysize, int val, int targetvalue);

class CBinaryHeap
{
    public:
        CBinaryHeap();
        
        bool    Initialize(int arraysize);
        
        void    PushNode(int value, bool (*comparison)(int, int) = BinaryHeapMinPush);
        
        int     PopNode(bool (*comparison)(int, int, int, int) = BinaryHeapMinPop);
        
        int     GetSize();
        
        void    Tidy();
    private:
    
        int     Parent(int node);
        int     Child(int node); // Also Child + 1
        
        int     *array;
        int     SizeOfArray;
};

#endif	/* CBINARYHEAP_H */

