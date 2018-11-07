#include <cmath>
/**
 * @file avltree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */

template <class K, class V>
V AVLTree<K, V>::find(const K& key) const
{
    return find(root, key);
}

template <class K, class V>
V AVLTree<K, V>::find(Node* subtree, const K& key) const
{
    if (subtree == NULL)
        return V();
    else if (key == subtree->key)
        return subtree->value;
    else {
        if (key < subtree->key)
            return find(subtree->left, key);
        else
            return find(subtree->right, key);
    }
}

template <class K, class V>
void AVLTree<K, V>::rotateLeft(Node*& t)
{
    functionCalls.push_back("rotateLeft"); // Stores the rotation name (don't remove this)
    // your code here
    if(t == NULL){
      return;
    }
    Node * temp = t;
    t = t->right;
    temp->right = t->left;
    t->left = temp;
    return ;

}

template <class K, class V>
void AVLTree<K, V>::rotateLeftRight(Node*& t)
{
    functionCalls.push_back("rotateLeftRight"); // Stores the rotation name (don't remove this)
    // Implemented for you:
    rotateLeft(t->left);
    rotateRight(t);
}

template <class K, class V>
void AVLTree<K, V>::rotateRight(Node*& t)
{
    functionCalls.push_back("rotateRight"); // Stores the rotation name (don't remove this)
    // your code here
    if(t == NULL){
      return;
    }
    Node * temp = t;
    t = t->left;
    temp->left = t->right;
    t->right = temp;
    return;
}

template <class K, class V>
void AVLTree<K, V>::rotateRightLeft(Node*& t)
{
    functionCalls.push_back("rotateRightLeft"); // Stores the rotation name (don't remove this)
    // your code here
    rotateRight(t->right);
    rotateLeft(t);
}

template <class K, class V>
void AVLTree<K, V>::rebalance(Node*& subtree)
{
    // your code here
   if(subtree == NULL){
     return ;
   }
   else{
     subtree->height = getHeight(subtree);
     if((getHeight(subtree->left) - getHeight(subtree->right)) == 2){
       if((getHeight((subtree->left)->left) - getHeight((subtree->left)->right)) == 1){
         rotateRight(subtree);
         subtree->height = getHeight(subtree);
         return;
       }
       else{
         rotateLeftRight(subtree);
         subtree->height = getHeight(subtree);
         return;
       }
   }
   else if((getHeight(subtree->right) - getHeight(subtree->left)) == 2){
     if((getHeight((subtree->right)->right) - getHeight((subtree->right)->left)) == 1){
       rotateLeft(subtree);
       subtree->height = getHeight(subtree);
       return;
     }
     else{
       rotateRightLeft(subtree);
       subtree->height = getHeight(subtree);
       return;
     }
   }
   else{
     return;
   }
 }
}

template <class K,class V>
int AVLTree<K,V>::getHeight(Node*subroot){
  if(subroot == NULL){
    return -1;
  }
  else{
    return 1+fmax(getHeight(subroot->left),getHeight(subroot->right));
  }
}

template <class K, class V>
void AVLTree<K, V>::insert(const K & key, const V & value)
{
    insert(root, key, value);
}

template <class K, class V>
void AVLTree<K, V>::insert(Node*& subtree, const K& key, const V& value)
{
    // your code here
    if(subtree == NULL){
      subtree = new Node(key,value);
    }

    if(key < subtree->key){
      insert(subtree->left,key,value);
      subtree->height = getHeight(subtree);
      rebalance(subtree);
      return;
    }
    else if(key > subtree->key){
      insert(subtree->right,key,value);
      subtree->height = getHeight(subtree);
      rebalance(subtree);
      return;
    }
    else{
      subtree->value = value;
      return;
    }
}

template <class K, class V>
void AVLTree<K, V>::remove(const K& key)
{
    remove(root, key);
}

template <class K, class V>
void AVLTree<K, V>::remove(Node*& subtree, const K& key)
{
    if (subtree == NULL)
        return;
    if (key < subtree->key) {
        // your code here
        remove(subtree->left,key);
        subtree->height = getHeight(subtree);
        rebalance(subtree);
        return;
    } else if (key > subtree->key) {
        remove(subtree->right,key);
        subtree->height = getHeight(subtree);
        rebalance(subtree);
        return;
        // your code here
    } else {
        if (subtree->left == NULL && subtree->right == NULL) {
            delete subtree;
            subtree = NULL;
            return;
            /* no-child remove */
            // your code here
        } else if (subtree->left != NULL && subtree->right != NULL) {
            /* two-child remove */
            Node * temp = subtree->left;
            while(temp->right !=NULL){
              temp = temp->right;
            }
            swap(subtree, temp);
          //subtree->key = temp->key;
          //subtree->value = temp->value;
        //  temp->key = temp_K;
          remove(subtree->left, key);
            // your code here
        } else {
            /* one-child remove */
            if(subtree->left != NULL && subtree->right == NULL){
              Node * temp = subtree;
              subtree = subtree->left;
              delete temp;
              return;
            }
            else{
              Node * temp = subtree;
              subtree = subtree->right;
              delete temp;
              return;
            }
            // your code here
        }
        // your code here
    }
}
