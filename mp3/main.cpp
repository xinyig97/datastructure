#include "list.h"

int main() {
  List<int> list;
  for (unsigned i = 3; i >0; i--) { list.insertBack(i); }
list.print(cout);
  //list.print(cout)
  //list.reverse();
  List<int> list2;
  for (unsigned i = 6; i < 12; i++) { list2.insertBack(i); }
  list.mergeWith(list2);
  //list.sort();
  list.print(cout);
//  list.waterfall();
  return 0;
}
