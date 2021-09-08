/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "HelloWorldScene.h"
#include "GameLayer.hpp"
#include "GameSprite.hpp"
#include <string>

USING_NS_CC;
using namespace std;

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    this->visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // 2. Add background
    auto court = Sprite::create("court.png");
    if (court ==  nullptr) {
        problemLoading("court.png");
    } else {
        court->setPosition(Vec2(this->visibleSize.width * 0.5, this->visibleSize.height * 0.5));
        this->addChild(court, 0);
    }
    
    // 3. Add user
    auto player1 = GameSprite::gameSpriteWithFile("mallet.png");
    if (player1 == nullptr) {
        problemLoading("mallet.png");
    } else {
        player1->setPosition(Vec2(this->visibleSize.width * 0.5, player1->radius() * 2));
        this->addChild(player1);
        this->players.push_back(player1);
    }
    
    auto player2 = GameSprite::gameSpriteWithFile("mallet.png");
    if (player2 == nullptr) {
        problemLoading("mallet.png");
    } else {
        player2->setPosition(Vec2(this->visibleSize.width * 0.5, this->visibleSize.height - player2->radius() * 2));
        this->addChild(player2);
        this->players.push_back(player2);
    }
    
    this->puck = GameSprite::gameSpriteWithFile("puck.png");
    if (this->puck == nullptr) {
        problemLoading("puch.png");
    } else {
        this->puck->setPosition(Vec2(this->visibleSize.width * 0.5, this->visibleSize.height * 0.5));
        this->addChild(this->puck);
    }
    
    // 4. Add score
    this->player1ScoreLabel = Label::createWithTTF("0", "fonts/Arial.ttf", 60);
    if (this->player1ScoreLabel == nullptr) {
        problemLoading("fonts/Arial.ttf");
    } else {
        this->player1ScoreLabel->setPosition(Vec2(this->visibleSize.width - 60, this->visibleSize.height * 0.5 - 80));
        this->addChild(this->player1ScoreLabel);
    }
    
    this->player2ScoreLabel = Label::createWithTTF("0", "fonts/Arial.ttf", 60);
    if (this->player2ScoreLabel == nullptr) {
        problemLoading("fonts/Arial.ttf");
    } else {
        this->player2ScoreLabel->setPosition(Vec2(this->visibleSize.width - 60, this->visibleSize.height * 0.5 + 80));
        this->addChild(this->player2ScoreLabel);
    }

    // 5. Controller
    auto listener = EventListenerTouchAllAtOnce::create();
    listener->onTouchesBegan = CC_CALLBACK_2(HelloWorld::onTouchesBegan, this);
    listener->onTouchesMoved = CC_CALLBACK_2(HelloWorld::onTouchesMoved, this);
    listener->onTouchesEnded = CC_CALLBACK_2(HelloWorld::onTouchesEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    this->scheduleUpdate();
    
    return true;
}

void HelloWorld::onTouchesBegan(const vector<Touch*>& touches, Event*) {
    for (auto& touch : touches) {
        if (touch == nullptr) {
            continue;
        }
        auto tap = touch->getLocation();
        for (auto& player : this->players) {
            if (player->getBoundingBox().containsPoint(tap)) {
                player->setTouch(touch);
            }
        }
    }
}

void HelloWorld::onTouchesMoved(const vector<Touch *>& touchers, Event*) {
    for (auto& touch : touchers) {
        if (touch == nullptr) {
            continue;
        }
        auto tap = touch->getLocation();
        for (auto& player : this->players) {
            if (player->getTouch() != touch) {
                continue;
            }
            auto nextPosition = tap;
            if (nextPosition.x < player->radius()) {
                nextPosition.x = player->radius();
            }
            if (nextPosition.x > this->visibleSize.width - player->radius()) {
                nextPosition.x = this->visibleSize.width - player->radius();
            }
            
            auto halfSizeHeight = this->visibleSize.height * 0.5;
            if (player->getPositionY() <= halfSizeHeight) {
                if (nextPosition.y < player->radius()) {
                    nextPosition.y = player->radius();
                }
                if (nextPosition.y > halfSizeHeight - player->radius()) {
                    nextPosition.y = halfSizeHeight - player->radius();
                }
            } else {
                if (nextPosition.y > this->visibleSize.height - player->radius()) {
                    nextPosition.y = this->visibleSize.height - player->radius();
                }
                if (nextPosition.y < halfSizeHeight + player->radius()) {
                    nextPosition.y = halfSizeHeight + player->radius();
                }
            }
            
            player->setNextPosition(nextPosition);
            player->setVector(Vec2(tap.x - player->getPositionX(), tap.y - player->getPositionY()));
        }
    }
}

void HelloWorld::onTouchesEnded(const vector<Touch *>& touchers, Event*) {
    for (auto& touch : touchers) {
        if (touch == nullptr) {
            continue;
        }
        for (auto& player : this->players) {
            if (player->getTouch() == touch) {
                player->setTouch(nullptr);
                player->setVector(Vec2(0, 0));
            }
        }
    }
}

void HelloWorld::update(float) {
    auto ballNextPosition = this->puck->getNextPosition();
    auto ballVector = this->puck->getVector();
    
    ballNextPosition += ballVector;
    auto squared_radii = pow(this->players[0]->radius() + this->puck->radius(), 2);
    
    for (auto& player : this->players) {
        auto playerNextPosition = player->getNextPosition();
        auto playerVector = player->getVector();
        
        float diffx = ballNextPosition.x - player->getPositionX();
        float diffy = ballNextPosition.y - player->getPositionY();
        
        float distance1 = pow(diffx, 2) + pow(diffy, 2);
        float distance2 = pow(this->puck->getPositionX() - playerNextPosition.x, 2) + pow(this->puck->getPositionY() - playerNextPosition.y, 2);
        
        if (distance1 <= squared_radii || distance2 <= squared_radii) {
            
            float mag_ball = pow(ballVector.x, 2) + pow(ballVector.y, 2);
            float mag_player = pow (playerVector.x, 2) + pow (playerVector.y, 2);
              
            float force = sqrt(mag_ball + mag_player);
            float angle = atan2(diffy, diffx);
            
            ballVector.x = force* cos(angle);
            ballVector.y = (force* sin(angle));
            
            ballNextPosition.x = playerNextPosition.x + (player->radius() + this->puck->radius() + force) * cos(angle);
            ballNextPosition.y = playerNextPosition.y + (player->radius() + this->puck->radius() + force) * sin(angle);
        }
        
        //check collision of ball and sides
        if (ballNextPosition.x < this->puck->radius()) {
            ballNextPosition.x = this->puck->radius();
            ballVector.x *= -0.8f;
        }
        
        if (ballNextPosition.x > this->visibleSize.width - this->puck->radius()) {
            ballNextPosition.x = this->visibleSize.width - this->puck->radius();
            ballVector.x *= -0.8f;
        }
        //ball and top of the court
        if (ballNextPosition.y > this->visibleSize.height - this->puck->radius()) {
            if (this->puck->getPosition().x < this->visibleSize.width* 0.5f - GOAL_WIDTH* 0.5f ||
                this->puck->getPosition().x > this->visibleSize.width* 0.5f + GOAL_WIDTH* 0.5f) {
                ballNextPosition.y = this->visibleSize.height - this->puck->radius();
                ballVector.y *= -0.8f;
            }
        }
        //ball and bottom of the court
        if (ballNextPosition.y < this->puck->radius() ) {
            if (this->puck->getPosition().x < this->visibleSize.width* 0.5f - GOAL_WIDTH* 0.5f ||
                this->puck->getPosition().x > this->visibleSize.width* 0.5f + GOAL_WIDTH* 0.5f) {
                ballNextPosition.y = this->puck->radius();
                ballVector.y *= -0.8f;
            }
        }
    }
    
    //finally, after all checks, update ball's vector and next position
    this->puck->setVector(ballVector);
    this->puck->setNextPosition(ballNextPosition);
    
    
    //check for goals!
    if (ballNextPosition.y  < this->puck->radius() * 2) {
        playerScore(2);

    }
    if (ballNextPosition.y > this->visibleSize.height + this->puck->radius() * 2) {
        playerScore(1);
    }
    
    //move pieces to next position
    for (auto& player : this->players) {
        player->setPosition(player->getNextPosition());
    }
    this->puck->setPosition(this->puck->getNextPosition());
}

void HelloWorld::playerScore(int player) {
    this->puck->setVector(Vec2(0,0));
    if (player == 1) {
        this->player1Score++;
        player1ScoreLabel->setString(to_string(this->player1Score));
        this->puck->setNextPosition(Vec2(this->visibleSize.width * 0.5, this->visibleSize.height * 0.5 + 2 * this->puck->radius()));
    } else {
        this->player2Score++;
        this->player2ScoreLabel->setString(to_string(this->player2Score));
        this->puck->setNextPosition(Vec2(this->visibleSize.width * 0.5, this->visibleSize.height * 0.5 - 2 * this->puck->radius()));
    }
    
    for (auto& player : this->players) {
        player->setPosition(player->getNextPosition());
        player->setTouch(nullptr);
    }
}
