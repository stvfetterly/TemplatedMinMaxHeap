#pragma once

#include <vector>

template <typename T>
class Heap
{
public:
	enum HeapType { MAX_HEAP, MIN_HEAP };

	//Actually use the heap

	//Add an item to the heap
	void Insert(const T& newItem)
	{
		m_heap.push_back(newItem);
		bubbleUp( (m_heap.size()-1) );
	}

	//Returns null if there are no values in the heap, otherwise gets the MAX or MIN value
	const T* getFirst() const
	{
		if (m_heap.size() > 0)
		{
			return &m_heap[0];
		}
		else
		{
			return NULL;
		}
	}

	void deleteFirst()
	{
		int length = m_heap.size();

		//Don't do anything, there's nothing to delete
		if (length == 0)
		{
			return;
		}

		//Swap the last node into the first node, and bubble down
		m_heap[0] = m_heap[length-1];
		m_heap.pop_back();
		bubbleDown(0);
	}

	int size() const
	{
		return m_heap.size();
	}

	//Accessor methods
	HeapType GetHeapType() const { return m_type; }
	void SetHeapType(HeapType type)
	{ 
		if (m_type != type)
		{
			m_type = type;
			createHeap();	//re-create the heap if we've changed type
		}
	}

	//Constructors
	Heap(HeapType type)
	{
		SetHeapType(type);
	}
	Heap(const T* dataArray, const int& length, HeapType type)
	{
		m_type = type;

		//copy new data into heap
		for (int i = 0; i < length; i++)
		{
			Insert(dataArray[i]);
		}
	}
	Heap(const std::vector<T>& dataVector, HeapType type)
	{
		m_type = type;

		//copy new data into heap
		m_heap = dataVector;

		createHeap();
	}
	//Copy Constructor
	Heap(const Heap& newHeap)
	{
		//Copy the variables
		m_heap = newHeap.getHeapVector();
		m_type = newHeap.GetHeapType();
	}

	//Assignment operator
	Heap& operator=(const Heap& rhs)
	{
		//Don't assign to self
		if (&rhs == this)
		{
			return *this;
		}

		//Assign stuff
		m_heap = rhs.getHeapVector();
		m_type = rhs.GetHeapType();

		return *this;
	}
	
	//Addition operator - keeps lhs heap type the same, adds in new data from rhs
	Heap& operator+(const Heap& rhs)
	{
		std::vector<T> rhsVector = rhs.getHeapVector();
		for (std::vector<T>::const_iterator it = rhsVector.begin(); it < rhsVector.end(); ++it)
		{
			Insert(*it);
		}

		return *this;
	}

	const std::vector<T>& getHeapVector() const
	{
		return m_heap;
	}

private:
	std::vector<T> m_heap;
	HeapType m_type;

	void createHeap()
	{
		//Sorts the heap by swapping the lowest nodes and working our way up
		for (int i = m_heap.size()-1; i >= 0; --i)
		{
			bubbleDown(i);
		}
	}
	//Used when adding a single item to the heap
	void bubbleUp(int child)
	{
		//No further recursion necessary, we're looking at the head node
		if (child == 0)
		{
			return;
		}

		int parent = (child - 1) / 2;

		//Check if the parent should be swapped with the child, if yes, recurse to check next level up
		if (swapWithParent(parent, child))
		{
			bubbleUp(parent);
		}
	}

	//Used to sort when multiple items are added to the heap, or when we delete the head
	void bubbleDown(int parent)
	{
		int length = m_heap.size();
		int leftChild = 2 * parent + 1;
		int rightChild = 2 * parent + 2;

		if (leftChild >= length)
		{
			return;		//no children, we're at the bottom of the tree
		}

		//figure out which child should be swapped
		int childToSwap = getChildToSwap(leftChild, rightChild);

		//If a swap was made, then we need to keep recursing
		if ( swapWithParent(parent, childToSwap))
		{
			bubbleDown(childToSwap);
		}
	}

	//Checks if the parent should be swapped with the child depending on type of heap
	//Returns FALSE when a swap was not made (heap is sorted)
	bool swapWithParent(int& parent, int& child)
	{
		//For MAX HEAP we want the parent to always be bigger than the child,
		//for MIN HEAP parent should be smaller than child.
		if ( (m_type == MAX_HEAP && m_heap[parent] < m_heap[child] ) ||
			 (m_type == MIN_HEAP && m_heap[parent] > m_heap[child])  )
		{
			//perform swap
			T temp = m_heap[child];
			m_heap[child] = m_heap[parent];
			m_heap[parent] = temp;
			return true;
		}
		return false;
	}

	//Determines if a bubble down should go with the right or left child
	int getChildToSwap(const int& leftChild, const int& rightChild) const
	{
		//If there is no right child, search the left child
		if ( rightChild >= m_heap.size() )
		{
			return leftChild;
		}

		//If there is a right child, check if it should be swapped with
		if (m_type == MAX_HEAP && (m_heap[leftChild] < m_heap[rightChild]) ||
			m_type == MIN_HEAP && (m_heap[rightChild] < m_heap[leftChild]) )
		{
			return rightChild;
		}
		return leftChild;
	}
};