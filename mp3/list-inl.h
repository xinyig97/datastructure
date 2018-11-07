#include<cmath>
/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 */

/**
 * Destroys the current List. This function should ensure that
 * memory does not leak on destruction of a list.
 */
template <class T>
List<T>::~List() {
  /// @todo Graded in MP3.1
    if(tail_ != NULL){
      if(head_!=NULL){
      while(tail_!=NULL){
        ListNode* temp = tail_;
        tail_ = tail_->prev;
        delete temp;
      }
        tail_ = NULL;
        head_ = NULL;
      }
      else{
        tail_ = NULL;
      }
    }

  else{
    if(head_!=NULL){
      head_ = NULL;
    }
  }

}

/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <class T>
void List<T>::clear() {
  /// @todo Graded in MP3.1
  if(head_ !=NULL && tail_ != NULL){
    while(tail_!=NULL){
      ListNode* temp = tail_;
      tail_ = tail_->prev;
      delete temp;
    }
    tail_ = NULL;
    head_ = NULL;
    return;
  }
  else{
    head_ = NULL;
    tail_ = NULL;
    return;
  }
}

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <class T>
void List<T>::insertFront(T const & ndata) {
  /// @todo Graded in MP3.1
  if(head_ == NULL){
    head_ = new ListNode(ndata);
    tail_ = head_;
    length_ ++;
    return;
  }
  // else{
  //   if(tail_ == NULL){
  //     ListNode* temp = head_;
  //     while(temp->next!=NULL){
  //       temp = temp->next;
  //     }
  //     tail_ = temp;
  //   }
    head_->prev = new ListNode(ndata);
    ListNode* temp = head_->prev;
    temp->next = head_;
    head_ = head_->prev;

    length_ ++;
    return;

}



/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <class T>
void List<T>::insertBack(const T & ndata) {
  /// @todo Graded in MP3.1
  if(tail_ == NULL){
    tail_ = new ListNode(ndata);
    head_ = tail_;
    length_ ++;
    return;
  }
  else{
    tail_->next = new ListNode(ndata);
    ListNode* temp = tail_->next;
    temp->prev = tail_;
    tail_ = tail_->next;
    length_++;
    return;
  }
}

/**
 * Reverses the current List.
 */
template <class T>
void List<T>::reverse() {
  reverse(head_, tail_);
}

/**
 * Helper function to reverse a sequence of linked memory inside a List,
 * starting at startPoint and ending at endPoint. You are responsible for
 * updating startPoint and endPoint to point to the new starting and ending
 * points of the rearranged sequence of linked memory in question.
 *
 * @param startPoint A pointer reference to the first node in the sequence
 *  to be reversed.
 * @param endPoint A pointer reference to the last node in the sequence to
 *  be reversed.
 */
template <class T>
void List<T>::reverse(ListNode *& startPoint, ListNode *& endPoint) {
  /// @todo Graded in MP3.1
  if(startPoint == NULL){
    return;
  }
  else if(startPoint == endPoint){
    ListNode* temp = startPoint->prev;
    startPoint->prev = startPoint->next;
    startPoint->next = temp;
    temp = startPoint;
    startPoint = endPoint;
    endPoint = temp;
    return;
  }
  else{
  ListNode* temp = startPoint;
  while(temp->next!=NULL){
    ListNode* store = temp->next;
    temp->next = temp->prev;
    temp->prev = store;
    temp = store;
  }
  temp->next = temp->prev;
  temp->prev = NULL;
  //startPoint = temp;
  endPoint = startPoint;
  startPoint = temp;
  return;
}
}
/*
  if(startPoint == NULL){
    std::cout << "wrong start" << std::endl;
  }
  else if(endPoint == NULL){
    std::cout << "wrong end" << std::endl;
  }
  else if(startPoint == endPoint){
    ListNode* temp = startPoint->next;
    startPoint->next = startPoint->prev;
    startPoint->prev = temp;
    return;
  }
  else if(startPoint->next == endPoint){
    ListNode* temp = startPoint->next;
    startPoint->next = startPoint->prev;
    startPoint->prev = temp;
    temp = endPoint->next;
    endPoint->next = endPoint->prev;
    endPoint->prev = temp;
    return;
  }
  else{
    ListNode* temp = startPoint->next;
    startPoint->next = startPoint->prev;
    startPoint->prev = temp;
    temp = endPoint->next;
    endPoint->next = endPoint->prev;
    endPoint->prev = temp;
    reverse(startPoint->prev, endPoint->next);
    temp = startPoint;
    startPoint = endPoint;
    endPoint = temp;
    return;
  }
}
*/
/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <class T>
void List<T>::reverseNth(int n) {
  /// @todo Graded in MP3.1
  if(n > this->size()){
    std::cout << "invalid" <<std::endl;
  }
  else{
    int index = ceil(((double)this->size())/((double)n));
    //do the first one separately because of the head pointer
    ListNode* temphead = head_;
    ListNode* tempend = head_;
    ListNode* save_sec = NULL;
    ListNode* saved_end = NULL;
    for(int j = 0; j<index; j++){
    //  if(temphead != NULL){
      for(int h = 1; h<n; h++){
        if(tempend->next !=NULL){
        tempend = tempend->next;
        save_sec = tempend->next;
        }
        else{save_sec = tempend->next;
          break;}
      }
     //save_sec = tempend->next;
     tempend->next = NULL;
     reverse(temphead,tempend);
     if(tempend->next == NULL){
       head_ = temphead;
       saved_end = tempend;
     }
     else{
       temphead->prev= saved_end;
       saved_end->next = temphead;
       saved_end = tempend;
     }
     if(save_sec !=NULL){
     temphead = save_sec;
     tempend = save_sec;
    }
    else{break;}
  //  }
  //  else{
    //  break;
    //}
  }
    tail_ = tempend;
    tail_->next = NULL;
    return;
  }
}

/**
 * Modifies the List using the waterfall algorithm.
 * Every other node (starting from the second one) is removed from the
 * List, but appended at the back, becoming the new tail. This continues
 * until the next thing to be removed is either the tail (**not necessarily
 * the original tail!**) or NULL.  You may **NOT** allocate new ListNodes.
 * Note that since the tail should be continuously updated, some nodes will
 * be moved more than once.
 */
template <class T>
void List<T>::waterfall() {
  /// @todo Graded in MP3.1
  ListNode* temphead = head_;
  while(temphead!=tail_){
    ListNode* temp_rm = temphead->next;
    if(temp_rm == tail_){
      //we reach the last node, nothing is done, just return
      return;
    }
    else{
      temphead->next = temp_rm->next;
      (temp_rm->next->prev) = temphead;
      tail_->next = temp_rm;
      temp_rm->next = NULL;
      temp_rm->prev = tail_;
      tail_ = tail_->next;
      temphead = temphead->next;
    }
  }
  return;
}

/**
 * Splits the given list into two parts by dividing it at the splitPoint.
 *
 * @param splitPoint Point at which the list should be split into two.
 * @return The second list created from the split.
 */
template <class T>
List<T> List<T>::split(int splitPoint) {
    if (splitPoint > length_)
        return List<T>();

    if (splitPoint < 0)
        splitPoint = 0;

    ListNode * secondHead = split(head_, splitPoint);

    int oldLength = length_;
    if (secondHead == head_) {
        // current list is going to be empty
        head_ = NULL;
        tail_ = NULL;
        length_ = 0;
    } else {
        // set up current list
        tail_ = head_;
        while (tail_ -> next != NULL)
            tail_ = tail_->next;
        length_ = splitPoint;
    }

    // set up the returned list
    List<T> ret;
    ret.head_ = secondHead;
    ret.tail_ = secondHead;
    if (ret.tail_ != NULL) {
        while (ret.tail_->next != NULL)
            ret.tail_ = ret.tail_->next;
    }
    ret.length_ = oldLength - splitPoint;
    return ret;
}

/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List or ListNode objects!
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <class T>
typename List<T>::ListNode * List<T>::split(ListNode * start, int splitPoint) {
  /// @todo Graded in MP3.2
  if(splitPoint ==0){
    return start;
  }
  else{
    ListNode* next_head = start;
    for(int i =1; i<splitPoint; i++){
    next_head = next_head->next;
    }
    ListNode* return_node = next_head->next;
    return_node->prev = NULL;
    next_head->next = NULL;
    return return_node;
  }
}

/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <class T>
void List<T>::mergeWith(List<T> & otherList) {
    // set up the current list
    head_ = merge(head_, otherList.head_);
    tail_ = head_;

    // make sure there is a node in the new list
    if (tail_ != NULL) {
        while (tail_->next != NULL)
            tail_ = tail_->next;
    }
    length_ = length_ + otherList.length_;

    // empty out the parameter list
    otherList.head_ = NULL;
    otherList.tail_ = NULL;
    otherList.length_ = 0;
}

/**
 * Helper function to merge two **sorted** and **independent** sequences of
 * linked memory. The result should be a single sequence that is itself
 * sorted.
 *
 * This function **SHOULD NOT** create **ANY** new List objects.
 *
 * @param first The starting node of the first sequence.
 * @param second The starting node of the second sequence.
 * @return The starting node of the resulting, sorted sequence.
 */
template <class T>
typename List<T>::ListNode * List<T>::merge(ListNode * first, ListNode* second) {
  /// @todo Graded in MP3.2
  if(first == NULL && second == NULL){
    return NULL;
  }
  else if(first == NULL && second !=NULL){
    return second;
  }
  else if(first !=NULL && second == NULL){
    return first;
  }
  else{
    if(first->data < second->data){
      ListNode* top = first;
      while(second!=NULL){
      while(first->next!=NULL){
        if((first->next)->data < second->data){
          first = first->next;
        }
        else{
          break;
        }
      }
      if(first->next == NULL){
        //if(first->data < second->data){
          first->next = second;
          second->prev = first;
          return top;
      }
      else{
        ListNode* temp = first->next;
        temp->prev = second;
        first->next = second;
        second->prev = first;
        ListNode* temp_2 = second->next;
        second->next = temp;
        second  = temp_2;
        first = first->next;
      }
    }
    return top;
  }
  else{
    ListNode* top = second;
    while(first!=NULL){
    while(second->next!=NULL){
      if((second->next)->data < first->data){
        second =second->next;
      }
      else{
        break;
      }
    }
    if(second->next == NULL){
      //if(first->data < second->data){
        second->next = first;
        first->prev = second;
        return top;
    }
    else{
      ListNode* temp = second->next;
      temp->prev = first;
      second->next = first;
      first->prev = second;
      ListNode* temp_2 = first->next;
      first->next = temp;
      first  = temp_2;
      second = second->next;
    }
  }
  return top;
}
}
}
//


/**
 * Sorts the current list by applying the Mergesort algorithm.
 */
template <class T>
void List<T>::sort() {
    if (empty())
        return;
    head_ = mergesort(head_, length_);
    tail_ = head_;
    while (tail_->next != NULL)
        tail_ = tail_->next;
}

/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <class T>
typename List<T>::ListNode* List<T>::mergesort(ListNode * start, int chainLength){
  /// @todo Graded in MP3.2
  if(chainLength%2 ==0){
    if(chainLength ==1){
      return start;
    }
  ListNode* temp = split(start, chainLength/2);
//  mergesort(start, chainLength/2);
  //mergesort(temp,chainLength/2);
  return merge(mergesort(start, chainLength/2),mergesort(temp,chainLength/2));
  }
  else{
  if(chainLength ==1){
    return start;
  }
ListNode* temp = split(start, chainLength/2);
//mergesort(start, chainLength/2);
//mergesort(temp,chainLength/2+1);
return merge(mergesort(start, chainLength/2),mergesort(temp,chainLength/2+1));

}
}
