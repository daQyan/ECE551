#include <cstdio>
#include <cstdlib>
#include <vector>
#include <iostream>
#include <exception>

/** The templated class MyDataS achieves the functions like insert, find, getmin, remove, and sort as good as HEAP and BST 
 * insert : O(lgN)
 * find : O(lgN)
 * getmin :  O(1)
 * remove : O(lgN)
 * sort : O(N)
 */
template <typename T>
class MyDataS{
public:
    class Node {
    public:
        T data;
        Node * left;
        Node * right;
    public:
        explicit Node(T el) : data(el), left(NULL), right(NULL) {}
    };
    
    Node *root;
    Node *min; //A node pointer that points to the min value of the BST

    MyDataS() : root(NULL), min(NULL) {}
    bool find(const T &key);
    void sort(); //Print in Inorder
    void inorder(Node *);
    void destroyHelp(Node * rt);

 /** The deconstructor is used to destory the node and release the memory  **/
    ~MyDataS() {
        std::cout << "Destroying MyDataS" << std::endl;
        destroyHelp(root);
    }
 /** The function insert is to insert a new value into our structure
 * @param el which is a type T constant reference and represents the value we are going to insert
 */
    void insert(const T & el) {
        root = insertHelper(el, root);
        if(min == NULL) {// If there is no min value, set the min point to the root
            min = root;
        }
        else if(min->data < el){// If the new insert value is smaller than our current minimum node value, we update the min pointer to point at the new node
            min = findMin(root);
        }
    }

 /** The function insertHelper is to help implement the insert function by tracing the new insert position
 * @param el which is a type T constant reference and represents the value we are going to insert
 * @param rt is the node pointer and represents our root node
 */
    Node * insertHelper(const T & el, Node * rt) {
        if (rt == NULL) {//create a new root if it is NULL
            return new Node(el);
        } 
        else {//If the new value is smaller that current node, then compare the new value with its left node. Otherwise, compare the new value with its right node.
            if (el < rt->data) {
                rt->left = insertHelper(el, rt->left);
            } 
            else {
                rt->right = insertHelper(el, rt->right);
            }
            return(rt);
        }
    }

 /** The function findMin is to find the minimum node in the structure by searching its leftmost node.
 * @param rt is the node pointer and represents our root node
 */
    Node *findMin(Node * rt) {
        if(rt == NULL) {
            return NULL;
        }
        while (rt->left != NULL) {
            rt = rt->left;
        }
        return rt;
    }

/** The function findMax is to find the maximum node in the structure by searching its rightmost node.
 * @param rt is the node pointer and represents our root node
 */  
    Node * findMax(Node * rt) {
        while (rt->right != NULL) {
            rt = rt->right;
        }
        return rt;
    }
/** The function remove is to delete the required node and adjust the structure after remove.
 * @param el is the target value we are going to delete.
 */     
    void remove(const T & el){  
        if (!find(el)) {
            throw ("The target value is not found!");
        }   
        if(min->data == el){ // If the target data is minimum value, a new minimum value is required after remove.
            root = removeHelp(el, root);
            min = findMin(root);
        }
        else {
            root = removeHelp(el, root);
        }
    }

/** The function removeHelp is to help achieve the remove function by finding the target position and adjusting the whole structure
 * @param el is the target value we are going to delete.
 * @param rt is the node pointer and represents our root node
 */
    Node *removeHelp(const T & el, Node * rt){
        if (rt == NULL) {
            return NULL;
        }
        if (el < rt->data) {// the target value is smaller than the node value, then we move to its left node
            rt->left = removeHelp(el, rt->left);
        } 
        else {
            if (el > rt->data) {// the target value is larger than the node value, then we move to its right node
                rt->right = removeHelp(el, rt->right);
            } 
            else { // found the target 
                if (rt->left == NULL) { // the target node has zero or only a right children
                    Node * temp = rt->right;
                    delete rt;
                    return temp;
                } 
                if (rt->right == NULL) { // the target node has only a left children
                    Node * temp = rt->left;
                    delete rt;
                    return temp;
                }
                Node * temp = findMax(rt->left);// the target node has only a left children
                rt->data = temp->data;
                rt->left = removeHelp(temp->data, rt->left);
            } 
        }
        return rt;
    }
/** The function getmin is obtain its minimum value */
    T getmin(){
        return min->data;
    }
};


/** The function find is to check whether a value is in the structure or not. If it exists, return true. Otherwise, return false.
 * @param key is the value we are going to search
 */
template <typename T>
bool MyDataS<T>::find(const T &key){
    Node *curr = root;
    while(curr != NULL){
        if(key == curr->data){
            return true;
        }
        else if(key < curr->data){
            curr = curr->left;
        }
        else{
            curr = curr->right;
        }
    }
    return false;
}

/** The function destroyHelp is to help deconstructor to destory all the nodes. It will delete parent nodes and children nodes by implementing recursion method.
 * @param rt is the node pointer and represents our root node
 */
template <typename T>
void MyDataS<T>::destroyHelp(Node * rt) {
    if (rt->left != NULL){
      destroyHelp(rt->left);
    }
    if (rt->right != NULL) {
      destroyHelp(rt->right);
    }
    delete rt;
}

/** The function sort aims at sorting the data value in order */
template <typename T>
void MyDataS<T>::sort(){
    inorder(root);
}

/** The function inorder is to print the data in our structure in order
 * @param curr is the node pointer we use to trace the nodes in the structure.
 */
template <typename T>
void MyDataS<T>::inorder(Node *curr){
    if(curr == NULL){
        return;
    }
    inorder(curr->left);
    std::cout << curr->data << std::endl;
    inorder(curr->right);
}