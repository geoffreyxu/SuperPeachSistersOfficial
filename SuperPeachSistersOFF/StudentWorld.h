#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "Level.h"
#include "Actor.h"
#include <string>
#include <vector>

using namespace std;
// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp

class Actor;

class StudentWorld : public GameWorld
{
public:
    StudentWorld(string assetPath);
    ~StudentWorld();
    virtual int init();
    virtual int move();
    virtual void cleanUp();
    bool canMoveTo(double endX, double endY);
    bool determineOverlap(double x, double y, double xx, double yy);
    bool bonkOverlapPeach(Actor* a);
    void bonkOverlapActor(Actor* a);
    bool damageOverlapActor(Actor* a);
    bool overlapsPeach(Actor* a);
    void peachWillBonk(double endX, double endY);
    bool peachInRange(double y);
    void addHealth();
    void addFlower();
    void addMushroom();
    void addStar();
    void addObject(Actor* actor);
    void reachedFlag();
    int leftOrRight(int xx);
    bool peachInXRange(double x);
    int peachDirection();
    void reachedMario();
private:
    vector<Actor*> actors;
    Peach* m_peach;
    int num_actors;
    bool levelComplete, gameComplete;
};

#endif // STUDENTWORLD_H_
