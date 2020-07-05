#ifndef _PLAYER_H_
#define _PLAYER_H_
#include "cocos2d.h"
#include "Scene/Maze.h"
#include "Scene/EndScene.h"
USING_NS_CC;

class Player: public Node {

public:
	float speedX, speedY;
	Sprite* sprite;
	Maze* maze = nullptr;
	EndScene* endScene = nullptr;
	
	void bindSprite(Sprite*);
	void registerKeyBoardEvent();
	void checkCollision();
	void checkEnd();
	void checkBorder();

	virtual void update(float);
	virtual bool init();
	
	CREATE_FUNC(Player);
};
#endif
