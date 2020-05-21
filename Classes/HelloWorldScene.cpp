/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "cocos-ext.h"
#include "../proj.win32/secondScene.h"

USING_NS_CC;
USING_NS_CC_EXT;

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //代码清单 3-14
  if ( !Scene::init() ) {
      return false;
  }

#ifndef Test_Scale9
  Scale9Sprite* wizard = Scale9Sprite::create("wizard.png");

  if (wizard == nullptr) {
    log("no such image");
    return true;
  }

  wizard->setContentSize(Size(50, 75));

  wizard->setPosition(Point(200, 200));

  this->addChild(wizard);
#endif

#ifdef Test_map
  Map<int, Label*> MapLabel;

  for (int i = 1; i <= 100; i++) {
    std::string name = "ShaunNo." + Value(i).asString();

    Label* lab = Label::create(name.c_str(), "Arial", 30);

    MapLabel.insert(i, lab);
  }

  Label* lab = MapLabel.at(1);

  lab->setPosition(Point(200, 400));

  this->addChild(lab);
#endif

#ifdef Test_vector
  Label* label1 = Label::create("Shaun", "Arial", 30);
  label1->setPosition(Point(250, 500));

  Label* label2 = Label::create("Shane", "Arial", 30);
  label2->setPosition(Point(250, 200));

  Vector<Label*> vec;

  vec.pushBack(label1), vec.pushBack(label2);

  for (auto lab : vec) {
    this->addChild(lab);
  }
#endif

#ifdef Test3_19
  auto valStr = Value("Shaun is");
  auto valInt = Value(0);
  log("%s %d", valStr.asString().c_str(), valInt.asInt());
#endif

#ifdef Test_3_14
  //获取屏幕大小
  Size visibleSize = Director::getInstance()->getVisibleSize();

  //创建菜单项
  MenuItemImage* pCloseItem =
      MenuItemImage::create("CloseNormal.png", "CloseSelected.png", this,
                            menu_selector(HelloWorld::menuCloseCallback)
  );

  //创建一个标签
  Label* label = Label::create("I am Label item.", "Arial", 30);
  
  //用标签对象创建一个标签菜单项 created with label
  MenuItemLabel* pLabelItem = MenuItemLabel::create(label);
   
  //创建菜单
  Menu* pMenu = Menu::create(pCloseItem, pLabelItem, NULL);

  //所有菜单项在垂直方向上自动排列
  pMenu->alignItemsVertically();

  //设置菜单坐标
  pMenu->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));

  //添加到菜单层里
  this->addChild(pMenu, 1);
#endif

#ifdef origin
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));

    if (closeItem == nullptr ||
        closeItem->getContentSize().width <= 0 ||
        closeItem->getContentSize().height <= 0)
    {
        problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
    }
    else
    {
        float x = origin.x + visibleSize.width - closeItem->getContentSize().width/2;
        float y = origin.y + closeItem->getContentSize().height/2;
        closeItem->setPosition(Vec2(x,y));
    }

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label

    auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
    if (label == nullptr)
    {
        problemLoading("'fonts/Marker Felt.ttf'");
    }
    else
    {
        // position the label on the center of the screen
        label->setPosition(Vec2(origin.x + visibleSize.width/2,
                                origin.y + visibleSize.height - label->getContentSize().height));

        // add the label as a child to this layer
        this->addChild(label, 1);
    }

    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("HelloWorld.png");
    if (sprite == nullptr)
    {
        problemLoading("'HelloWorld.png'");
    }
    else
    {
        // position the sprite on the center of the screen
        sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

        // add the sprite as a child to this layer
        this->addChild(sprite, 0);
    }
#endif
    return true;
}



void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    //Director::getInstance()->end();

  auto director = Director::getInstance();
  //director->replaceScene(TransitionSlideInT::create(3.0f, secondScene::createScene()));
  director->pushScene(secondScene::createScene());

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);
}
