#include "secondScene.h"

Scene* secondScene::createScene() { 
  auto scene = Scene::create();

  auto layer = secondScene::create();

  scene->addChild(layer);

  return scene;
}

void secondScene::popScene(Ref* pSender) {
  Director::getInstance()->popScene();
}

bool secondScene::init() { 
  Label* lable = Label::create("Hi, are you mutou?", "Arial", 40);

  lable->setPosition((ccp(200, 200)));

  this->addChild(lable);

  /*Ìí¼Ó°´Å¥*/
  MenuItemImage* pCloseItem = MenuItemImage::create(
      "CloseNormal.png", 
      "CloseSelected.png", 
      this,
      menu_selector(secondScene::popScene));
  pCloseItem->setPosition(ccp(Director::getInstance()->getWinSize().width - 20, 20));

  Menu* pMenu = Menu::create(pCloseItem, NULL);
  pMenu->setPosition(Vec2::ZERO);
  this->addChild(pMenu, 1);

  return true;
}