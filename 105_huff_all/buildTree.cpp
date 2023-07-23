#include "node.h"

Node *  buildTree(uint64_t * counts) {
  //WRITE ME!
  priority_queue_t pque;
  for (size_t i = 0; i < 257; i++) {
    if (counts[i] != 0) {
      pque.push(new Node(i, counts[i]));
      
    }
    
  }
  while (pque.size() != 1) {
    Node * node1 = pque.top();
    pque.pop();
    Node * node2 = pque.top();
    pque.pop();
    pque.push(new Node(node1, node2));
  }
  return pque.top();
}
  

  
