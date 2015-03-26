#include "Projectile.h"

using namespace cocos2d;

Projectile::Projectile()
{
	// Make it active object
	_isActive = true;
	_damage = 1;
	// Get screen width and height for player condition
	_screenSize = CCDirector::sharedDirector() -> getWinSize();
}

Projectile::~Projectile()
{

}

Projectile* Projectile::create()
{
	Projectile* projObj = new Projectile();
	if(projObj){
		projObj->autorelease();
		projObj->initWithFile("projectile.png");
		return projObj;
	} else {
		delete projObj;
		projObj = NULL;
		return NULL;
	}
}

bool Projectile::getActiveResult()
{
	return _isActive;
}

void Projectile::setIsActive(bool value)
{
	_isActive = value;
}

void Projectile::setDirection(int value)
{
	_direction = value;
}

void Projectile::shootProjectile(int powerupLevel, CCPoint pLocation)
{
	_projectileY = this->getPositionY();

	if(_projectileY < 420)
		_projectileSpeed = 1;
	else if(_projectileY >= 420 && _projectileY < 840)
		_projectileSpeed = 0.7;
	else
		_projectileSpeed = 0.3;

	if(_direction == 0){
		this->runAction(CCMoveTo::create(_projectileSpeed, CCPoint(this->getPositionX()-25, _screenSize.height + 100)));
		this->setPositionX(pLocation.x);
	}
	else if(_direction == 1){
		this->runAction(CCMoveTo::create(_projectileSpeed, CCPoint(this->getPositionX(), _screenSize.height + 100)));
		this->setPositionX(pLocation.x - 25);
	}
	else{
		this->runAction(CCMoveTo::create(_projectileSpeed, CCPoint(this->getPositionX()+25, _screenSize.height + 100)));
		this->setPositionX(pLocation.x + 25);
	}
	//this->runAction(CCMoveTo::create(_projectileSpeed, CCPoint(this->getPositionX()+300, _screenSize.height + 100)));

	this->setPositionY(pLocation.y);

	if(powerupLevel == 1)
	{
		_damage = 1;
		this->runAction(CCScaleTo::create(0,1));
	}
  if(powerupLevel == 2)
	{
		_damage = 2;
		this->runAction(CCScaleTo::create(0,2));
	}
	else if(powerupLevel == 3) 
	{
		_damage = 3;
		this->runAction(CCScaleTo::create(0,2.5));
	}
}

void Projectile::setInitialPosition(float pLocationX, float pLocationY)
{
	this->setPositionX(pLocationX);
	this->setPositionY(pLocationY);
}

void Projectile::projectileUpdate(int dt)
{
	if (!_isActive){
		return;
	}

	int y = this->getPositionY();
	if(y + this->getContentSize().height / 2 > _screenSize.height)
	{
		// TODO: Clean projectile and remove visibility from screen
		_isActive = false;
	}
}

void Projectile::destroy()
{
	this->stopAllActions();
	this->removeFromParentAndCleanup(true);
}