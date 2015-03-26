#include "Enemy.h";
using namespace cocos2d;

Enemy::Enemy()
{
	this->setAnchorPoint(ccp(0.5f, 0.5f));
	_screenSize = CCDirector::sharedDirector() -> getWinSize();
	_isActive = true;
	_shield = 3;
	_enemyType = 1;
	_enemyTravelTime = rand() % 3 + 2;
	int randPositionX = rand() % (int)(_screenSize.width - 200) + 100;
	this->setPosition(CCPoint(randPositionX, _screenSize.height - 100));
}


Enemy::~Enemy()
{
}

Enemy* Enemy::create()
{
	Enemy* enemyObj = new Enemy();
	if (enemyObj){
		enemyObj -> autorelease();
		// String changes accrd to i
		std::string colorPath;
		int i = rand() % 7;
		// Switch for each random value -- DRY conflict
		switch (i)
		{
		case 1 :
			enemyObj -> initWithFile("meteor1.png");
			break;
		case 2:
			enemyObj -> initWithFile("meteor2.png");
			break;
		case 3:
			enemyObj -> initWithFile("meteor3.png");
			break;
		case 4:
			enemyObj -> initWithFile("meteor4.png");
			break;
		case 5:
			enemyObj -> initWithFile("meteor5.png");
			enemyObj->setShield(2);
			break;
		case 6:
			enemyObj -> initWithFile("enemyShip.png");
			enemyObj ->setShield(4);
			enemyObj->_enemyType = 2;
			break;
		default:
			enemyObj -> initWithFile("meteor6.png");
			enemyObj->setShield(2);
			break;
		}
		return enemyObj;
	} else {
		delete enemyObj;
		enemyObj = NULL;
		return NULL;
	}
}

bool Enemy::getActiveResult()
{
	return _isActive;
}

void Enemy::setIsActive(bool value)
{
	_isActive = value;
}

int Enemy::getShield()
{
	return _shield;
}

void Enemy::setShield(int value)
{
	_shield = value;
}

int Enemy::getEnemyType()
{
	return _enemyType;
}

float Enemy::getEnemyTravelTime()
{
	return _enemyTravelTime;
}

void Enemy::setEnemyTravelTime(float value)
{
	_enemyTravelTime = value;
}

void Enemy::enemyDamage()
{
	CCTintTo* tintTo = CCTintTo::create(0.1,255,0,50);
	CCTintTo* tintBack = CCTintTo::create(0.1,255,255,255);
	CCSequence* sequence = CCSequence::create(tintTo,tintBack,NULL);
	this->runAction(sequence);
}

void Enemy::performCharge(CCPoint pLocation)
{
	if(_enemyType == 1)
		this->runAction(CCRepeatForever::create(CCRotateBy::create(4,360)));
	this->runAction(CCMoveTo::create(_enemyTravelTime, ccp(pLocation.x, -200)));
}

void Enemy::enemyUpdate(float dt)
{
	if(!_isActive)
	{ return; }

	if(this->getPositionY() < -100)
	{
		_isActive = false;
	}
}

void Enemy::destroy()
{
	this->stopAllActions();
	this->removeFromParentAndCleanup(true);
}
