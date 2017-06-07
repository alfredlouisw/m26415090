#include "GameScene.h"
#include "SimpleAudioEngine.h"
#include <time.h>
#include <stdlib.h>
USING_NS_CC;

Scene* Game::createScene()
{
	return Game::create();
}



// on "init" you need to initialize your instance
bool Game::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Scene::init())
	{
		return false;
	}
	srand(time(0));
	auto factor = Director::getInstance()->getContentScaleFactor();
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	for (int i = 0; i < 8; i++){
		for (int j = 0; j < 8; j++){
			board[i][j] = 0;
		}
	}
	board[3][3] = 1;
	board[3][4] = 2;
	board[4][3] = 2;
	board[4][4] = 1;

	auto label = Label::createWithTTF("Othello!", "fonts/Marker Felt.ttf", 36);
	// position the label on the center of the screen
	label->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height - label->getContentSize().height ));
	this->addChild(label, 1);
	



	// position the sprite on the center of the screen

	boardSprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	// add the sprite as a child to this layer


	for (int i = 0; i < 8; i++){
		for (int j = 0; j < 8; j++){
			if (i != j){
				if (board[i][j] == 1){
					piece[i][j] = Sprite::create("piece.png", Rect(6 * 64 / factor, 0, 64 / factor, 64 / factor));
					piece[i][j]->setPosition(Vec2(((8 - i) * 67 - 33.5) / factor, ((j + 1) * 66 - 33) / factor));
					piece[i][j]->setName("white");
					boardSprite->addChild(piece[i][j], 1);
				}
				else if (board[i][j] == 2){
					piece[i][j] = Sprite::create("piece.png", Rect(6 * 64 / factor, 64 / factor, 64 / factor, 64 / factor));
					piece[i][j]->setPosition(Vec2(((8 - i) * 67 - 33.5) / factor, ((j + 1) * 66 - 33) / factor));

					piece[i][j]->setName("black");
					boardSprite->addChild(piece[i][j], 1);
				}
				else{
					piece[i][j] = Sprite::create();
					piece[i][j]->setName("none");
					boardSprite->addChild(piece[i][j], 1);

				}
			}
			else{
				if (board[i][j] == 1){
					piece[i][j] = Sprite::create("piece.png", Rect(6 * 64 / factor, 0, 64 / factor, 64 / factor));
					piece[i][j]->setPosition(Vec2(((i + 1) * 67 - 33.5) / factor, ((8 - j) * 66 - 33) / factor));
					piece[i][j]->setName("white");
					boardSprite->addChild(piece[i][j], 1);
				}
				else if (board[i][j] == 2){
					piece[i][j] = Sprite::create("piece.png", Rect(6 * 64 / factor, 64 / factor, 64 / factor, 64 / factor));
					piece[i][j]->setPosition(Vec2(((i + 1) * 67 - 33.5) / factor, ((8 - j) * 66 - 33) / factor));

					piece[i][j]->setName("black");
					boardSprite->addChild(piece[i][j], 1);
				}
				else{
					piece[i][j] = Sprite::create();
					piece[i][j]->setName("none");
					boardSprite->addChild(piece[i][j], 1);


				}
			}


		}
	}

	this->addChild(boardSprite, 0);
	this->scheduleUpdate();
	return true;
}
void Game::update(float delta){
	int whiteCount = 0, blackCount = 0;
	for (int i = 0; i < 8; i++){
		for (int j = 0; j < 8; j++){
			if (board[i][j] == 1){
				whiteCount++;
			}
			else if (board[i][j] == 2){
				blackCount++;
			}
		}
	}
	if (whiteCount + blackCount == 64){
		if (blackCount > whiteCount){
			MessageBox("black win", "");
		}
		else if (blackCount < whiteCount){
			MessageBox("white win", "");
		}
	}
	else if (whiteCount == 0){
		MessageBox("black win", "");
	}
	else if (blackCount == 0){
		MessageBox("white win", "");
	}
	else{


		auto factor = Director::getInstance()->getContentScaleFactor();
		for (int i = 0; i < valid.size(); i++){
			boardSprite->removeChild(valid[i].sprite, true);
		}
		valid = getValidMoves(board, turn);

		if (valid.size() == 0){
			if (turn == 1){
				turn = 2;
			}
			else{
				turn = 1;
			}
		}
		else{
			if (ai){
				if (turn == 1){
					for (int i = 0; i < valid.size(); i++){
						valid[i].sprite = Sprite::create("green_dot.png");
						valid[i].sprite->setPosition(Vec2(((valid[i].col + 1) * 67 - 33.5) / factor, ((8 - valid[i].row) * 66 - 33) / factor));
						valid[i].sprite->setScale(0.05);

						auto touchListener = EventListenerTouchOneByOne::create();
						touchListener->onTouchBegan = [&](Touch* touch, Event* event) -> bool {

							auto target = event->getCurrentTarget();
							auto factor = Director::getInstance()->getContentScaleFactor();

							//Get the position of the current point relative to the button
							Point locationInNode = target->convertToNodeSpace(touch->getLocation());
							Size s = target->getContentSize();
							Rect rect = Rect(0, 0, s.width, s.height);

							if (rect.containsPoint(locationInNode)){

								if (turn == 1){

									int row = floor(target->getPosition().x / 64 * factor);
									int col = floor(target->getPosition().y / 64 * factor);
									/*std::stringstream c;
									c << row << " " << col;
									MessageBox(c.str().c_str(), "");*/

									piece[7 - col][row] = Sprite::create("piece.png", Rect(6 * 64 / factor, 0, 64 / factor, 64 / factor));
									piece[7 - col][row]->setPosition(Vec2(((row + 1) * 67 - 33.5) / factor, ((col + 1) * 66 - 33) / factor));
									piece[7 - col][row]->setName("white");
									boardSprite->addChild(piece[7 - col][row], 1);

									board[7 - col][row] = 1;

									a.str("");
									for (int i = 0; i < 8; i++){
										for (int j = 0; j < 8; j++){
											a << board[i][j] << " ";
										}
										a << std::endl;
									}
									a << std::endl;

									for (int i = 0; i < 8; i++){
										for (int j = 0; j < 8; j++){
											if (piece[i][j]->getName() == "white"){
												a << 1 << " ";
											}
											else if (piece[i][j]->getName() == "black"){
												a << 2 << " ";
											}
											else{
												a << 0 << " ";
											}
										}
										a << std::endl;
									}
									MessageBox(a.str().c_str(), "player 1kmkm");
									//right
									int j = 1;
									while (board[7 - col][row - j] == 2){
										j++;
									}
									if (board[7 - col][row - j] == 1 && j >= 2){
										for (int i = 1; i <= j; i++){
											board[7 - col][row - i] = 1;
											piece[7 - col][row - i]->setTextureRect(Rect(6 * 64 / factor, 0, 64 / factor, 64 / factor));
											piece[7 - col][row - i]->setName("white");

										}
									}

									//left
									j = 1;
									while (board[7 - col][row + j] == 2){
										j++;
									}
									if (board[7 - col][row + j] == 1 && j >= 2){
										for (int i = 1; i <= j; i++){
											board[7 - col][row + i] = 1;
											piece[7 - col][row + i]->setTextureRect(Rect(6 * 64 / factor, 0, 64 / factor, 64 / factor));
											piece[7 - col][row + i]->setName("white");

										}
									}
									//up
									j = 1;
									while (board[7 - col + j][row] == 2){
										j++;
									}
									if (board[7 - col + j][row] == 1 && j >= 2){
										for (int i = 1; i <= j; i++){
											board[7 - col + i][row] = 1;
											piece[7 - col + i][row]->setTextureRect(Rect(6 * 64 / factor, 0, 64 / factor, 64 / factor));
											piece[7 - col + i][row]->setName("white");

										}
									}
									//down
									j = 1;
									while (board[7 - col - j][row] == 2){
										j++;
									}
									if (board[7 - col - j][row] == 1 && j >= 2){
										for (int i = 1; i <= j; i++){
											board[7 - col - i][row] = 1;
											piece[7 - col - i][row]->setTextureRect(Rect(6 * 64 / factor, 0, 64 / factor, 64 / factor));
											piece[7 - col - i][row]->setName("white");

										}
									}

									//down right
									j = 1;
									while (board[7 - col - j][row - j] == 2){
										j++;
									}
									if (board[7 - col - j][row - j] == 1 && j >= 2){
										for (int i = 1; i <= j; i++){
											board[7 - col - i][row - i] = 1;
											piece[7 - col - i][row - i]->setTextureRect(Rect(6 * 64 / factor, 0, 64 / factor, 64 / factor));
											piece[7 - col - i][row - i]->setName("white");

										}
									}
									//down left
									j = 1;
									while (board[7 - col - j][row + j] == 2){
										j++;
									}
									if (board[7 - col - j][row + j] == 1 && j >= 2){
										for (int i = 1; i <= j; i++){
											board[7 - col - i][row + i] = 1;
											piece[7 - col - i][row + i]->setTextureRect(Rect(6 * 64 / factor, 0, 64 / factor, 64 / factor));
											piece[7 - col - i][row + i]->setName("white");

										}
									}
									//up right
									j = 1;
									while (board[7 - col + j][row - j] == 2){
										j++;
									}
									if (board[7 - col + j][row - j] == 1 && j >= 2){
										for (int i = 1; i <= j; i++){
											board[7 - col + i][row - i] = 1;
											piece[7 - col + i][row - i]->setTextureRect(Rect(6 * 64 / factor, 0, 64 / factor, 64 / factor));
											piece[7 - col + i][row - i]->setName("white");

										}
									}
									//up left
									j = 1;
									while (board[7 - col + j][row + j] == 2){
										j++;
									}
									if (board[7 - col + j][row + j] == 1 && j >= 2){
										for (int i = 1; i <= j; i++){
											board[7 - col + i][row + i] = 1;
											piece[7 - col + i][row + i]->setTextureRect(Rect(6 * 64 / factor, 0, 64 / factor, 64 / factor));
											piece[7 - col + i][row + i]->setName("white");

										}
									}


									a.str("");
									for (int i = 0; i < 8; i++){
										for (int j = 0; j < 8; j++){
											a << board[i][j] << " ";
										}
										a << std::endl;
									}
									a << std::endl;

									for (int i = 0; i < 8; i++){
										for (int j = 0; j < 8; j++){
											if (piece[i][j]->getName() == "white"){
												a << 1 << " ";
											}
											else if (piece[i][j]->getName() == "black"){
												a << 2 << " ";
											}
											else{
												a << 0 << " ";
											}
										}
										a << std::endl;  
									}
									MessageBox(a.str().c_str(), "player 1kmkm");



									turn = 2;
								}

							}

							return true;
						};

						Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener->clone(), valid[i].sprite);
						boardSprite->addChild(valid[i].sprite, 1);
					}
				}
				else if (turn == 2){

					std::stringstream d;
					for (int i = 0; i < valid.size(); i++){
						d << 7-valid[i].row << " " << valid[i].col << std::endl;
					}
					MessageBox(d.str().c_str(), "");

					int random = rand() % valid.size();
					int a = valid[random].row;
					int b = valid[random].col;
					
					int row = 7-a;
					int col = b;



					piece[7 - col][row] = Sprite::create("piece.png", Rect(6 * 64 / factor, 64 / factor, 64 / factor, 64 / factor));
					piece[7 - col][row]->setPosition(Vec2(((row + 1) * 67 - 33.5) / factor, ((col + 1) * 66 - 33) / factor));
					piece[7 - col][row]->setName("black");
					boardSprite->addChild(piece[7 - col][row], 1);

					board[7 - col][row] = 2;

					
					//right
					int j = 1;
					while (board[7 - col][row - j] == 1){
						j++;
					}
					if (board[7 - col][row - j] == 2 && j >= 2){
						for (int i = 1; i <= j; i++){
							board[7 - col][row - i] = 2;
							piece[7 - col][row - i]->setTextureRect(Rect(6 * 64 / factor, 64 / factor, 64 / factor, 64 / factor));
							piece[7 - col][row - i]->setName("black");

						}
					}

					//left
					j = 1;
					while (board[7 - col][row + j] == 1){
						j++;
					}
					if (board[7 - col][row + j] == 2 && j >= 2){
						for (int i = 1; i <= j; i++){
							board[7 - col][row + i] = 2;
							piece[7 - col][row + i]->setTextureRect(Rect(6 * 64 / factor, 64 / factor, 64 / factor, 64 / factor));
							piece[7 - col][row + i]->setName("black");

						}
					}
					//up
					j = 1;
					while (board[7 - col + j][row] == 1){
						j++;
					}
					if (board[7 - col + j][row] == 2 && j >= 2){
						for (int i = 1; i <= j; i++){
							board[7 - col + i][row] = 2;
							piece[7 - col + i][row]->setTextureRect(Rect(6 * 64 / factor, 64 / factor, 64 / factor, 64 / factor));
							piece[7 - col + i][row]->setName("black");

						}
					}
					//down
					j = 1;
					while (board[7 - col - j][row] == 1){
						j++;
					}
					if (board[7 - col - j][row] == 2 && j >= 2){
						for (int i = 1; i <= j; i++){
							board[7 - col - i][row] = 2;
							piece[7 - col - i][row]->setTextureRect(Rect(6 * 64 / factor, 64 / factor, 64 / factor, 64 / factor));
							piece[7 - col - i][row]->setName("black");

						}
					}

					//down right
					j = 1;
					while (board[7 - col - j][row - j] == 1){
						j++;
					}
					if (board[7 - col - j][row - j] == 2 && j >= 2){
						for (int i = 1; i <= j; i++){
							board[7 - col - i][row - i] = 2;
							piece[7 - col - i][row - i]->setTextureRect(Rect(6 * 64 / factor, 64 / factor, 64 / factor, 64 / factor));
							piece[7 - col - i][row - i]->setName("black");

						}
					}
					//down left
					j = 1;
					while (board[7 - col - j][row + j] == 1){
						j++;
					}
					if (board[7 - col - j][row + j] == 2 && j >= 2){
						for (int i = 1; i <= j; i++){
							board[7 - col - i][row + i] = 2;
							piece[7 - col - i][row + i]->setTextureRect(Rect(6 * 64 / factor, 64 / factor, 64 / factor, 64 / factor));
							piece[7 - col - i][row + i]->setName("black");

						}
					}
					//up right
					j = 1;
					while (board[7 - col + j][row - j] == 1){
						j++;
					}
					if (board[7 - col + j][row - j] == 2 && j >= 2){
						for (int i = 1; i <= j; i++){
							board[7 - col + i][row - i] = 2;
							piece[7 - col + i][row - i]->setTextureRect(Rect(6 * 64 / factor, 64 / factor, 64 / factor, 64 / factor));
							piece[7 - col + i][row - i]->setName("black");

						}
					}
					//up left
					j = 1;
					while (board[7 - col + j][row + j] == 1){
						j++;
					}
					if (board[7 - col + j][row + j] == 2 && j >= 2){
						for (int i = 1; i <= j; i++){
							board[7 - col + i][row + i] = 2;
							piece[7 - col + i][row + i]->setTextureRect(Rect(6 * 64 / factor, 64 / factor, 64 / factor, 64 / factor));
							piece[7 - col + i][row + i]->setName("black");

						}
					}


					turn = 1;
					ai = true;

				}
			}
			else{

				for (int i = 0; i < valid.size(); i++){
					valid[i].sprite = Sprite::create("green_dot.png");
					valid[i].sprite->setPosition(Vec2(((valid[i].col + 1) * 67 - 33.5) / factor, ((8 - valid[i].row) * 66 - 33) / factor));
					valid[i].sprite->setScale(0.05);

					auto touchListener = EventListenerTouchOneByOne::create();
					touchListener->onTouchBegan = [&](Touch* touch, Event* event) -> bool {

						auto target = event->getCurrentTarget();
						auto factor = Director::getInstance()->getContentScaleFactor();

						//Get the position of the current point relative to the button
						Point locationInNode = target->convertToNodeSpace(touch->getLocation());
						Size s = target->getContentSize();
						Rect rect = Rect(0, 0, s.width, s.height);

						if (rect.containsPoint(locationInNode)){

							if (turn == 1){

								int row = floor(target->getPosition().x / 64 * factor);
								int col = floor(target->getPosition().y / 64 * factor);


								piece[7 - col][row] = Sprite::create("piece.png", Rect(6 * 64 / factor, 0, 64 / factor, 64 / factor));
								piece[7 - col][row]->setPosition(Vec2(((row + 1) * 67 - 33.5) / factor, ((col + 1) * 66 - 33) / factor));
								piece[7 - col][row]->setName("white");
								boardSprite->addChild(piece[7 - col][row], 1);

								board[7 - col][row] = 1;

								a.str("");
								for (int i = 0; i < 8; i++){
									for (int j = 0; j < 8; j++){
										a << board[i][j] << " ";
									}
									a << std::endl;
								}
								a << std::endl;

								for (int i = 0; i < 8; i++){
									for (int j = 0; j < 8; j++){
										if (piece[i][j]->getName() == "white"){
											a << 1 << " ";
										}
										else if (piece[i][j]->getName() == "black"){
											a << 2 << " ";
										}
										else{
											a << 0 << " ";
										}
									}
									a << std::endl;
								}
								MessageBox(a.str().c_str(), "player 1");
								//right
								int j = 1;
								while (board[7 - col][row - j] == 2){
									j++;
								}
								if (board[7 - col][row - j] == 1 && j >= 2){
									for (int i = 1; i <= j; i++){
										board[7 - col][row - i] = 1;
										piece[7 - col][row - i]->setTextureRect(Rect(6 * 64 / factor, 0, 64 / factor, 64 / factor));
										piece[7 - col][row - i]->setName("white");

									}
								}

								//left
								j = 1;
								while (board[7 - col][row + j] == 2){
									j++;
								}
								if (board[7 - col][row + j] == 1 && j >= 2){
									for (int i = 1; i <= j; i++){
										board[7 - col][row + i] = 1;
										piece[7 - col][row + i]->setTextureRect(Rect(6 * 64 / factor, 0, 64 / factor, 64 / factor));
										piece[7 - col][row + i]->setName("white");

									}
								}
								//up
								j = 1;
								while (board[7 - col + j][row] == 2){
									j++;
								}
								if (board[7 - col + j][row] == 1 && j >= 2){
									for (int i = 1; i <= j; i++){
										board[7 - col + i][row] = 1;
										piece[7 - col + i][row]->setTextureRect(Rect(6 * 64 / factor, 0, 64 / factor, 64 / factor));
										piece[7 - col + i][row]->setName("white");

									}
								}
								//down
								j = 1;
								while (board[7 - col - j][row] == 2){
									j++;
								}
								if (board[7 - col - j][row] == 1 && j >= 2){
									for (int i = 1; i <= j; i++){
										board[7 - col - i][row] = 1;
										piece[7 - col - i][row]->setTextureRect(Rect(6 * 64 / factor, 0, 64 / factor, 64 / factor));
										piece[7 - col - i][row]->setName("white");

									}
								}

								//down right
								j = 1;
								while (board[7 - col - j][row - j] == 2){
									j++;
								}
								if (board[7 - col - j][row - j] == 1 && j >= 2){
									for (int i = 1; i <= j; i++){
										board[7 - col - i][row - i] = 1;
										piece[7 - col - i][row - i]->setTextureRect(Rect(6 * 64 / factor, 0, 64 / factor, 64 / factor));
										piece[7 - col - i][row - i]->setName("white");

									}
								}
								//down left
								j = 1;
								while (board[7 - col - j][row + j] == 2){
									j++;
								}
								if (board[7 - col - j][row + j] == 1 && j >= 2){
									for (int i = 1; i <= j; i++){
										board[7 - col - i][row + i] = 1;
										piece[7 - col - i][row + i]->setTextureRect(Rect(6 * 64 / factor, 0, 64 / factor, 64 / factor));
										piece[7 - col - i][row + i]->setName("white");

									}
								}
								//up right
								j = 1;
								while (board[7 - col + j][row - j] == 2){
									j++;
								}
								if (board[7 - col + j][row - j] == 1 && j >= 2){
									for (int i = 1; i <= j; i++){
										board[7 - col + i][row - i] = 1;
										piece[7 - col + i][row - i]->setTextureRect(Rect(6 * 64 / factor, 0, 64 / factor, 64 / factor));
										piece[7 - col + i][row - i]->setName("white");

									}
								}
								//up left
								j = 1;
								while (board[7 - col + j][row + j] == 2){
									j++;
								}
								if (board[7 - col + j][row + j] == 1 && j >= 2){
									for (int i = 1; i <= j; i++){
										board[7 - col + i][row + i] = 1;
										piece[7 - col + i][row + i]->setTextureRect(Rect(6 * 64 / factor, 0, 64 / factor, 64 / factor));
										piece[7 - col + i][row + i]->setName("white");

									}
								}


								a.str("");
								for (int i = 0; i < 8; i++){
									for (int j = 0; j < 8; j++){
										a << board[i][j] << " ";
									}
									a << std::endl;
								}
								a << std::endl;

								for (int i = 0; i < 8; i++){
									for (int j = 0; j < 8; j++){
										if (piece[i][j]->getName() == "white"){
											a << 1 << " ";
										}
										else if (piece[i][j]->getName() == "black"){
											a << 2 << " ";
										}
										else{
											a << 0 << " ";
										}
									}
									a << std::endl;
								}
								MessageBox(a.str().c_str(), "player 1");



								turn = 2;
							}
							else if (turn == 2){


								int row = floor(target->getPosition().x / 64 * factor);
								int col = floor(target->getPosition().y / 64 * factor);

								piece[7 - col][row] = Sprite::create("piece.png", Rect(6 * 64 / factor, 64 / factor, 64 / factor, 64 / factor));
								piece[7 - col][row]->setPosition(Vec2(((row + 1) * 67 - 33.5) / factor, ((col + 1) * 66 - 33) / factor));
								piece[7 - col][row]->setName("black");
								boardSprite->addChild(piece[7 - col][row], 1);

								board[7 - col][row] = 2;

								a.str("");
								for (int i = 0; i < 8; i++){
									for (int j = 0; j < 8; j++){
										a << board[i][j] << " ";
									}
									a << std::endl;
								}
								a << std::endl;

								for (int i = 0; i < 8; i++){
									for (int j = 0; j < 8; j++){
										if (piece[i][j]->getName() == "white"){
											a << 1 << " ";
										}
										else if (piece[i][j]->getName() == "black"){
											a << 2 << " ";
										}
										else{
											a << 0 << " ";
										}
									}
									a << std::endl;
								}
								MessageBox(a.str().c_str(), "player 2");
								//right
								int j = 1;
								while (board[7 - col][row - j] == 1 && row-j >=0){
									j++;
								}
								if (board[7 - col][row - j] == 2 && j >= 2){
									for (int i = 1; i <= j; i++){
										board[7 - col][row - i] = 2;
										piece[7 - col][row - i]->setTextureRect(Rect(6 * 64 / factor, 64 / factor, 64 / factor, 64 / factor));
										piece[7 - col][row - i]->setName("black");

									}
								}

								//left
								j = 1;
								while (board[7 - col][row + j] == 1 && row + j <= 7){
									j++;
								}
								if (board[7 - col][row + j] == 2 && j >= 2){
									for (int i = 1; i <= j; i++){
										board[7 - col][row + i] = 2;
										piece[7 - col][row + i]->setTextureRect(Rect(6 * 64 / factor, 64 / factor, 64 / factor, 64 / factor));
										piece[7 - col][row + i]->setName("black");

									}
								}
								//up
								j = 1;
								while (board[7 - col + j][row] == 1 && 7-col + j <= 7){
									j++;
								}
								if (board[7 - col + j][row] == 2 && j >= 2){
									for (int i = 1; i <= j; i++){
										board[7 - col + i][row] = 2;
										piece[7 - col + i][row]->setTextureRect(Rect(6 * 64 / factor, 64 / factor, 64 / factor, 64 / factor));
										piece[7 - col + i][row]->setName("black");

									}
								}
								//down
								j = 1;
								while (board[7 - col - j][row] == 1 && 7-col-j >= 0){
									j++;
								}
								if (board[7 - col - j][row] == 2 && j >= 2){
									for (int i = 1; i <= j; i++){
										board[7 - col - i][row] = 2;
										piece[7 - col - i][row]->setTextureRect(Rect(6 * 64 / factor, 64 / factor, 64 / factor, 64 / factor));
										piece[7 - col - i][row]->setName("black");

									}
								}

								//down right
								j = 1;
								while (board[7 - col - j][row - j] == 1 && row - j >= 0 && 7-col-j >=0){
									j++;
								}
								if (board[7 - col - j][row - j] == 2 && j >= 2){
									for (int i = 1; i <= j; i++){
										board[7 - col - i][row - i] = 2;
										piece[7 - col - i][row - i]->setTextureRect(Rect(6 * 64 / factor, 64 / factor, 64 / factor, 64 / factor));
										piece[7 - col - i][row - i]->setName("black");

									}
								}
								//down left
								j = 1;
								while (board[7 - col - j][row + j] == 1 && row + j <= 7 && 7 - col - j >= 0){
									j++;
								}
								if (board[7 - col - j][row + j] == 2 && j >= 2){
									for (int i = 1; i <= j; i++){
										board[7 - col - i][row + i] = 2;
										piece[7 - col - i][row + i]->setTextureRect(Rect(6 * 64 / factor, 64 / factor, 64 / factor, 64 / factor));
										piece[7 - col - i][row + i]->setName("black");

									}
								}
								//up right
								j = 1;
								while (board[7 - col + j][row - j] == 1 && row - j >= 0 && 7 - col + j <= 7){
									j++;
								}
								if (board[7 - col + j][row - j] == 2 && j >= 2){
									for (int i = 1; i <= j; i++){
										board[7 - col + i][row - i] = 2;
										piece[7 - col + i][row - i]->setTextureRect(Rect(6 * 64 / factor, 64 / factor, 64 / factor, 64 / factor));
										piece[7 - col + i][row - i]->setName("black");

									}
								}
								//up left
								j = 1;
								while (board[7 - col + j][row + j] == 1 && row + j <= 7 && 7 - col + j <= 7){
									j++;
								}
								if (board[7 - col + j][row + j] == 2 && j >= 2){
									for (int i = 1; i <= j; i++){
										board[7 - col + i][row + i] = 2;
										piece[7 - col + i][row + i]->setTextureRect(Rect(6 * 64 / factor, 64 / factor, 64 / factor, 64 / factor));
										piece[7 - col + i][row + i]->setName("black");

									}
								}


								a.str("");
								for (int i = 0; i < 8; i++){
									for (int j = 0; j < 8; j++){
										a << board[i][j] << " ";
									}
									a << std::endl;
								}
								a << std::endl;

								for (int i = 0; i < 8; i++){
									for (int j = 0; j < 8; j++){
										if (piece[i][j]->getName() == "white"){
											a << 1 << " ";
										}
										else if (piece[i][j]->getName() == "black"){
											a << 2 << " ";
										}
										else{
											a << 0 << " ";
										}
									}
									a << std::endl;
								}
								MessageBox(a.str().c_str(), "player 2");
								turn = 1;

							}
						}

						return true;
					};

					Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener->clone(), valid[i].sprite);
					boardSprite->addChild(valid[i].sprite, 1);
				}
			}
		}
	}
}
void Game::menuCloseCallback(Ref* pSender)
{
	//Close the cocos2d-x game scene and quit the application
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif

	/*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/

	//EventCustom customEndEvent("game_scene_close_event");
	//_eventDispatcher->dispatchEvent(&customEndEvent);


}
