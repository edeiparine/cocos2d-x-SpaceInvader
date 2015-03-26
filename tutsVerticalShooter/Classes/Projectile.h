#ifndef _VERTICAL_SHOOTER_PROJECTILE_H_
#define _VERTICAL_SHOOTER_PROJECTILE_H_

#include "cocos2d.h"

class Projectile : public cocos2d::CCSprite
{
public:
	Projectile();
	~Projectile();

	static Projectile* create();
	void projectileUpdate(int dt);
	bool getActiveResult();
	void setIsActive(bool);
	void shootProjectile(int, cocos2d::CCPoint);
	void setInitialPosition(float,float);
	void setDirection(int);
	void destroy();

private:
	bool _isActive;
	float _projectileSpeed;
	float _projectileX;
	float _projectileY;
	int _direction;
	int _damage;

	cocos2d::CCSize _screenSize;
};
#endif //_VERTICAL_SHOOTER_PROJECTILE_H_