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
	vector<vector<Sprite*>> MapSprite; //地图精灵
	vector<vector<pair<int, int>>> Pre; //记录最短路上前驱
	int rowScale, columnScale;          //迷宫规模
	
	int timeLimit;
	static int level;
	
	static float pictureScaleX, pictureScaleY; //缩放比例

	Player* player = nullptr;

	Label* timeLable = nullptr;

	Sprite* portalEnd = nullptr;
	Sprite* portalStart = nullptr;

	template <typename T>
	void initVector(vector<vector<T>>&, const T&); //初始化vetor，定大小，内容
	void buildMap(); //生成地图
	void printMap();//打印地图
	int searchPath(); //求最短路

	void createFloor(float, float, Value); //生成地板
	void createWall(float, float, Value); //生成墙

 public:
  static Scene* createScene();

  virtual bool init();

  CREATE_FUNC(Maze);

 // void ShowPath();//显示路径
};
#endif