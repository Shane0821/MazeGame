#ifndef _ENDSCENE_H_
#define _ENDSCENE_H_

#include "cocos2d.h"

USING_NS_CC;

class Player;
class EndScene:public Scene {
public:
	static Scene* createScene();
	
	Player* player = nullptr;

	virtual bool init();

	/*»Øµ÷º¯Êý*/
	void menuCloseCallbackStart(Ref*);

	CREATE_FUNC(EndScene);
};
#endif 
