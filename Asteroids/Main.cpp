// Asteroids.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "AsteroidsGame.h"

int main()
{
	AsteroidsGame ag;
	ag.createWindow(sf::VideoMode(1000, 1000), "Asteroids");
	ag.start();
	return EXIT_SUCCESS;
}
