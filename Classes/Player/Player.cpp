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
			this->speedY = 3.0f;
			break;

		case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
			this->speedY = -3.0f;
			break;

		case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
			this->speedX = -3.0f;
			this->sprite->setFlippedX(true);
			break;

		case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
			this->speedX = 3.0f;
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


}

void Player::update(float delta) {
	Point position = this->getPosition();
	log("%.f %.f", this->speedX, this->speedY);
	this->setPosition(position + Point(this->speedX, this->speedY));
}

bool Player::init() {
	this->bindSprite(Sprite::create("player.png"));

	this->speedX = this->speedY = 0.0f;

	this->registerKeyBoardEvent();
	this->scheduleUpdate();
	return true;
}