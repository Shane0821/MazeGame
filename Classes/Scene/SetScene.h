#ifndef _SETSCENE_H_
#define _SETSCENE_H_

#include "cocos2d.h"
USING_NS_CC;

class SetScene : public Scene
{
public:
	static Scene* createScene();

	virtual bool init();

	void menuCloseCallbackEnd(Ref* );//关闭设置面板的回调函数
	void menuCloseCallbackChange(Ref* );//改变音乐播放状态的回调函数

	void menuCloseCallbackVolumeHigher(Ref* );//升高音量
	void menuCloseCallbackVolumeLower(Ref* );//降低音量

	CREATE_FUNC(SetScene);
private:
	//菜单
	Menu* Menu01;
	Menu* Menu02;
	Menu* Menu03;
	Menu* MenuHigherVolume;
	Menu* MenuLowerVolume;

	/*音量大小标签*/
	Label* volumeNumLab;

	int volume = 50;//初始音量
};
#endif 
