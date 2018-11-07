/* Your code here! */

#ifndef _DSETS_H_
#define _DSETS_H_

#include <string>
#include <vector>
class DisjointSets{

  public:
  DisjointSets();
  ~DisjointSets();
  void addelements(int num);
  int find(int elem);
  void setunion(int a, int b);
  int size(int elem);

  private:
    std::vector<int> elems_;
};
#endif
