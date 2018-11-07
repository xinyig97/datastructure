/**
 * @file binarytree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */
#include "TreeTraversals/InorderTraversal.h"
#include <iostream>
/**
 * @return The height of the binary tree. Recall that the height of a binary
 *  tree is just the length of the longest path from the root to a leaf, and
 *  that the height of an empty tree is -1.
 */
template <typename T>
int BinaryTree<T>::height() const
{
    // Call recursive helper function on root
    return height(root);
}

/**
 * Private helper function for the public height function.
 * @param subRoot
 * @return The height of the subtree
 */
template <typename T>
int BinaryTree<T>::height(const Node* subRoot) const
{
    // Base case
    if (subRoot == NULL)
        return -1;

    // Recursive definition
    return 1 + max(height(subRoot->left), height(subRoot->right));
}

/**
 * Prints out the values of the nodes of a binary tree in order.
 * That is, everything to the left of a node will be printed out before that
 * node itself, and everything to the right of a node will be printed out after
 * that node.
 */
template <typename T>
void BinaryTree<T>::printLeftToRight() const
{
    // Call recursive helper function on the root
    printLeftToRight(root);

    // Finish the line
    cout << endl;
}

/**
 * Private helper function for the public printLeftToRight function.
 * @param subRoot
 */
template <typename T>
void BinaryTree<T>::printLeftToRight(const Node* subRoot) const
{
    // Base case - null node
    if (subRoot == NULL)
        return;

    // Print left subtree
    printLeftToRight(subRoot->left);

    // Print this node
    cout << subRoot->elem << ' ';

    // Print right subtree
    printLeftToRight(subRoot->right);
}

/**
 * Flips the tree over a vertical axis, modifying the tree itself
 *  (not creating a flipped copy).
 */
template <typename T>
void BinaryTree<T>::mirror()
{
    //your code here
    mirror(root);
}

template <typename T>
void BinaryTree<T>::mirror(Node* Subroot){
  if(Subroot == NULL){
    return;
  }
  else{
    Node* temp = Subroot->right;
    Subroot->right = Subroot->left;
    Subroot->left = temp;
    mirror(Subroot->left);
    mirror(Subroot->right);
  }
}

/**
 * isOrdered() function iterative version
 * @return True if an in-order traversal of the tree would produce a
 *  nondecreasing list output values, and false otherwise. This is also the
 *  criterion for a binary tree to be a binary search tree.
 */
template <typename T>
bool BinaryTree<T>::isOrderedIterative() const
{
    // your code here
    if(root == NULL){
      return true;
    }
    else{
      InorderTraversal<T> iot(root);
      typename TreeTraversal<T>::Iterator it = iot.begin();
      T cur = (*it)->elem;
      ++it;
      while(it!=iot.end()){
        T next = (*it)->elem;
        if(cur > next){
          return false;
        }
        else{
          cur = next;
          ++it;
        }
      }
      return true;
    }
}

/**
 * isOrdered() function recursive version
 * @return True if an in-order traversal of the tree would produce a
 *  nondecreasing list output values, and false otherwise. This is also the
 *  criterion for a binary tree to be a binary search tree.
 */
template <typename T>
bool BinaryTree<T>::isOrderedRecursive() const
{
    // your code here
    if(root == NULL){
      return true;
    }
    else{
    return isOrderedRecursive_left(root->left,root->elem) && isOrderedRecursive_right(root->right,root->elem);
  }
}

template <typename T>
bool BinaryTree<T>::isOrderedRecursive_left(const Node* subroot,T data_max) const{
  if(subroot == NULL){
    return true;
  }
  else{
    if(subroot->elem > data_max){
      return false;
    }
    else{
      return isOrderedRecursive_left(subroot->left, data_max) && isOrderedRecursive_right(subroot->right,subroot->elem);
    }
  }
}

template <typename T>
bool BinaryTree<T>::isOrderedRecursive_right(const Node* subroot, T data_min) const{
  if(subroot == NULL){
    return true;
  }
  else{
    if(subroot->elem < data_min){
      return false;
    }
    else{
      return isOrderedRecursive_left(subroot->left,subroot->elem) && isOrderedRecursive_right(subroot->right, data_min);
    }
  }
}
/*
template <typename T>
bool BinaryTree<T>::isOrderedRecursive_right(const Node* subroot, T data_min, T data_max) const{
  if(subroot == NULL){
    return true;
  }
  else if(subroot->left == NULL&&subroot->right!=NULL){
    if(subroot->right->elem > subroot->elem){
      return isOrderedRecursive(subroot->right);
    }
    else{
      return false;
    }
  }
  else if(subroot->right == NULL&&subroot->left!=NULL){
    if(subroot->left->elem < subroot->elem){
      return isOrderedRecursive(subroot->left);
    }
    else{
      return false;
    }
  }
  else if(subroot->left!=NULL && subroot->right!=NULL){
    if(subroot->right->elem > subroot->elem && subroot->left->elem < subroot->elem){
      return isOrderedRecursive(subroot->right) && isOrderedRecursive(subroot->left);
    }
    else{
      return false;
    }
  }
  else{
    return true;
  }
}*/

/**
 * creates vectors of all the possible paths from the root of the tree to any leaf
 * node and adds it to another vector.
 * Path is, all sequences starting at the root node and continuing
 * downwards, ending at a leaf node. Paths ending in a left node should be
 * added before paths ending in a node further to the right.
 * @param paths vector of vectors that contains path of nodes
 */
template <typename T>
void BinaryTree<T>::printPaths(vector<vector<T> > &paths) const
{
    paths.clear();
    vector<T> temp;
    paths.push_back(temp);
    printPath(paths, root);
    // your code here
}

template <typename T>
void BinaryTree<T>::printPath(vector<vector<T>> &paths, Node* subroot)const{
  if(subroot!=NULL){
    (paths.back()).push_back(subroot->elem);
    vector<T> temp_1 = paths.back();
    //temp_1.push_back(subroot->elem);
    if(subroot->left!=NULL){
      printPath(paths,subroot->left);
    }
    /*if(subroot->right!=NULL){
      paths.push_back(temp_1);
      printPath(paths,subroot->right);
   }*/
   if(subroot->left == NULL &&subroot->right!=NULL){
     //paths.push_back(temp_1);
     printPath(paths,subroot->right);
   }
   if(subroot->left!=NULL && subroot->right!=NULL){
     paths.push_back(temp_1);
     printPath(paths,subroot->right);
   }
}
}


/**
 * Each node in a tree has a distance from the root node - the depth of that
 * node, or the number of edges along the path from that node to the root. This
 * function returns the sum of the distances of all nodes to the root node (the
 * sum of the depths of all the nodes). Your solution should take O(n) time,
 * where n is the number of nodes in the tree.
 * @return The sum of the distances of all nodes to the root
 */
template <typename T>
int BinaryTree<T>::sumDistances() const
{
    // your code here
    return -1;
}
