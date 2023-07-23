#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <utility>
#include <cstdlib>
#include <set>
#include <stack>
#include <queue>
#include "onePage.hpp"
#include <map>

/** styBook is the story book containing all pages 
     * @param allPages stores all onePages of the story
     */
class styBook{
private:
  std::vector<onePage> allPages;
	// std::set<size_t> pageSets;
	// std::vector<std::pair<size_t, size_t> > cheatSheet;

	void checkRefering(std::vector<onePage>& pages);
	void checkRefered(std::vector<onePage>& pages);
	void checkWinLose(std::vector<onePage>& pages);
	void printExitpaths(std::vector<std::vector<std::pair<size_t, size_t> > >& paths);

public:
	styBook() {}
	// constructor
	styBook(std::string dirct) {
		std::ifstream dic(dirct);
		size_t num = 1;
		while (true) {			
			std::stringstream buff;
			buff << dirct << "/page" << num << ".txt";
			std::string pageName = buff.str();
			std::ifstream pageN(buff.str());
			if (!pageN && num == 1) {
				throw std::runtime_error("no page1.txt file");
			}
			// not find the page file
			else if (!pageN) {											
				break;
			}
			allPages.push_back(onePage(pageName));
			allPages[num - 1].pageIndex = num;
			++num;
		}
		checkRefering(allPages);
		checkRefered(allPages);
		checkWinLose(allPages);		
	}

// New Step4
	void findExit();
	void go(std::pair<size_t, size_t>& node, std::set<size_t>& visited, 
		std::vector<std::pair<size_t, size_t> >& currPath, std::vector<std::vector<std::pair<size_t, size_t> > >& paths, size_t Gnode);

// New Step3

	std::vector<size_t> getDepth();
	void printDepth(std::vector<size_t>& depthSheet);
	void goPlay();
	void playHelper(size_t num);
	// check if the input number from the user is valid, if not repeat until it is 
	size_t checkNumValid(size_t index);

};



// for the previous README <_<

/* STEP3

	void checkReachy() {
		goReach(0);
		// 
		for (size_t i = 2; i <= allPages.size(); i++) {
			if (pageSets.find(i) == pageSets.end()) {
				std::cout << "Page " << i << " is not reachable" << std::endl;
			}			
		}	
	}

	void goReach(size_t index) {
		if (allPages[index].navigMode == LOSE || allPages[index].navigMode == WIN) {
			return;
		}
		for (size_t i = 0; i < allPages[index].navigTxt.size(); i++) {
			size_t pdex =  allPages[index].navigTxt[i].first;
			pageSets.insert(pdex);
			goReach(pdex-1);
		}
	}

*/

// // STEP 4
// 	void lookCheetSheet(size_t winnn) {
		
// 		for (int i = cheatSheet.size()-1; i >= 0; i--) {
// 			std::cout << "Page " << cheatSheet[i].first << " Choice " << cheatSheet[i].second << std::endl;
// 		}
// 		// std::vector<std::pair<size_t,size_t> >::reverse_iterator i = cheatSheet.rbegin();
// 		// while (i != cheatSheet.rend()) {
// 		// 	std::cout << "Page " << i->first << " Choice " << i->second << std::endl;
// 		// 	++i;
// 		// }
// 		std::cout << "Page " << winnn << " WIN" << std::endl;
// 	}

// 	// find the win path and print out 
// 	void Cheat() {
// 		// check win page reachable first.
// 		// for (size_t i = 2; i <= allPages.size(); i++) {
// 		// 	if (pageSets.find(i) == pageSets.end() && allPages[i].navigMode == WIN) {
// 		// 		std::cout << "There is no way to win" << std::endl;
// 		// 		return;
// 		// 	}			
// 		// }
// 		size_t winPage;
// 		for (size_t i = 0; i < allPages.size(); i++) {
// 			if (allPages[i].navigMode == WIN) {
// 				std::set<int> visitList;
// 				goBack(allPages[i].pageIndex, visitList);
// 				winPage = allPages[i].pageIndex;

// 			}			
// 		}
// 		lookCheetSheet(winPage);
// 	}

// 	void goBack(size_t pdex, std::set<int>& visitList) {
		
// 		if (visitList.find(pdex) == visitList.end()) {
// 			visitList.insert(pdex);
// 			for (size_t i = 0; i < allPages.size(); i++) {
// 				for (size_t j = 0; j < allPages[i].navigTxt.size(); j++) {
// 					if (allPages[i].navigTxt[j].first == pdex) {
// 						// find = true;
// 						cheatSheet.push_back(std::pair<size_t, size_t> (allPages[i].pageIndex, j+1));
// 						// std::cout << "Page " << allPages[i].pageIndex << " Choice " << j+1 << std::endl;
// 						if (allPages[i].pageIndex == 1) {
// 							return;
// 						}
// 						goBack(allPages[i].pageIndex, visitList);
// 					}
// 				}
// 			}
// 		}				
// 	}


// template <typename T, typename S>
// std::set<S> remapSet(const std::set<T>& t, const std::map<T,S>& s) {
// 	typename std::set<T>::const_iterator it = t.begin();
// 	std::set<S> ans;
// 	while (it != t.end()) {
// 		std::map<T,S>::const_iterator i = s.find(*it);
// 		if (i == s.end()) {
// 			throw std::domain_error("not find")
// 		}
// 		ans.add()
		
// 		++it;
// 	}
// 	return ans;
// }



// void removeGreater(int t) {
// 	Node* dummy = new Node(0);
// 	dummy->next = head;
// 	Node * curr = dummy;
// 	while (curr != NULL)
// 	{
// 		Node * temp = cuur->next;
// 		if (curr->next->data > t) {
// 			curr->next = curr->next->next;
// 			delete temp;
// 			curr = curr->next;
// 		}
// 		else {
// 			curr = curr->next;
// 		}
// 	}
// }



// ///////////////////////////////////////////////////////////////////////////////////


// template <typename T>
// std::map<T,int> addOne(std::map<T,int>& my_map, T to_add) {
// 	typename std::map<T,int>::iterator it = my_map.find(to_add);
// 	if (it == my_map.end()) {
// 		my_map.insert(std::pair<T, int>(to_add, 1));
// 	}
// 	else {
// 		my_map[to_add]++;
// 	}
// 	return my_map;
// }

// ////

// Mylist & operator+() {

// }

// try {

// }
// catch () {

// }
// ///////////////////////////////////////////////////////////////////////////////////


// 7:

// // overloaded sum operator + for the class MyList
// MyList & MyList::operator+(const MyList &rhs) {
//   try {
// 		// check if rhs is null
// 		assert(rhs != NULL);
// 		// create a new copy list of rhs
// 		Mylist cpyList(rhs);
// 		// check if the current list is null
// 		if (head == NULL) {
// 			head = cpyList.head;
// 		}	
// 		// if not null, append the copied list to the end
// 		else {
// 			Node * curr = head;
// 			while (curr != NULL) {
// 				curr = curr->next;
// 			}
// 			curr->next = cpyList;		
// 		}
//   } catch (...) {
//     throw;
//   }
//   return *this;
// }


// Q6:
// template <typename T>
// void addOne(std::map<T, int> &my_map, const T &to_add) {
//   typename std::map<T, int>::iterator it = my_map.find(to_add);
//   if (it == my_map.end()) {
//     // The key is not in the map, insert it with value 1.
//     my_map.insert(std::make_pair(to_add, 1));
//   } else {
//     // The key is already in the map, increment the value.
//     it->second++;
//   }
// }

// template <typename T>
// void addOne(std::map<T,int>& my_map, cosnt T& to_add) {
// 	typename std::map<T,int>::iterator it = my_map.find(to_add);
// 	// if find the key
// 	if (it == my_map.end()) {
// 		my_map.insert(std::pair<T, int>(to_add, 1));
// 	}
// 	// if not find the key
// 	else {
// 		++it->second;
// 	}
// }


// Q7:

// // Appends a copy of the given MyList to the calling object.
// // Provides a strong exception guarantee.
// MyList &MyList::operator+(const MyList &other) {
//   // Create a new Node to append to the calling object.
//   Node *new_node = new Node();
//   try {
//     // Copy the data from the other MyList.
//     new_node->data = other.data;
//     new_node->next = other.next;

//     // Append the new Node to the end of the calling MyList.
//     // Find the last Node of the calling object.
//     Node *last = &head;
//     while (last->next != nullptr) {
//       last = last->next;
//     }
//     // Append the new Node.
//     last->next = new_node;
//   } catch (...) {
//     // If an exception is thrown while copying the other MyList,
//     // delete the new Node and rethrow the exception.
//     delete new_node;
//     throw;
//   }
//   // Return the calling object.
//   return *this;
// }



// Q8:

// For this coding exercise, you can only use C++98 features, and cannot use the STL data types.
// Write the enList function (outside of the BST class), which takes as parameter an instance of the following templated BST class, and returns a doubly linked list that contains all the leaf elements in the argument tree.


// Here is a possible implementation of the enList function in C++98, which takes a BST object and returns a doubly linked list containing all the leaf elements in the tree:

// // Returns a doubly linked list containing all the leaf elements in the given BST.
// template <typename T>
// DLList<T> enList(const BST<T> &tree) {
//   // Create an empty doubly linked list.
//   DLList<T> list;

//   // Recursively visit all the nodes of the tree.
//   enListHelper(tree.root, list);

//   // Return the doubly linked list.
//   return list;
// }

// // Helper function that recursively visits all the nodes of the tree and adds
// // the leaf nodes to the given doubly linked list.
// template <typename T>
// void enListHelper(const typename BST<T>::Node *node, DLList<T> &list) {
//   if (node == nullptr) {
//     // If the node is null, return without doing anything.
//     return;
//   }
//   if (node->left == nullptr && node->right == nullptr) {
//     // If the node is a leaf, add it to the doubly linked list.
//     list.push_back(node->data);
//   } else {
//     // If the node is not a leaf, recursively visit its children.
//     enListHelper(node->left, list);
//     enListHelper(node->right, list);
//   }
// }
// This code uses a recursive helper function enListHelper that visits all the nodes of the tree and adds the leaf nodes to the doubly linked list. The enList function initializes an empty doubly linked list and calls enListHelper to visit the nodes of the tree and add the leaf nodes to the list. Finally, it returns the doubly linked list.



// // Doubly linked list interface
// template<typename T>
// class DLList<T> {
// 	class Node {
// 		T data;
// 		Node * prev;
// 		Node * next;  
// 		Node(T d) data(d) {}   
// 	}
// 	public:
// 	Node * head;
// 	DLList() {}
// 	DLList(T d) : Node(d) {}
// 	// push the node at the end of the list
// 	void push_back(Node& n);  		
// }

// // Return a doubly linked list containing all the leaf elements in the given BST.
// template <typename T>
// DLList<T> enList(const BST<T> & bst) {
//   DLList<T> dllist;
//   // scan the tree recursively
//   enListHelper(bst.root, dllist);
//   return dllist;
// }

// // recursion helper that add the leaf nodes to the doubly linked list.
// template <typename T>
// void enListHelper(const typename BST<T>::Node * node, DLList<T> & dllist) {
//   // return if go to the end
// 	if (node == NULL) {
//     return;
//   }
//   if (node->left == nullptr && node->right == nullptr) {
//     // now the node is a leaf so add it to the doubly linked dllist.
// 		DLLNode<T> newNode = new DLLNode<T>(node->data);
//     dllist.push_back(newNode);
//   } 
// 	else {
//     // the node is not a leaf, go to its children
//     enListHelper(node->left, dllist);
//     enListHelper(node->right, dllist);
//   }
// }