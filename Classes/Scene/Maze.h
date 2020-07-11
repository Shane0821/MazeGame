#ifndef _MAZE_H_
#define _MAZE_H_

#include "cocos2d.h"

#include <vector>
#include <utility>

USING_NS_CC;
using namespace std;

class Player;

class Maze : public Scene {	
	friend class Player;

private:
	vector<vector<bool>> Map; //记录Map[i][j]类型 0表示墙，1表示路径
	vector<vector<pair<int, int>>> Pre; //记录路径上前驱
	int rowScale, columnScale;          //迷宫规模
	
	int timeLimit, curTime;
	
	static float pictureScaleX, pictureScaleY; //缩放比例

	Player* player = nullptr;//人物

	Label* timeLabel = nullptr;//计时标签
	Label* failLabel = nullptr;//失败提示标签
	
	Menu* exitMenu = nullptr;//返回主菜单按钮

	Sprite* portalEnd = nullptr;//两个传送门
	Sprite* portalStart = nullptr;

	template <typename T>
	void initVector(vector<vector<T>>&, const T&); //初始化vetor，定大小，内容
	void buildMap(); //生成地图
	void printMap();//打印地图
	int searchPath(); //求最短路

	void createFloor(float, float, Value); //生成地板
	void createWall(float, float, Value); //生成墙
	void showPath(float, float);//显示路径

	void updateTimeLabel(float);//更新时间标签
	void mazeCloseCallBackMenu(Ref*);//回调主界面

 public:
	static int level;
	static Scene* createScene();

	virtual bool init();

	CREATE_FUNC(Maze);
};
#endif