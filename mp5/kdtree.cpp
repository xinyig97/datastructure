/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

#include <utility>
#include <math.h>
#include <algorithm>
#include <iostream>

using namespace std;

template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim) const
{
    /**
     * @todo Implement this function!
     */
     if (first[curDim] < second[curDim])
      return true;
     else if (first[curDim] > second[curDim])
      return false;
     else return (first < second);

}

template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential) const
{
    /**
     * @todo Implement this function!
     */
     double currDist;
     double potDist;
     for (int i = 0; i < Dim; i++)
     {
       currDist = currDist + (target[i] - currentBest[i])*(target[i] - currentBest[i]);
       potDist = potDist + (target[i] - potential[i])*(target[i] - potential[i]);
     }

     if (potDist < currDist)
      return true;
     else if (potDist > currDist)
      return false;
     else return (potential < currentBest);

}

template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
    /**
     * @todo Implement this function!
     */
    if (newPoints.empty())
      root = new KDTreeNode();
    else
      root =  KDTreeHelper(newPoints, 0, 0, newPoints.size()-1);
}

template <int Dim>
typename KDTree<Dim>::KDTreeNode* KDTree<Dim>::KDTreeHelper(vector<Point<Dim>> newPoints, int dim, int start, int end)
{
    /**
     * @todo Implement this function!
     */
     if (start == end)
       return new KDTreeNode(newPoints[start]);
     else if (start > end || start < 0 || end < 0)
       return NULL;
     else {
       quickSort(newPoints, start, end, dim);

       for (int i = start; i <= end; i++)
          cout << newPoints[i][dim] << "  ";
       cout << endl;


       KDTreeNode* newNode = new KDTreeNode(newPoints[(end + start)/2]);
       newNode->left = KDTreeHelper(newPoints, (dim+1)%Dim, start, ((end + start)/2)-1);
       newNode->right = KDTreeHelper(newPoints, (dim+1)%Dim, ((end+start)/2)+1, end);
       return newNode;
     }
}

template <int Dim>
void KDTree<Dim>::quickSort(vector<Point<Dim>>& newPoints, int first, int last,
                            int dim)
{
  int i = first, j = last;
      Point<Dim> tmp;
      Point<Dim> pivot = newPoints[(first + last) / 2];

      /* partition */
      while (i <= j) {
            while (smallerDimVal(newPoints[i], pivot, dim))
                  i++;
            while (smallerDimVal(pivot, newPoints[j], dim))
                  j--;
            if (i <= j) {
                  tmp = newPoints[i];
                  newPoints[i] = newPoints[j];
                  newPoints[j] = tmp;
                  i++;
                  j--;
            }
      };

      /* recursion */
      if (first < j)
            quickSort(newPoints, first, j, dim);
      if (i < last)
            quickSort(newPoints, i, last, dim);
}

template <int Dim>
KDTree<Dim>::KDTree(const KDTree& other) {
  /**
   * @todo Implement this function!
   */
   size = other.getSize();
   root = copy(other.getRoot());

}

template <int Dim>
size_t KDTree<Dim>::getSize() const
{
  return size;
}

template <int Dim>
const KDTree<Dim>& KDTree<Dim>::operator=(const KDTree& rhs) {
  /**
   * @todo Implement this function!
   */
   if (this != &rhs) {
       clear(root);
       root = copy(rhs.getRoot());
   }
   return *this;

}

template <int Dim>
KDTree<Dim>::~KDTree() {
  /**
   * @todo Implement this function!
   */
   clear(root);
}

template <int Dim>
typename KDTree<Dim>::KDTreeNode* KDTree<Dim>::copy(const KDTreeNode* subRoot)
{
    if (subRoot == NULL)
        return NULL;

    // Copy this node and it's children
    KDTreeNode* newNode = new KDTreeNode(subRoot->point);
    newNode->left = copy(subRoot->left);
    newNode->right = copy(subRoot->right);
    return newNode;
}

template <int Dim>
void KDTree<Dim>::clear(KDTreeNode* subRoot)
{
  if (subRoot == NULL)
        return;

    clear(subRoot->left);
    clear(subRoot->right);
  delete subRoot;
}

template <int Dim>
typename KDTree<Dim>::KDTreeNode* KDTree<Dim>::getRoot() const
{
  return root;
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
    if (root == NULL)
      return Point<Dim>();
  //  cout << "QUERY: " << query[0] << endl;
    return findNearest_Helper(query, root, root, 0)->point;
}

template <int Dim>
typename KDTree<Dim>::KDTreeNode* KDTree<Dim>::findNearest_Helper(const Point<Dim>& query, KDTreeNode* curr, KDTreeNode* best, int split) const
{
    if (curr->left == NULL && curr->right == NULL)
    {
      return curr;
    }
    // cout << "curr: (";
    // for (int i = 0; i < Dim; i++)
    // {
    //   cout << curr->point[i] << ", ";
    // }
    //  cout << ")" << endl;

    KDTreeNode* potFirst = curr;
    if (smallerDimVal(query, curr->point, split) && (curr->left != NULL))
    {
      //cout << "GOING LEFT..." << endl;
      potFirst = findNearest_Helper(query, curr->left, best, (split+1) % Dim);
    }
    else if (!smallerDimVal(query, curr->point, split) && (curr->right != NULL))
    {
      //cout << "GOING RIGHT..." << endl;
      potFirst = findNearest_Helper(query, curr->right, best, (split+1) % Dim);
    }

    if (shouldReplace(query, best->point, potFirst->point))
      best = potFirst;
    // cout << "current best: (";
    // for (int i = 0; i < Dim; i++)
    // {
    //   cout << best->point[i] << ", ";
    // }
    //  cout << ")" << endl;
    //
    // cout << "curr: " << curr->point[split] << endl;
    // cout << "curr: (";
    // for (int i = 0; i < Dim; i++)
    // {
    //   cout << curr->point[i] << ", ";
    // }
    //  cout << ")" << endl;

    if (curr->point == query)
      return curr;

    if (shouldReplace(query, best->point, curr->point))
    {
      best = curr;
    //   cout << "new best: " << best->point[split] << endl;
    //   cout << "new best: (";
    //   for (int i = 0; i < Dim; i++)
    //   {
    //     cout << best->point[i] << ", ";
    //   }
    //    cout << ")" << endl;
    //
    //   cout << "curr best: " << best->point[split];
     }

    double radius = dist(query, best->point);


    // if (best->point[split] > query[split])
    // {

      double x = query[split] + radius;
      if ((x >= curr->point[split]) && (curr->right != NULL))
      {
        //cout << "GOING RIGHT..." << endl;
        KDTreeNode* pot = findNearest_Helper(query, curr->right, best, (split+1) % Dim);
        if (shouldReplace(query, best->point, pot->point))
          best = pot;
      }

    // }

    // if (best->point[split] < query[split])
    // {
      radius = dist(query, best->point);
      x = query[split] - radius;
      if ((x <= curr->point[split]) && (curr->left != NULL))
      {
        cout << "GOING LEFT..." << endl;
        //this print out is messing around our code somehow
        KDTreeNode* pot = findNearest_Helper(query, curr->left, best, (split+1) % Dim);
        if (shouldReplace(query, best->point, pot->point))
          best = pot;
      }


      // cout << "curr best: (";
      // for (int i = 0; i < Dim; i++)
      // {
      //   cout << best->point[i] << ", ";
      // }
      //  cout << ")" << endl;
    // }

    return best;

}

template <int Dim>
double KDTree<Dim>::dist(Point<Dim> point1, Point<Dim> point2) const
{
  double currDist = 0;
  for (int i = 0; i < Dim; i++)
  {
    currDist = currDist + (point1[i] - point2[i])*(point1[i] - point2[i]);
  }

  return sqrt(currDist);
}
