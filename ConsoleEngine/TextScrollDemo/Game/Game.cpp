#include "Game.h"

Game::Game() : Engine()
{
	SetCursorType(ECursorType::NoCursor);
	SetTargetFrameRate(12);
}

Game::~Game()
{
}
