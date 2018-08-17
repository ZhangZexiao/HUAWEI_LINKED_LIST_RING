// LinkedListRingDetector.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <climits>
#include <random>
#include <iostream>
using ull = unsigned long long;
struct HW_Node
{
	// "index" for debug printing, useless
	ull index;
	HW_Node *next;
};
class HW_LinkedListRing
{
	HW_Node *head, *joint;
	ull size, jointIndex;
public:
	HW_LinkedListRing(ull size, ull jointIndex):size(size), jointIndex(jointIndex), head(nullptr), joint(nullptr)
	{
		this->Construct();
		this->PrintInformation();
	}
	~HW_LinkedListRing()
	{
		this->Destruct();
	}
	HW_Node *GetHead()
	{
		return this->head;
	}
	ull GetSize()
	{
		return this->size;
	}
	ull GetJointIndex()
	{
		if (nullptr != this->joint)
		{
			return this->joint->index;
		}
		return ULLONG_MAX;
	}
private:
	void Construct()
	{		
		// create the head node
		this->head = new HW_Node();
		this->head->index = 0;
		// if size equals 1, then it will not enter while loop, joint assignment will not be called.
		// following special if code block fixed this case + joint index equals 0.
		if (0 == this->jointIndex)
		{
			this->joint = this->GetHead();
		}
		// prepare for looping
		HW_Node *current = this->GetHead();
		ull tmpIndex = 0;
		while (tmpIndex < this->GetSize() - 1)
		{
			// set joint node
			if (this->jointIndex == tmpIndex)
			{
				this->joint = current;
			}
			// fill current node
			current->index = tmpIndex;
			current->next = new HW_Node();
			// prepare for next node
			current = current->next;
			tmpIndex++;
		}
		// make the ring
		current->index = tmpIndex;
		current->next = this->joint;
	}
	void Destruct()
	{
		HW_Node *tmpNext;
		while (nullptr != head)
		{
			tmpNext = this->head->next;
			delete this->head;
			this->head = tmpNext;
		}
	}
	void PrintInformation()
	{
		std::cout << "There are " << this->GetSize() << " nodes in the linked list. " << std::endl;
		std::cout << "The joint node is placed at " << this->GetJointIndex() << "th node in the linked list." << std::endl;
	}
};
bool isLoop(HW_LinkedListRing *linkedList)
{
	HW_Node *n1 = linkedList->GetHead(), *n2 = linkedList->GetHead();
	ull count = 0;
	int n1j = 0, n2j = 0, nj = 0;
	static int maxNj = 0;
	while (n1 && n2)
	{
		n1 = n1->next;
		if (nullptr == n2->next)
		{
			return false;
		}
		n2 = n2->next->next;
		if (n1->index == linkedList->GetJointIndex())
		{
			n1j++;
		}
		if (n2->index == linkedList->GetJointIndex() || n2->index - 1 == linkedList->GetJointIndex())
		{
			n2j++;
			if (n1j > 0)
			{
				nj++;
				if (maxNj < nj)
				{
					maxNj = nj;
				}
			}
		}
		count++;
		if (n1 == n2)
		{
			std::cout << "n1 index is " << n1->index << ", n2 index is " << n2->index << ", n1j is " << n1j << ", n2j is " << n2j
				<< ", nj is " << nj << ", joint index is " << linkedList->GetJointIndex()
				<< ", size is " << linkedList->GetSize() << ", max nj is " << maxNj
				<< std::endl;
			//X000__>00X00__>0000X0__>000000X
			//000X   0000X   00000X   000000X
			std::cout << "Classic algorithm, We compared " << count << " times to get result." << std::endl;
			double currentCompareTime = count / (double)linkedList->GetSize();
			std::cout << "compare times / list size = " << currentCompareTime << std::endl;
			static double maxCompareTime = 0;
			if (maxCompareTime < currentCompareTime)
			{
				maxCompareTime = currentCompareTime;
			}
			std::cout << "MAX: compare times / list size = " << maxCompareTime << std::endl;
			return true;
		}
		
	}
	return false;
}
bool isLoop3(HW_LinkedListRing *linkedList)
{
	HW_Node *n1 = linkedList->GetHead(), *n2 = linkedList->GetHead();
	ull count = 0;
	while (n1 && n2)
	{
		n1 = n1->next;
		if (nullptr == n2->next)
		{
			return false;
		}
		if (nullptr == n2->next->next)
		{
			return false;
		}
		n2 = n2->next->next->next;
		count++;
		if (n1 == n2)
		{
			std::cout << "Variant 3 of classic algorithm, We compared " << count << " times to get result." << std::endl;
			double currentCompareTime = count / (double)linkedList->GetSize();
			std::cout << "compare times / list size = " << currentCompareTime << std::endl;
			static double maxCompareTime = 0;
			if (maxCompareTime < currentCompareTime)
			{
				maxCompareTime = currentCompareTime;
			}
			std::cout << "MAX: compare times / list size = " << maxCompareTime << std::endl;
			return true;
		}

	}
	return false;
}
bool isLoop5(HW_LinkedListRing *linkedList)
{
	HW_Node *n1 = linkedList->GetHead(), *n2 = linkedList->GetHead();
	ull count = 0;
	while (n1 && n2)
	{
		n1 = n1->next;
		if (nullptr == n2->next)
		{
			return false;
		}
		if (nullptr == n2->next->next)
		{
			return false;
		}
		if (nullptr == n2->next->next->next)
		{
			return false;
		}
		if (nullptr == n2->next->next->next->next)
		{
			return false;
		}
		n2 = n2->next->next->next->next->next;
		count++;
		if (n1 == n2)
		{
			std::cout << "Variant 5 of classic algorithm, We compared " << count << " times to get result." << std::endl;
			double currentCompareTime = count / (double)linkedList->GetSize();
			std::cout << "compare times / list size = " << currentCompareTime << std::endl;
			static double maxCompareTime = 0;
			if (maxCompareTime < currentCompareTime)
			{
				maxCompareTime = currentCompareTime;
			}
			std::cout << "MAX: compare times / list size = " << maxCompareTime << std::endl;
			return true;
		}

	}
	return false;
}
bool isRing(HW_LinkedListRing *linkedList)
{
	HW_Node *i1 = linkedList->GetHead(), *i2 = linkedList->GetHead()->next;
	if (nullptr == i2)
	{
		return false;
	}
	ull index = 1, current = 1;	
	while (i1 != i2)
	{		
		if (nullptr == i2)
		{
			return false;
		}
		//std::cout << i2->index << ", ";
		if (current == 2 * index)
		{
			std::cout << "Reset index of compared node from " << index << " to " << current << std::endl;
			index = current;
			i1 = i2;
		}
		i2 = i2->next;
		current++;
	}
	std::cout << "We compared " << current << " times to get result." << std::endl;
	double currentCompareTime = current / (double)linkedList->GetSize();
	std::cout << "compare times / list size = " << currentCompareTime << std::endl;
	static double maxCompareTime = 0;
	if (maxCompareTime < currentCompareTime)
	{
		maxCompareTime = currentCompareTime;
	}
	std::cout << "MAX: compare times / list size = " << maxCompareTime << std::endl;
	return true;
}
void printRing(bool isRing)
{
	if (isRing)
	{
		std::cout << "it is a ring linked list" << std::endl;
	}
	else
	{
		std::cout << "it is NOT a ring linked list" << std::endl;
	}
	std::cout << std::endl;
}
int main()
{
	std::default_random_engine generator;
	// make sure n >= 1, that there at least 1 node.
	std::uniform_int_distribution<ull> distribution(1, UINT16_MAX);
	//HW_LinkedListRing llr1(1, 0);
	//printRing(isRing(&llr1));
	//printRing(isLoop(&llr1));
	//printRing(isLoop3(&llr1));
	//HW_LinkedListRing llr2(1, 1);
	//printRing(isRing(&llr2));
	//printRing(isLoop(&llr2));
	//printRing(isLoop3(&llr2));
	//HW_LinkedListRing llr3(100, 0);
	//printRing(isRing(&llr3));
	//printRing(isLoop(&llr3));
	//printRing(isLoop3(&llr3));
	//HW_LinkedListRing llr4(100, 99);
	//printRing(isRing(&llr4));
	//printRing(isLoop(&llr4));
	//printRing(isLoop3(&llr4));
	ull tmp = 1000;
	while (tmp > 0)
	{
		ull n = distribution(generator);
		// because there at least 1 node, so (n - 1 >= 0). 
		std::uniform_int_distribution<ull> distribution(0, n - 1);
		ull jointIndex = distribution(generator);

		HW_LinkedListRing *ring = new HW_LinkedListRing(n, jointIndex);
		//printRing(isRing(ring));
		printRing(isLoop(ring));
		//printRing(isLoop3(ring));
		//printRing(isLoop5(ring));
		//getchar();
		delete ring;
		tmp--;
	}
	getchar();
    return 0;
}