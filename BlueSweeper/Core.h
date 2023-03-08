#ifndef CORE_H
#define CORE_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <filesystem>
#include <chrono>

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "User.h"
#include "Table.h"
#include "TileMap.h"
#include "Random.h"

namespace fs = std::filesystem;

// Screen
#define GAMEMENU       0
#define PROFILE        1
#define LOGIN          2 
#define SIGNUP         3
#define CHANGEPASSWORD 4
#define NEWGAME        5
#define MAINGAME       6
#define RANKING        7
#define SETTINGS       8
#define ABOUT          9

// Level
#define BEGINNER       0
#define INTERMEDIATE   1
#define EXPERT         2
#define CUSTOM         3

struct Core {
private:
	User user;
	Table table;
	sf::RenderWindow window;
	sf::Texture backgroundTexture, logoTexture;
	sf::Music mainMusic;
	sf::Font font;
	int currentScreen;
	sf::Text messageText;
	sf::Clock messageClock;

	// stuff for main game
	int mode;
	bool firstMove;
	int numFrame, posBombX, posBombY;
	bool continueUsed;

	// settings
	int musicVolume, soundVolume;
	bool enableQuestionMark;
	bool enableCantWinMode;

public:
	Core();
	bool positionInBox(sf::Vector2i, sf::FloatRect);
	sf::Vector2f centerPosition(sf::FloatRect, sf::FloatRect);
	void gameMenu();
	void profile();
	void logIn();
	void signUp();
	void changePassword();
	void newGame();
	void mainGame();
	void updateLocalRanking(int);
	void updateGlobalRanking(int);
	void ranking();
	void settings();
	void about();
	void run();
};

#endif