#ifndef _SECONDSCNEN_H_
#define _SECONDSCNEN_H_

#include "cocos2d.h"
USING_NS_CC;

class secondScene : public Layer {
 public:
  static Scene* createScene();
  virtual bool init();
  void popScene(Ref* pSender);
  CREATE_FUNC(secondScene);
};

#endif
