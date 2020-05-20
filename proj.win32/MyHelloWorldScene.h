#ifndef _MYHELLOWORLD_SCENE_H_
#define _MYHELLOWORLD_SCENE_H_

#include "cocos2d.h"
USING_NS_CC;

class myScene : public Layer {
 public:
  static Scene* createScene();

  virtual bool init();

  CREATE_FUNC(myScene);
};


#endif