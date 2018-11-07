/* Your code here! */
#include "maze.h"
#include<sys/time.h>
#include <map>
#include <queue>
#include <iostream>
SquareMaze::SquareMaze(){};

void SquareMaze::makeMaze(int width, int height){
  width_ = width;
  height_ = height;
  for(int i = 0; i < width*height ; i++){
    walls_.push_back(wall());
    cell_.push_back(1);
  }
  cells_.addelements(width*height);

  //0 goes right, 1 goes down
  struct timeval time;
  gettimeofday(&time, NULL);
  srand((time.tv_sec * 1000) + (time.tv_usec / 1000));
  while(cells_.size(0)!=width_*height_){

    int x_random = (rand()%width_);
    int y_random = (rand()%height_);
    int dir_random = (rand()%2);

    if(dir_random == 0 && x_random+1 < width_ && (cells_.find(y_random*width_+x_random)!=cells_.find(y_random*width_+x_random+1))){
      setWall(x_random,y_random,0,false);
      cells_.setunion(y_random*width_+x_random,y_random*width_+x_random+1);
    }
    else if(dir_random == 1 && y_random+1 <height_ && (cells_.find(y_random*width_+x_random)!=cells_.find((y_random+1)*width_+x_random))){
      setWall(x_random,y_random,1,false);
      cells_.setunion(y_random*width_+x_random, (y_random+1)*width_+x_random);
    }
 }
}

bool SquareMaze::canTravel(int x, int y, int dir) const{
  if(dir == 0){
    // if goes right
      if(x+1 >= width_){
        return false;
      }
      else{
          if(walls_[y*width_+x].right_ == false){
            //if there's no wall return true cuz can travel
          return true;
          }
          else{
            //otherwise return false cuz you cant walk through a wall
          return false;
          }
      }
  }
  else if(dir == 1){
    //if goes down
      if(y+1>=height_){
        return false;
      }
      else{
        if(walls_[y*width_+x].down_ == false){
          //if theres no wall, go ahead returntrus
          return true;
        }
        else{
          //otherwise return false cuZ you dont wanna die by hitting in the wall
          return false;
        }
      }
  }
  else if(dir == 2){
    //go left
    if(x-1<0){
      return false;
    }
    else{
      if(walls_[y*width_+x-1].right_ == false){
        return true;
      }
      else{
        return false;
      }
    }
  }
  else{
    if(y-1<0){
      return false;
    }
    else{
      if(walls_[(y-1)*width_+x].down_ == false){
        return true;
      }
      else{
        return false;
      }
    }
  }
}

void SquareMaze::setWall(int x, int y, int dir, bool exists){
  if(dir == 0){
    //the right wall of current cell
    if(exists == true){
      //if to set a wall
      if(walls_[y*width_+x].right_ == true){
        //the wall already exists
        return;
      }
      else{
        //otherwise build DisjointSets
        walls_[y*width_+x].right_ = true;
        return;
      }
    }
    else{
      //if destroy a wall
      if(walls_[y*width_+x].right_ == false){
        //if the wall doesnt exist
        return;
      }
      else{
        walls_[y*width_+x].right_ = false;
        return;
      }
    }
  }
else{
  //if the down wall of current cell_
  if(exists == true){
    //to set up a walls_
    if(walls_[y*width_+x].down_ == true){
      //if the wall already exists
      return;
    }
    else{
      //otherwise build a walls_
      walls_[y*width_+x].down_= true;
      return;
    }
  }
  else{
    //if to destroy a walls_
    if(walls_[y*width_+x].down_ == false){
      //if doesnt exist
      return;
    }
    else{
      walls_[y*width_+x].down_ = false;
      return;
    }
  }
}
}

vector<int> SquareMaze::solveMaze(){
  //i use Dijika to find the largest path
  //each cell i see them as node of a graph
  //each nonexisteing wall i see them as edges
  //use bfs traversal and update the bigger distcance of each nnnnnnnnode from the starting
  
    vector<int> step;
    struct node{
      int par;
      int dir;
      int dist;
      bool vis;
      node(){};
      node(int x, int d,int l,bool var){par = x;dir = d;dist = l;vis = var;};
    };
    //create a new structure as nodes on a graph that saves predecessors and distance
    map<int,node> bat;
    //map the unique info with its unique index
    std::queue<int> q;
    //using bfs
    q.push(0);
    //push the key
    //every new node start with false == vis,
    //once visited, change to true
    bat[0] = node(0,0,0,false);
    while(!q.empty()){
      int cur = q.front();
      q.pop();
      //if already visited, just pop
      if(bat[cur].vis == true){
        continue;
      }
      else{
        //find the correct index conversion
      int x = cur%width_;
      int y = (cur-x)/width_;
      bat[cur].vis = true;
      if(canTravel(x,y,0)){
        // std::cout<<cur<<std::endl;
        if(bat.find(y*width_+x+1)==bat.end()){
        bat[y*width_+x+1] = node(cur,0,bat[cur].dist+1,false);
        q.push(y*width_+x+1);
        }
        //if already have the node, check the distance and check if thats the parent
        else if(bat[cur].dist +1 >bat[y*width_+x+1].dist&&bat[cur].par!=(y*width_+x+1)){
        bat[y*width_+x+1].dist = bat[cur].dist +1;
        bat[y*width_+x+1].par = cur;
        bat[y*width_+x+1].dir = 0;
        q.push(y*width_+x+1);
        }
      }
      if(canTravel(x,y,1)){
        // std::cout<<"1"<<std::endl;
        if(bat.find((y+1)*width_+x)==bat.end()){
          bat[(y+1)*width_+x] = node(cur,1,bat[cur].dist+1,false);
          q.push((y+1)*width_+x);
        }
        else if(bat[(y+1)*width_+x].dist < bat[cur].dist+1&&bat[cur].par!=((y+1)*width_+x)){
          bat[(y+1)*width_+x].dist = bat[cur].dist +1;
          bat[(y+1)*width_+x].par = cur;
          bat[(y+1)*width_+x].dir = 1;
            q.push((y+1)*width_+x);
        }
      }
      if(canTravel(x,y,2)){
                // std::cout<<"2"<<std::endl;
        if(bat.find(y*width_+x-1)==bat.end()){
          bat[y*width_+x-1] = node(cur,2,bat[cur].dist+1,false);
          q.push(y*width_+x-1);
        }
        else if(bat[y*width_+x-1].dist < bat[cur].dist +1&&bat[cur].par != (y*width_+x-1)){
          bat[y*width_+x-1].dist = bat[cur].dist +1;
          bat[y*width_+x-1].par = cur;
          bat[y*width_+x-1].dir = 2;
            q.push(y*width_+x-1);
        }
      }
      if(canTravel(x,y,3)){
                // std::cout<<"3"<<std::endl;
        if(bat.find((y-1)*width_+x) == bat.end()){
          bat[(y-1)*width_+x] = node(cur,3,bat[cur].dist+1,false);
          q.push((y-1)*width_+x);
        }
        else if(bat[(y-1)*width_+x].dist < bat[cur].dist+1&&bat[cur].par != ((y-1)*width_+x)){
          bat[(y-1)*width_+x].dist = bat[cur].dist +1;
          bat[(y-1)*width_+x].par = cur;
          bat[(y-1)*width_+x].dir  = 3;
            q.push((y-1)*width_+x);
        }
      }
    }
  }
  // std::cout<<"here>";
  //loop through the bottom line to see which  hasssssssssss the bigegstttttttttttt distance
      int long_dis = -1;
      int cad;
      for(int i =0; i < width_; i++){
        if(bat.find((height_-1)*width_+i)!=bat.end()){
        if(long_dis == -1){
          long_dis = bat[(height_-1)*width_+i].dist;
          cad = i;
        }
        else{

          if(bat[(height_-1)*width_+i].dist > long_dis){
            long_dis = bat[(height_-1)*width_+i].dist;
            cad = i;
          }
        }
      }
      }
//backtrack to the start
      int parent = (height_-1)*width_+cad;
      y_des = height_-1;
      x_des = cad;
      while(parent != 0){
      step.insert(step.begin(),bat[parent].dir);
      parent = bat[parent].par;
      }

      return step;
}
PNG* SquareMaze::drawMaze() const{
  PNG* ret = new PNG(width_*10+1,height_*10+1);
  for(size_t i = 10; i < ret->width() ; i++){
    //topmost
    HSLAPixel& cur = ret->getPixel(i,0);
    cur.h = 0;
    cur.s = 0;
    cur.l = 0;
    cur.a = 1;
  }
  for(size_t i = 0; i < ret->height(); i++){
    //left most
    HSLAPixel& cur = ret->getPixel(0,i);
    cur.h = 0;
    cur.s = 0;
    cur.l = 0;
    cur.a = 1;
  }
  for(int i = 0; i < width_; i++){
    for(int j = 0 ; j<height_; j++){
      if(walls_[j*width_+i].right_ == true){
        for(int k = 0; k <=10; k++){
        HSLAPixel& cur = ret->getPixel((i+1)*10,(j*10)+k);
        cur.h = 0;
        cur.s = 0;
        cur.l = 0;
        cur.a = 1;
      }
    }
    if(walls_[j*width_+i].down_ == true){
      for(int k = 0; k<=10; k++){
        HSLAPixel & cur = ret->getPixel((i*10)+k,(j+1)*10);
        cur.h = 0;
        cur.l = 0;
        cur.s = 0;
        cur.a = 1;
      }
    }
    }
  }
return ret;
}

PNG* SquareMaze::drawMazeWithSolution(){
  //thanks parnter!!
  cs225::PNG * png = drawMaze();
	vector<int> sol = solveMaze();

	int currX = 5;
	int currY = 5;
	unsigned idx = 0;

	cs225::HSLAPixel red(0,1,0.5,1);

	while(idx < sol.size()){
		if(sol[idx] == 0){	//color right
			for(int i = 0; i <= 10; i++){
				cs225::HSLAPixel & newPixel = png->getPixel(currX + i, currY);
				newPixel = red;
			}
			currX = currX + 10;
		}
		else if(sol[idx] == 1){	//color down
			for(int i = 0; i <= 10; i++){
				cs225::HSLAPixel & newPixel = png->getPixel(currX, currY + i);
				newPixel = red;
			}
			currY = currY + 10;
		}
		else if(sol[idx] == 2){	//color left
			for(int i = 0; i <= 10; i++){
				cs225::HSLAPixel & newPixel = png->getPixel(currX - i, currY);
				newPixel = red;
			}
			currX = currX - 10;
		}
		else if(sol[idx] == 3){	//color up
			for(int i = 0; i <= 10; i++){
				cs225::HSLAPixel & newPixel = png->getPixel(currX, currY - i);
				newPixel = red;
			}
			currY = currY - 10;
		}
		idx++;
	}

	cs225::HSLAPixel white(0,0,1,1);

	for(int k = 1; k <=9; k++){
		cs225::HSLAPixel & newPixel = png->getPixel(x_des*10+k, (y_des+1)*10);
		newPixel = white;
	}

	return png;
}
PNG* SquareMaze::drawCreativeMaze(){
  HSLAPixel grey = HSLAPixel(0,0,0.73);
  HSLAPixel db = HSLAPixel(195,1,0.27);
  HSLAPixel gb = HSLAPixel(213,0.43,0.46);
  HSLAPixel dp = HSLAPixel(248,0.53,0.58);
  map<int,HSLAPixel> background ;
  background[0] = grey;
  background[1] = db;
  background[2] = gb;
  background[3] = dp;
  HSLAPixel red = HSLAPixel(0,1,0.5);
  HSLAPixel org = HSLAPixel(51,1,0.5);
  HSLAPixel yel = HSLAPixel(103,1,0.5);
  HSLAPixel gre = HSLAPixel(154,1,0.5);
  HSLAPixel blu = HSLAPixel(206,1,0.5);
  HSLAPixel brib = HSLAPixel(257,1,0.5);
  HSLAPixel pur = HSLAPixel(309,1,0.5);
  HSLAPixel bri = HSLAPixel(170,0.95,0.93);
  map<int,HSLAPixel> color;
  color[0] = red;
  color[1] = org;
  color[2] = yel;
  color[3] = gre;
  color[4] = blu;
  color[5] = brib;
  color[6] = pur;
  PNG* ret = new PNG(width_*10+1,height_*10+1);
  for(size_t i = 0; i < ret->width(); i++){
    for(size_t j = 0; j< ret->height();j++){
      HSLAPixel& cur = ret->getPixel(i,j);
      cur = background[rand()%4];
    }
  }
  // for(size_t i = 10; i < ret->width() ; i++){
  //   //topmost
  //   HSLAPixel& cur = ret->getPixel(i,0);
  //   cur = bri;
  // }
  // for(size_t i = 0; i < ret->height(); i++){
  //   //left most
  //   HSLAPixel& cur = ret->getPixel(0,i);
  //   cur =bri;
  // }
  for(int i = 0; i < width_; i++){
    for(int j = 0 ; j<height_; j++){
      if((i-0.5*width_)*(j-0.5*height_)<=0.25*height_*width_){
      if(walls_[j*width_+i].right_ == true){
        for(int k = 0; k <=10; k++){
        HSLAPixel& cur = ret->getPixel((i+1)*10,(j*10)+k);
        cur = bri;
      }
    }
  if(walls_[j*width_+i].right_ == true){
    for(int k = 0; k <=10; k++){
    HSLAPixel& cur = ret->getPixel((i+1)*10,(j*10)+k);
    cur = bri;
  }
}
}
   //
   // if(i*i+j*j >= (0.25*width_*height_)){
   //  if(walls_[j*width_+i].down_ == true){
   //    for(int k = 0; k<=10; k++){
   //      HSLAPixel & cur = ret->getPixel((i*10)+k,(j+1)*10);
   //      cur = color[rand()%7];
   //    }
   //  }
   //  }
  }
  }

return ret;
}
