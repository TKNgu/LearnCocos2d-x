//
//  GameSprite.hpp
//  AirHockey
//
//  Created by TK Ngu on 05/09/2021.
//

#ifndef GameSprite_hpp
#define GameSprite_hpp

#include <stdio.h>
#include <string>
#include "cocos2d.h"

class GameSprite: public cocos2d::Sprite {
public:
    GameSprite();
    ~GameSprite();
    CC_SYNTHESIZE(cocos2d::Vec2, _nextPosition, NextPosition);
    CC_SYNTHESIZE(cocos2d::Vec2, _vector, Vector);
    CC_SYNTHESIZE(cocos2d::Touch*, _touch, Touch);
    static GameSprite* gameSpriteWithFile(std::string);
    void setPosition(const cocos2d::Vec2 &) override;
    float radius();
};

#endif /* GameSprite_hpp */
