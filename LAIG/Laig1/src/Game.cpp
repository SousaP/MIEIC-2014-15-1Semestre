#include "Game.h"

Game::Game(){
	GameBoard = new Board();
}

void Game::nextPlayer() {
	this->player++;
	this->player %= 2;
}

void Game::previousPlayer() {
	this->player--;
	this->player %= 2;
}

Board* Game::getBoard(){
	return GameBoard;
}


Game :: ~Game(void){
	delete(GameBoard);
}