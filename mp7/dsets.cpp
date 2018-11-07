/* Your code here! */

#include"dsets.h"
#include<cmath>

DisjointSets::DisjointSets(){}
DisjointSets::~DisjointSets(){}

void DisjointSets::addelements(int num){
    for(int i =0 ;i < num; i ++){
      elems_.push_back(-1);
      //add the right number of elements in the vectors
    }
    return;
}

int DisjointSets::find(int elem){
  //if this elem is the root, which means elems_[elem] is negative, return this element.
  if(elems_[elem]<0){
    return elem;
  }
  else{
    //otherwise, keep finding its root
    int root = find(elems_[elem]);
    //apply path suppression
    elems_[elem] = root;
    //return root
    return root;
  }
}

void DisjointSets::setunion(int a, int b){
  //find two roots
  int root_a = find(a);
  int root_b = find(b);
  //if they are already in the same root, just leav it
  if(root_a==root_b){
    return;
  }
  //otherwise, if the first has more element, which means more negative, set that as the new root
  else if(elems_[root_a]<elems_[root_b]){
    //update the count
    elems_[root_a] = elems_[root_a]+elems_[root_b];
    //update the root
    elems_[root_b] = root_a;
    return;
  }
  else{
    //otherwise, set the second as the new root
    elems_[root_b] = elems_[root_a]+elems_[root_b];
    elems_[root_a] = root_b;
    return;
  }
}

int DisjointSets::size(int elem){
  //find the root and then return the absolute value of the size
  int temp_r = find(elem);
  return elems_[temp_r]*-1;
}
