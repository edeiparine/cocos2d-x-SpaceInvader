#ifndef _VERTICAL_SHOOTER_PLAYER_H_
#define _VERTICAL_SHOOTER_PLAYER_H_

#include "cocos2d.h"

class Player : public cocos2d::CCSprite{

public:
	Player();
	~Player();

	static Player* create();
	void playerUpdate(int);
	void updatePosition(cocos2d::CCPoint);
	bool beganOnTouch(cocos2d::CCPoint);
	int getLife();
	bool getPowerup();
	int getPowerupLevel();
	bool getShield();

	void setLife(int);
	void setPowerup(bool);
	void setPowerupLevel(int);
	void setShield(bool);

	cocos2d::CCPoint getPlayerLocation();

private:
	int _powerupLevel;
	bool _isActive;
	bool _hasPowerup;
	float _spriteWidth;
	float _spriteHeight;
	cocos2d::CCSize _screenSize;
	cocos2d::CCPoint _prevTouchInput;
	int _life;
	bool _hasShield;

};

#endif // _VERTICAL_SHOOTER_PLAYER_H_