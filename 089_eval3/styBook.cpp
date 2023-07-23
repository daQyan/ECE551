#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <utility>
#include <cstdlib>
#include <set>
#include <queue>
#include "styBook.hpp"

/// @brief check the referenced page is reachable by comparing the boundary with max and min referenced page
/// @param pages is the pages in the story
void styBook::checkRefering(std::vector<onePage>& pages) {
  size_t maxPage = 0;
  size_t minPage = 1;
  for (size_t i = 0; i < allPages.size(); i++) {
    for (size_t j = 0; j < allPages[i].navigTxt.size(); j++) {
      if (allPages[i].navigTxt[j].first > maxPage) {
        maxPage = allPages[i].navigTxt[j].first;
      }
      if (allPages[i].navigTxt[j].first < minPage) {
        minPage = allPages[i].navigTxt[j].first;
      }
    }			
  }
  if (minPage < 1 || maxPage > allPages.size()) {
    throw std::runtime_error("referenced pages out of boundary!");
  }				
}

/// @brief check each page reachable is refered by at least one of other reahcable pages
/// @param pages is the pages in the story
void styBook::checkRefered(std::vector<onePage>& pages) {
  for (size_t num = 2; num <= allPages.size(); num++) {
    size_t hasRef = 0;
    // std::cout << "check check\n";
    for (size_t i = 0; i < allPages.size(); i++) {
      for (size_t j = 0; j < allPages[i].navigTxt.size(); j++) {
        if (allPages[i].navigTxt[j].first == num && (num != i+1)) {
          hasRef = 1;
          break;
        }					
      }
    }
    if (!hasRef) {
      throw std::runtime_error("some page's reference is not found!"); //
    }			
  }
}

/** check if the pages have Page WIN and LOSE
 * @param pages is the vector hold all pages in the stry
 */
void styBook::checkWinLose(std::vector<onePage>& pages) {
  bool hasWin = false;
  bool hasLose = false;
  for (size_t i = 0; i < allPages.size(); i++) {
    if (allPages[i].navigMode == LOSE) {
      hasLose = true;
    }
    if (allPages[i].navigMode == WIN) {
      hasWin = true;
    }
  }
  if (! (hasWin&&hasLose)) {
    throw std::runtime_error("pages not have win and lose!");
  }
}

// New Step4
/** find all non-loop paths that can win the game using recursion
 * @param paths store all win paths
 * @param currPath store the current path 
 * @param visited store visited page number
 * @param node is in format pair(page index, choice)
*/
void styBook::findExit() {
  std::vector<std::vector<std::pair<size_t, size_t> > > paths;			    
  std::vector<std::pair<size_t, size_t> > currPath;          
  std::set<size_t> visited;		                                  
  std::pair<size_t, size_t> node(1,0);                             
  size_t guardNode = 1;
  // find the guard node
  for (size_t i = 0; i < allPages.size(); i++) {
    if (allPages[i].navigTxt.size() == 1) {
      guardNode = i+1;
    }
    else break;
  }
  // start recursion to get the path
  go(node, visited, currPath, paths, guardNode);	
  printExitpaths(paths);
}

// recursion helper: go through each line using DFS and store paths that win
void styBook::go(std::pair<size_t, size_t>& node, std::set<size_t>& visited, std::vector<std::pair<size_t, size_t> >& currPath, 
    std::vector<std::vector<std::pair<size_t, size_t> > >& paths, size_t gNode) {  
  if (visited.find(node.first) != visited.end()) {
    return;
  }	
  currPath.push_back(node);
  visited.insert(node.first);
  // if the node is WIN
  if (allPages[node.first - 1].navigMode == WIN) {
    paths.push_back(currPath);
    std::vector<std::pair<size_t, size_t> > & temp = *paths.rbegin(); // use size for index
    for (size_t i = 0; i < temp.size() - 1; i++) {
      temp[i].second = temp[i + 1].second;
    }
    temp.rbegin()->second = 0;
    visited.erase(currPath.rbegin()->first);
    currPath.pop_back();
  }
  // if the node is LOSE
  else if (allPages[node.first - 1].navigMode == LOSE) {			
    visited.erase(currPath.rbegin()->first);
    currPath.pop_back();
  }
  // if the node is STEP, traverse the page num
  else {    
    for (size_t i = 0; i < allPages[node.first-1].navigTxt.size(); i++) {
      size_t pdex =  allPages[node.first-1].navigTxt[i].first;	
      std::pair<size_t, size_t> tempnode (pdex, i+1);
      go(tempnode, visited, currPath, paths, gNode);			
    }
    // pop the guard node and remove the guard node from visited
    if (currPath.rbegin()->first != gNode) {
      visited.erase(currPath.rbegin()->first);
      currPath.pop_back();            
    }
  }
}


// print all the valid win paths
void styBook::printExitpaths(std::vector<std::vector<std::pair<size_t, size_t> > >& paths) {
  if (paths.begin() == paths.end()) {
    std::cout << "This story is unwinnable!" << std::endl;
  }
  std::vector<std::vector<std::pair<size_t, size_t> > >::iterator path = paths.begin();
  while(path != paths.end()) {			
    std::vector<std::pair<size_t, size_t> >::iterator node = path->begin();
    while (node != path->end()) {
      if (node->second != 0) {
        std::cout << node->first << "(" << node->second << "),";
      }
      else {
        std::cout << node->first << "(win)" << std::endl;
      }
      ++node;
    }
    ++path;
  }
}

// New Step3
/** using BFS to get the depth of each page number
 * @param depthSheet store the depth of each page
 * @param visited store visited page number in a set
 * @param toVisit page number to visit, store in a queue
 * @param n
*/
std::vector<size_t> styBook::getDepth() {
  std::vector<size_t> depthSheet(allPages.size(), 0);
  std::set<int> visited;
  std::queue<int> toVisit;
  // start from page1
  toVisit.push(1);
  depthSheet[0] = 0;
  visited.insert(1);
  while (! toVisit.empty())	{
    int tempdex = toVisit.front();
    toVisit.pop();
    if (allPages[tempdex - 1].navigMode != STEP) {
      continue;
    }			
    // traverse the children nodes
    for (size_t i = 0; i < allPages[tempdex-1].navigTxt.size(); i++) {
      int pdex = allPages[tempdex-1].navigTxt[i].first;
      if (visited.find(pdex) == visited.end())	{
        visited.insert(pdex);
        depthSheet[pdex-1] = depthSheet[tempdex-1] + 1;
        toVisit.push(pdex);
      }				
    }			
  }
  return depthSheet;
}

/** print the depth sheet using @param depthSheet get from the previous function
*/
void styBook::printDepth(std::vector<size_t>& depthSheet) {
  std::vector<size_t>::iterator itr = depthSheet.begin();
  size_t pdex = 1;
  while (itr != depthSheet.end()) {
    if (*itr == 0 && pdex != 1) {
      std::cout << "Page " << pdex << " is not reachable" << std::endl;
    }
    else {
      std::cout << "Page " << pdex << ":" << *itr << std::endl;
    }
    ++pdex;
    ++itr;
  }
}

// play the cyoa story, start from page 1 and go recursion to play next next page
void styBook::goPlay() {
  playHelper(1);
}
// recursion helper to play each page
void styBook::playHelper(size_t num) {
  size_t index = num-1;
  allPages[index].printPage();
  if (allPages[index].navigMode == LOSE || allPages[index].navigMode == WIN) {		// win or lose
    return;			// directly exit will cause memory leak
  }
  size_t pNum = checkNumValid(index);
  playHelper(pNum);
}


/** take user's input and check if the input number from the user is valid, if not repeat until it is 
 * @param index is page number
*/
size_t styBook::checkNumValid(size_t index) {
  std::string input;
  std::cin >> input;

  char * ptr;
  size_t pNum = strtol(input.c_str(), &ptr, 10);
  // check is a number
  size_t n = allPages[index].navigTxt.size();
  if (pNum == 0 || *ptr != '\0') {
    std::cout << "That is not a valid choice, please try again" << std::endl;
    return checkNumValid(index);
  }
  // check number is reachable
  else if (pNum > 0 && pNum <= n) {
    return allPages[index].navigTxt[pNum-1].first;
  }	
  else {
    std::cout << "That is not a valid choice, please try again" << std::endl;
    return checkNumValid(index);
  }
}

