
#include "Player.h";
using namespace cocos2d;

Player::Player()
{
	this->setAnchorPoint(ccp(0.5f, 0.5f));
	// Set the player active
	_isActive = true;
	_life = 3;
	_hasPowerup = false;
	_powerupLevel = 1;
	_hasShield = false;
	// Get screen width and height for player condition
	_screenSize = CCDirector::sharedDirector() -> getWinSize();
	// Set player position
	this->setPosition( ccp(_screenSize.width / 2, 100) );
	CCLOG("Player: Player construct!");
}

Player::~Player(){


}

Player* Player::create()
{
	Player* playerObj = new Player();
	if ( playerObj ) {
		playerObj -> autorelease();
		playerObj -> initWithFile("playerShip.png");
		return playerObj;
	} else {
		delete playerObj;
		playerObj = NULL;
		return NULL;
	}
}

int Player::getLife()
{
	return _life;
}
int Player::getPowerupLevel()
{
	return _powerupLevel;
}
bool Player::getPowerup()
{
	return _hasPowerup;
}
bool Player::getShield()
{
	return _hasShield;
}


void Player::setLife(int value)
{
	_life = value;
}

void Player::setPowerup(bool value)
{
	_hasPowerup = value;
}

void Player::setPowerupLevel(int value)
{
	_powerupLevel = value;
}
void Player::setShield(bool value)
{
	_hasShield = value;
}




void Player::playerUpdate(int dt)
{
	// Condition check if active
	if(!_isActive) {
		return;
	}

	// Check the clamping of player sprite
	CCPoint currentPos = this->getPosition();
	_spriteWidth = this->getContentSize().width;
	_spriteHeight = this->getContentSize().height;

	if((currentPos.x - _spriteWidth / 2) < 0)
	{ 
		this->setPositionX( _spriteWidth / 2);
	} 
	if((currentPos.x + _spriteWidth / 2) > _screenSize.width)
	{
		this->setPositionX(_screenSize.width - _spriteWidth / 2);
	}
	if((currentPos.y + _spriteHeight / 2) > _screenSize.height)
	{
		this->setPositionY(_screenSize.height- _spriteHeight / 2);
	}
	if((currentPos.y - _spriteHeight / 2) < 0)
	{
		this->setPositionY(_spriteHeight / 2);
	}
}

void Player::updatePosition(CCPoint presentLocation)
{
	float deltaDistX = presentLocation.x - _prevTouchInput.x;
	float deltaDistY = presentLocation.y - _prevTouchInput.y;
	this->setPositionX(this->getPositionX() + deltaDistX);
	this->setPositionY(this->getPositionY() + deltaDistY);
	_prevTouchInput = presentLocation;
}

bool Player::beganOnTouch(CCPoint touchLocation)
{
	_prevTouchInput = touchLocation;
	return true;
}

CCPoint Player::getPlayerLocation()
{
	return this->getPosition();
}

