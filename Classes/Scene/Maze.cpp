#include "Maze.h"

#include "Player/Player.h"
#include "StartScene.h"

// D:\GitRepo\Game\proj.win32\bin\soulKnight\Debug\Resources\Map

// Map// Alien// or Forest// or Ghost //Ice // Knight // Lava //Skeleton

int Maze::level = 0;
float Maze::pictureScaleX = 1.0f;
float Maze::pictureScaleY = 1.0f;

Scene* Maze::createScene() { return Maze::create(); }

bool Maze::init() {
    static int rScale[] = {11, 19, 29, 39};
    static int cScale[] = {9, 15, 23, 31};

    this->rowScale = rScale[level], this->columnScale = cScale[level];
    this->pictureScaleY = this->pictureScaleX =
        788.0f / this->columnScale / 40.0f;

    this->buildMap();
    this->curTime = this->timeLimit = this->searchPath() / 2.5f + 4;
    this->printMap();

    this->player = Player::create();
    this->player->maze = this;
    this->addChild(this->player);
    this->player->setPosition(
        Point(20.0f * this->pictureScaleX, 60.0f * this->pictureScaleY));

    this->portalStart = Sprite::create("Map//portal3.png");
    this->portalStart->setScale(pictureScaleX);
    this->portalStart->setGlobalZOrder(1);
    this->portalStart->setPosition(
        Point(20.0f * this->pictureScaleX, 70.0f * this->pictureScaleY));
    ;
    this->addChild(portalStart);

    this->portalEnd = Sprite::create("Map//portal3.png");
    this->portalEnd->setScale(pictureScaleX);
    this->portalEnd->setGlobalZOrder(1);
    this->portalEnd->setPosition(
        Point((40.0f * rowScale - 20.0f) * this->pictureScaleX,
              (40.0f * columnScale - 40.0f) * this->pictureScaleY));
    ;
    this->addChild(portalEnd);

    this->timeLabel = Label::createWithTTF("", "fonts/Marker Felt.ttf", 36);
    this->timeLabel->setPosition(
        Point((40.0f * rowScale * this->pictureScaleX + 1400) / 2, 450));
    this->addChild(timeLabel);

    this->failLabel = Label::createWithTTF("Game Clearance Failed",
                                           "fonts/Marker Felt.ttf", 36);
    this->failLabel->setPosition(
        Point((40.0f * rowScale * this->pictureScaleX + 1400) / 2, 450));
    this->addChild(failLabel);
    this->failLabel->setVisible(false);

    auto exitLabel =
        Label::createWithTTF("Back to Menu", "fonts/Marker Felt.ttf", 36);
    auto callBackButton = MenuItemLabel::create(
        exitLabel, CC_CALLBACK_1(Maze::mazeCloseCallBackMenu, this));
    this->exitMenu = Menu::create(callBackButton, NULL);
    this->exitMenu->setPosition(
        Point((40.0f * rowScale * this->pictureScaleX + 1400) / 2, 350));
    this->addChild(exitMenu);
    this->exitMenu->setVisible(false);

    this->schedule(schedule_selector(Maze::updateTimeLabel), 1.0f);
    return true;
}

int Maze::searchPath() {
    int dx[] = {0, 0, 1, -1};
    int dy[] = {1, -1, 0, 0};

    vector<vector<bool>> Vis;
    vector<vector<int>> Dis;

    initVector(Vis, false);
    initVector(Dis, 0);
    initVector(Pre, make_pair(this->rowScale, this->columnScale - 2));

    queue<pair<int, int>> Queue;
    Queue.push(make_pair(this->rowScale - 1, this->columnScale - 2));
    while (!Queue.empty()) {
        int x = Queue.front().first;
        int y = Queue.front().second;
        Queue.pop();
        Vis[x][y] = 1;
        for (int i = 0; i < 4; i++) {
            int tx = x + dx[i];
            int ty = y + dy[i];
            if (tx >= 0 && tx < rowScale && ty >= 0 && ty < columnScale &&
                Map[tx][ty] && !Vis[tx][ty]) {
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
    Map[this->rowScale - 1][this->columnScale - 2] = 1;

    int dx[] = {0, 0, 2, -2};
    int dy[] = {2, -2, 0, 0};

    vector<vector<bool>> isPath, inQueue;
    initVector(isPath, false), initVector(inQueue, false);

    vector<pair<int, int>> Queue;
    Queue.push_back(make_pair(1, 1));
    isPath[1][1] = 1;
    inQueue[1][1] = 1;

    while (Queue.size()) {
        swap(Queue[rand() % Queue.size()], Queue[Queue.size() - 1]);
        pair<int, int> now = Queue.back();
        Queue.pop_back();
        int x = now.first;
        int y = now.second;
        inQueue[x][y] = 0;
        for (int i = 0; i < 4; i++) {
            int tx = x + dx[i];
            int ty = y + dy[i];
            if (tx > 0 && tx < this->rowScale - 1 && ty > 0 &&
                ty <= this->columnScale - 2 && !isPath[tx][ty]) {
                isPath[x + tx >> 1][y + ty >> 1] = 1;
                isPath[tx][ty] = 1;
                if (!inQueue[tx][ty]) {
                    Queue.push_back(make_pair(tx, ty));
                    inQueue[tx][ty] = 1;
                }
            }
        }
    }
    for (int i = 1; i <= this->rowScale - 2; i++)
        for (int j = 1; j <= this->columnScale - 1; j++)
            if (isPath[i][j]) Map[i][j] = 1;
}

void Maze::printMap() {
    srand(static_cast<unsigned int>(time(NULL)));

    static vector<std::string> fileNameVector = {
        "Map//Forest//", "Map//Ghost//", "Map//Ice//",
        "Map//Knight//", "Map//Lava//",  "Map//Skeleton//"};
    int Index = rand() % 6;
    Value fileName(fileNameVector[Index]);

    const float startX = 20.0f * this->pictureScaleX;
    const float startY = 20.0f * this->pictureScaleY;

    float curX = startX, curY = startY;  //ͼƬ����λ��
    for (int j = 0; j < this->columnScale; j++) {
        for (int i = 0; i < this->rowScale; i++) {
            if (this->Map[i][j])
                createFloor(curX, curY, fileName);  //���ɵذ�
            else
                createWall(curX, curY, fileName);  //����ǽ
            curX += 40.0f * pictureScaleX;
        }
        curX = startX, curY += 40.0f * pictureScaleY;
    }
}

void Maze::showPath(float lastPosX, float lastPosY) {
    int x = lastPosX / 40.0f / Maze::pictureScaleX;
    int y = lastPosY / 40.0f / Maze::pictureScaleY;

    pair<int, int> now = this->Pre[x][y];
    x = now.first;
    y = now.second;

    while (make_pair(x, y) !=
           make_pair(this->rowScale - 1, this->columnScale - 2)) {
        int nextX = this->Pre[x][y].first;
        int nextY = this->Pre[x][y].second;
        Sprite* sprite = nullptr;

        if (nextY > y)
            sprite = Sprite::create("up.png");  // up arrow
        else if (nextY < y)
            sprite = Sprite::create("down.png");  // down arrrow
        else if (nextX > x)
            sprite = Sprite::create("right.png");  // right arrrow
        else
            sprite = Sprite::create("left.png");  // left arrrow

        sprite->setPosition(Point(
            20.0f * Maze::pictureScaleX + x * Maze::pictureScaleX * 40.0f,
            20.0f * Maze::pictureScaleX + y * Maze::pictureScaleY * 40.0f));
        sprite->setGlobalZOrder(1);
        this->addChild(sprite);

        sprite->setScaleX(Maze::pictureScaleX);
        sprite->setScaleY(Maze::pictureScaleY);

        x = nextX;
        y = nextY;
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

    sprite->setContentSize(Size(40.0f, 60.0f));  //���ô�С
    sprite->setAnchorPoint(Point(0.5f, 0.5f));  //����ê��Ϊ����

    Value wallName("wall" + Value(1 + rand() % 2).asString() + ".png");

    auto wallUp = Sprite::create(fileName.asString() + wallName.asString(),
                                 Rect(0, 0, 40, 35));  //���Ͻ����꣬������
    sprite->addChild(wallUp);
    wallUp->setPosition(Point(20, 42.5f));  //����λ��
    wallUp->setGlobalZOrder(3);
    //�����²�ǽ
    auto wallDown = Sprite::create(fileName.asString() + wallName.asString(),
                                   Rect(0, 35, 40, 25));
    sprite->addChild(wallDown);
    wallDown->setPosition(Point(20, 12.5f));
    wallDown->setGlobalZOrder(1);
    //������Ӱ
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

void Maze::updateTimeLabel(float delta) {
    if (curTime == 0) {
        this->showPath(player->getPositionX(), player->getPositionY());
        this->timeLabel->setVisible(false);
        this->level = 0;
        this->failLabel->setVisible(true);
        this->exitMenu->setVisible(true);
        this->cleanup();
        return;
    }
    curTime--;
    this->timeLabel->setString("Time Remain: " + Value(curTime).asString() +
                               " s");
}

void Maze::mazeCloseCallBackMenu(Ref* pSender) {
    Director::getInstance()->replaceScene(
        TransitionCrossFade::create(0.0f, StartScene::createScene()));
}