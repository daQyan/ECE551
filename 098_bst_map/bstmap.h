#include <cstdio>
#include <cstdlib>
#include <iostream>

#include "map.h"  

template<typename K, typename V>
class BstMap : public Map<K, V> {
  private:
    class Node {
      public:
        K key;
        V value;
        Node * left;
        Node * right;
        // Node() : key(0), value(0), left(NULL), right(NULL) {}
        Node(K key, V val) : key(key), value(val), left(NULL), right(NULL) {}
    };
  Node * root;

  public:
    BstMap<K, V>() : root(NULL) {}

    BstMap(const BstMap & rhs) : root(NULL) { root = copyHelper(rhs.root); }
    Node * copyHelper(Node * current) {
      if (current == NULL) {
        return NULL;
      }
      Node * copyNode = new Node(current->key, current->value);
      copyNode->left = copyHelper(current->left);
      copyNode->right = copyHelper(current->right);
      return copyNode;
    }

    BstMap & operator=(const BstMap & rhs) {
      if (this != &rhs) {
        deleteHelper(root);
        root = copyHelper(rhs.root);
      }
      return *this;
    }

    ~BstMap<K, V>() {
      deleteHelper(root);
    }
    // recursive 
    void deleteHelper(Node * current) {
      if (current != NULL) {
        deleteHelper(current->left);
        deleteHelper(current->right);
        delete current;
      }
    }


    virtual void add(const K & key, const V & value) {
      Node ** curr = &root;
      while (*curr != NULL) {
        if ((*curr)->key == key) {
          (*curr)->value = value;
          return;
        }
        if ((*curr)->key > key) {
          curr = &(*curr)->left;
        }
        else {
          curr = &(*curr)->right;
        }        
      }
      *curr = new Node(key, value);
    }

    
    virtual const V & lookup(const K & key) const throw(std::invalid_argument) {
      Node * curr = root;
      while (curr != NULL) {
        if (curr->key == key) {
          return curr->value;
        }
        if (curr->key > key) {
          curr = curr->left;
        }
        else {
          curr = curr->right;
        }        
      }
      throw std::invalid_argument("key not found!");
    }


    virtual void remove(const K & key) {
      Node ** curr = &root;
      Node * temp;
      while (*curr != NULL) {
        if ((*curr)->key == key) {
          if ((*curr)->left == NULL) {
            temp = (*curr)->right;
            delete *curr;     // *curr is a pointer, curr hai zai
            *curr = temp;            
          }
          else if ((*curr)->right == NULL) {
            temp = (*curr)->left;
            delete * curr;
            *curr = temp;
          }
          else {
            Node ** near = curr;
            curr = &(*curr)->left;
            while ((*curr)->right != NULL) {
              curr = &(*curr)->right;
            }
            (*near)->key = (*curr)->key;
            (*near)->value = (*curr)->value;
            temp = (*curr)->left;
            delete(*curr);
            (*curr) = temp; ///
          }
        }
        else if (key < (*curr)->key) {
          curr = &(*curr)->left;
        }
        else {
          curr = &(*curr)->right;
        }
      }
    }

};