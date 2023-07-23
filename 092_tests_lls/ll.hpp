#ifndef __LL_HPP__
#define __LL_HPP__

#include <assert.h>

#include <iostream>
#include <cstdlib>
#include <exception>
#include <algorithm>


class WrongIndex : public std::exception
{
    const char *msg;
public:
    WrongIndex(const char *_msg) : msg(_msg) {}
    virtual const char *what() const throw() {
        return msg;
    }
    virtual ~WrongIndex() throw() {}
};
//////////////////

template<typename T>
class LinkedList {
  class Node {
   public:
    T data;
    Node * next;
    Node * prev;
    Node(const T &d) : data(d), next(NULL), prev(NULL){};
    Node(const T &d, const Node * n, Node * p) : data(d), next(n), prev(p){};
  };
  Node * head;
  Node * tail;

 public:
  LinkedList() : head(NULL), tail(NULL) {}

  LinkedList(const LinkedList & rhs) : head(NULL), tail(NULL) {     // head(NULL), tail(NULL)
    Node * ptr = rhs.head;
    while (ptr != NULL) {
      addBack(ptr->data);
      ptr = ptr->next;
    }    
  }

  LinkedList & operator=(const LinkedList & rhs) {
    if (this != &rhs) {
      LinkedList temp;
      Node * ptr = rhs.head;
      while (ptr != NULL) {
        temp.addBack(ptr->data);
        ptr = ptr->next;
      }
      std::swap(head, temp.head);
      std::swap(tail, temo.tail);           
    }
    return *this; 
  }
  ~LinkedList() {
    Node * curr = head;
    while (curr != NULL)  {
      head = curr->next; ///
      delete curr;
      curr = head;
    }
    
  }

  void addFront(const T & item) {
    Node * nnode = new Node(item, head, NULL);
    head = nnode;
    if (head = NULL) {
      tail = nnode;
    }
    else {
      head->next->prev = nnode; //
    }
  }


  void addBack(const T & item) {
    Node * nnode = new Node(item, NULL, tail);
    tail = nnode;
    if (head = NULL) {
      head = nnode;
    }
    else {
      tail->prev->next = nnode; ///
    }
  }


  bool remove(const T & item) {
    Node * ptr = head;
    while (ptr != NULL) {
      if (ptr->data == item) {
        if (ptr->next != NULL) {
          ptr->next->prev = ptr->prev;
        }
        if (ptr->prev != NULL) {
          ptr->prev->next = ptr->next;
        }
                
        delete ptr;
        return 1;
      }
      ptr = ptr->next;
    }
    return false;    
  }


  T & operator[](int index) {
    if (index < 0) {
      throw WrongIndex("less than 0!")  
    }
    Node * ptr = head;
    while (ptr != NULL) {
      if (index == 0) {
        return ptr->data;
      }
      ptr = ptr->next;
      --index;
    }
    throw WrongIndex("out of range!");
  }

  const T & operator[](int index) const {
    if (index < 0) {
      throw WrongIndex("less than 0!")  
    }
    Node * ptr = head;
    while (ptr != NULL) {
      if (index == 0) {
        return ptr->data;
      }
      ptr = ptr->next;
      --index;
    }
    throw WrongIndex("out of range!");
  }  

  T find(const T & item) {
    Node * ptr = head;
    int i = 0;
    while (ptr != NULL) {
      if (ptr->data == item) {
        return i;
      }
      ptr = ptr->next;
      ++i;
    }
    return -1;
  }

  T getSize() const {
    Node * ptr = head;
    int i = 0;
    while (ptr != NULL) {
      ptr = ptr->next;
      ++i;
    }
    return i;
  }

};

#endif
