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

USING_NS_CC;

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

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // 2. Add background
    auto court = Sprite::create("court.png");
    if (court ==  nullptr) {
        problemLoading("court.png");
    } else {
        court->setPosition(Vec2(visibleSize.width * 0.5, visibleSize.height * 0.5));
        this->addChild(court, 0);
    }
    
    // 3. Add user
    auto player1 = GameSprite::gameSpriteWithFile("mallet.png");
    if (player1 == nullptr) {
        problemLoading("mallet.png");
    } else {
        player1->setPosition(Vec2(visibleSize.width * 0.5, player1->radius() * 2));
        this->addChild(player1);
    }
    
    auto player2 = GameSprite::gameSpriteWithFile("mallet.png");
    if (player2 == nullptr) {
        problemLoading("mallet.png");
    } else {
        player2->setPosition(Vec2(visibleSize.width * 0.5, visibleSize.height - player2->radius() * 2));
        this->addChild(player2);
    }
    
    // 4. Add score
    this->player1ScoreLabel = Label::createWithTTF("0", "fonts/Arial.ttf", 60);
    if (this->player1ScoreLabel == nullptr) {
        problemLoading("fonts/Arial.ttf");
    } else {
        this->player1ScoreLabel->setPosition(Vec2(visibleSize.width - 60, visibleSize.height * 0.5 - 80));
        this->addChild(this->player1ScoreLabel);
    }
    
    this->player2ScoreLabel = Label::createWithTTF("0", "fonts/Arial.ttf", 60);
    if (this->player2ScoreLabel == nullptr) {
        problemLoading("fonts/Arial.ttf");
    } else {
        this->player2ScoreLabel->setPosition(Vec2(visibleSize.width - 60, visibleSize.height * 0.5 + 80));
        this->addChild(this->player2ScoreLabel);
    }

    // 5. Controller
//    auto listener = EventListenerTouchAllAtOnce::create();
//    CC_CALLBACK_2(HelloWorld::onTouchesBegan, this);
    
    auto listener1 = EventListenerTouchOneByOne::create();

    // trigger when you push down
    listener1->onTouchBegan = [&](Touch* touch, Event* event){
        player2ScoreLabel->setString("Touch");
        return true; // if you are consuming it
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, this);
    this->unscheduleUpdate();
    
    this->player1ScoreLabel->setString("Init");
    
    return true;
}

void HelloWorld::onTouchesBegan(const vector<Touch*> &touches, Event* event) {
    this->player2ScoreLabel->setString("Touch");
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}
