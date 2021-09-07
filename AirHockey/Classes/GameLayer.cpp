//
//  GameLayer.cpp
//  AirHockey
//
//  Created by TK Ngu on 05/09/2021.
//

#include "GameLayer.hpp"
#include <string>

GameLayer::GameLayer() {
    //TODO
}

GameLayer::~GameLayer() {
    //TODO
}

bool GameLayer::init() {
    this->_screenSize = Director::getInstance()->getWinSize();
    
    auto court = Sprite::create("court.png");
    court->setPosition(Vec2(this->_screenSize.width * 0.5f, this->_screenSize.height * 0.5f));
    auto scaleWidth = this->_screenSize.width / court->getTextureRect().size.width;
    auto scaleHeight = this->_screenSize.height / court->getTextureRect().size.height;
    auto scale = std::min(scaleWidth, scaleHeight);
    court->setScale(scale, scale);
    this->addChild(court);
    return true;
}
