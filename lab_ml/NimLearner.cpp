/**
 * @file NimLearner.cpp
 * CS 225: Data Structures
 */

#include "NimLearner.h"
#include <ctime>


/**
 * Constructor to create a game of Nim with `startingTokens` starting tokens.
 *
 * This function creates a graph, `g_` representing all of the states of a
 * game of Nim with vertex labels "p#-X", where:
 * - # is the current player's turn; p1 for Player 1, p2 for Player2
 * - X is the tokens remaining at the start of a player's turn
 *
 * For example:
 *   "p1-4" is Player 1's turn with four (4) tokens remaining
 *   "p2-8" is Player 2's turn with eight (8) tokens remaining
 *
 * All legal moves between states are created as edges with initial weights
 * of 0.
 *
 * @param startingTokens The number of starting tokens in the game of Nim.
 */
NimLearner::NimLearner(unsigned startingTokens) : g_(true, true) {
    /* Your code goes here! */
    for(unsigned i = 0; i <= startingTokens; i++){
      g_.insertVertexByLabel("p1-"+std::to_string(i));
      g_.insertVertexByLabel("p2-"+std::to_string(i));
    }
    for(unsigned i =0; i<=startingTokens; i++){
      unsigned j = 1+i;
      while(j-i<=2 && j<=startingTokens){
      g_.insertEdge("p2-"+std::to_string(j),"p1-"+std::to_string(i));
      g_.setEdgeWeight("p2-"+std::to_string(j),"p1-"+std::to_string(i),0);
      j++;
     }
    }
    for(unsigned i =0; i<=startingTokens; i++){
      unsigned j = 1+i;
      while(j-i<=2 && j<=startingTokens){
      g_.insertEdge("p1-"+std::to_string(j),"p2-"+std::to_string(i));
      g_.setEdgeWeight("p1-"+std::to_string(j),"p2-"+std::to_string(i),0);
      j++;
     }
   }
   startingVertex_ = g_.getVertexByLabel("p1-"+std::to_string(startingTokens));
}

/**
 * Plays a random game of Nim, returning the path through the state graph
 * as a vector of `Edge` classes.  The `origin` of the first `Edge` must be
 * the vertex with the label "p1-#", where # is the number of starting
 * tokens.  (For example, in a 10 token game, result[0].origin must be the
 * vertex "p1-10".)
 *
 * @returns A random path through the state space graph.
 */
std::vector<Edge> NimLearner::playRandomGame() const {
  vector<Edge> path;
 /* Your code goes here! */
  bool player = 0;
  //0 means player 1, 1 means player 2
  int random = (rand()%2) +1;
  size_t idx = g_.getVertexLabel(startingVertex_).find("-");
  string str2 = g_.getVertexLabel(startingVertex_).substr (idx+1);
  int remaining = std::stoi(str2)-random;
  if(remaining <0){
    path.push_back(g_.getEdge(startingVertex_,g_.getVertexByLabel("p2-"+std::to_string(0))));
    return path;
  }
  // std::cout<<"wer"<<remaining;
  while(remaining >=0){
    if(player == 0){
      path.push_back(g_.getEdge(g_.getVertexByLabel("p1-"+std::to_string(remaining+random)),g_.getVertexByLabel("p2-"+std::to_string(remaining))));
      player = 1;
      random = (rand()%2)+1;
      remaining -= random;
    }
    else{
      path.push_back(g_.getEdge(g_.getVertexByLabel("p2-"+std::to_string(remaining+random)),g_.getVertexByLabel("p1-"+std::to_string(remaining))));
      player = 0;
      random = (rand()%2)+1;
      remaining -= random;
    }
  }
  if(remaining+random !=0){
    if(player == 1){
    path.push_back(g_.getEdge(g_.getVertexByLabel("p1-"+std::to_string(remaining+random)),g_.getVertexByLabel("p2-"+std::to_string(0))));
    }
  else{
    path.push_back(g_.getEdge(g_.getVertexByLabel("p2-"+std::to_string(remaining+random)),g_.getVertexByLabel("p1-"+std::to_string(0))));
  }
  }

  return path;
}

/*
 * Updates the edge weights on the graph based on a path through the state
 * tree.
 *
 * If the `path` has Player 1 winning (eg: the last vertex in the path goes
 * to Player 2 with no tokens remaining, or "p2-0", meaning that Player 1
 * took the last token), then all choices made by Player 1 (edges where
 * Player 1 is the source vertex) are rewarded by increasing the edge weight
 * by 1 and all choices made by Player 2 are punished by changing the edge
 * weight by -1.
 *
 * Likewise, if the `path` has Player 2 winning, Player 2 choices are
 * rewarded and Player 1 choices are punished.
 *
 * @param path A path through the a game of Nim to learn.
 */
void NimLearner::updateEdgeWeights(const std::vector<Edge> & path) {
 /* Your code goes here! */
 bool winner = 1;
 for(int i = (int)path.size()-1; i>=0; i--){
   if(winner ==1){
   g_.setEdgeWeight(path[i].source,path[i].dest,1+path[i].getWeight());
   winner = 0;
   }
   else{
     g_.setEdgeWeight(path[i].source,path[i].dest,-1+path[i].getWeight());
     winner = 1;
   }
 }
 return;
}

/**
 * Label the edges as "WIN" or "LOSE" based on a threshold.
 */
void NimLearner::labelEdgesFromThreshold(int threshold) {
  for (const Vertex & v : g_.getVertices()) {
    for (const Vertex & w : g_.getAdjacent(v)) {
      int weight = g_.getEdgeWeight(v, w);

      // Label all edges with positve weights as "WINPATH"
      if (weight > threshold)           { g_.setEdgeLabel(v, w, "WIN"); }
      else if (weight < -1 * threshold) { g_.setEdgeLabel(v, w, "LOSE"); }
    }
  }
}

/**
 * Returns a constant reference to the state space graph.
 *
 * @returns A constant reference to the state space graph.
 */
const Graph & NimLearner::getGraph() const {
  return g_;
}
