#ifndef INORDERTRAVERSAL_H
#define INORDERTRAVERSAL_H

#include <iterator>
#include <stack>
#include "../binarytree.h"
#include "TreeTraversal.h"

using namespace std;

/**
 * A derived, templatized class for inorder traversal algorithms on trees.
 *
 * Simulates an iterative traversal of a given tree using a stack
 * and a given root node.
 */
template <typename T>
class InorderTraversal : public TreeTraversal<T> {
  public:
    /**
     * Initializes a Inorder TreeTraversal of a tree,
     * with the traversal storing the tree's root.
     * Hint: See lab handout for guidance
     *
     * @param root The root node of the tree
     */
    InorderTraversal(typename BinaryTree<T>::Node* root)
	    : root(root)
    {
      while(root!=NULL){
      stack.push(root);
      root = root->left;
      }
      // your code here
    }

    /**
     * Returns an iterator for the traversal starting at the root node.
     * Important for sake of looping through an iterator's contents.
     *
     * @return The iterator object pointing to the first node in the traversal
     */
    typename TreeTraversal<T>::Iterator begin() {
      InorderTraversal* iot = new InorderTraversal(root);
      return typename TreeTraversal<T>::Iterator(*iot, root);
    }

    /**
     * Returns an iterator for the traversal pointing to the
     * element one past the end of the traversal.
     * Important for the sake of looping through an iterator's contents
     *
     * @return The iterator object pointing to the elemnt after the end of the traversal.
     */
    typename TreeTraversal<T>::Iterator end() {
      return typename TreeTraversal<T>::Iterator();
    }

    /**
     * Given a node in the tree, add the next appropriate
     * nodes to the stack such that when popped, and inorder
     * traversal is simulated.
     * Hint: See lab handout for guidance
     *
     * @param treeNode The subroot that determines what next nodes
     *        should be added to the traversal
     */
    void add(typename BinaryTree<T>::Node *& treeNode) {
      // your code here
      treeNode = treeNode->right;
      while(treeNode!=NULL){
        stack.push(treeNode);
        treeNode = treeNode->left;
      }
     }
    /*  if(treeNode==NULL){
        stack.pop();
      }
      else if(treeNode->left!=NULL){

      stack.push(treeNode);
      treeNode = treeNode->left;
      stack.push(treeNode);
      }
      else{
        if(root->right !=NULL){
          stack.push(root->right);
        }
        else{
          stack.pop();
        }
        //stack.push(treeNode->right);
      }
    }*/
/*
      else if(treeNode ->left == NULL){
      //  if(treeNode->right!=NULL){
          stack.push(treeNode->right);
      //  }
      //  else{
      //    pop();
      //  }
      }
      else{
        stack.push(treeNode->left);
      }
    }
    */

    /**
     * Removes and returns the current node in the traversal.
     *
     * @return The current node in the traversal
     */
    typename BinaryTree<T>::Node* pop() {
      typename BinaryTree<T>::Node* topNode = stack.top();
      stack.pop();
      return topNode;
    }

    /**
     * Returns the current node in the traversal or
     * NULL if the stack is empty.
     *
     * @return The current node in the traversal
     */
    typename BinaryTree<T>::Node* peek() const {
      return empty() ? NULL : stack.top();
    }

    /**
     * Returns true if the traversal is empty.
     *
     * @return true if the traversal is empty.
     */
    bool empty() const {
      return stack.empty();
    }

  private:
    stack<typename BinaryTree<T>::Node*> stack;
    typename BinaryTree<T>::Node* root;
};
#endif
