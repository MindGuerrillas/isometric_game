#include "CBinaryHeap.h"
#include <utility>
#include <cstdio>
#include <algorithm>

bool BinaryHeapMaxPush(int a, int b)
{
    return (a > b);
}

bool BinaryHeapMinPush(int a, int b)
{
    return (a < b);
}

bool BinaryHeapMinPop(int node, int arraysize, int val, int targetvalue)
{
   return ((node <= arraysize) && val < targetvalue);
}

bool BinaryHeapMaxPop(int node, int arraysize, int val, int targetvalue)
{
   return ((node <= arraysize) && val > targetvalue);
}

CBinaryHeap::CBinaryHeap()
{
    SizeOfArray = 0;
    array = NULL;
}

bool CBinaryHeap::Initialize(int arraysize)
{
    // Delete any existing array
    if (array)
        delete [] array;
        
    // Load up array space
    array = new int[arraysize + 1];
    
    SizeOfArray = 0;
    
    if (array == NULL)
        return false;
    
    return true;
}

void CBinaryHeap::PushNode(int value, bool (*comparison)(int, int))
{
    if (array == NULL)
    {
        printf("ERROR: Binary Heap not initialized\n");
        return;
    }
    
    SizeOfArray++;
    
    // Add value to array;
    int CurrentIndex = SizeOfArray;
    
    array[CurrentIndex] = value;
    
    int ParentIndex = Parent(CurrentIndex);
    
    if (ParentIndex == 0)
        return;
    
    // Shuffle
    //while (array[CurrentIndex] < array[ParentIndex])
    while (comparison(array[CurrentIndex], array[ParentIndex]))
    {
        // Swap
        std::swap(array[CurrentIndex], array[ParentIndex]);
        
        CurrentIndex = ParentIndex;
        ParentIndex = Parent(CurrentIndex);
        
        if (CurrentIndex == 1) // It's reached the top
            break;
    }
    
    return;
}

int CBinaryHeap::PopNode(bool (*comparison)(int, int, int, int))
{
    if (SizeOfArray < 1)
        return -1;
    
    // Read top value and re-order array;
    int val = array[1];
    
    // Swap with Last
    array[1] = array[SizeOfArray];
    array[SizeOfArray] = 0;
    SizeOfArray--;
    
    // Reorder
    int node = 1;
    
    while (true)
    {
        int leftChild = Child(node);
        int rightChild = Child(node) + 1;
        int Smallest = node;

        if (leftChild <= SizeOfArray)
            if (comparison(leftChild, SizeOfArray, array[leftChild], array[Smallest]))
                Smallest = leftChild;

        if (rightChild <= SizeOfArray)
            if (comparison(rightChild, SizeOfArray, array[rightChild], array[Smallest]))
                Smallest = rightChild;

        if (Smallest != node)
        {
            std::swap(array[node], array[Smallest]);
            node = Smallest;
        }else
            break;
    }
    
    return val;
}

int CBinaryHeap::Child(int node)
{
    return node * 2;
}

int CBinaryHeap::Parent(int node)
{
    return (int)(node / 2);
}

int CBinaryHeap::GetSize()
{
    return SizeOfArray;
}

void CBinaryHeap::Tidy()
{
    if (array)
    {
        delete [] array;
        array = NULL;
    }
}