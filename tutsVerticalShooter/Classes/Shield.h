#ifndef _VERTICAL_SHOOTER_SHIELD_H_
#define _VERTICAL_SHOOTER_SHIELD_H_

#include "cocos2d.h"

class Shield : public cocos2d::CCSprite
{
public:
	Shield();
	~Shield();

	static Shield* create();

private:
	cocos2d::CCSize _screenSize;
	bool _isActive;
};
#endif // _VERTICAL_SHOOTER_SHIELD_H_