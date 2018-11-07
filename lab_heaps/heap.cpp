
/**
 * @file heap.cpp
 * Implementation of a heap class.
 */

template <class T, class Compare>
size_t heap<T, Compare>::root() const
{
    // @TODO Update to return the index you are choosing to be your root.
    return 1;
}

template <class T, class Compare>
size_t heap<T, Compare>::leftChild(size_t currentIdx) const
{
    // @TODO Update to return the index of the left child.
    return 2*currentIdx;
}

template <class T, class Compare>
size_t heap<T, Compare>::rightChild(size_t currentIdx) const
{
    // @TODO Update to return the index of the right child;
    return 2*currentIdx+1;
}

template <class T, class Compare>
size_t heap<T, Compare>::parent(size_t currentIdx) const
{
    // @TODO Update to return the index of the parent.
    return floor(currentIdx/2);
}

template <class T, class Compare>
bool heap<T, Compare>::hasAChild(size_t currentIdx) const
{
    // @TODO Update to return whether the given node has a child
    if(leftChild(currentIdx) > _elems.size() || leftChild(currentIdx) == _elems.size()){
      return false;
    }
    return true;
}

template <class T, class Compare>
size_t heap<T, Compare>::maxPriorityChild(size_t currentIdx) const
{
    // @TODO Update to return the index of the child with highest priority
    ///   as defined by higherPriority()
    if(hasAChild(currentIdx)){
      if(rightChild(currentIdx) < _elems.size()){
        if(higherPriority(_elems[rightChild(currentIdx)],_elems[leftChild(currentIdx)])){
          return rightChild(currentIdx);
        }
        else {
          return leftChild(currentIdx);
        }
      }
      else{
        return leftChild(currentIdx);
      }
    }
    else{
    return currentIdx;
    }
}

template <class T, class Compare>
void heap<T, Compare>::heapifyDown(size_t currentIdx)
{
    // @TODO Implement the heapifyDown algorithm.
    if(hasAChild(currentIdx)){
      if(rightChild(currentIdx)<_elems.size()){
        size_t child = maxPriorityChild(currentIdx);
        if(higherPriority(_elems[child],_elems[currentIdx])){
          std::swap(_elems[child],_elems[currentIdx]);
          heapifyDown(child);
        }
        else{
          return;
        }
      }
      else{
        if(higherPriority(_elems[leftChild(currentIdx)],_elems[currentIdx])){
          std::swap(_elems[leftChild(currentIdx)],_elems[currentIdx]);
          heapifyDown(leftChild(currentIdx));
        }
        else{
          return;
        }
      }
    }
    return;
  }


template <class T, class Compare>
void heap<T, Compare>::heapifyUp(size_t currentIdx)
{
    if (currentIdx == root())
        return;
    size_t parentIdx = parent(currentIdx);
    if (higherPriority(_elems[currentIdx], _elems[parentIdx])) {
        std::swap(_elems[currentIdx], _elems[parentIdx]);
        heapifyUp(parentIdx);
    }
}

template <class T, class Compare>
heap<T, Compare>::heap()
{
    // @TODO Depending on your implementation, this function may or may
    ///   not need modifying

    //index from 1 instead of 0
    _elems.push_back(T());

}

template <class T, class Compare>
heap<T, Compare>::heap(const std::vector<T>& elems)
{
    // @TODO Construct a heap using the buildHeap algorithm
    _elems.push_back(T());
    if(!elems.empty()){
      // size_t temp = floor((elems.size())/2);
      // for(size_t i =temp; i < elems.size(); i++){
      //   _elems.push_back(elems[i]);
      // }
      // for(size_t i = 0; i<temp;i++){
      //   _elems.insert(_elems.begin()+1,elems[i]);
      //   heapifyDown(1);
      for(size_t i = 0; i < elems.size(); i++){
        _elems.push_back(elems[i]);
      }
      for(size_t i = _elems.size()/2; i > 0; i--){
        heapifyDown(i);
      }
    }

}

template <class T, class Compare>
T heap<T, Compare>::pop()
{
    // @TODO Remove, and return, the element with highest priorit
    T temp = _elems[1];
    _elems[1] = _elems[_elems.size()-1];
    _elems.erase(_elems.begin()+_elems.size()-1);
    heapifyDown(1);
    return temp;
}

template <class T, class Compare>
T heap<T, Compare>::peek() const
{
    // @TODO Return, but do not remove, the element with highest priority
    return _elems[1];
}

template <class T, class Compare>
void heap<T, Compare>::push(const T& elem)
{
    // @TODO Add elem to the heap
    _elems.push_back(elem);
    heapifyUp(_elems.size()-1);
    // for(size_t i = 1; i < _elems.size(); i++){
    //   std::cout << _elems[i]<<" ";
    // }
    // std::cout << std::endl;
    return;
}

template <class T, class Compare>
bool heap<T, Compare>::empty() const
{
    // @TODO Determine if the heap is empty
    if(_elems.size()<=1){
      return true;
    }
    return false;
}

template <class T, class Compare>
void heap<T, Compare>::getElems(std::vector<T> & heaped) const
{
    for (size_t i = root(); i < _elems.size(); i++) {
        heaped.push_back(_elems[i]);
    }

}
