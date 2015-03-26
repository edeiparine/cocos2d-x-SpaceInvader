#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "Player.h"
#include "Background.h"
#include "Projectile.h"
#include "Enemy.h"
#include "Powerup.h"
#include "Shield.h"

class GameScene : public cocos2d::CCLayer
{
private:
	Player* _player;
	Background* _backGround;
	std::vector< Projectile* > _projectiles;
	std::vector< Enemy* > _enemies;
	std::vector< cocos2d::CCSprite* > _lives;
	std::vector< Powerup* > _powerups;
	int _timeSpan;
	int _timeCount;
	int _powerupTimeSpan;
	int _powerupCount;

public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
		void loadContent();

		void changeEnemyMovement(float);
		void update(float);
		void updateProjectiles(float);
		void updateEnemies(float);
		void updateCollision(float);
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);
		bool ccTouchBegan(cocos2d::CCTouch* touch, cocos2d::CCEvent* event);
		void ccTouchMoved(cocos2d::CCTouch* touch, cocos2d::CCEvent* event);
    // implement the "static node()" method manually
    CREATE_FUNC(GameScene);
};

#endif // __GAME_SCENE_H__
