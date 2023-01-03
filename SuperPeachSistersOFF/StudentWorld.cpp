#include "StudentWorld.h"
#include "GameConstants.h"
#include <string>
#include <sstream>
#include <iostream>
using namespace std;

GameWorld* createStudentWorld(string assetPath)
{
    return new StudentWorld(assetPath);
}

// Students:  Add code to this file, StudentWorld.h, Actor.h, and Actor.cpp

StudentWorld::StudentWorld(string assetPath)
: GameWorld(assetPath), num_actors(0)
{
    m_peach = nullptr;
    actors.clear();
}
StudentWorld::~StudentWorld()
{
    cleanUp();
}

int StudentWorld::init()
{
    levelComplete = false;
    gameComplete = false;
    Level level(assetPath());
    string levelName;
    if (getLevel() <= 9)
    {
        int i = getLevel();
        levelName = "level0" + to_string(i) + ".txt";
    }
    else if (getLevel() > 9)
    {
        int i = getLevel();
        levelName = "level" + to_string(i) + ".txt";
    }
    Level::LoadResult result = level.loadLevel(levelName);
    if (result == Level::load_fail_bad_format)
    {
        return GWSTATUS_LEVEL_ERROR;
    }
    if (result == Level::load_fail_file_not_found)
    {
        return GWSTATUS_LEVEL_ERROR;
    }
    else if (result == Level::load_success)
    {
        for (int i = 0; i < GRID_WIDTH; i++)
        {
            for (int j = 0; j < GRID_HEIGHT; j++)
            {
                double startX = i * SPRITE_WIDTH;
                double startY = j * SPRITE_HEIGHT;
                Level::GridEntry entry = level.getContentsOf(i, j);
                if (entry == Level::peach)
                {
                    m_peach = new Peach(this, startX, startY);
                }
                else if (entry == Level::block)
                {
                    actors.push_back(new Block(this, startX, startY));
                    num_actors++;
                }
                else if (entry == Level::mushroom_goodie_block)
                {
                    actors.push_back(new mushroomBlock(this, startX, startY));
                    num_actors++;
                }
                else if (entry == Level::star_goodie_block)
                {
                    actors.push_back(new starBlock(this, startX, startY));
                    num_actors++;
                }
                else if (entry == Level::flower_goodie_block)
                {
                    actors.push_back(new flowerBlock(this, startX, startY));
                    num_actors++;
                }
                else if (entry == Level::pipe)
                {
                    actors.push_back(new Pipe(this, startX, startY));
                    num_actors++;
                }
                else if (entry == Level::flag)
                {
                    actors.push_back(new Flag(this, startX, startY));
                    num_actors++;
                }
                else if (entry == Level::koopa)
                {
                    actors.push_back(new Koopa(this, startX, startY));
                    num_actors++;
                }
                else if (entry == Level::goomba)
                {
                    actors.push_back(new Goomba(this, startX, startY));
                    num_actors++;
                }
                else if (entry == Level::piranha)
                {
                    actors.push_back(new Piranha(this, startX, startY));
                    num_actors++;
                }
                else if (entry == Level::mario)
                {
                    actors.push_back(new Mario(this, startX, startY));
                    num_actors++;
                }
            }
        }
    }
    return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move()
{
    // This code is here merely to allow the game to build, run, and terminate after you hit enter.
    // Notice that the return value GWSTATUS_PLAYER_DIED will cause our framework to end the current level.
    m_peach->doSomething();
    for (int i = 0; i < num_actors; i++)
    {
        if (actors[i]->isAlive())
        {
            actors[i]->doSomething();
        }
    }
    if (!m_peach->isAlive())
    {
        decLives();
        playSound(SOUND_PLAYER_DIE);
        if (getLives() == 0)
        {
            playSound(SOUND_GAME_OVER);
        }
        return GWSTATUS_PLAYER_DIED;
    }
    if (levelComplete) {
        playSound(SOUND_FINISHED_LEVEL);
        return GWSTATUS_FINISHED_LEVEL;
    }
    if (gameComplete) {
        return GWSTATUS_PLAYER_WON;
    }
    vector<Actor*>::iterator it = actors.begin();
    while (it != actors.end())
    {
        if (!(*it)->isAlive())
        {
            delete *it;
            it = actors.erase(it);
            num_actors--;
        }
        else
            it++;
    }
    
    ostringstream oss;
    oss.setf(ios::fixed);
    oss.precision(0);
    oss << "Lives: " << getLives();
    if (getLevel() < 10)
        oss << "  Level: 0" << getLevel();
    else
        oss << "  Level: " << getLevel();
    if (getScore() < 10)
        oss << "  Points: 00000" << getScore();
    else if (getScore() < 100)
        oss << "  Points: 0000" << getScore();
    else if (getScore() < 1000)
        oss << "  Points: 000" << getScore();
    else if (getScore() < 10000)
        oss << "  Points: 00" << getScore();
    else if (getScore() < 100000)
        oss << "  Points: 0" << getScore();
    else if (getScore() > 99999)
        oss << "  Points: " << getScore();
    if (m_peach->getFlower())
        oss << " ShootPower!";
    if (m_peach->getMushroom())
        oss << " JumpPower!";
    if (m_peach->getStar())
        oss << " StarPower!";
    setGameStatText(oss.str());
    return GWSTATUS_CONTINUE_GAME;
}

void StudentWorld::cleanUp()
{
    vector<Actor*>::iterator it = actors.begin();
    while (it != actors.end())
    {
        delete *it;
        it = actors.erase(it);
        num_actors--;
    }
    delete m_peach;
    m_peach = nullptr;
}

bool StudentWorld::canMoveTo(double endX, double endY)
{
    vector<Actor*>::iterator it = actors.begin();
    while (it != actors.end())
    {
        Actor* actor = *it;
        if(determineOverlap(endX, endY, actor->getX(), actor->getY()) && actor->isCollidable() && actor->isAlive())
        {
            return false;
        }
        it++;
    }
    return true;
}

void StudentWorld::peachWillBonk(double endX, double endY)
{
    vector<Actor*>::iterator it = actors.begin();
    while (it != actors.end())
    {
        Actor* actor = *it;
        if(determineOverlap(endX, endY, actor->getX(), actor->getY()) && actor->isAlive() && actor->isCollidable())
        {
            actor->getBonked();
        }
        it++;
    }
}

bool StudentWorld::determineOverlap(double x, double y, double xx, double yy)
{
    if ((x <= xx && x + SPRITE_WIDTH > xx) || (x >= xx && x < xx + SPRITE_WIDTH))
           if ((y <= yy && y + SPRITE_HEIGHT > yy) || (y >= yy && y < yy + SPRITE_HEIGHT))
               return true;
    return false;
}

bool StudentWorld::overlapsPeach(Actor* a)
{
    if(determineOverlap(a->getX(), a->getY(), m_peach->getX(), m_peach->getY()))
        return true;
    return false;
}

bool StudentWorld::bonkOverlapPeach(Actor* a)
{
    if(determineOverlap(a->getX(), a->getY(), m_peach->getX(), m_peach->getY()))
    {
        m_peach->getBonked();
        return true;
    }
    return false;
}

void StudentWorld::bonkOverlapActor(Actor* a)
{
    vector<Actor*>::iterator it = actors.begin();
    while (it != actors.end())
    {
        Actor* actor = *it;
        if(determineOverlap(a->getX(), a->getY(), actor->getX(), actor->getY()) && actor->isAlive())
        {
            actor->getBonked();
        }
        it++;
    }
}

bool StudentWorld::damageOverlapActor(Actor* a)
{
    vector<Actor*>::iterator it = actors.begin();
    while (it != actors.end())
    {
        Actor* actor = *it;
        if(determineOverlap(a->getX(), a->getY(), actor->getX(), actor->getY()) && actor->isAlive() && actor->isDamageable())
        {
            actor->getDamaged();
            return true;
        }
        it++;
    }
    return false;
}

void StudentWorld::addHealth()
{
    m_peach->addHealths();
}

void StudentWorld::addFlower()
{
    m_peach->flowerGoodie();
}

void StudentWorld::addMushroom()
{
    m_peach->mushroomGoodie();
}

void StudentWorld::addStar()
{
    m_peach->starGoodie();
}

void StudentWorld::reachedFlag()
{
    levelComplete = true;
}

bool StudentWorld::peachInRange(double y)
{
    if (m_peach->getY() <= 1.5 * SPRITE_HEIGHT + y && m_peach->getY() >= y - 1.5 * SPRITE_HEIGHT)
        return true;
    return false;
}

bool StudentWorld::peachInXRange(double x)
{
    if (m_peach->getX() <= 8 * SPRITE_WIDTH + x && m_peach->getX() >= x - 8 * SPRITE_WIDTH)
        return true;
    return false;
}

void StudentWorld::addObject(Actor* actor)
{
    actors.push_back(actor);
    num_actors++;
}

int StudentWorld::leftOrRight(int xx)
{
    if (m_peach->getX() > xx)
        return 0;
    else
        return 180;
}

int StudentWorld::peachDirection()
{
    return m_peach->getDirection();
}

void StudentWorld::reachedMario()
{
    gameComplete = true;
}
