#include "GameScene.h"

USING_NS_CC;

CCScene* GameScene::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    GameScene *layer = GameScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}
// on "init" you need to initialize your instance
bool GameScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

		this-> loadContent();


		// Initialize time span of projectile
		_timeSpan = 15;
		_timeCount = 0;
		_powerupTimeSpan = 100;
		_powerupCount = 0;
    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    //CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
     //                                   "CloseNormal.png",
    //                                    "CloseSelected.png",
    //                                    this,
     //                                   menu_selector(GameScene::menuCloseCallback));
    
	//pCloseItem->setPosition(ccp(origin.x + visibleSize.width - pCloseItem->getContentSize().width/2 ,
                               // origin.y + pCloseItem->getContentSize().height/2));

    // create menu, it's an autorelease object
   // CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
   // pMenu->setPosition(CCPointZero);
   // this->addChild(pMenu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
   // CCLabelTTF* pLabel = CCLabelTTF::create("Hello World", "Arial", 24);
    
    // position the label on the center of the screen
   // pLabel->setPosition(ccp(origin.x + visibleSize.width/2,
                           // origin.y + visibleSize.height - pLabel->getContentSize().height));

    // add the label as a child to this layer
    //this->addChild(pLabel, 1);

    // add "GameScene" splash screen"
   // CCSprite* pSprite = CCSprite::create("GameScene.png");

    // position the sprite on the center of the screen
   // pSprite->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
//
    // add the sprite as a child to this layer
    //this->addChild(pSprite, 0);
    
    return true;
}

void GameScene::loadContent(){

		_backGround =  Background::create();
		this->addChild(_backGround, -1);
		_player = Player::create();
		this->addChild(_player, 0);

		CCSprite* life;
		for (int i = 0; i < 3; i++)
		{
			life = CCSprite::create();
			life->setPosition(ccp(50*(i+1),1240));
			life->initWithFile("life.png");
			this->addChild(life,0);
			_lives.push_back(life);
		}

		this->schedule(schedule_selector(GameScene::update), 0);
		this->schedule(schedule_selector(GameScene::changeEnemyMovement),0.5);

		CCDirector::sharedDirector() -> getTouchDispatcher() -> addTargetedDelegate( this, 0, true );
}

void GameScene::update(float dt)
{
	_player->playerUpdate(dt);

	if ( _timeCount > _timeSpan )
	{
		// Release projectile
		if(_player->getPowerup() == true)
		{
			for (int i = 1; i < 3; i++)
			{
				Projectile* projectile = Projectile::create();		
				projectile->setDirection(i);
				projectile->shootProjectile(_player->getPowerupLevel(), _player->getPosition());
				this->addChild(projectile, -1);
				// Push to vector obj
				_projectiles.push_back(projectile);
			}
		}
		else
		{
				Projectile* projectile = Projectile::create();
				projectile->setDirection(0);
				projectile->shootProjectile(_player->getPowerupLevel(), _player->getPosition());
				this->addChild(projectile, -1);
				// Push to vector obj
				_projectiles.push_back(projectile);
		}
		_timeCount = 0;

	}

	int random = rand() % 500;
	if ( random / 10  <= 1 )
	{
		int enemyType =  rand() % 2;
		Enemy* enemy = Enemy::create();
		enemy->performCharge(_player->getPosition());
		this->addChild(enemy, 0);
		_enemies.push_back(enemy);
	}

	if(_powerupCount > _powerupTimeSpan)
	{
		Powerup* powerup = Powerup::create();
		int randPositionX = rand() % (int)(720) + 100;
		powerup->setPosition(ccp(randPositionX,1180));
		powerup->performMove();
		this->addChild(powerup,0);
		_powerups.push_back(powerup);

		_powerupTimeSpan =  rand() % 400 + 200;
		_powerupCount = 0;
	}


		_powerupCount++;
		_timeCount++;
		updateProjectiles(dt);
		updateEnemies(dt);
		updateCollision(dt);
}

void GameScene::changeEnemyMovement(float dt)
{
	for (int i = 0; i < _enemies.size(); i++)
	{
		 if(_enemies[i]->getEnemyType() == 2)
		 {
			 _enemies[i]->stopAllActions();
			 _enemies[i]->setEnemyTravelTime(_enemies[i]->getEnemyTravelTime() - 0.5);
			 _enemies[i]->runAction(CCMoveTo::create(_enemies[i]->getEnemyTravelTime(), ccp(_player->getPositionX(), -200)));
		 }

	}
}

void GameScene::updateProjectiles(float dt)
{
	for (int i = 0; i < _projectiles.size(); i++)
	{
		_projectiles[i]->projectileUpdate(dt);
		//Check it obj is not active
		if(_projectiles[i]->getActiveResult() != true)
		{
			_projectiles[i]->destroy();
			_projectiles.erase(_projectiles.begin()+ i);
		}
	}
}

void GameScene::updateEnemies(float dt)
{
	for(int i = 0; i < _enemies.size(); i++)
	{
		_enemies[i]->enemyUpdate(dt);
		// Check obj is not active
		if(_enemies[i]->getActiveResult() != true)
		{
			_enemies[i]->destroy();
			_enemies.erase(_enemies.begin()+i);
		}
	}
}

void GameScene::updateCollision(float dt)
{
	// Check player and enemy collision
	for(int i = 0; i < _enemies.size(); i++)
	{
		if(_player->boundingBox().intersectsRect(_enemies[i]->boundingBox()))
		{
			CCArray* actionSequence = CCArray::create();
			actionSequence->addObject(CCScaleTo::create(0.5,2));
			actionSequence->addObject(CCScaleTo::create(0.5,1));
			_player->runAction(CCSequence::create(actionSequence));
			actionSequence->removeAllObjects();
			actionSequence = NULL;
			_enemies[i]->setIsActive(false);

			// check if player has shield
			if(_player->getShield() == true)
			{
				//destroy shield
				 _player->setShield(false);
				 _player->removeAllChildrenWithCleanup(true);
			}
			else //player has no shield
				{
				_player->setPowerupLevel(1);
				_player->setPowerup(false);
				if(_player->getLife() == 1)
					 CCDirector::sharedDirector()->end();
				else
				{
					_player->setLife(_player->getLife()-1);
					_lives[_player->getLife()]->removeFromParentAndCleanup(true);
					_lives.erase(_lives.begin()+(_player->getLife()));
				}	
			}
				
		}
	}
	// check for character and powerup collision
	for(int i = 0; i < _powerups.size(); i++)
	{
		if(_player->boundingBox().intersectsRect(_powerups[i]->boundingBox()))
		{
			CCArray* actionSequence = CCArray::create();
			actionSequence->addObject(CCScaleTo::create(0.5,2));
			actionSequence->addObject(CCScaleTo::create(0.5,1));
			_player->runAction(CCSequence::create(actionSequence));
			actionSequence->removeAllObjects();
			actionSequence = NULL;
			_powerups[i]->setIsActive(false);
			if(_powerups[i]->getPowerupType() == 1)
			{
				if(_player->getPowerupLevel() != 3)
				{
					_player->setPowerupLevel(_player->getPowerupLevel() + 1);
				}
				_player->setPowerup(true);
			}
			else 
			{
				if(_player->getShield() == false)
				{
					Shield* shield = Shield::create();
					_player->addChild(shield,-1);
					_player->setShield(true);
				}
			}
			_powerups[i]->destroy();
			_powerups.erase(_powerups.begin()+i);
		}
	}

	//Check enemy and projectile collision
	for (int i = 0; i < (unsigned int)_projectiles.size(); i++)
	{
		for (int j = 0; j < (unsigned int)_enemies.size(); j++)
		{
			if(_projectiles[i]->boundingBox().intersectsRect(_enemies[j]->boundingBox()))
			{
				// Destroy the both of them
				_projectiles[i]->setIsActive(false);
				if(_enemies[j]->getShield() == 1)
					_enemies[j]->setIsActive(false);
				else
				{
					_enemies[j]->enemyDamage();
					_enemies[j]->setShield(_enemies[j]->getShield() - 1);
				}
			}
		}
	}
}

bool GameScene::ccTouchBegan(CCTouch* touch, CCEvent* event)
{
	// Debug tool
	CCLOG("GameSceneScene: Touch Began");
	// Get location x and y
	CCPoint touchLocation = touch -> getLocation();
    CCLOG("touch loc %f %f", touchLocation.x, touchLocation.y);
	// player is not available, skip process
	if ( _player != NULL )
	{
		// Return true to swallow touch
		return _player->beganOnTouch(touchLocation);
	}
	return false;
}

void GameScene::ccTouchMoved( cocos2d::CCTouch* touch, cocos2d::CCEvent* event )
{
	CCPoint touchLoc = convertTouchToNodeSpace( touch );
	// Track the touch’s position when dragged.
	// CCLOG( "Touch: %f, %f", touchLoc.x, touchLoc.y );
	if ( _player != NULL ) _player->updatePosition(touchLoc);
}




void GameScene::menuCloseCallback(CCObject* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
    CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
#endif
}
