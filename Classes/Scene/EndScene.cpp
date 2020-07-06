#include "EndScene.h"
#include "StartScene.h"
#include "Player/Player.h"
#include "Scene/Maze.h"
Scene* EndScene::createScene() { return EndScene::create(); }

bool EndScene::init() {
	//����ͼ
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//���ذ�ť
	auto startImg = Sprite::create("end.png");
	
	startImg->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(startImg, 0);

	//������
	auto portalImg = Sprite::create("Map//portal3.png");
	portalImg->setScale(3);
	portalImg->setPosition(Point(750, 130));
	this->addChild(portalImg);

	//����
	this->player = Player::create();
	this->player->endScene = this;
	this->addChild(this->player);
	this->player->setPosition(Point(750,130));

	//��ӻص�
	auto exitImg = MenuItemImage::create (
		"exit.png",
		"exit.png",
		CC_CALLBACK_1(EndScene::menuCloseCallbackStart, this));

	auto Menu = Menu::create(exitImg, NULL);
	Menu->setPosition(1300, 700);
	this->addChild(Menu, 1);
	return true;
}

//�ص��������������˵�
void EndScene::menuCloseCallbackStart(Ref* pSender)	{
	Director::getInstance()->replaceScene(TransitionCrossFade::create(2.0f, StartScene::createScene()));
}

