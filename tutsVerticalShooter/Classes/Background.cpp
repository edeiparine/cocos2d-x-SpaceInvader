#include "Background.h";

using namespace cocos2d;

Background::Background()
{
	_bgColor = CCLayerColor::create(ccc4(29,29,29,255));
	this->addChild(_bgColor, 0);
}

Background::~Background()
{
}

Background* Background::create()
{
	Background* bgObj = new Background();
	if( bgObj ) {
		bgObj -> autorelease();
		return bgObj;
	} else {
		delete bgObj;
		bgObj = NULL;
		return NULL;
	}
}