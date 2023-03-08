#include "Core.h"

void Core::gameMenu() {
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

    sf::Texture whiteBoxTexture;
    whiteBoxTexture.setSmooth(true);
    if (!whiteBoxTexture.loadFromFile("Images/WhiteBox600x80.png")) {
        window.close();
        return;
    }

    sf::Texture blueBoxTexture;
    blueBoxTexture.setSmooth(true);
    if (!blueBoxTexture.loadFromFile("Images/BlueBox600x80.png")) {
        window.close();
        return;
    }

    sf::Texture blackAboutButtonTexture;
    blackAboutButtonTexture.setSmooth(true);
    if (!blackAboutButtonTexture.loadFromFile("Images/BlackAboutButton.png")) {
        window.close();
        return;
    }

    sf::Texture whiteAboutButtonTexture;
    whiteAboutButtonTexture.setSmooth(true);
    if (!whiteAboutButtonTexture.loadFromFile("Images/WhiteAboutButton.png")) {
        window.close();
        return;
    }

    if (mainMusic.getStatus() != sf::SoundSource::Status::Playing) {
        mainMusic.play();
    }
    
    bool leftMouseButtonHoldingInTitleBar = false;
    int distanceX = 0, distanceY = 0;
    while (window.isOpen()) {
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
            messageText.setString("");
            messageText.setPosition((window.getSize().x - messageText.getGlobalBounds().width) / 2, 2);
            messageClock.restart();
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

        // Logo
        sf::Sprite LogoSprite(logoTexture);
        LogoSprite.setPosition((window.getSize().x - LogoSprite.getGlobalBounds().width) / 2, 30);

        // New game
        sf::Sprite newGameBox(whiteBoxTexture);
        newGameBox.setPosition((window.getSize().x - newGameBox.getGlobalBounds().width) / 2, 230);

        sf::Text newGameText("New game", font, 40);
        newGameText.setFillColor(sf::Color::Black);
        newGameText.setPosition(newGameBox.getGlobalBounds().left + (newGameBox.getGlobalBounds().width - newGameText.getGlobalBounds().width) / 2, 245);

        if (positionInBox(sf::Mouse::getPosition(window), newGameBox.getGlobalBounds())) {
            newGameBox.setTexture(blueBoxTexture);
            newGameText.setFillColor(sf::Color::White);
        }

        // Load game
        sf::Sprite loadGameBox(whiteBoxTexture);
        loadGameBox.setPosition((window.getSize().x - loadGameBox.getGlobalBounds().width) / 2, 340);

        sf::Text loadGameText("Load game", font, 40);
        loadGameText.setFillColor(sf::Color::Black);
        loadGameText.setPosition(loadGameBox.getGlobalBounds().left + (loadGameBox.getGlobalBounds().width - loadGameText.getGlobalBounds().width) / 2, 355);

        if (positionInBox(sf::Mouse::getPosition(window), loadGameBox.getGlobalBounds())) {
            loadGameBox.setTexture(blueBoxTexture);
            loadGameText.setFillColor(sf::Color::White);
        }

        // Ranking
        sf::Sprite rankingBox(whiteBoxTexture);
        rankingBox.setPosition((window.getSize().x - rankingBox.getGlobalBounds().width) / 2, 450);

        sf::Text rankingText("Ranking", font, 40);
        rankingText.setFillColor(sf::Color::Black);
        rankingText.setPosition(rankingBox.getGlobalBounds().left + (rankingBox.getGlobalBounds().width - rankingText.getGlobalBounds().width) / 2, 465);

        if (positionInBox(sf::Mouse::getPosition(window), rankingBox.getGlobalBounds())) {
            rankingBox.setTexture(blueBoxTexture);
            rankingText.setFillColor(sf::Color::White);
        }

        // Settings
        sf::Sprite settingsBox(whiteBoxTexture);
        settingsBox.setPosition((window.getSize().x - settingsBox.getGlobalBounds().width) / 2, 560);

        sf::Text settingsText("Settings", font, 40);
        settingsText.setFillColor(sf::Color::Black);
        settingsText.setPosition(settingsBox.getGlobalBounds().left + (settingsBox.getGlobalBounds().width - settingsText.getGlobalBounds().width) / 2, 575);

        if (positionInBox(sf::Mouse::getPosition(window), settingsBox.getGlobalBounds())) {
            settingsBox.setTexture(blueBoxTexture);
            settingsText.setFillColor(sf::Color::White);
        }

        // Quit
        sf::Sprite quitBox(whiteBoxTexture);
        quitBox.setPosition((window.getSize().x - quitBox.getGlobalBounds().width) / 2, 670);

        sf::Text quitText("Quit", font, 40);
        quitText.setFillColor(sf::Color::Black);
        quitText.setPosition(quitBox.getGlobalBounds().left + (quitBox.getGlobalBounds().width - quitText.getGlobalBounds().width) / 2, 685);

        if (positionInBox(sf::Mouse::getPosition(window), quitBox.getGlobalBounds())) {
            quitBox.setTexture(blueBoxTexture);
            quitText.setFillColor(sf::Color::White);
        }

        // About
        sf::Sprite aboutButton(blackAboutButtonTexture);
        aboutButton.setPosition(window.getSize().x - 20 - aboutButton.getGlobalBounds().width, window.getSize().y - 20 - aboutButton.getGlobalBounds().height);

        if (positionInBox(sf::Mouse::getPosition(window), aboutButton.getGlobalBounds())) {
            aboutButton.setTexture(whiteAboutButtonTexture);
        }

        window.clear();

        window.draw(titleBarBox);
        window.draw(titleBarText);
        window.draw(messageText);
        window.draw(closeButtonSprite);

        window.draw(backgroundSprite);

        window.draw(LogoSprite);

        window.draw(newGameBox);
        window.draw(newGameText);

        window.draw(loadGameBox);
        window.draw(loadGameText);

        window.draw(rankingBox);
        window.draw(rankingText);

        window.draw(settingsBox);
        window.draw(settingsText);

        window.draw(quitBox);
        window.draw(quitText);

        window.draw(aboutButton);

        window.display();

        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
            case sf::Event::Closed:
                window.close();
                break;

            case sf::Event::MouseButtonPressed:
                if (event.mouseButton.  button == sf::Mouse::Left) {
                    if (positionInBox(sf::Mouse::getPosition(window), titleBarBox.getGlobalBounds()) && !positionInBox(sf::Mouse::getPosition(window), closeButtonSprite.getGlobalBounds())) {
                        distanceX = sf::Mouse::getPosition().x - window.getPosition().x;
                        distanceY = sf::Mouse::getPosition().y - window.getPosition().y;
                        leftMouseButtonHoldingInTitleBar = true;
                    }
                }

                break;

            case sf::Event::MouseButtonReleased:
                if (event.mouseButton.button == sf::Mouse::Left) {
                    if (positionInBox(sf::Mouse::getPosition(window), closeButtonSprite.getGlobalBounds())) {
                        window.close();
                        return;
                    }

                    if (positionInBox(sf::Mouse::getPosition(window), newGameBox.getGlobalBounds())) {
                        currentScreen = NEWGAME;
                        return;
                    }

                    if (positionInBox(sf::Mouse::getPosition(window), loadGameBox.getGlobalBounds())) {
                        if (!fs::exists("Data/Local/" + user.getUsername() + "/Save.txt")) {
                            messageText.setString("There was no saved game, sensei");
                            messageText.setFillColor(sf::Color::Black);
                            messageText.setPosition((window.getSize().x - messageText.getGlobalBounds().width) / 2, 2);
                            messageClock.restart();
                        } else {
                            messageText.setString("Game was loaded, sensei");
                            messageText.setFillColor(sf::Color::Black);
                            messageText.setPosition((window.getSize().x - messageText.getGlobalBounds().width) / 2, 2);
                            messageClock.restart(); 

                            std::ifstream fin;
                            fin.open("Data/Local/" + user.getUsername() + "/Save.txt");
                            table.inputData(fin);
                            fin >> mode >> firstMove >> numFrame >> posBombX >> posBombY >> continueUsed;
                            fin.close();

                            fs::remove("Data/Local/" + user.getUsername() + "/Save.txt");

                            currentScreen = MAINGAME;
                            return;
                        }
                    }

                    if (positionInBox(sf::Mouse::getPosition(window), rankingBox.getGlobalBounds())) {
                        currentScreen = RANKING;
                        return;
                    }

                    if (positionInBox(sf::Mouse::getPosition(window), settingsBox.getGlobalBounds())) {
                        currentScreen = SETTINGS;
                        return;
                    }

                    if (positionInBox(sf::Mouse::getPosition(window), quitBox.getGlobalBounds())) {
                        window.close();
                        return;
                    }

                    if (positionInBox(sf::Mouse::getPosition(window), aboutButton.getGlobalBounds())) {
                        currentScreen = ABOUT;
                        return;
                    }

                    leftMouseButtonHoldingInTitleBar = false;
                }

                break;
            }
        }
    }
}