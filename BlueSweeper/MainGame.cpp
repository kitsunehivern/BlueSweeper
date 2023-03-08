#include <tuple>

#include "Core.h"

void Core::mainGame() {
    sf::Texture whiteCloseButtonTexture;
    if (!whiteCloseButtonTexture.loadFromFile("Images/WhiteCloseButton.png")) {
        window.close();
        return;
    }

    sf::Texture redCloseButtonTexture;
    if (!redCloseButtonTexture.loadFromFile("Images/RedCloseButton.png")) {
        window.close();
        return;
    }

    sf::Texture whiteBackButtonTexture;
    whiteBackButtonTexture.setSmooth(true);
    if (!whiteBackButtonTexture.loadFromFile("Images/WhiteBackButton.png")) {
        window.close();
        return;
    }

    sf::Texture blackBackButtonTexture;
    blackBackButtonTexture.setSmooth(true);
    if (!blackBackButtonTexture.loadFromFile("Images/BlackBackButton.png")) {
        window.close();
        return;
    }

    sf::Texture whiteRefreshButtonTexture;
    whiteRefreshButtonTexture.setSmooth(true);
    if (!whiteRefreshButtonTexture.loadFromFile("Images/WhiteRefreshButton.png")) {
        window.close();
        return;
    }

    sf::Texture blackRefreshButtonTexture;
    blackRefreshButtonTexture.setSmooth(true);
    if (!blackRefreshButtonTexture.loadFromFile("Images/BlackRefreshButton.png")) {
        window.close();
        return;
    }

    sf::Texture whiteContinueButtonTexture;
    whiteContinueButtonTexture.setSmooth(true);
    if (!whiteContinueButtonTexture.loadFromFile("Images/WhiteContinueButton.png")) {
        window.close();
        return;
    }

    sf::Texture blackContinueButtonTexture;
    blackContinueButtonTexture.setSmooth(true);
    if (!blackContinueButtonTexture.loadFromFile("Images/BlackContinueButton.png")) {
        window.close();
        return;
    }

    sf::Texture whiteBoxTexture;
    whiteBoxTexture.setSmooth(true);
    if (!whiteBoxTexture.loadFromFile("Images/WhiteBox300x80.png")) {
        window.close();
        return;
    }

    sf::Texture AronaStatesTexture;
    AronaStatesTexture.setSmooth(true);
    if (!AronaStatesTexture.loadFromFile("Images/AronaStates.png")) {
        window.close();
        return;
    }

    sf::SoundBuffer loseSoundBuffer;
    if (!loseSoundBuffer.loadFromFile("Sounds/Bonk.wav")) {
        window.close();
        return;
    }

    sf::Sound loseSound;
    loseSound.setVolume(soundVolume);
    loseSound.setBuffer(loseSoundBuffer);

    sf::Music gameMusic;
    gameMusic.setLoop(true);
    gameMusic.setVolume(musicVolume);
    if (!gameMusic.openFromFile("Musics/Lemonade_Diary.ogg")) {
        window.close();
        return;
    }

    sf::Music winMusic;
    winMusic.setLoop(true);
    winMusic.setVolume(musicVolume);
    if (!winMusic.openFromFile("Musics/Party_Time.ogg")) {
        window.close();
        return;
    }

    mainMusic.stop();
    gameMusic.play();

    bool leftMouseButtonHolding = false;
    int gameState = table.gameState();
    sf::FloatRect tableBox((window.getSize().x - 32 * table.getNumCol()) / 2, 112 + (window.getSize().y - 32 * table.getNumRow()) / 2, 32 * table.getNumCol(), 32 * table.getNumRow());
    bool leftMouseButtonHoldingInTitleBar = false;
    int distanceX = 0, distanceY = 0;
    while (window.isOpen()) {
        if (firstMove && gameState == 0) {
            numFrame++;
        }

        if (leftMouseButtonHoldingInTitleBar) {
            window.setPosition(sf::Vector2i(sf::Mouse::getPosition().x - distanceX, sf::Mouse::getPosition().y - distanceY));
        }

        // Title bar
        sf::RectangleShape titleBarBox(sf::Vector2f(window.getSize().x, 32));
        titleBarBox.setFillColor(sf::Color::White);

        sf::Text titleBarText("BlueSweeper", font, 20);
        titleBarText.setFillColor(sf::Color::Black);
        titleBarText.setPosition(10, 2);

        float currentMessageTime = messageClock.getElapsedTime().asSeconds();
        if (currentMessageTime >= 4.f) {
            messageText.setFillColor(sf::Color::White);
        } else if (currentMessageTime >= 3.f) {
            int color = (currentMessageTime - 3.f) * 255;
            messageText.setFillColor(sf::Color(color, color, color));
        }

        sf::Sprite closeButtonSprite(whiteCloseButtonTexture);
        closeButtonSprite.setPosition(window.getSize().x - closeButtonSprite.getGlobalBounds().width, 0);

        if (positionInBox(sf::Mouse::getPosition(window), closeButtonSprite.getGlobalBounds())) {
            closeButtonSprite.setTexture(redCloseButtonTexture);
        }

        // Background
        sf::Sprite backgroundSprite(backgroundTexture);
        backgroundSprite.setPosition(0, 32);

        // Back
        sf::Sprite backButtonSprite(blackBackButtonTexture);
        backButtonSprite.setPosition(20, 52);

        if (positionInBox(sf::Mouse::getPosition(window), backButtonSprite.getGlobalBounds())) {
            backButtonSprite.setTexture(whiteBackButtonTexture);
        }

        // Flag
        sf::Sprite flagBox(whiteBoxTexture);
        flagBox.setPosition(136, 52);

        sf::Text flagText(("Flag: " + std::to_string(table.getNumBomb() - table.getNumMarked())).c_str(), font, 40);
        flagText.setFillColor(sf::Color::Black);
        flagText.setPosition(flagBox.getGlobalBounds().left + (flagBox.getGlobalBounds().width - flagText.getGlobalBounds().width) / 2, 67);

        // Refresh
        sf::Sprite refreshButtonSprite(blackRefreshButtonTexture);
        refreshButtonSprite.setPosition(472, 52);

        if (positionInBox(sf::Mouse::getPosition(window), refreshButtonSprite.getGlobalBounds())) {
            refreshButtonSprite.setTexture(whiteRefreshButtonTexture);              
        }

        // Time
        sf::Sprite timeBox(whiteBoxTexture);
        timeBox.setPosition(588, 52);

        sf::Text timeText(("Time: " + std::to_string(numFrame / 60)).c_str(), font, 40);
        timeText.setFillColor(sf::Color::Black);
        timeText.setPosition(timeBox.getGlobalBounds().left + (timeBox.getGlobalBounds().width - timeText.getGlobalBounds().width) / 2, 67);

        // Continue
        sf::Sprite continueButtonSprite(blackContinueButtonTexture);
        continueButtonSprite.setPosition(924, 52);

        if (gameState == -1 && positionInBox(sf::Mouse::getPosition(window), continueButtonSprite.getGlobalBounds())) {
            continueButtonSprite.setTexture(whiteContinueButtonTexture);
        }

        // Tile map
        std::vector <std::vector <int> > indexMap(table.getNumRow() + 2, std::vector <int> (table.getNumCol() + 2));
        for (int posX = 0; posX < table.getNumRow() + 2; posX++) {
            for (int posY = 0; posY < table.getNumCol() + 2; posY++) {
                int &index = indexMap[posX][posY];

                if (posX == 0 && posY == 0) {
                    index = 16;
                    continue;
                }

                if (posX == 0 && posY == table.getNumCol() + 1) {
                    index = 17;
                    continue;
                }

                if (posX == table.getNumRow() + 1 && posY == 0) {
                    index = 18;
                    continue;
                }

                if (posX == table.getNumRow() + 1 && posY == table.getNumCol() + 1) {
                    index = 19;
                    continue;
                }

                if (posX == 0) {
                    index = 20;
                    continue;
                }

                if (posX == table.getNumRow() + 1) {
                    index = 21;
                    continue;
                }

                if (posY == 0) {
                    index = 22;
                    continue;
                }

                if (posY == table.getNumCol() + 1) {
                    index = 23;
                    continue;
                }

                if (table.isVeiled(posX - 1, posY - 1)) {
                    index = 11 + table.isSpecial(posX - 1, posY - 1);
                    continue;
                }
                
                if (table.isMarked(posX - 1, posY - 1)) {
                    index = 13;
                    if (gameState == -1 && !table.isBomb(posX - 1, posY - 1)) {
                        index = 14;
                    }

                    continue;
                }

                if (table.isBomb(posX - 1, posY - 1)) {
                    index = 9 + (posX - 1 == posBombX && posY - 1 == posBombY);
                } else {
                    index = table.getAdjacentBombs(posX - 1, posY - 1);
                }
            }
        }

        if (gameState == 0 && leftMouseButtonHolding && positionInBox(sf::Mouse::getPosition(window), tableBox)) {
            int posX = (sf::Mouse::getPosition(window).y - tableBox.top) / 32;
            int posY = (sf::Mouse::getPosition(window).x - tableBox.left) / 32;
            if (table.isVeiled(posX, posY)) {
                indexMap[posX + 1][posY + 1] = 0;
            } else if (!table.isMarked(posX, posY)) {
                for (int deltaX : {-1, 0, 1}) {
                    for (int deltaY : {-1, 0, 1}) {
                        if (deltaX == 0 && deltaY == 0) {
                            continue;
                        }

                        int newX = posX + deltaX;
                        int newY = posY + deltaY;

                        if (0 > newX || newX >= table.getNumRow() || 0 > newY || newY >= table.getNumCol()) {
                            continue;
                        }

                        if (table.isVeiled(newX, newY)) {
                            indexMap[newX + 1][newY + 1] = 0;
                        }
                    }
                }
            }
        }

        TileMap tileMap;
        if (!tileMap.load("Images/TileSet.png", sf::Vector2u(32, 32), indexMap, sf::Vector2f(tableBox.left - 32, tableBox.top - 32))) {
            window.close();
            return;
        }

        // Arona
        sf::Sprite AronaStateSprite(AronaStatesTexture);
        AronaStateSprite.setTextureRect(sf::IntRect(80 * (gameState + 1), 0, 80, 80));
        AronaStateSprite.setPosition((window.getSize().x - AronaStateSprite.getGlobalBounds().width) / 2, tableBox.top - 24 - AronaStateSprite.getGlobalBounds().height);

        window.clear();

        window.draw(titleBarBox);
        window.draw(titleBarText);
        window.draw(messageText);
        window.draw(closeButtonSprite);

        window.draw(backgroundSprite);

        window.draw(backButtonSprite);
        window.draw(flagBox);
        window.draw(flagText);
        window.draw(refreshButtonSprite);
        window.draw(timeBox);
        window.draw(timeText);
        window.draw(continueButtonSprite);

        window.draw(tileMap);
        window.draw(AronaStateSprite);

        window.display();

        auto saveGame = [&]() -> void {
            std::ofstream fout;
            fout.open("Data/Local/" + user.getUsername() + "/Save.txt");
            table.outputData(fout);
            fout << mode << " " << firstMove << " " << numFrame << " " << posBombX << " " << posBombY << " " << continueUsed;
            fout.close();
        };

        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
            case sf::Event::Closed:
                window.close();
                break;

            case sf::Event::MouseButtonPressed:
                if (event.mouseButton.button == sf::Mouse::Left) {
                    leftMouseButtonHolding = true;
                    if (positionInBox(sf::Mouse::getPosition(window), titleBarBox.getGlobalBounds()) && !positionInBox(sf::Mouse::getPosition(window), closeButtonSprite.getGlobalBounds())) {
                        distanceX = sf::Mouse::getPosition().x - window.getPosition().x;
                        distanceY = sf::Mouse::getPosition().y - window.getPosition().y;
                        leftMouseButtonHoldingInTitleBar = true;
                    }
                } else {
                    if (gameState == 0 && positionInBox(sf::Mouse::getPosition(window), tableBox)) {
                        int posX = (sf::Mouse::getPosition(window).y - tableBox.top) / 32;
                        int posY = (sf::Mouse::getPosition(window).x - tableBox.left) / 32;

                        table.mark(posX, posY);

                        if (!firstMove) {
                            numFrame = 0;
                            firstMove = true;
                        }
                    }
                }

                break;

            case sf::Event::MouseButtonReleased:
                if (event.mouseButton.button == sf::Mouse::Left) {
                    if (positionInBox(sf::Mouse::getPosition(window), closeButtonSprite.getGlobalBounds())) {
                        if (firstMove && gameState == 0 && !user.getUsername().empty()) {
                            saveGame();
                        }

                        window.close();
                        return;
                    }

                    if (positionInBox(sf::Mouse::getPosition(window), backButtonSprite.getGlobalBounds())) {
                        if (firstMove && gameState == 0) {
                            messageText.setString("Game was saved, sensei");
                            messageText.setFillColor(sf::Color::Black);
                            messageText.setPosition((window.getSize().x - messageText.getGlobalBounds().width) / 2, 2);
                            messageClock.restart();

                            saveGame();
                        }   
                        
                        table = Table();
                        firstMove = false;
                        numFrame = 0, posBombX = posBombY = -1;
                        continueUsed = false;

                        if (gameState == 1) {
                            winMusic.stop();
                        } else {
                            gameMusic.stop();
                        }

                        mainMusic.play();

                        currentScreen = GAMEMENU;
                        return;
                    }

                    if (positionInBox(sf::Mouse::getPosition(window), refreshButtonSprite.getGlobalBounds())) {
                        messageText.setString("Game was refreshed, sensei");
                        messageText.setFillColor(sf::Color::Black);
                        messageText.setPosition((window.getSize().x - messageText.getGlobalBounds().width) / 2, 2);
                        messageClock.restart();

                        table.refresh();
                        firstMove = false;
                        numFrame = 0;
                        continueUsed = false;

                        if (gameState == 1) {
                            winMusic.stop();
                            gameMusic.play();
                        }

                        gameState = 0;
                    }

                    if (gameState == -1 && positionInBox(sf::Mouse::getPosition(window), continueButtonSprite.getGlobalBounds())) {
                        table.undo();
                        gameState = 0;
                        continueUsed = true;
                    }

                    if (gameState == 0 && leftMouseButtonHolding && positionInBox(sf::Mouse::getPosition(window), tableBox)) {
                        int posX = (sf::Mouse::getPosition(window).y - tableBox.top) / 32;
                        int posY = (sf::Mouse::getPosition(window).x - tableBox.left) / 32;

                        if (!firstMove) {
                            numFrame = 0;
                            firstMove = true;
                        }

                        table.open(posX, posY);

                        gameState = table.gameState();

                        if (enableCantWinMode && gameState == 1) {
                            table.undo();

                            std::vector <std::pair <int, int> > toOpen;
                            for (int newX = 0; newX < table.getNumRow(); newX++) {
                                for (int newY = 0; newY < table.getNumCol(); newY++) {
                                    if (table.isBomb(newX, newY) && table.isVeiled(newX, newY)) {
                                        toOpen.push_back(std::make_pair(newX, newY));
                                    }
                                }
                            }

                            if (!toOpen.empty()) {
                                int pos = randInt(0, toOpen.size() - 1);
                                sf::Mouse::setPosition(sf::Vector2i(tableBox.left + 32 * toOpen[pos].second + 16, tableBox.top + 32 * toOpen[pos].first + 16), window);
                                table.open(toOpen[pos].first, toOpen[pos].second);
                                gameState = table.gameState();

                                posX = (sf::Mouse::getPosition(window).y - tableBox.top) / 32;
                                posY = (sf::Mouse::getPosition(window).x - tableBox.left) / 32;
                            } else {
                                messageText.setString("Game was refreshed");
                                messageText.setFillColor(sf::Color::Black);
                                messageText.setPosition((window.getSize().x - messageText.getGlobalBounds().width) / 2, 2);
                                messageClock.restart();

                                sf::Mouse::setPosition(sf::Vector2i(window.getSize().x / 2, 92), window);

                                table.refresh();

                                firstMove = false;
                                numFrame = 0;
                                continueUsed = false;
                                gameMusic.play();
                                gameState = 0;
                            }
                        }

                        if (gameState == 1) {
                            messageText.setString(std::string("Great job, sensei") + (user.getUsername().empty() || mode == CUSTOM || continueUsed ? "" : ". Ranking was updated"));
                            messageText.setFillColor(sf::Color::Black);
                            messageText.setPosition((window.getSize().x - messageText.getGlobalBounds().width) / 2, 2);
                            messageClock.restart();

                            if (!continueUsed) {
                                updateLocalRanking(numFrame / 60);
                                updateGlobalRanking(numFrame / 60);
                            }

                            gameMusic.stop();
                            winMusic.play();
                        }

                        if (gameState == -1) {
                            messageText.setString("That was unlucky. Let's try again, sensei");
                            messageText.setFillColor(sf::Color::Black);
                            messageText.setPosition((window.getSize().x - messageText.getGlobalBounds().width) / 2, 2);
                            messageClock.restart();

                            if (table.isBomb(posX, posY)) {
                                posBombX = posX;
                                posBombY = posY;   
                            } else {
                                for (int deltaX : {-1, 0, 1}) {
                                    for (int deltaY : {-1, 0, 1}) {
                                        if (deltaX == 0 && deltaY == 0) {
                                            continue;
                                        }

                                        int newX = posX + deltaX;
                                        int newY = posY + deltaY;

                                        if (0 > newX || newX >= table.getNumRow() || 0 > newY || newY >= table.getNumCol()) {
                                            continue;
                                        }

                                        if (table.isBomb(newX, newY) && !table.isMarked(newX, newY)) {
                                            posBombX = newX;
                                            posBombY = newY;
                                        }
                                    }
                                }
                            }
                            
                            loseSound.play();
                        }
                    }

                    leftMouseButtonHolding = false;
                    leftMouseButtonHoldingInTitleBar = false;
                }

                break;

            }
        }
    }
}
