/**
 * @file graph_tools.cpp
 * This is where you will implement several functions that operate on graphs.
 * Be sure to thoroughly read the comments above each function, as they give
 *  hints and instructions on how to solve the problems.
 */

#include "graph_tools.h"
#include <map>

using namespace std;

/**
 * Finds the minimum edge weight in the Graph graph.
 * THIS FUNCTION IS GRADED.
 *
 * @param graph - the graph to search
 * @return the minimum weighted edge
 *
 * @todo Label the minimum edge as "MIN". It will appear blue when
 *  graph.savePNG() is called in minweight_test.
 *
 * @note You must do a traversal.
 * @note You may use the STL stack and queue.
 * @note You may assume the graph is connected.
 *
 * @hint Initially label vertices and edges as unvisited.
 */
int GraphTools::findMinWeight(Graph& graph)
{
    //TODO: YOUR CODE HERE
    vector<Vertex> vertice_ = graph.getVertices();
    Edge min = Edge();
    for(size_t i =0; i<vertice_.size(); i++){
      if(graph.getVertexLabel(vertice_[i])!="VISITED"){
        min = BFS(graph, vertice_[i]);
      }
    }
    return min.getWeight();
}

Edge GraphTools::BFS(Graph& graph,  Vertex start){
  std::queue<Vertex> rec;
  Edge found = Edge();
  start = graph.setVertexLabel(start,"VISITED");
  rec.push(start);

  while(!rec.empty()){
    Vertex temp_v = rec.front();
    rec.pop();
    vector<Vertex> adj = graph.getAdjacent(temp_v);
    if(adj.empty()){
      break;
    }
    else{
      for(size_t i = 0; i < adj.size(); i++){
        if(found.getWeight()==-1){
          found = graph.getEdge(temp_v,adj[i]);
        }
        else if(graph.getEdge(temp_v,adj[i])<found){
          found = graph.getEdge(temp_v,adj[i]);
        }

        if(graph.getVertexLabel(adj[i])!="VISITED"){
          adj[i] = graph.setVertexLabel(adj[i],"VISITED");
          graph.setEdgeLabel(temp_v,adj[i],"DISCOVERY");
          rec.push(adj[i]);
        }
        else if(graph.getEdge(temp_v,adj[i]).getLabel()!="DISCOVERY"){
          graph.setEdgeLabel(temp_v,adj[i],"CROSS");
        }
      }
    }
  }
  graph.setEdgeLabel(found.source, found.dest,"MIN");
  return found;
}

/**
 * Returns the shortest distance (in edges) between the Vertices
 *  start and end.
 * THIS FUNCTION IS GRADED.
 *
 * @param graph - the graph to search
 * @param start - the vertex to start the search from
 * @param end - the vertex to find a path to
 * @return the minimum number of edges between start and end
 *
 * @todo Label each edge "MINPATH" if it is part of the minimum path
 *
 * @note Remember this is the shortest path in terms of edges,
 *  not edge weights.
 * @note Again, you may use the STL stack and queue.
 * @note You may also use the STL's unordered_map, but it is possible
 *  to solve this problem without it.
 *
 * @hint In order to draw (and correctly count) the edges between two
 *  vertices, you'll have to remember each vertex's parent somehow.
 */
int GraphTools::findShortestPath(Graph& graph, Vertex start, Vertex end)
{
    //TODO: YOUR CODE HERE
    vector<Vertex> set = graph.getVertices();
    std::map<Vertex,int> distance;
    for(Vertex x: set){
      distance[x] = -1;
    }
    distance[start] = 0;
    std::map<Vertex,Vertex> parent;
    std::queue<Vertex> q;
    q.push(start);
    while(!q.empty()){
      Vertex temp_v = q.front();
      q.pop();
      vector<Vertex> tem = graph.getAdjacent(temp_v);
      for(Vertex x: tem){
         if(distance[x]==-1){
           parent[x] = temp_v;
           distance[x] = 1 + distance[temp_v];
           q.push(x);
         }
         else{
          int temp_d = 1 + distance[temp_v];
          if (temp_d < distance[x]){
            parent[x] = temp_v;
            distance[x] = temp_d;
          }
         }
       }
      }
      int min = distance[end];
      while(parent[end]!=parent[start]){
        graph.setEdgeLabel(parent[end],end,"MINPATH");
        end = parent[end];
      }
    return min;
}
//
/**
 * Finds a minimal spanning tree on a graph.
 * THIS FUNCTION IS GRADED.
 *
 * @param graph - the graph to find the MST of
 *
 * @todo Label the edges of a minimal spanning tree as "MST"
 *  in the graph. They will appear blue when graph.savePNG() is called.
 *
 * @note Use your disjoint sets class from MP 7.1 to help you with
 *  Kruskal's algorithm. Copy the files into the dsets.h and dsets.cpp .
 * @note You may call std::sort instead of creating a priority queue.
 */
void GraphTools::findMST(Graph& graph)
{
    //TODO: YOUR CODE HERE
    vector<Vertex> vertice = graph.getVertices();
    DisjointSets forest;
    forest.addelements(vertice.size());
    std::map<Vertex,int> tran;
    int idx = 0;
    for(Vertex x: vertice){
      tran[x] = idx;
      idx++;
    }
    vector<Edge> kru = graph.getEdges();
    sort(kru.begin(),kru.end());
    for(Edge x : kru){
      if(forest.find(tran[x.source])!=forest.find(tran[x.dest])){
        forest.setunion(tran[x.source],tran[x.dest]);
        graph.setEdgeLabel(x.source,x.dest,"MST");
        // kru.erase(kru.begin());
      }
    }
    return;

}
