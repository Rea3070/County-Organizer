#ifndef LIST_H
#define LIST_H

#include<iostream>

using namespace std;

//Doubly linked list class with merge sort function.
template <typename T>
class List
{
    private:
		//our node structure with pointers
        struct ListNode
        {
            T value;
            struct ListNode *next;
            struct ListNode *previous;	

        };

        ListNode *head;		// List head pointer
	    ListNode *tail;		//List tail pointer
        void print(ListNode*);	//prints all data at the specific node
        typename List<T>::ListNode*  mergeSort(ListNode*, ListNode*);	//recursively sorts the list using merge sort
        typename List<T>::ListNode*  merge(ListNode*, ListNode*);	//merges two node lists
        typename List<T>::ListNode*  split(ListNode*, ListNode*);	//spilst a list and returns the midpoint

    public:
		//constructor
        List()
		{ 
			head = NULL; 
			tail = NULL;
		}
		//deconstructor
        ~List();

		//appends a new node to the list
        void appendNode(T);
		//prints all nodes
        void print();
		//sorts list using merge sort
        void mergeSort();


};

//Appends a new node to the end of the list.
template <typename T>
void List<T>::appendNode(T value)
{

	//create new node
	ListNode *newNode; 

	//set node values
	newNode = new ListNode;
	newNode->value = value;
	newNode->next = NULL;
	newNode->previous = NULL;

	//append node if it is the first
	if (!head ) 
	{
		head = newNode;
		tail = newNode;
	}
	//append node if it is no the first
	else  
	{
		tail->next = newNode;
		newNode->previous = tail;
		tail = newNode;
	}
}

//prints all nodes in the list
template <typename T>
void List<T>::print()
{
	// To move through the lists
	ListNode *nodePtr = head;  
	print(nodePtr);
}


//prints all nodes from a specific node
template <typename T>
void List<T>::print(ListNode *nodePtr)
{
	//While nodePtr points to a node, traverse the list
	while (nodePtr)
	{
		//Display the value in this node
		cout << *(nodePtr->value) << endl;

		//Move to the next node
		nodePtr = nodePtr->next;
	}
}

//merges two nodes depending on which value is smaller
template <typename T>
typename List<T>::ListNode*  List<T>::merge(ListNode* first, ListNode* second)
{

    // If first linked list is empty 
    if (!first) 
        return second; 
  
    // If second linked list is empty 
    if (!second) 
        return first; 
	
	//if the first value is smaller
    if(first->value->operator<(*(second->value))) 
    { 
		// merge the first pointer
        first->next = merge(first->next, second); 
        first->next->previous = first; 
        first->previous = NULL; 
        return first; 
    } 
    else // if the second value is smaller
    { 	
		//merge the second pointer
        second->next = merge(first,second->next); 
        second->next->previous = second; 
        second->previous = NULL; 
        return second; 
    } 
}

//use mergesort to sort the list with recursion
template <typename T>
typename List<T>::ListNode* List<T>::mergeSort(ListNode* head, ListNode* tail)
{
	//if there is no data, abandon
	if (!head || !head->next) 
        return head; 

	//set the begining and midpoints to compare
	ListNode *a = head;
	ListNode *mid = split(head, tail);

	//merge the split lists
	a = mergeSort(a, mid); 
    mid = mergeSort(mid, tail);

	//return the merged list
	return merge(a,mid); 	
}

//split the list in the middle and retrun the middle node
template <typename T>
typename List<T>::ListNode* List<T>::split(ListNode* head, ListNode* tail)
{	
	//This was my attempt at making it work with double traversal. I couldn't get it to work all the way through, it would always get stuck at some point, so i googled a 
	//different way and found the fast/slow method which was actually easier for me to understand. I still have no idea how to make it work. 
    /* ListNode *first = head, *last = tail; 
	*
    * if(first->next != NULL){
    *     while
	*	last = last->previous;
    * } 
    * ListNode *temp = first->next; 
	* first->next = NULL;
    *return temp; 
	*/
	// ListNode *first = head;
	// ListNode *second = tail;
	// ListNode *temp1, temp2;

	// while(temp1 != temp2->next && temp){

	// }
	// temp = first->next;
	// first->next = NULL;
	// return temp;


	//set two new nodes to the first node
	ListNode *fast = head;
	ListNode *slow = head; 

	//advances one node "faster" than the other by making the fast one advance by 2 and the slow one by 1, this makes it so that the slow pointer is in the middle when the fast pointer reaches the end.
    while (fast->next && fast->next->next) 
    { 
		//fast advance by 2
        fast = fast->next->next;
		//slow advance by 1 
        slow = slow->next; 
    } 
	//slow is centered at the midpoint so put it into a temp variable 
    ListNode *temp = slow->next; 

	//seperate the list
    slow->next = NULL; 

	//return mid point
    return temp; 
}

//sorts the list using merge sort
template <typename T>
void List<T>::mergeSort()
{	
	//refernce node
	ListNode *refNode;
	

	//the first node of the new sorted list
	refNode = mergeSort(head, tail);

	//sets new head
	head = refNode;

	//traverse to find tail
	while(refNode->next != NULL)
	{
		refNode = refNode->next;
	}
	//sets new tail
	tail = refNode;
}

//deconstructor
template <typename T>
List<T>::~List()
{
	ListNode *nodePtr;   // To traverse the list
	ListNode *nextNode;  // To point to the next node

	//Position nodePtr at the head of the list
	nodePtr = head;

	//While nodePtr is not at the end of the list
	while (nodePtr != NULL)
	{
		// Save a pointer to the next node.
		nextNode = nodePtr->next;

		// Delete the current node.
		delete nodePtr;

		// Position nodePtr at the next node.
		nodePtr = nextNode;
	}
}
#endif