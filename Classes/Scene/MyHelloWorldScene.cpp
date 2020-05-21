#include "MyHelloWorldScene.h"

Scene* myScene::createScene() { 
	auto scene = Scene::create(); 

	auto layer = myScene::create();

	scene->addChild(layer);

	return scene;
}

bool myScene::init() { 
	auto sprite = Sprite::create("HelloWorld.png");
	
	sprite->setPosition(ccp(300, 300));

	this->addChild(sprite);
        
	return true;
}