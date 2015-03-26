#include "Shield.h";

using namespace cocos2d;

Shield::Shield()
{
	_isActive = true;
}

Shield::~Shield()
{
}

Shield* Shield::create()
{
	Shield* shieldObj = new Shield();
	if(shieldObj)
	{
		shieldObj->autorelease();
		shieldObj->initWithFile("shield.png");
		return shieldObj;
	} else {
		delete shieldObj;
		shieldObj = NULL;
		return NULL;
	}
}