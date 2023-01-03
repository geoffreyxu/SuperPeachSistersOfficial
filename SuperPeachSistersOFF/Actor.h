#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp

class StudentWorld;

class Actor : public GraphObject
{
public:
    Actor(StudentWorld* world, int imageID, double startX, double startY, int startDirection, double depth, double size);
    virtual ~Actor();
    virtual void doSomething() = 0;
    virtual void getBonked() = 0;
    virtual bool isCollidable() = 0;
    virtual bool isDamageable() = 0;
    virtual void getDamaged() { return; }
    void turn();
    bool isAlive() const { return m_alive; }
    void setDead() { m_alive = false; }
    StudentWorld* getWorld() const { return m_world; }
private:
    StudentWorld* m_world;
    bool m_alive;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Peach : public Actor
{
public:
    Peach(StudentWorld* world, double startX, double startY);
    virtual void doSomething();
    virtual bool isDamageable() { return !getStar(); }
    virtual void getBonked();
    virtual bool isCollidable() { return false; }
    void flowerGoodie();
    void mushroomGoodie();
    void starGoodie();
    void addHealths() { m_health = 2; }
    bool getFlower() { return flower; }
    bool getMushroom() { return mushroom; }
    bool getStar() { return star; }
    virtual ~Peach();
private:
    int remaining_jump_distance;
    int recharge_before_next_fire;
    int m_health;
    int flower, mushroom, star;
    int invincible_ticks;
    int temp_invincible;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Person : public Actor
{
public:
    Person(StudentWorld* world, int imageID, double startX, double startY, int startDirection);
    virtual void doSomething() = 0;
    virtual bool isDamageable() { return true; }
    virtual bool isCollidable() { return false; }
    virtual void getBonked();
    virtual void getDamaged();
    virtual void doActivity() = 0;
    virtual ~Person();
private:
};

class Koopa : public Person
{
public:
    Koopa(StudentWorld* world, double startX, double startY);
    virtual void doSomething();
    virtual void doActivity();
    ~Koopa();
private:
};

class Goomba : public Person
{
public:
    Goomba(StudentWorld* world, double startX, double startY);
    virtual void doSomething();
    virtual void doActivity() { return; }
    ~Goomba();
private:
};

class Piranha : public Person
{
public:
    Piranha(StudentWorld* world, double startX, double startY);
    virtual void doSomething();
    virtual void doActivity() { return; }
    ~Piranha();
private:
    int firingDelay;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class End : public Actor
{
public:
    End(StudentWorld* world, int imageID, double x, double y, double depth, double size);
    virtual void doSomething();
    virtual void doActivity() = 0;
    virtual void getBonked() { return; }
    virtual bool isDamageable() { return false; }
    virtual bool isCollidable() { return false; }
    virtual ~End();
private:
};

class Flag : public End
{
public:
    Flag(StudentWorld* world, double x, double y);
    virtual void doActivity();
    virtual ~Flag();
private:
};

class Mario : public End
{
public:
    Mario(StudentWorld* world, double x, double y);
    virtual void doActivity();
    virtual ~Mario();
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Projectile : public Actor
{
public:
    Projectile(StudentWorld* world, int imageID, int startDirection, double x, double y);
    virtual void doSomething();
    virtual void doActivity() = 0;
    virtual bool isCollidable() { return false; }
    virtual void getBonked() { return; }
    virtual bool isDamageable() { return false; }
    virtual ~Projectile();
private:
};

class PiranhaFireball : public Projectile
{
public:
    PiranhaFireball(StudentWorld* world, double x, double y);
    virtual void doActivity();
    virtual ~PiranhaFireball();
private:
    int initial_fire_direction;
};

class Shell : public Projectile
{
public:
    Shell(StudentWorld* world, int direction, double x, double y);
    virtual void doActivity();
    virtual ~Shell();
private:
    int initial_fire_direction;
};

class PeachFireball : public Projectile
{
public:
    PeachFireball(StudentWorld* world, double x, double y);
    virtual void doActivity();
    virtual ~PeachFireball();
private:
    int initial_peach_direction;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Inanimate : public Actor
{
public:
    Inanimate(StudentWorld* world, int imageID, double startX, double startY, double depth, double size);
    virtual void doSomething() { return; }
    virtual bool isCollidable() { return true; }
    virtual bool isDamageable() { return false; }
    virtual ~Inanimate();
private:
};

class Block : public Inanimate
{
public:
    Block(StudentWorld* world, double x, double y);
    virtual void getBonked();
    virtual ~Block();
private:
};

class Pipe : public Inanimate
{
public:
    Pipe(StudentWorld* world, double x, double y);
    virtual void getBonked() { return; }
    virtual ~Pipe();
private:
};

class flowerBlock : public Block
{
public:
    flowerBlock(StudentWorld* world, double x, double y);
    virtual void getBonked();
    virtual ~flowerBlock();
private:
    bool hasGoodie;
};

class mushroomBlock : public Block
{
public:
    mushroomBlock(StudentWorld* world, double x, double y);
    virtual void getBonked();
    virtual ~mushroomBlock();
private:
    bool hasGoodie;
};

class starBlock : public Block
{
public:
    starBlock(StudentWorld* world, double x, double y);
    virtual void getBonked();
    virtual ~starBlock();
private:
    bool hasGoodie;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Goodie : public Actor
{
public:
    Goodie(StudentWorld* world, int imageID, double startX, double startY);
    virtual void doSomething();
    virtual bool isCollidable() { return false; }
    virtual bool isDamageable() { return false; }
    virtual void getBonked() { return; }
    virtual void doActivity() = 0;
    virtual ~Goodie();
private:
};

class Flower : public Goodie
{
public:
    Flower(StudentWorld* world, double startX, double startY);
    virtual void doActivity();
    virtual ~Flower();
private:
};

class Mushroom : public Goodie
{
public:
    Mushroom(StudentWorld* world, double startX, double startY);
    virtual void doActivity();
    virtual ~Mushroom();
private:
};

class Star : public Goodie
{
public:
    Star(StudentWorld* world, double startX, double startY);
    virtual void doActivity();
    virtual ~Star();
private:
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#endif // ACTOR_H_
