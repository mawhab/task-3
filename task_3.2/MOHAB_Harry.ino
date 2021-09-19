#include <LinkedList.h>

#define front 4 // front ir sensor
#define left 5 // left ir sensor
#define right 3 // right ir sensor

class Coordinate{ // coordinate class to store x and y of a coordinate
  public:
  Coordinate(){
  }
  Coordinate(int x, int y){ // constructor to assign values
    this->x = x;
    this->y = y;
  }
  int x;
  int y;
};

// function to search through a linked list given the target coordinate
bool search(LinkedList<Coordinate> cont, Coordinate target){ 
  for(int i=0;i<cont.size();i++){
    Coordinate tmp = cont.get(i);
    if(tmp.x==target.x && tmp.y == target.y)
      return true;
  }
  return false;
}
void moveForward(){
  
}
void rotate90left(){
  
}
void rotate90right(){
  
}


int coordinates[] = {0,0}; // current coordinates
int sign[] = {1,1}; // sign of current coordinates (direction)
int i=1; // idicates whether we are moving on x or y

LinkedList<Coordinate> visited; // linked list to store visited coordinates in crossroads

void setup()
{
  pinMode(front, INPUT);
  pinMode(right, INPUT);
  pinMode(left, INPUT);
}

void loop()
{
  // while we only have forward direction, move forward
  while(digitalRead(front)==HIGH && digitalRead(left)==LOW && digitalRead(right)==LOW){
    moveForward();
    coordinates[i] += sign[i]; // update current coordinates as you go
  }
  // if we dont have any directions to go to go back
  if(digitalRead(front)==LOW && digitalRead(left)==LOW && digitalRead(right)==LOW){
    rotate90left();
    rotate90left();
    sign[i] *= -1;
    return;
  }

  // flag to indicate that we have more than one road we can take
  bool crossroad = digitalRead(front)==HIGH && digitalRead(left)==HIGH ||
                   digitalRead(right)==HIGH && digitalRead(left)==HIGH ||
                   digitalRead(front)==HIGH && digitalRead(right)==HIGH;
  if(crossroad){
    // add the road we just took to visited coordinates
    int temp[] = {coordinates[0], coordinates[1]};
    temp[i] -= sign[i];
    Coordinate tmp = Coordinate(temp[0], temp[1]);
    visited.add(tmp);
  }
  
  // if we are at a crossrads we check forward then left then right
  if(digitalRead(front)==HIGH){ 
    // we need to check if we already visited this so we check first coordinate of this road
    int temp[] = {coordinates[0], coordinates[1]};
    temp[i] += sign[i];
    Coordinate tmp = Coordinate(temp[0], temp[1]);
    if(!search(visited,tmp)){ // if not visited then move forward
      moveForward();
      coordinates[i] += sign[i];
    }
  }
  // now we check left
  if(digitalRead(left)==HIGH){
    // temporary values to check direction before actually switching to it
    int tmpi, tmpsign;
    if(i){ // if we are going on y direction
      tmpi = 0;
      if(sign[i]){ // if we are going up
        tmpsign = -1; // switch to left
      }else{ // if we are going down
        tmpsign = 1; // siwtch to right
      }
    }else{ // if we are going on x direction
      tmpi = 1;
      if(sign[i]) // if we are going right
        tmpsign = 1; // switch to up
      else // if we are going left
        tmpsign = -1; // switch to down
    }
    if(crossroad){ // if we have more than one option
      // we need to check if we already visited this so we check first coordinate of this road
      int temp[] = {coordinates[0], coordinates[1]};
      temp[tmpi] += tmpsign;
      Coordinate tmp = Coordinate(temp[0], temp[1]);
      if(!search(visited,tmp)){ // if not visited then move forward
        rotate90left();
        i = tmpi;
        sign[i] = tmpsign;
        moveForward();
        coordinates[i] += sign[i];
      }
    }else{
      rotate90left();
      i = tmpi;
      sign[i] = tmpsign;
      moveForward();
      coordinates[i] += sign[i];
    }
  }
  if(digitalRead(right)==HIGH){
    // temporary values to check direction before actually switching to it
    int tmpi, tmpsign;
    if(i){ // if we are going on y direction
      tmpi = 0;
      if(sign[i]){ // if we are going up
        tmpsign = 1; // switch to right
      }else{ // if we are going down
        tmpsign = -1; // siwtch to left
      }
    }else{ // if we are going on x direction
      tmpi = 1;
      if(sign[i]) // if we are going right
        tmpsign = -1; // switch to down
      else // if we are going left
        tmpsign = 1; // switch to up
    }
    if(crossroad){ // if we have more than one option
      // we need to check if we already visited this so we check first coordinate of this road
      int temp[] = {coordinates[0], coordinates[1]};
      temp[tmpi] += tmpsign;
      Coordinate tmp = Coordinate(temp[0], temp[1]);
      if(!search(visited,tmp)){ // if not visited then move forward
        rotate90right();
        i = tmpi;
        sign[i] = tmpsign;
        moveForward();
        coordinates[i] += sign[i];
      }
    }else{
      rotate90right();
      i = tmpi;
      sign[i] = tmpsign;
      moveForward();
      coordinates[i] += sign[i];
    }
  }
    
}
