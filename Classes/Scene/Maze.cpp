#include "Maze.h"
#include "Player/Player.h"

//D:\GitRepo\Game\proj.win32\bin\soulKnight\Debug\Resources\Map

//Map// Alien// or Forest// or Ghost //Ice // Knight // Lava //Skeleton

int Maze::level = 0;
float Maze::pictureScaleX = 1.0f;
float Maze::pictureScaleY = 1.0f;

Scene* Maze::createScene() { return Maze::create(); }

bool Maze::init() { 
    static int rScale[] = { 11, 19, 31, 45 };
    static int cScale[] = { 9, 15, 25, 35 };

	this->rowScale = rScale[level], this->columnScale = cScale[level];
    this->pictureScaleY = this->pictureScaleX = 788.0f / this->columnScale / 40.0f;

    this->buildMap();
    this->timeLimit = this->searchPath()/ 2;
    this->printMap();

    this->player = Player::create();
    this->player->maze = this;
    this->addChild(this->player);
    this->player->setPosition(Point(20.0f * this->pictureScaleX, 60.0f * this->pictureScaleY));
    

    this->portalStart = Sprite::create("Map//portal3.png");
    this->portalStart->setScale(pictureScaleX);
    this->portalStart->setGlobalZOrder(1);
    this->portalStart->setPosition(Point(20.0f * this->pictureScaleX, 70.0f * this->pictureScaleY));;
    this->addChild(portalStart);

    this->portalEnd = Sprite::create("Map//portal3.png");
    this->portalEnd->setScale(pictureScaleX);
    this->portalEnd->setGlobalZOrder(1);
    this->portalEnd->setPosition(Point((40.0f * rowScale - 20.0f) * this->pictureScaleX, (40.0f * columnScale - 40.0f) * this->pictureScaleY));;
    this->addChild(portalEnd);
    return true;
}

int Maze::searchPath() {
    int dx[] = { 0, 0, 1, -1 };
    int dy[] = { 1, -1, 0, 0 };

    vector<vector<bool>> Vis;
    vector<vector<int>> Dis;
    
    initVector(Vis, false);
    initVector(Dis, 0);
    initVector(Pre, make_pair(this->rowScale, this->rowScale-2));
    
    queue<pair<int, int>> Queue;
    Queue.push(make_pair(this->rowScale-1, this->columnScale-2));
    while (!Queue.empty()) {
        int x = Queue.front().first;
        int y = Queue.front().second;
        Queue.pop();
        Vis[x][y] = 1;
        for (int i = 0; i < 4; i++) {
            int tx = x + dx[i];
            int ty = y + dy[i];
            if (tx >= 0 && tx < rowScale && ty >= 0 && ty < columnScale &&
                Map[tx][ty]  && !Vis[tx][ty]) {
                Vis[tx][ty] = 1;
                Dis[tx][ty] = Dis[x][y] + 1;
                Pre[tx][ty] = make_pair(x, y);
                Queue.push(make_pair(tx, ty));
            }
        }
    }
    return Dis[0][1];
}

template <typename T>
void Maze::initVector(vector<vector<T>>& v, const T& element) {
    v.resize(rowScale);
    for (int i = 0; i < rowScale; i++) v[i].resize(columnScale);
    for (int i = 0; i < rowScale; i++)
        for (int j = 0; j < columnScale; j++) v[i][j] = element;
}

void Maze::buildMap() {
    srand(static_cast<unsigned int>(time(NULL)));
    initVector(Map, false);
    Map[0][1] = 1;
    Map[this->rowScale-1][this->columnScale-2] = 1;

    int dx[] = { 0, 0, 2, -2 };
    int dy[] = { 2, -2, 0, 0 };

    vector<vector<bool>> isPath, inQueue;
    initVector(isPath, false), initVector(inQueue, false);
    
    priority_queue<pair<int, pair<int, int>>> Queue;
    Queue.push(make_pair(rand(), make_pair(1, 1)));
    isPath[1][1] = 1;
    inQueue[1][1] = 1;
    
    while (!Queue.empty()) {
        pair<int, pair<int, int>> now = Queue.top();
        Queue.pop();
        int x = now.second.first;
        int y = now.second.second;
        inQueue[x][y] = 0;
        vector<int> tmp;
        for (int i = 0; i < 4; i++) {
            int tx = x + dx[i];
            int ty = y + dy[i];
            if (tx > 0 && tx < this->rowScale-1 && ty > 0 && ty <= this->columnScale-2 &&
                !isPath[tx][ty]) {
                isPath[x + tx >> 1][y + ty >> 1] = 1;
                isPath[tx][ty] = 1;
                if (!inQueue[tx][ty]) {
                    Queue.push(make_pair(rand(), make_pair(tx, ty)));
                    inQueue[tx][ty] = 1;
                }
            }
        }
    }
    for (int i =  1; i <= this->rowScale-2 ; i++)
        for (int j = 1; j <= this->columnScale-1; j++)
            if (isPath[i][j]) Map[i][j] = 1;
}

void Maze::printMap() {
    srand(static_cast<unsigned int>(time(NULL)));
    
    static vector<std::string>  
    fileNameVector = {"Map//Forest//" ,"Map//Ghost//", "Map//Ice//",
                      "Map//Knight//" , "Map//Lava//", "Map//Skeleton//"};
    int Index = rand() % 6;
    Value fileName(fileNameVector[Index]);

    const float startX = 20.0f * this->pictureScaleX;
    const float startY = 20.0f * this->pictureScaleY;

    float curX = startX, curY = startY;//图片中心位置
    for (int j = 0; j < this->columnScale; j++) {
        for (int i = 0; i < this->rowScale; i++) {
            if (this->Map[i][j]) createFloor(curX, curY, fileName); //生成地板
            else createWall(curX, curY, fileName); //生成墙
            curX += 40.0f * pictureScaleX;
        }
        curX = startX, curY += 40.0f * pictureScaleY;
    }
}

void Maze::createFloor(float curX, float curY, Value fileName) {
    Value floorName("floor" + Value(1 + rand() % 3).asString() + ".png");

    auto sprite = Sprite::create(fileName.asString() + floorName.asString());
    sprite->setPosition(Point(curX, curY));
    sprite->setGlobalZOrder(0);
    this->addChild(sprite);

    sprite->setScaleX(pictureScaleX);
    sprite->setScaleY(pictureScaleY);
}

void Maze::createWall(float curX, float curY, Value fileName) {
    auto sprite = Sprite::create();

    sprite->setContentSize(Size(40.0f, 60.0f)); //设置大小
    sprite->setAnchorPoint(Point(0.5f, 0.5f)); //设置锚点为中心

    Value wallName("wall" + Value(1 + rand() % 2).asString() + ".png");

    auto wallUp = Sprite::create(fileName.asString() + wallName.asString(), Rect(0, 0, 40, 35));//左上角坐标，长，宽
    sprite->addChild(wallUp);
    wallUp->setPosition(Point(20, 42.5f));//中心位置
    wallUp->setGlobalZOrder(3);
    //添加下层墙
    auto wallDown = Sprite::create(fileName.asString() + wallName.asString(), Rect(0, 35, 40, 25));
    sprite->addChild(wallDown);
    wallDown->setPosition(Point(20, 12.5f));
    wallDown->setGlobalZOrder(1);
    //添加阴影
    auto shadow = Sprite::create("Map//RectShadow.png");
    shadow->setGlobalZOrder(0);
    shadow->setPosition(Point(Point(20, 0)));
    shadow->setOpacity(160);
    sprite->addChild(shadow);

    sprite->setPosition(Point(curX, curY + 10.0f * pictureScaleY));
    this->addChild(sprite);

    sprite->setScaleX(pictureScaleX);
    sprite->setScaleY(pictureScaleY);
}
