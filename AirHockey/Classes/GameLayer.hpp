//
//  GameLayer.hpp
//  AirHockey
//
//  Created by TK Ngu on 05/09/2021.
//

#ifndef GameLayer_hpp
#define GameLayer_hpp

#include <stdio.h>
#include "cocos2d.h"

using namespace cocos2d;

class GameLayer: public Layer {
public:
    GameLayer();
    virtual ~GameLayer();
    virtual bool init();
    CREATE_FUNC(GameLayer);
private:
    Size _screenSize;
};

#endif /* GameLayer_hpp */
