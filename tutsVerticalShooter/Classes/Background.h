#ifndef VERTICAL_SHOOTER_MAIN_BACKGROUND_H_
#define VERTICAL_SHOOTER_MAIN_BACKGROUND_H_

#include "cocos2d.h"

class Background : public cocos2d::CCLayer
{
public:
	Background();
	~Background();
	static Background* create();
private:
	cocos2d::CCSprite* _mainBgImage;
	cocos2d::CCLayerColor* _bgColor;
};

#endif // VERTICAL_SHOOTER_MAIN_BACKGROUND_H_