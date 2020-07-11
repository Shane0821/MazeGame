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
	vector<vector<bool>> Map; //��¼Map[i][j]���� 0��ʾǽ��1��ʾ·��
	vector<vector<pair<int, int>>> Pre; //��¼·����ǰ��
	int rowScale, columnScale;          //�Թ���ģ
	
	int timeLimit, curTime;
	
	static float pictureScaleX, pictureScaleY; //���ű���

	Player* player = nullptr;//����

	Label* timeLabel = nullptr;//��ʱ��ǩ
	Label* failLabel = nullptr;//ʧ����ʾ��ǩ
	
	Menu* exitMenu = nullptr;//�������˵���ť

	Sprite* portalEnd = nullptr;//����������
	Sprite* portalStart = nullptr;

	template <typename T>
	void initVector(vector<vector<T>>&, const T&); //��ʼ��vetor������С������
	void buildMap(); //���ɵ�ͼ
	void printMap();//��ӡ��ͼ
	int searchPath(); //�����·

	void createFloor(float, float, Value); //���ɵذ�
	void createWall(float, float, Value); //����ǽ
	void showPath(float, float);//��ʾ·��

	void updateTimeLabel(float);//����ʱ���ǩ
	void mazeCloseCallBackMenu(Ref*);//�ص�������

 public:
	static int level;
	static Scene* createScene();

	virtual bool init();

	CREATE_FUNC(Maze);
};
#endif