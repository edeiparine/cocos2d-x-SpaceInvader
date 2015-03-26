#include "Powerup.h"

using namespace cocos2d;

Powerup::Powerup()
{
	// Make it active object
	_isActive = true;
	// Get screen width and height for player condition
	_screenSize = CCDirector::sharedDirector() -> getWinSize();
	_powerupType = 1;
	//int randPositionX = rand() % (int)(_screenSize.width - 100) + 100;
	//this->setPosition(ccp(randPositionX, _screenSize.height - 100));
}

Powerup::~Powerup()
{

}

Powerup* Powerup::create()
{
	Powerup* projObj = new Powerup();
	if(projObj){
		projObj->autorelease();
		int i = rand() % 2;
		switch(i)
		{
			case 1:
				projObj->initWithFile("powerupLaser.png");
				break;
			default:
				projObj -> initWithFile("powerupShield.png");
				projObj ->setPowerupType(2);
				break;
		}
		return projObj;
	} else {
		delete projObj;
		projObj = NULL;
		return NULL;
	}
}

void Powerup::setIsActive(bool value)
{
	_isActive = value;
}

void Powerup::setPowerupType(int value)
{
	_powerupType = value;
}

int Powerup::getPowerupType()
{
	return _powerupType;
}


void Powerup::performMove()
{
	this->runAction(CCMoveTo::create(3, ccp(this->getPositionX(), -200)));
}

void Powerup::powerupUpdate(float dt)
{
	if(!_isActive)
	{ return; }

	if(this->getPositionY() < -100)
	{
		_isActive = false;
	}
}

void Powerup::destroy()
{
	this->stopAllActions();
	this->removeFromParentAndCleanup(true);
}