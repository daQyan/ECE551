#include <assert.h>

#include <cstdlib>
#include <iostream>

#include "ll.hpp"

typedef LinkedList<int> IntList;

class Tester {
 public:
  // testing for default constructor is done for you
  void testDefCtor() {

    IntList il;
    assert(il.head == NULL);
    assert(il.tail == NULL);
    assert(il.getSize() == 0);
  }
  // example of another method you might want to write
  void testAddFront() {
    IntList ls;

    ls.addFront(1);
    IntList::Node * N1 = ls.head;
   
    assert(ls.head != NULL);
    assert(ls.tail == ls.head);
    assert(ls.getSize() == 1);
    assert(ls[0] == 1);
   
    assert(N1->data == 1);
    assert(N1->next == NULL);
    assert(N1->prev == NULL);

   
    ls.addFront(2);
    IntList::Node * N2 = ls.head;
    
    assert(ls.head != NULL);
    assert(ls.tail == N1);
    assert(ls.getSize() == 2);
    assert(ls[0] == 2);
    assert(ls[1] == 1);
 
    assert(N1->data == 1);
    assert(N1->next == NULL);
    assert(N1->prev == N2);

    assert(N2->data == 2);
    assert(N2->next == N1);
    assert(N2->prev == NULL);
  }
  // many more tester methods

  void testAddBack() {
    IntList ls;
	    // First addBack
	    ls.addBack(1);
	    IntList::Node * N1 = ls.tail;
	    // Check list
	    assert(ls.head != NULL);
	    assert(ls.tail == ls.head);
	    assert(ls.getSize() == 1);
	    assert(ls[0] == 1);
	    // Check N1
	    assert(N1->data == 1);
	    assert(N1->next == NULL);
	    assert(N1->prev == NULL);
	

	    // Second addBack
	    ls.addBack(2);
	    IntList::Node * N2 = ls.tail;
	    // Check list
	    assert(ls.head == N1);
	    assert(ls.tail != NULL);
	    assert(ls.getSize() == 2);
	    assert(ls[0] == 1);
	    assert(ls[1] == 2);
	    // Check N1
	    assert(N1->data == 1);
	    assert(N1->next == N2);
	    assert(N1->prev == NULL);
	    // Check N2
	    assert(N2->data == 2);
	    assert(N2->next == NULL);
	    assert(N2->prev == N1);
	

	    // Third addFront
	    ls.addFront(3);
	    IntList::Node * N3 = ls.head;
	    // Check list
	    assert(ls.head != NULL);
	    assert(ls.tail == N2);
	    assert(ls.getSize() == 3);
	    assert(ls[0] == 3);
	    assert(ls[1] == 1);
	    assert(ls[2] == 2);
	    // Check N1
	    assert(N1->data == 1);
	    assert(N1->next == N2);
	    assert(N1->prev == N3);
	    // Check N2
	    assert(N2->data == 2);
	    assert(N2->next == NULL);
	    assert(N2->prev == N1);
	    // Check N3
	    assert(N3->data == 3);
	    assert(N3->next == N1);
	    assert(N3->prev == NULL);

  
  }

    void testCopy() {
        IntList llls0;
        llls0.addBack(1);
        llls0.addBack(-1);
        llls0.addBack(0);
        
        IntList llls1(llls0);
        assert(llls0.getSize() == 3);
        assert(llls1.getSize() == 3); // test 10
        IntList::Node *curr0 = llls0.head;
        IntList::Node *curr1 = llls1.head;
        assert(curr1->data == 1 && curr1->prev == NULL && curr1->next != NULL);
        assert(curr0 != curr1); // test 11
        curr1 = curr1->next;
        curr0 = curr0->next;
        assert(curr1->data == -1 && curr1->prev != NULL && curr1->next != NULL);
        assert(curr1->prev->data == 1);
        assert(curr0 != curr1);
        assert(curr0->prev != curr1->prev);
        curr1 = curr1->next;
        curr0 = curr0->next;
        assert(curr1->data == 0 && curr1->prev != NULL && curr1->next == NULL);
        assert(curr1->prev->data == -1);
        assert(curr0 != curr1);
        assert(curr0->prev != curr1->prev);
        assert(llls1.tail == curr1);

        IntList llls2;
        IntList llls3(llls2);
        assert(llls3.head == NULL && llls3.tail == NULL);
        assert(llls3.getSize() == 0);


  }

  void testAssign() {
    IntList * dut1 = new IntList();
    dut1->addBack(1);
    dut1->addBack(2);
    IntList * dut2 = new IntList();
    dut2->addFront(1);
    dut2->addFront(2);
    dut2->addFront(3);
    *dut2 = *dut1;
    assert(dut2->getSize() == 2);
    assert(dut1->head != dut2->head);
    assert(dut1->tail != dut2->tail);
    assert(dut2->tail->next == NULL);
    delete dut1;
    delete dut2;
  }

    void testRemove() {
    IntList ls3;
    ls3.addBack(1);
    assert(ls3[0] == 1);
    assert(ls3.remove(1));
    assert(ls3.remove(0) == false);
    assert(ls3.getSize() == 0);
    assert(ls3.head == NULL && ls3.tail == NULL);

    IntList ls;
    ls.addBack(1);
    IntList::Node * N1 = ls.tail;

    ls.addBack(2);
    ls.addBack(3);
    IntList::Node * N3 = ls.tail;
    ls.addBack(2);
    IntList::Node * N2 = ls.tail;

    // Zeroth invalid remove
    assert(ls.remove(0) == false);
    assert(ls.remove(2) == true);
    // Check list
    assert(ls.head == N1);
    assert(ls.tail == N2);
    assert(ls.getSize() == 3);
    assert(ls[0] == 1);
    assert(ls[1] == 3);
    assert(ls[2] == 2);
    // Check N1
    assert(N1->data == 1);
    assert(N1->next == N3);
    assert(N1->prev == NULL);
    // Check N2
    assert(N2->data == 2);
    assert(N2->next == NULL);
    assert(N2->prev == N3);
    // Check N3
    assert(N3->data == 3);
    assert(N3->next == N2);
    assert(N3->prev == N1);

    assert(ls.remove(2) == true);
    // Check list
    assert(ls.head == N1);
    // std::cout << ls[1] << std::endl;
    assert(ls.tail == N3);
    assert(ls.getSize() == 2);
    assert(ls[0] == 1);
    assert(ls[1] == 3);
    // Check N1
    assert(N1->data == 1);
    assert(N1->next == N3);
    assert(N1->prev == NULL);
    // Check N3
    assert(N3->data == 3);
    assert(N3->next == NULL);
    assert(N3->prev == N1);

    assert(ls.remove(1) == true);
    // Check list
    assert(ls.head == N3);
    assert(ls.tail == N3);
    assert(ls.getSize() == 1);
    assert(ls[0] == 3);
    // Check N3
    assert(N3->data == 3);
    assert(N3->next == NULL);
    assert(N3->prev == NULL);

    // Fourth remove
    assert(ls.remove(3) == true);
    // Check list
    assert(ls.head == NULL);
    assert(ls.tail == NULL);
    assert(ls.getSize() == 0);

    assert(ls.remove(1) == false);
  }


};

int main(void) {
  Tester t;
  t.testDefCtor();
  t.testAddFront();
  t.testAddBack();
  t.testCopy();
  t.testAssign();
  t.testRemove();
  // write calls to your other test methods here
  return EXIT_SUCCESS;
}
