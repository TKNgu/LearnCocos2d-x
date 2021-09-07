//
//  GameSprite.cpp
//  AirHockey
//
//  Created by TK Ngu on 05/09/2021.
//

#include "GameSprite.hpp"

GameSprite::GameSprite():
_vector(0, 0) {
    //TODO
}

GameSprite::~GameSprite() {
    //TODO
}

GameSprite* GameSprite::gameSpriteWithFile(std::string fileName) {
    auto sprite = new GameSprite();
    if (sprite && sprite->initWithFile(fileName)) {
        sprite->autorelease();
        return sprite;
    }
    CC_SAFE_FREE(sprite);
    return nullptr;
}

void GameSprite::setPosition(const cocos2d::Vec2 &pos) {
    Sprite::setPosition(pos);
    if (!this->_nextPosition.equals(pos)) {
        this->_nextPosition = pos;
    }
}

float GameSprite::radius() {
    return getTexture()->getContentSize().width * 0.5f;
}
