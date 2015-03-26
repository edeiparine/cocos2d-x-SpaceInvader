#ifndef _VERTICAL_SHOOTER_ENEMY_H_
#define _VERTICAL_SHOOTER_ENEMY_H_

#include "cocos2d.h"

class Enemy : public cocos2d::CCSprite
{
public:
	Enemy();
	~Enemy();
	static Enemy* create();
	// Get _isActive value
	bool getActiveResult();
	// Set _isActive value

	void performCharge(cocos2d::CCPoint);
	void enemyUpdate(float);
	void destroy();
	void enemyDamage();

	int getShield();
	int getEnemyType();
	float getEnemyTravelTime();

	void setIsActive(bool);
	void setShield(int);
	void setEnemyTravelTime(float);

private:
	cocos2d::CCSize _screenSize;
	bool _isActive;
	int _shield;
	int _enemyType;
	float _enemyTravelTime;
};

#endif //_VERTICAL_SHOOTER_ENEMY_H_