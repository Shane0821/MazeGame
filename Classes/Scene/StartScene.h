#ifndef _STARTSCENE_H_
#define _STARTSCENE_H_

#include "cocos2d.h"
#include <SimpleAudioEngine.h>
USING_NS_CC;

class StartScene : public Scene
{
public:
	static Scene* createScene();

	virtual bool init();

	/*三个回调函数*/
	void menuCloseCallbackEnd(Ref* );
	void menuCloseCallbackStart(Ref* );
	void menuCloseCallbackSet(Ref* );

	CREATE_FUNC(StartScene);
private:
	CocosDenshion::SimpleAudioEngine* audio;//背景音乐管理器
};

#endif 
