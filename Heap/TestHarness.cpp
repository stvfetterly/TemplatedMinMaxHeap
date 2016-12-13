// Heap.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Heap.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

int main()
{
	srand( static_cast<unsigned int>( time(NULL) ) );

	//TEST BASIC MAX_HEAP FUNCTIONS
	//Create a MAX_HEAP
	Heap<int> myMaxHeap( Heap<int>::MAX_HEAP );
	cout << "Created a MAX heap with max value of: NULL and a size of: " << myMaxHeap.size()<< endl;
	
	//Insert ten nodes
	cout << "Inserting: ";
	for (int i = 0; i < 10; i++)
	{
		int j = rand() % 100;
		myMaxHeap.Insert(j);
		cout << " " << j;
	}

	//Print the highest value of the heap
	cout << endl << "MAX heap now has max value of: " << *(myMaxHeap.getFirst()) << " and a size of: " << myMaxHeap.size() << endl;

	//Delete max value
	cout << "Deleting first value";
	myMaxHeap.deleteFirst();
	cout << endl << "MAX heap now has max value of: " << *(myMaxHeap.getFirst()) << " and a size of: " << myMaxHeap.size() << endl;


	system("pause");





	//TEST BASIC MIN_HEAP FUNCTIONS
	//Create a MIN_HEAP with ten nodes
	int myArray[10] = { 9, 99, 8, 88, 7, 77, 6, 66, 5, 55 };
	Heap<int> myMinHeap(myArray, 10, Heap<int>::MIN_HEAP);
	cout << "Creating MIN heap with: 9, 99, 8, 88, 7, 77, 6, 66, 5, 55" << endl;

	//Print the lowest value of the heap
	cout << "MIN heap min value is: "<< *(myMinHeap.getFirst()) <<" and size is: " << myMinHeap.size() << endl;

	//Delete the lowest value node
	myMinHeap.deleteFirst();
	cout << "MIN heap min value after deletion is: " << *(myMinHeap.getFirst()) << " and a size of: " << myMinHeap.size() << endl;

	//Delete all nodes
	cout << "Deleting: ";
	while (myMinHeap.size() > 0)
	{
		cout << *(myMinHeap.getFirst()) << " ";
		myMinHeap.deleteFirst();
	}
	cout << endl;

	if (myMinHeap.getFirst() == NULL)
	{
		cout << "NULL value in heap of size: " << myMinHeap.size();
	}
	cout << endl;



	//TEST OVERRIDES
	//Create a third heap via copy constructor
	Heap<int> myMaxHeap2(myMaxHeap);
	cout << "MAX heap 2 from copy constructor size: " << myMaxHeap2.size() << endl;

	//Test assignment operator
	myMinHeap = myMaxHeap;
	cout << "MIN heap now a MAX heap with size: " << myMinHeap.size() << endl;

	//Add heaps one and two together


	myMaxHeap = myMaxHeap + myMaxHeap2;
	cout << "After adding to myMaxHeap2, myMaxHeap has a new size of: " << myMaxHeap.size() << endl;

	//Heapsort
	vector<int> myVector = myMaxHeap.getSortedVector();
	cout << "Sorted vector returns: ";
	for (unsigned int i = 0; i < myVector.size(); i++)
	{
		cout << myVector[i] << " ";
	}
	cout << endl;


	//Delete all nodes
	cout << "Deleting: ";
	while (myMaxHeap.size() > 0)
	{
		cout << *(myMaxHeap.getFirst()) << " ";
		myMaxHeap.deleteFirst();
	}
	cout << endl;






	//TEST THREADING

	//Create a new thread, make lots of access calls to a thread

	//make lots of access calls in this thread

	cout << endl;
	system("pause");

    return 0;
}

