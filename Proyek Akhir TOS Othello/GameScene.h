#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "Cell.h"
#include <vector>

class Game : public cocos2d::Scene
{
public:
	int board[8][8];
	cocos2d::Sprite* piece[8][8];
	cocos2d::Sprite* boardSprite = cocos2d::Sprite::create("Board.jpg");
	int turn = 1;
	std::vector<Cell> valid;
	std::stringstream a,b;
	int whiteCount = 0, blackCount = 0;
	bool ai = true;
	
	static cocos2d::Scene* createScene();

	virtual bool init();

	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);

	std::vector<Cell> getValidMoves(int board[8][8], int player){
		std::vector<Cell> valid;
		std::vector<Cell> piece;
		int enemy;
		if (player == 1){
			enemy = 2;
		}
		else if (player == 2){
			enemy = 1;
		}

		for (int i = 0; i < 8; i++){
			for (int j = 0; j < 8; j++){
				if (board[i][j] == player){
					Cell tmp;
					tmp.row = i;
					tmp.col = j;
					piece.push_back(tmp);
				}
			}
		}

		for (int i = 0; i < piece.size(); i++){
			//right
			int j = 1;
			if (piece[i].col + j <= 6){
				while (board[piece[i].row][piece[i].col + j] == enemy){
					j++;
				}

				if (board[piece[i].row][piece[i].col + j] == 0 && j >= 2){
					Cell tmp;
					tmp.row = piece[i].row;
					tmp.col = piece[i].col + j;
					if (tmp.row >= 0 && tmp.row <= 7 && tmp.col >= 0 && tmp.col <= 7){ valid.push_back(tmp);}
					
				}
			}
			//left
			j = 1;
			if (piece[i].col - j >= 1){
				while (board[piece[i].row][piece[i].col - j] == enemy){
					j++;
				}

				if (board[piece[i].row][piece[i].col - j] == 0 && j >= 2){
					Cell tmp;
					tmp.row = piece[i].row;
					tmp.col = piece[i].col -j;
					if (tmp.row >= 0 && tmp.row <= 7 && tmp.col >= 0 && tmp.col <= 7){ valid.push_back(tmp);}
				}
			}
			//up
			j = 1;
			if (piece[i].row - j >= 1){
				while (board[piece[i].row-j][piece[i].col] == enemy){
					j++;
				}

				if (board[piece[i].row-j][piece[i].col] == 0 && j >= 2){
					Cell tmp;
					tmp.row = piece[i].row-j;
					tmp.col = piece[i].col;
					if (tmp.row >= 0 && tmp.row <= 7 && tmp.col >= 0 && tmp.col <= 7){ valid.push_back(tmp);}
				}
			}
			//down
			j = 1;
			if (piece[i].row + j <= 6){
				while (board[piece[i].row + j][piece[i].col] == enemy){
					j++;
				}

				if (board[piece[i].row + j][piece[i].col] == 0 && j >= 2){
					Cell tmp;
					tmp.row = piece[i].row + j;
					tmp.col = piece[i].col; 
					if (tmp.row >= 0 && tmp.row <= 7 && tmp.col >= 0 && tmp.col <= 7){ valid.push_back(tmp); }
				}
			}
			//up left
			j = 1;
			if (piece[i].row - j >= 1 && piece[i].col - j >=1){
				while (board[piece[i].row - j][piece[i].col - j] == enemy){
					j++;
				}

				if (board[piece[i].row - j][piece[i].col - j] == 0 && j >= 2){
					Cell tmp;
					tmp.row = piece[i].row - j;
					tmp.col = piece[i].col - j;
					if (tmp.row >= 0 && tmp.row <= 7 && tmp.col >= 0 && tmp.col <= 7){ valid.push_back(tmp); }
				}
			}

			//up right
			j = 1;
			if (piece[i].row - j >= 1 && piece[i].col + j <= 6){
				while (board[piece[i].row - j][piece[i].col + j] == enemy){
					j++;
				}

				if (board[piece[i].row - j][piece[i].col + j] == 0 && j >= 2){
					Cell tmp;
					tmp.row = piece[i].row - j;
					tmp.col = piece[i].col + j;
					if (tmp.row >= 0 && tmp.row <= 7 && tmp.col >= 0 && tmp.col <= 7){ valid.push_back(tmp); }
				}
			}


			//down right
			j = 1;
			if (piece[i].row + j <= 6 && piece[i].col + j <= 6){
				while (board[piece[i].row + j][piece[i].col + j] == enemy){
					j++;
				}

				if (board[piece[i].row + j][piece[i].col + j] == 0 && j >= 2){
					Cell tmp;
					tmp.row = piece[i].row + j;
					tmp.col = piece[i].col + j;
					if (tmp.row >= 0 && tmp.row <= 7 && tmp.col >= 0 && tmp.col <= 7){ valid.push_back(tmp); }
				}
			}

			//down left
			j = 1;
			if (piece[i].row + j <= 6 && piece[i].col - j >= 1){
				while (board[piece[i].row + j][piece[i].col - j] == enemy){
					j++;
				}

				if (board[piece[i].row + j][piece[i].col - j] == 0 && j >= 2){
					Cell tmp;
					tmp.row = piece[i].row + j;
					tmp.col = piece[i].col - j;
					if (tmp.row >= 0 && tmp.row <= 7 && tmp.col >= 0 && tmp.col <= 7){ valid.push_back(tmp); }
				}
			}

		}
		
		return valid;
	}
	
	// implement the "static create()" method manually
	CREATE_FUNC(Game);
	void update(float) override;
};

#endif // __HELLOWORLD_SCENE_H__
