#include "Player.h"

void Player::bindSprite(Sprite* sprite) {
	this->sprite = sprite;
	sprite->setScaleX(Maze::pictureScaleX);
	sprite->setScaleY(Maze::pictureScaleY);
	this->sprite->setGlobalZOrder(2);

	//将entity中心和sprite中心重合
	Size size = this->sprite->getContentSize();
	this->setContentSize(size); //设置大小

	this->setAnchorPoint(Point(0.5f, 0.5f)); //设置锚点
	setPosition(Point(.0f, .0f));

	this->addChild(sprite);
	sprite->setPosition(Point(size.width / 2, size.height / 2));

}

void Player::registerKeyBoardEvent() {
	auto listener = EventListenerKeyboard::create();
		listener->onKeyPressed = [&](EventKeyboard::KeyCode code, Event*) {
			switch (code) {
			case EventKeyboard::KeyCode::KEY_UP_ARROW:
				if (this->maze != nullptr)
					this->speedY = 3.0f * Maze::pictureScaleX;
				break;

			case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
				if (this->maze != nullptr)
					this->speedY = -3.0f * Maze::pictureScaleX;
				break;

			case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
				this->speedX = -3.0f * Maze::pictureScaleX;
				this->sprite->setFlippedX(true);
				break;

			case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
				this->speedX = 3.0f * Maze::pictureScaleX;
				this->sprite->setFlippedX(false);
				break;
			}
		};

		listener->onKeyReleased = [&](EventKeyboard::KeyCode code, Event*) {
			switch (code) {
			case EventKeyboard::KeyCode::KEY_UP_ARROW:
				this->speedY = 0.0f;
				break;

			case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
				this->speedY = 0.0f;
				break;

			case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
				this->speedX = 0.0f;
				break;

			case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
				this->speedX = 0.0f;
				break;
			}
		};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void Player::checkCollision() {
	float pictureScale = Maze::pictureScaleX;

	float playerPosX = this->getPositionX();
	float playerPosY = this->getPositionY();
	if (this->speedX > 0.0f) {
		int i = (playerPosX + 20.0f * pictureScale) / 40.0f / pictureScale;
		int upj = playerPosY / 40.0f / pictureScale;
		int downj = (playerPosY - 20.0f * pictureScale) / 40.0f / pictureScale;
		if (i >= maze->rowScale || !maze->Map[i][upj] || !maze->Map[i][downj])
			this->speedX = 0;
	}

	if (this->speedX < 0.0f) {
		int i = (playerPosX - 20.0f * pictureScale) / 40.0f / pictureScale;
		int upj = playerPosY / 40.0f / pictureScale;
		int downj = (playerPosY - 20.0f * pictureScale) / 40.0f / pictureScale;
		if (i < 0 || !maze->Map[i][upj] || !maze->Map[i][downj])
			this->speedX = 0;
	}

	if (this->speedY < 0.0f) {
		int j = (playerPosY - 26.0f * pictureScale) / 40.0f / pictureScale;
		int lefti = (playerPosX - 10.0f * pictureScale) / 40.0f / pictureScale;
		int righti = (playerPosX + 10.0f * pictureScale) / 40.0f / pictureScale;
		if (j < 0 || !maze->Map[lefti][j] || !maze->Map[righti][j])
			this->speedY = 0;
	}

	if (this->speedY > 0.0f) {
		int j = (playerPosY + 10.0f * pictureScale) / 40.0f / pictureScale;
		int lefti = (playerPosX - 10.0f * pictureScale) / 40.0f / pictureScale;
		int righti = (playerPosX + 10.0f * pictureScale) / 40.0f / pictureScale;
		if (j >= maze->columnScale || !maze->Map[lefti][j] || !maze->Map[righti][j])
			this->speedY = 0;
	}
}

void Player::checkEnd() {
	if (this->getPosition().getDistance(maze->portalEnd->getPosition()) <= 15.0f * Maze::pictureScaleX) {
		maze->level++;
		this->cleanup();
		if (maze->level < 4)
			Director::getInstance()->replaceScene(TransitionCrossFade::create(2.0f, Maze::createScene()));
		else {
			maze->level = 0;
			Maze::pictureScaleX = Maze::pictureScaleY = 788.0f / 9.0f / 40.0f;
			Director::getInstance()->replaceScene(TransitionFade::create(0.0f, EndScene::createScene()));
		}
	}
}

void Player::checkBorder() {
	float playerPosX = this->getPositionX();
	float playerPosY = this->getPositionY();
	if (this->speedX < 0.0f && playerPosX - 20.0 < 0)
		this->speedX = 0;
	if (this->speedX > 0.0f && playerPosX + 20.0 > 1400)
		this->speedX = 0;
}

void Player::update(float delta) {
	Point position = this->getPosition();
	
	if(this->maze != nullptr) {
		this->checkCollision();
		this->checkEnd();
	}else
		this->checkBorder();
	this->setPosition(position + Point(this->speedX, this->speedY));
}

bool Player::init() {
	this->bindSprite(Sprite::create("player.png"));
	this->maze = nullptr;
	this->endScene = nullptr;
	this->speedX = this->speedY = 0.0f;

	this->registerKeyBoardEvent();
	this->scheduleUpdate();
	return true;
}