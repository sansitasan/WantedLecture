#include "Game.h"

Game::Game() : Engine()
{
	SetCursorType(ECursorType::NoCursor);
	SetTargetFrameRate(24);
}

Game::~Game()
{
}
