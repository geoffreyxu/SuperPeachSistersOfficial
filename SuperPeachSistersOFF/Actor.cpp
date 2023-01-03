#include "Actor.h"
#include "StudentWorld.h"

// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Actor::Actor(StudentWorld* world, int imageID, double startX, double startY, int startDirection, double depth, double size) :
GraphObject(imageID, startX, startY), m_world(world), m_alive(true) {};

Actor::~Actor() {}

void Actor::turn()
{
    if (getDirection() == 180)
        setDirection(0);
    else if (getDirection() == 0)
        setDirection(180);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Person::Person(StudentWorld* world, int imageID, double startX, double startY, int startDirection) :
Actor(world, imageID, startX, startY, startDirection, 0, 1.0) {};

Person::~Person() {}

void Person::getBonked()
{
    getWorld()->playSound(SOUND_PLAYER_KICK);
    getWorld()->increaseScore(100);
    setDead();
    doActivity();
}

void Person::getDamaged()
{
    setDead();
    getWorld()->increaseScore(100);
    doActivity();
}

Koopa::Koopa(StudentWorld* world, double startX, double startY) :
Person(world, IID_KOOPA, startX, startY, (randInt(90, 270) / 180) * 180) {};

Koopa::~Koopa() {}

void Koopa::doActivity()
{
    getWorld()->addObject(new Shell(getWorld(), getDirection(), getX(), getY()));
}

void Koopa::doSomething()
{
    if (!isAlive())
        return;
    if (getWorld()->bonkOverlapPeach(this))
        return;
    if (getDirection() == 0 && getWorld()->canMoveTo(getX() + 1, getY()) && !getWorld()->canMoveTo(getX() + 8, getY() - 1))
    {
        moveTo(getX() + 1, getY());
        return;
    }
    else if (getDirection() == 180 && getWorld()->canMoveTo(getX() - 1, getY()) && !getWorld()->canMoveTo(getX() - 8, getY() - 1))
    {
        moveTo(getX() - 1, getY());
        return;
    }
    else
    {
        turn();
        if (getDirection() == 0 && getWorld()->canMoveTo(getX() + 1, getY()) && !getWorld()->canMoveTo(getX() + 8, getY() - 1))
        {
            moveTo(getX() + 1, getY());
            return;
        }
        else if (getDirection() == 180 && getWorld()->canMoveTo(getX() - 1, getY()) && !getWorld()->canMoveTo(getX() - 8, getY() - 1))
        {
            moveTo(getX() - 1, getY());
            return;
        }
    }
}

Goomba::Goomba(StudentWorld* world, double startX, double startY) :
Person(world, IID_GOOMBA, startX, startY, (randInt(90, 270) / 180) * 180) {};

Goomba::~Goomba() {}

void Goomba::doSomething()
{
    if (!isAlive())
        return;
    if (getWorld()->bonkOverlapPeach(this))
        return;
    if (getDirection() == 0 && getWorld()->canMoveTo(getX() + 1, getY()) && !getWorld()->canMoveTo(getX() + 8, getY() - 1))
    {
        moveTo(getX() + 1, getY());
        return;
    }
    else if (getDirection() == 180 && getWorld()->canMoveTo(getX() - 1, getY()) && !getWorld()->canMoveTo(getX() - 8, getY() - 1))
    {
        moveTo(getX() - 1, getY());
        return;
    }
    else
    {
        turn();
        if (getDirection() == 0 && getWorld()->canMoveTo(getX() + 1, getY()) && !getWorld()->canMoveTo(getX() + 8, getY() - 1))
        {
            moveTo(getX() + 1, getY());
            return;
        }
        else if (getDirection() == 180 && getWorld()->canMoveTo(getX() - 1, getY()) && !getWorld()->canMoveTo(getX() - 8, getY() - 1))
        {
            moveTo(getX() - 1, getY());
            return;
        }
    }
}

Piranha::Piranha(StudentWorld* world, double startX, double startY) :
Person(world, IID_PIRANHA, startX, startY, (randInt(90, 270) / 180) * 180), firingDelay(0) {};

Piranha::~Piranha() {}

void Piranha::doSomething()
{
    if (!isAlive())
        return;
    increaseAnimationNumber();
    if (getWorld()->bonkOverlapPeach(this))
        return;
    if (!getWorld()->peachInRange(getY()))
    {
        return;
    }
    else
    {
        if (getWorld()->leftOrRight(getX()))
            setDirection(180);
        else
            setDirection(0);
        if (firingDelay > 0)
        {
            firingDelay--;
            return;
        }
        else
        {
            if (getWorld()->peachInXRange(getX()))
            {
                getWorld()->addObject(new PiranhaFireball(getWorld(), getX(), getY()));
                getWorld()->playSound(SOUND_PIRANHA_FIRE);
                firingDelay = 40;
            }
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Goodie::Goodie(StudentWorld* world, int imageID, double startX, double startY) :
Actor(world, imageID, startX, startY, 0, 1, 1) {};

void Goodie::doSomething()
{
    if (getWorld()->overlapsPeach(this))
    {
        setDead();
        getWorld()->playSound(SOUND_PLAYER_POWERUP);
        doActivity();
    }
    if (getWorld()->canMoveTo(getX(), getY() - 2))
    {
        moveTo(getX(), getY() - 2);
    }
    if (getDirection() == 0)
    {
        if (getWorld()->canMoveTo(getX() + 2, getY()))
        {
            moveTo(getX() + 2, getY());
            return;
        }
        else
        {
            setDirection(180);
            return;
        }
    }
    else if (getDirection() == 180)
    {
        if (getWorld()->canMoveTo(getX() - 2, getY()))
        {
            moveTo(getX() - 2, getY());
            return;
        }
        else
        {
            setDirection(0);
            return;
        }
    }
}

Goodie::~Goodie() {}

Flower::Flower(StudentWorld* world, double startX, double startY) :
Goodie(world, IID_FLOWER, startX, startY) {};

Flower::~Flower() {}

void Flower::doActivity()
{
    getWorld()->increaseScore(50);
    getWorld()->addFlower();
    getWorld()->addHealth();
}

Mushroom::Mushroom(StudentWorld* world, double startX, double startY) :
Goodie(world, IID_MUSHROOM, startX, startY) {};

Mushroom::~Mushroom() {}

void Mushroom::doActivity()
{
    getWorld()->increaseScore(75);
    getWorld()->addMushroom();
    getWorld()->addHealth();
}

Star::Star(StudentWorld* world, double startX, double startY) :
Goodie(world, IID_STAR, startX, startY) {};

Star::~Star() {}

void Star::doActivity()
{
    getWorld()->increaseScore(100);
    getWorld()->addStar();
    getWorld()->addHealth();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
End::End(StudentWorld* world, int imageID, double x, double y, double depth, double size) :
Actor(world, imageID, x, y, 0, 1, 1) {};

End::~End() {}

void End::doSomething()
{
    if (getWorld()->overlapsPeach(this))
    {
        getWorld()->increaseScore(1000);
        setDead();
        doActivity();
    }
}

Flag::Flag(StudentWorld* world, double x, double y) :
End(world, IID_FLAG, x, y, 1, 1.0) {};

void Flag::doActivity()
{
    getWorld()->reachedFlag();
}

Flag::~Flag() {}

Mario::Mario(StudentWorld* world, double x, double y) :
End(world, IID_MARIO, x, y, 1, 1) {};

void Mario::doActivity()
{
    getWorld()->reachedMario();
}

Mario::~Mario() {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Peach::Peach(StudentWorld* world, double startX, double startY) :
Actor(world, IID_PEACH, startX, startY, 0, 0, 1), m_health(1), remaining_jump_distance(0), flower(0), mushroom(0), star(0), recharge_before_next_fire(0), invincible_ticks(0), temp_invincible(0) {};

void Peach::doSomething()
{
    if (!isAlive())
        return;
    int act;
    if (invincible_ticks > 0)
        invincible_ticks--;
    temp_invincible--;
    if (invincible_ticks == 0)
        star = 0;
    if (remaining_jump_distance > 0)
    {
        if (getWorld()->canMoveTo(getX(), getY() + 4))
        {
            moveTo(getX(), getY() + 4);
            getWorld()->peachWillBonk(getX(), getY() + 4);
            remaining_jump_distance--;
        }
        else
        {
            remaining_jump_distance = 0;
        }
    }
    else if (remaining_jump_distance == 0)
    {
        if (getWorld()->canMoveTo(getX(), getY() - 4))
            moveTo(getX(), getY() - 4);
    }
    if(getWorld()->getKey(act))
    {
        switch(act)
        {
            case KEY_PRESS_LEFT:
                setDirection(180);
                if (getWorld()->canMoveTo(getX() - 4, getY()))
                {
                    getWorld()->peachWillBonk(getX() - 4, getY());
                    moveTo(getX() - 4, getY());
                }
                break;
            case KEY_PRESS_RIGHT:
                setDirection(0);
                if (getWorld()->canMoveTo(getX() + 4, getY()))
                {
                    getWorld()->peachWillBonk(getX() - 4, getY());
                    moveTo(getX() + 4, getY());
                }
                break;
            case KEY_PRESS_UP:
                if (!getWorld()->canMoveTo(getX(), getY() - 1))
                {
                    getWorld()->playSound(SOUND_PLAYER_JUMP);
                    if (getMushroom())
                        remaining_jump_distance = 12;
                    else
                        remaining_jump_distance = 8;
                }
                break;
            case KEY_PRESS_SPACE:
                if (!flower)
                    break;
                else if (recharge_before_next_fire > 0)
                    break;
                else
                {
                    getWorld()->playSound(SOUND_PLAYER_FIRE);
                    recharge_before_next_fire = 8;
                    if (getDirection() == 0)
                        getWorld()->addObject(new PeachFireball(getWorld(), getX() + 4, getY()));
                    else
                        getWorld()->addObject(new PeachFireball(getWorld(), getX() - 4, getY()));
                }
                break;
            default:
                break;
        }
    }
    recharge_before_next_fire--;
    if (!isDamageable())
    {
        getWorld()->bonkOverlapActor(this);
    }
}

void Peach::flowerGoodie()
{
    flower++;
    addHealths();
}

void Peach::mushroomGoodie()
{
    mushroom++;
    addHealths();
}

void Peach::starGoodie()
{
    star++;
    invincible_ticks = 150;
}

void Peach::getBonked()
{
    if (star > 0 || temp_invincible > 0)
        return;
    else
    {
        m_health--;
        if (temp_invincible < 0)
            temp_invincible = 10;
        mushroom = 0;
        flower = 0;
        if (m_health <= 0)
            setDead();
        if (isAlive())
        {
            getWorld()->playSound(SOUND_PLAYER_HURT);
        }
    }
}
Peach::~Peach() {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Inanimate::Inanimate(StudentWorld* world, int imageID, double startX, double startY, double depth, double size):
Actor(world, imageID, startX, startY, 0, depth, size) {}

Inanimate::~Inanimate() {}

Block::Block(StudentWorld* world, double x, double y) :
Inanimate(world, IID_BLOCK, x, y, 2, 1.0) {};

void Block::getBonked()
{
    getWorld()->playSound(SOUND_PLAYER_BONK);
    return;
}

Block::~Block() {}

flowerBlock::flowerBlock(StudentWorld* world, double x, double y) :
Block(world, x, y), hasGoodie(true) {};

flowerBlock::~flowerBlock() {}

void flowerBlock::getBonked()
{
    if(!hasGoodie)
    {
        getWorld()->playSound(SOUND_PLAYER_BONK);
        return;
    }
    else
    {
        getWorld()->playSound(SOUND_POWERUP_APPEARS);
        getWorld()->addObject(new Flower(getWorld(), getX(), getY() + 8));
        hasGoodie = false;
    }
}


mushroomBlock::mushroomBlock(StudentWorld* world, double x, double y) :
Block(world, x, y), hasGoodie(true) {};

mushroomBlock::~mushroomBlock() {}

void mushroomBlock::getBonked()
{
    if(!hasGoodie)
    {
        getWorld()->playSound(SOUND_PLAYER_BONK);
        return;
    }
    else
    {
        getWorld()->playSound(SOUND_POWERUP_APPEARS);
        getWorld()->addObject(new Mushroom(getWorld(), getX(), getY() + 8));
        hasGoodie = false;
    }
}

starBlock::starBlock(StudentWorld* world, double x, double y) :
Block(world, x, y), hasGoodie(true) {};

starBlock::~starBlock() {}

void starBlock::getBonked()
{
    if(!hasGoodie)
    {
        getWorld()->playSound(SOUND_PLAYER_BONK);
        return;
    }
    else
    {
        getWorld()->playSound(SOUND_POWERUP_APPEARS);
        getWorld()->addObject(new Star(getWorld(), getX(), getY() + 8));
        hasGoodie = false;
    }
}

Pipe::Pipe(StudentWorld* world, double x, double y) :
Inanimate(world, IID_PIPE, x, y, 2, 1.0) {};

Pipe::~Pipe() {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Projectile::Projectile(StudentWorld* world, int imageID, int startDirection, double x, double y) :
Actor(world, imageID, x, y, 0, 1, 1) {};

void Projectile::doSomething()
{
    doActivity();
    if (getWorld()->canMoveTo(getX(), getY() - 2))
    {
        moveTo(getX(), getY() - 2);
    }
    if (getDirection() == 0)
    {
        if (getWorld()->canMoveTo(getX() + 2, getY()))
            moveTo(getX() + 2, getY());
        else {
            setDead();
            return;
        }
    }
    else if (getDirection() == 180)
    {
        if (getWorld()->canMoveTo(getX() - 2, getY()))
            moveTo(getX() - 2, getY());
        else {
            setDead();
            return;
        }
    }
}

Projectile::~Projectile() {}

PiranhaFireball::PiranhaFireball(StudentWorld* world, double x, double y) :
Projectile(world, IID_PIRANHA_FIRE, 0, x, y), initial_fire_direction(getWorld()->leftOrRight(getX())) {};

void PiranhaFireball::doActivity()
{
    setDirection(initial_fire_direction);
    if (getWorld()->bonkOverlapPeach(this))
    {
        setDead();
        return;
    }
}

PiranhaFireball::~PiranhaFireball() {}

PeachFireball::PeachFireball(StudentWorld* world, double x, double y) :
Projectile(world, IID_PEACH_FIRE, 0, x, y), initial_peach_direction(getWorld()->peachDirection()) {};

void PeachFireball::doActivity()
{
    setDirection(initial_peach_direction);
    if (getWorld()->damageOverlapActor(this))
    {
        setDead();
    }
    return;
}

PeachFireball::~PeachFireball() {}

Shell::Shell(StudentWorld* world, int direction, double x, double y) :
Projectile(world, IID_SHELL, 0, x, y), initial_fire_direction(direction) {};

void Shell::doActivity()
{
    setDirection(initial_fire_direction);
    if (getWorld()->damageOverlapActor(this))
    {
        setDead();
    }
    return;
}

Shell::~Shell() {}
