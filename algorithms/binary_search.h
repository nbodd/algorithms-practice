//
//  binary_search.hpp
//  algorithms
//
//  Created by Nick on 2/2/16.
//  Copyright © 2016 Nick. All rights reserved.
//

#ifndef binary_search_hpp
#define binary_search_hpp

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

typedef int Node;

struct BinaryTreeNode {
    int key;
    Node val;
    
    BinaryTreeNode(int _key, Node _val) {
        key = _key;
        val = _val;
    }
};

bool BinaryTreeNodeCompare(BinaryTreeNode & a, BinaryTreeNode & b) {
    return a.key > b.key;
}



#endif
 
