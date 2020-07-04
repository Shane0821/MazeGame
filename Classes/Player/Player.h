#ifndef _PLAYER_H_
#define _PLAYER_H_
#include "cocos2d.h"
#include "Scene/Maze.h"

USING_NS_CC;

class Player: public Node {

public:
	float speedX, speedY;
	Sprite* sprite;
	
	void bindSprite(Sprite*);
	void registerKeyBoardEvent();
	void checkCollision();
	virtual void update(float);
	virtual bool init();
	
	CREATE_FUNC(Player);
};
#endif
