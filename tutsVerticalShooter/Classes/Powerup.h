#ifndef _VERTICAL_SHOOTER_POWERUP_H_
#define _VERTICAL_SHOOTER_POWERUP_H_

#include "cocos2d.h"

class Powerup : public cocos2d::CCSprite
{

public:
	Powerup();
	~Powerup();

	static Powerup* create();

	void setIsActive(bool);
	void performMove();
	void powerupUpdate(float);
	void destroy();
	int getPowerupType();
	void setPowerupType(int);


private:
	cocos2d::CCSize _screenSize;
	bool _isActive;
	int _powerupType;

};


#endif //_VERTICAL_SHOOTER_POWERUP_H_