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
	vector<vector<Sprite*>> MapSprite; //��ͼ����
	vector<vector<pair<int, int>>> Pre; //��¼���·��ǰ��
	int rowScale, columnScale;          //�Թ���ģ
	
	int timeLimit;
	static int level;
	
	static float pictureScaleX, pictureScaleY; //���ű���

	Player* player = nullptr;

	Label* timeLable = nullptr;

	Sprite* portalEnd = nullptr;
	Sprite* portalStart = nullptr;

	template <typename T>
	void initVector(vector<vector<T>>&, const T&); //��ʼ��vetor������С������
	void buildMap(); //���ɵ�ͼ
	void printMap();//��ӡ��ͼ
	int searchPath(); //�����·

	void createFloor(float, float, Value); //���ɵذ�
	void createWall(float, float, Value); //����ǽ

 public:
  static Scene* createScene();

  virtual bool init();

  CREATE_FUNC(Maze);

 // void ShowPath();//��ʾ·��
};
#endif