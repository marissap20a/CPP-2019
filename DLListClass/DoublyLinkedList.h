#ifndef DOUBLYLINKEDLIST_H
#define DOUBLYLINKEDLIST_H
#include "Node.h"
#include <string>
#include <iostream>
#include <iomanip>
#include <sstream>

//////////////////////////////////////////////////////////////////////////////
//                         class template definition                        //
//////////////////////////////////////////////////////////////////////////////

template<typename T>
class DoublyLinkedList {
public:
    /* uncomment the declarations as you implement them */
    DoublyLinkedList();
    DoublyLinkedList(T);
    DoublyLinkedList(const DoublyLinkedList<T>&);
    DoublyLinkedList<T>& operator=(const DoublyLinkedList<T>&);
    ~DoublyLinkedList();
    unsigned int size() const { return sz; }
    T& front();
    //const T& front() const;
    T& back();
    // const T& back() const;
    void push_back(T);
    void push_front(T);
    void pop_back();
    void pop_front();
    void erase(unsigned int);
    void insert(T data, unsigned int idx);
    void clear();
    std::string to_str() const;
    // breaks encapsulation... gives operator== access to private data... not great approach, but makes the homework easier for you since we haven't talked about iterators :).
    template<typename U> friend bool operator==(DoublyLinkedList<U> const&, DoublyLinkedList<U> const&);
private:
    // do not change ordering.
    Node<T> *head;
    Node<T> *tail;
    unsigned int sz;
};

//////////////////////////////////////////////////////////////////////////////
//                       helper function declarations                       //
//////////////////////////////////////////////////////////////////////////////
template<typename T> std::ostream& operator<<(std::ostream &, DoublyLinkedList<T> const&);

template<typename T> bool operator==(DoublyLinkedList<T> const&, DoublyLinkedList<T> const&);

template<typename T> bool operator!=(DoublyLinkedList<T> const&, DoublyLinkedList<T> const&);

//////////////////////////////////////////////////////////////////////////////
//                     member template function definitions                 //
//////////////////////////////////////////////////////////////////////////////




template<typename T>
std::string DoublyLinkedList<T>::to_str() const
{
    std::stringstream os;
    const Node<T> *curr = head;
    os << std::endl << std::setfill('-') << std::setw(80) << '-' << std::setfill(' ') << std::endl;
    os << "head: " << head << std::endl;
    os << "tail: " << tail << std::endl;
    os << "  sz: " << sz << std::endl;
    os << std::setw(16) << "node" << std::setw(16) << "node.prev" << std::setw(16) << "node.data" <<  std::setw(16) << "node.next" << std::endl;
    while (curr) {
        os << std::setw(16) << curr;
        os << std::setw(16) << curr->prev;
        os << std::setw(16) << curr->data;
        os << std::setw(16) << curr->next;
        os << std::endl;
        curr = curr->next;
    }
    os << std::setfill('-') << std::setw(80) << '-' << std::setfill(' ') << std::endl;
    return os.str();
}

//////////////////////////////////////////////////////////////////////////////
//                     helper template function definitions                 //
//////////////////////////////////////////////////////////////////////////////

template<typename T>
bool operator==(DoublyLinkedList<T> const& lhs, DoublyLinkedList<T> const& rhs)
{
    // getting you started on this once... definition for this overloaded operator will go here.
	unsigned int currIdx = 0;
	Node<T>* curr_lhs = lhs.head;
	Node<T>* curr_rhs = rhs.head;
	if(lhs.size() == rhs.size()){
		if(lhs.size() == 0){
			return true;
		}
		else{
			while(curr_lhs != nullptr){
				if(curr_lhs->data != curr_rhs->data){
					return false;
				}
				curr_lhs = curr_lhs->next;
				curr_rhs = curr_rhs->next;
			}
			return true;
		}
	}
    return false;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, DoublyLinkedList<T> const& rhs)
{
    os << rhs.to_str();
    return os;
}

template<typename T>
DoublyLinkedList<T>::DoublyLinkedList() : head(nullptr), tail(nullptr), sz(0){}

template<typename T>
DoublyLinkedList<T>::DoublyLinkedList(T dat) : head(nullptr), tail(nullptr), sz(0)
{	
	sz += 1;
	head = new Node<T>(dat);
	tail = head;
}

template<typename T>
void DoublyLinkedList<T>::clear()
{
	Node<T>* next_node = nullptr;
	while(head)
	{
		next_node = head->next; //assign a temp node with the node in front of head
		delete head; //head wiped out 
		head = next_node; //head is now the new node 
		
	}
	head = nullptr;
	tail = nullptr;
	sz = 0;
	
}

template<typename T>
DoublyLinkedList<T>::~DoublyLinkedList()
{
	clear();	
}

template<typename T>
T& DoublyLinkedList<T>::front(){
	return this->head->data;
}

template<typename T>
T& DoublyLinkedList<T>::back(){
	return this->tail->data;
}		
	
template<typename T>
void DoublyLinkedList<T>::push_back(T data)
{
	if(head == nullptr){//0elements
		head = new Node<T>(data);
		tail = head;
	}
	else{
		Node<T>* newTail = new Node<T>(data);
		tail->next = newTail;
		newTail->prev = tail;
		tail = newTail;
		
	}
	sz+=1;	
}

template<typename T>
void DoublyLinkedList<T>::push_front(T data)
{
	if(head == nullptr){
		head = new Node<T>(data);
		tail = head;
	}
	else{
		Node<T>* newHead = new Node<T>(data);
		newHead->next = head;
		head->prev = newHead;
		head = newHead;
	}
	sz+=1;
}

template<typename T>
void DoublyLinkedList<T>::erase(unsigned int idx)
{	
	unsigned int currIdx = 0;
	if(idx >= 0 && idx < sz){
		if(head != nullptr){
			if(idx == 0){
				pop_front();
			}
			else if(idx == sz-1){
				pop_back();
			}
			else{
				Node<T>* curr = head;
				while(currIdx != idx){
					curr = curr->next;
					currIdx += 1;
				}
				//Node<T>* newEnd = nullptr;
				//newEnd = curr->next;
				//newEnd->prev = curr->prev;
				curr->next->prev = curr->prev;
				curr->prev->next = curr->next;
				curr->prev = nullptr;
				curr->next = nullptr;
				delete curr;
			
				sz-=1;
			}
			
			
		}
	}
}
template<typename T>
void DoublyLinkedList<T>::insert(T data, unsigned int idx)
{
	unsigned int currIdx = 0;
	if(idx >= sz){
		return;
	}
	else{
		if(idx == 0){
			push_front(data);
		}
		else if(idx == sz-1){
			Node<T>* node = new Node<T>(data);
			node->next = tail;
			node->prev = tail->prev;
			
			tail->prev->next = node;
			tail->prev = node;
			sz+=1;
		}
		else{
			Node<T>* curr = head;
			while(currIdx != idx-1){
				curr = curr->next;
				currIdx += 1;
			}
			//Node<T>* newEnd = nullptr;
			//newEnd = curr->next;
			//newEnd->prev = curr->prev;
			Node<T>* node = new Node<T>(data);
			node->prev = curr;
			node->next = curr->next;
			node->next->prev = node;
			curr->next = node;
			sz+=1;
		}	
	}
	
}

template<typename T>
void DoublyLinkedList<T>::pop_back()
{
	if(head != nullptr){
		if(sz == 1){
			clear();
		}
		else{
			Node<T>* curr = tail->prev;
			tail->prev = nullptr;
			delete tail;
			curr->next = nullptr;
			tail = curr;
			sz-=1;
		}
	}
	
}

template<typename T>
void DoublyLinkedList<T>::pop_front()
{
	if(head != nullptr){
		if(sz == 1){
			clear();
		}
		else{
			Node<T>* curr = head->next;
			head->next = nullptr;
			delete head;
			curr->prev = nullptr;
			head = curr;
			sz -= 1;
		}	
		
	}
	
}
template<typename T>
DoublyLinkedList<T>::DoublyLinkedList(const DoublyLinkedList<T>& oldList){
  if(oldList.sz == 0){
	sz = 0;
	head=nullptr;
	tail=nullptr;
    }
  else{
	sz=0;
	Node<T> *rhs = oldList.head;
	Node<T> *lhs = nullptr;
	head = tail = new Node<T>(rhs->data);
	lhs = head;
	sz+=1;
	rhs = rhs->next;
	while (rhs != nullptr) {
		Node<T>* node = new Node<T>(rhs->data);
		lhs->next = node; 
		tail = node;
		tail->prev = lhs;
		sz += 1;
		rhs = rhs->next;
		lhs = lhs->next;
	// update tail too
	// move both rhs and lhs
	}
  }
}
template<typename T>
DoublyLinkedList<T>& DoublyLinkedList<T>::operator=(const DoublyLinkedList<T>& rhs)
{
	if(this == &rhs){
		return *this;	
	}
	clear();
	DoublyLinkedList<T> temp(rhs);
	std::swap(temp.head, head);
	std::swap(temp.tail, tail);
	std::swap(temp.sz, sz);
	return *this;
	
	
	
	
	
}

#endif
