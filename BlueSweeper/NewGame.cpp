#include "Core.h"

void Core::newGame() {
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

    sf::Texture grayButtonsTexture;
    grayButtonsTexture.setSmooth(true);
    if (!grayButtonsTexture.loadFromFile("Images/GrayButtons.png")) {
        window.close();
        return;
    }

    sf::Texture blackButtonsTexture;
    blackButtonsTexture.setSmooth(true);
    if (!blackButtonsTexture.loadFromFile("Images/BlackButtons.png")) {
        window.close();
        return;
    }

    sf::Texture blueButtonsTexture;
    blueButtonsTexture.setSmooth(true);
    if (!blueButtonsTexture.loadFromFile("Images/BlueButtons.png")) {
        window.close();
        return;
    }

    sf::Texture blueBoxTexture;
    blueBoxTexture.setSmooth(true);
    if (!blueBoxTexture.loadFromFile("Images/BlueBox600x80.png")) {
        window.close();
        return;
    }

    sf::Texture whiteBoxTexture;
    whiteBoxTexture.setSmooth(true);
    if (!whiteBoxTexture.loadFromFile("Images/WhiteBox600x80.png")) {
        window.close();
        return;
    }

    int customRow = 2, customCol = 2, customBombs = 1;
    int currentMode = BEGINNER;
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

        // New game
        sf::Text newGameText("New game", font, 90);
        newGameText.setFillColor(sf::Color::Black);
        newGameText.setPosition((window.getSize().x - newGameText.getGlobalBounds().width) / 2, 90);

        // Mode
        sf::Sprite modeBox(whiteBoxTexture);
        modeBox.setPosition((window.getSize().x - modeBox.getGlobalBounds().width) / 2, 230);

        sf::Text modeText("Mode", font, 40);
        modeText.setFillColor(sf::Color::Black);
        switch (currentMode) {
        case BEGINNER:
            modeText.setString("Beginner");
            break;

        case INTERMEDIATE:
            modeText.setString("Intermediate");
            break;

        case EXPERT:
            modeText.setString("Expert");
            break;

        case CUSTOM:
            modeText.setString("Custom");
            break;
        }

        modeText.setPosition(modeBox.getGlobalBounds().left + (modeBox.getGlobalBounds().width - modeText.getGlobalBounds().width) / 2, 245);

        sf::RectangleShape prevModeBox(sf::Vector2f(80, 80));
        prevModeBox.setPosition(modeBox.getGlobalBounds().left, modeBox.getGlobalBounds().top);

        sf::Sprite prevModeSprite;
        if (positionInBox(sf::Mouse::getPosition(window), prevModeBox.getGlobalBounds())) {
            prevModeSprite.setTexture(blueButtonsTexture);
        } else {
            prevModeSprite.setTexture(blackButtonsTexture);
        }

        prevModeSprite.setTextureRect(sf::IntRect(80, 0, 80, 80));
        prevModeSprite.setPosition(centerPosition(prevModeBox.getGlobalBounds(), prevModeSprite.getGlobalBounds()));

        sf::RectangleShape nextModeBox(sf::Vector2f(80, 80));
        nextModeBox.setPosition(modeBox.getGlobalBounds().left + modeBox.getGlobalBounds().width - nextModeBox.getGlobalBounds().width, modeBox.getGlobalBounds().top);

        sf::Sprite nextModeSprite;
        if (positionInBox(sf::Mouse::getPosition(window), nextModeBox.getGlobalBounds())) {
            nextModeSprite.setTexture(blueButtonsTexture);
        }  else {
            nextModeSprite.setTexture(blackButtonsTexture);
        }

        nextModeSprite.setTextureRect(sf::IntRect(160, 0, 80, 80));
        nextModeSprite.setPosition(centerPosition(nextModeBox.getGlobalBounds(), nextModeSprite.getGlobalBounds()));

        // Width
        sf::Sprite widthBox(whiteBoxTexture);
        widthBox.setPosition((window.getSize().x - widthBox.getGlobalBounds().width) / 2, 340);

        sf::Text widthText("Width", font, 40);
        widthText.setFillColor(sf::Color::Black);
        widthText.setPosition(widthBox.getGlobalBounds().left + 20, 355);

        sf::RectangleShape dprevWidthBox(sf::Vector2f(80, 80));
        dprevWidthBox.setPosition(widthBox.getGlobalBounds().left + 180, 340);

        sf::Sprite dprevWidthSprite;
        if (currentMode != CUSTOM || (currentMode == CUSTOM && customCol == 2)) {
            dprevWidthSprite.setTexture(grayButtonsTexture);
        } else if (positionInBox(sf::Mouse::getPosition(window), dprevWidthBox.getGlobalBounds())) {
            dprevWidthSprite.setTexture(blueButtonsTexture);
        } else {
            dprevWidthSprite.setTexture(blackButtonsTexture);
        }

        dprevWidthSprite.setTextureRect(sf::IntRect(0, 0, 80, 80));
        dprevWidthSprite.setPosition(centerPosition(dprevWidthBox.getGlobalBounds(), dprevWidthSprite.getGlobalBounds()));

        sf::RectangleShape prevWidthBox(sf::Vector2f(80, 80));
        prevWidthBox.setPosition(widthBox.getGlobalBounds().left + 260, 340);

        sf::Sprite prevWidthSprite;
        if (currentMode != CUSTOM || (currentMode == CUSTOM && customCol == 2)) {
            prevWidthSprite.setTexture(grayButtonsTexture);
        } else if (positionInBox(sf::Mouse::getPosition(window), prevWidthBox.getGlobalBounds())) {
            prevWidthSprite.setTexture(blueButtonsTexture);
        } else {
            prevWidthSprite.setTexture(blackButtonsTexture);
        }

        prevWidthSprite.setTextureRect(sf::IntRect(80, 0, 80, 80));
        prevWidthSprite.setPosition(centerPosition(prevWidthBox.getGlobalBounds(), prevWidthSprite.getGlobalBounds()));

        sf::RectangleShape customWidthBox(sf::Vector2f(100, 80));
        customWidthBox.setPosition(widthBox.getGlobalBounds().left + 340, 340);

        sf::Text customWidthText("0", font, 40);
        customWidthText.setFillColor(sf::Color::Black);
        if (currentMode == BEGINNER) {
            customWidthText.setString("9");
        } else if (currentMode == INTERMEDIATE) {
            customWidthText.setString("16");
        } else if (currentMode == EXPERT) {
            customWidthText.setString("30");
        } else {
            customWidthText.setString(std::to_string(customCol).c_str());
        }

        customWidthText.setPosition(customWidthBox.getPosition().x + (customWidthBox.getSize().x - customWidthText.getGlobalBounds().width) / 2, 355);

        sf::RectangleShape nextWidthBox(sf::Vector2f(80, 80));
        nextWidthBox.setPosition(widthBox.getGlobalBounds().left + 440, 340);

        sf::Sprite nextWidthSprite;
        if (currentMode != CUSTOM || (currentMode == CUSTOM && customCol == 30)) {
            nextWidthSprite.setTexture(grayButtonsTexture);
        } else if (positionInBox(sf::Mouse::getPosition(window), nextWidthBox.getGlobalBounds())) {
            nextWidthSprite.setTexture(blueButtonsTexture);
        } else {
            nextWidthSprite.setTexture(blackButtonsTexture);
        }

        nextWidthSprite.setTextureRect(sf::IntRect(160, 0, 80, 80));
        nextWidthSprite.setPosition(centerPosition(nextWidthBox.getGlobalBounds(), nextWidthSprite.getGlobalBounds()));

        sf::RectangleShape dnextWidthBox(sf::Vector2f(80, 80));
        dnextWidthBox.setPosition(widthBox.getGlobalBounds().left + 520, 340);

        sf::Sprite dnextWidthSprite;
        if (currentMode != CUSTOM || (currentMode == CUSTOM && customCol == 30)) {
            dnextWidthSprite.setTexture(grayButtonsTexture);
        } else if (positionInBox(sf::Mouse::getPosition(window), dnextWidthBox.getGlobalBounds())) {
            dnextWidthSprite.setTexture(blueButtonsTexture);
        } else {
            dnextWidthSprite.setTexture(blackButtonsTexture);
        }

        dnextWidthSprite.setTextureRect(sf::IntRect(240, 0, 80, 80));
        dnextWidthSprite.setPosition(centerPosition(dnextWidthBox.getGlobalBounds(), dnextWidthSprite.getGlobalBounds()));

        // Height
        sf::Sprite heightBox(whiteBoxTexture);
        heightBox.setPosition((window.getSize().x - heightBox.getGlobalBounds().width) / 2, 450);

        sf::Text heightText("Height", font, 40);
        heightText.setFillColor(sf::Color::Black);
        heightText.setPosition(heightBox.getGlobalBounds().left + 20, 465);
        
        sf::RectangleShape dprevHeightBox(sf::Vector2f(80, 80));
        dprevHeightBox.setPosition(heightBox.getGlobalBounds().left + 180, 450);

        sf::Sprite dprevHeightSprite;
        if (currentMode != CUSTOM || (currentMode == CUSTOM && customRow == 2)) {
            dprevHeightSprite.setTexture(grayButtonsTexture);
        } else if (positionInBox(sf::Mouse::getPosition(window), dprevHeightBox.getGlobalBounds())) {
            dprevHeightSprite.setTexture(blueButtonsTexture);
        } else {
            dprevHeightSprite.setTexture(blackButtonsTexture);
        }

        dprevHeightSprite.setTextureRect(sf::IntRect(0, 0, 80, 80));
        dprevHeightSprite.setPosition(centerPosition(dprevHeightBox.getGlobalBounds(), dprevHeightSprite.getGlobalBounds()));

        sf::RectangleShape prevHeightBox(sf::Vector2f(80, 80));
        prevHeightBox.setPosition(heightBox.getGlobalBounds().left + 260, 450);

        sf::Sprite prevHeightSprite;
        if (currentMode != CUSTOM || (currentMode == CUSTOM && customRow == 2)) {
            prevHeightSprite.setTexture(grayButtonsTexture);
        } else if (positionInBox(sf::Mouse::getPosition(window), prevHeightBox.getGlobalBounds())) {
            prevHeightSprite.setTexture(blueButtonsTexture);
        } else {
            prevHeightSprite.setTexture(blackButtonsTexture);
        }

        prevHeightSprite.setTextureRect(sf::IntRect(80, 0, 80, 80));
        prevHeightSprite.setPosition(centerPosition(prevHeightBox.getGlobalBounds(), prevHeightSprite.getGlobalBounds()));

        sf::RectangleShape customHeightBox(sf::Vector2f(100, 80));
        customHeightBox.setPosition(heightBox.getGlobalBounds().left + 340, 450);

        sf::Text customHeightText("0", font, 40);
        customHeightText.setFillColor(sf::Color::Black);
        if (currentMode == BEGINNER) {
            customHeightText.setString("9");
        }  else if (currentMode == INTERMEDIATE) {
            customHeightText.setString("16");
        } else if (currentMode == EXPERT) {
            customHeightText.setString("16");
        } else {
            customHeightText.setString(std::to_string(customRow).c_str());
        }

        customHeightText.setPosition(customHeightBox.getPosition().x + (customHeightBox.getSize().x - customHeightText.getGlobalBounds().width) / 2, 465);

        sf::RectangleShape nextHeightBox(sf::Vector2f(80, 80));
        nextHeightBox.setPosition(heightBox.getGlobalBounds().left + 440, 450);

        sf::Sprite nextHeightSprite;
        if (currentMode != CUSTOM || (currentMode == CUSTOM && customRow == 16)) {
            nextHeightSprite.setTexture(grayButtonsTexture);
        }else if (positionInBox(sf::Mouse::getPosition(window), nextHeightBox.getGlobalBounds())) {
            nextHeightSprite.setTexture(blueButtonsTexture);
        } else {
            nextHeightSprite.setTexture(blackButtonsTexture);
        }

        nextHeightSprite.setTextureRect(sf::IntRect(160, 0, 80, 80));
        nextHeightSprite.setPosition(centerPosition(nextHeightBox.getGlobalBounds(), nextHeightSprite.getGlobalBounds()));

        sf::RectangleShape dnextHeightBox(sf::Vector2f(80, 80));
        dnextHeightBox.setPosition(heightBox.getGlobalBounds().left + 520, 450);

        sf::Sprite dnextHeightSprite;
        if (currentMode != CUSTOM || (currentMode == CUSTOM && customRow == 16)) {
            dnextHeightSprite.setTexture(grayButtonsTexture);
        } else if (positionInBox(sf::Mouse::getPosition(window), dnextHeightBox.getGlobalBounds())) {
            dnextHeightSprite.setTexture(blueButtonsTexture);
        } else {
            dnextHeightSprite.setTexture(blackButtonsTexture);
        }

        dnextHeightSprite.setTextureRect(sf::IntRect(240, 0, 80, 80));
        dnextHeightSprite.setPosition(centerPosition(dnextHeightBox.getGlobalBounds(), dnextHeightSprite.getGlobalBounds()));

        // Bombs
        sf::Sprite bombsBox(whiteBoxTexture);
        bombsBox.setPosition((window.getSize().x - bombsBox.getGlobalBounds().width) / 2, 560);

        sf::Text bombsText("Bombs", font, 40);
        bombsText.setFillColor(sf::Color::Black);
        bombsText.setPosition(bombsBox.getGlobalBounds().left + 20, 575);

        sf::RectangleShape dprevBombsBox(sf::Vector2f(80, 80));
        dprevBombsBox.setPosition(bombsBox.getGlobalBounds().left + 180, 560);

        sf::Sprite dprevBombsSprite;
        if (currentMode != CUSTOM || (currentMode == CUSTOM && customBombs == 1)) {
            dprevBombsSprite.setTexture(grayButtonsTexture);
        } else if (positionInBox(sf::Mouse::getPosition(window), dprevBombsBox.getGlobalBounds())) {
            dprevBombsSprite.setTexture(blueButtonsTexture);
        } else {
            dprevBombsSprite.setTexture(blackButtonsTexture);
        }

        dprevBombsSprite.setTextureRect(sf::IntRect(0, 0, 80, 80));
        dprevBombsSprite.setPosition(centerPosition(dprevBombsBox.getGlobalBounds(), dprevBombsSprite.getGlobalBounds()));

        sf::RectangleShape prevBombsBox(sf::Vector2f(80, 80));
        prevBombsBox.setPosition(bombsBox.getGlobalBounds().left + 260, 560);

        sf::Sprite prevBombsSprite;
        if (currentMode != CUSTOM || (currentMode == CUSTOM && customBombs == 1)) {
            prevBombsSprite.setTexture(grayButtonsTexture);
        } else if (positionInBox(sf::Mouse::getPosition(window), prevBombsBox.getGlobalBounds())) {
            prevBombsSprite.setTexture(blueButtonsTexture);
        } else {
            prevBombsSprite.setTexture(blackButtonsTexture);
        }

        prevBombsSprite.setTextureRect(sf::IntRect(80, 0, 80, 80));
        prevBombsSprite.setPosition(centerPosition(prevBombsBox.getGlobalBounds(), prevBombsSprite.getGlobalBounds()));

        sf::RectangleShape customBombsBox(sf::Vector2f(100, 80));
        customBombsBox.setPosition(bombsBox.getGlobalBounds().left + 340, 560);

        sf::Text customBombsText("0", font, 40);
        customBombsText.setFillColor(sf::Color::Black);
        if (currentMode == BEGINNER) {
            customBombsText.setString("10");
        } else if (currentMode == INTERMEDIATE) {
            customBombsText.setString("40");
        } else if (currentMode == EXPERT) { 
            customBombsText.setString("99");
        } else {
            customBombsText.setString(std::to_string(customBombs).c_str());
        }

        customBombsText.setPosition(customBombsBox.getPosition().x + (customBombsBox.getSize().x - customBombsText.getGlobalBounds().width) / 2, 575);

        sf::RectangleShape nextBombsBox(sf::Vector2f(80, 80));
        nextBombsBox.setPosition(bombsBox.getGlobalBounds().left + 440, 560);

        sf::Sprite nextBombsSprite;
        if (currentMode != CUSTOM || (currentMode == CUSTOM && customBombs == customRow * customCol / 2)) {
            nextBombsSprite.setTexture(grayButtonsTexture);
        } else if (positionInBox(sf::Mouse::getPosition(window), nextBombsBox.getGlobalBounds())) {
            nextBombsSprite.setTexture(blueButtonsTexture);
        } else {
            nextBombsSprite.setTexture(blackButtonsTexture);
        }

        nextBombsSprite.setTextureRect(sf::IntRect(160, 0, 80, 80));
        nextBombsSprite.setPosition(centerPosition(nextBombsBox.getGlobalBounds(), nextBombsSprite.getGlobalBounds()));

        sf::RectangleShape dnextBombsBox(sf::Vector2f(80, 80));
        dnextBombsBox.setPosition(bombsBox.getGlobalBounds().left + 520, 560);

        sf::Sprite dnextBombsSprite;
        if (currentMode != CUSTOM || (currentMode == CUSTOM && customBombs == customRow * customCol / 2)) {
            dnextBombsSprite.setTexture(grayButtonsTexture);
        } else if (positionInBox(sf::Mouse::getPosition(window), dnextBombsBox.getGlobalBounds())) {
            dnextBombsSprite.setTexture(blueButtonsTexture);
        } else {
            dnextBombsSprite.setTexture(blackButtonsTexture);
        }

        dnextBombsSprite.setTextureRect(sf::IntRect(240, 0, 80, 80));
        dnextBombsSprite.setPosition(centerPosition(dnextBombsBox.getGlobalBounds(), dnextBombsSprite.getGlobalBounds()));

        // Play
        sf::Sprite playBox(whiteBoxTexture);
        playBox.setPosition((window.getSize().x - playBox.getGlobalBounds().width) / 2, 670);

        sf::Text playText("Play", font, 40);
        playText.setFillColor(sf::Color::Black);
        playText.setPosition(playBox.getGlobalBounds().left + (playBox.getGlobalBounds().width - playText.getGlobalBounds().width) / 2, 685);

        if (positionInBox(sf::Mouse::getPosition(window), playBox.getGlobalBounds())) {
            playBox.setTexture(blueBoxTexture);
            playText.setFillColor(sf::Color::White);
        }

        window.clear();

        window.draw(titleBarBox);
        window.draw(titleBarText);
        window.draw(messageText);
        window.draw(closeButtonSprite);

        window.draw(backgroundSprite);
        
        window.draw(backButtonSprite);

        window.draw(newGameText);

        window.draw(modeBox);
        window.draw(modeText);
        window.draw(prevModeSprite);
        window.draw(nextModeSprite);

        window.draw(widthBox);
        window.draw(widthText);
        window.draw(dprevWidthSprite);
        window.draw(prevWidthSprite);
        window.draw(customWidthText);
        window.draw(nextWidthSprite);
        window.draw(dnextWidthSprite);
        

        window.draw(heightBox);
        window.draw(heightText);
        window.draw(dprevHeightSprite);
        window.draw(prevHeightSprite);
        window.draw(customHeightText);
        window.draw(nextHeightSprite);
        window.draw(dnextHeightSprite);

        window.draw(bombsBox);
        window.draw(bombsText);
        window.draw(dprevBombsSprite);
        window.draw(prevBombsSprite);
        window.draw(customBombsText);
        window.draw(nextBombsSprite);
        window.draw(dnextBombsSprite);

        window.draw(playBox);
        window.draw(playText);

        window.display();

        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
            case sf::Event::Closed:
                window.close();
                break;

            case sf::Event::MouseButtonPressed:
                if (event.mouseButton.button == sf::Mouse::Left) {
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

                    if (positionInBox(sf::Mouse::getPosition(window), backButtonSprite.getGlobalBounds())) {
                        currentScreen = GAMEMENU;
                        return;
                    }

                    if (positionInBox(sf::Mouse::getPosition(window), prevModeBox.getGlobalBounds())) {
                        if (currentMode == BEGINNER) {
                            currentMode = CUSTOM;
                        } else if (currentMode == INTERMEDIATE) {
                            currentMode = BEGINNER;
                        } else if (currentMode == EXPERT) {
                            currentMode = INTERMEDIATE;
                        } else {
                            currentMode = EXPERT;
                        }
                    }

                    if (positionInBox(sf::Mouse::getPosition(window), nextModeBox.getGlobalBounds())) {
                        if (currentMode == BEGINNER) {
                            currentMode = INTERMEDIATE;
                        } else if (currentMode == INTERMEDIATE) {
                            currentMode = EXPERT;
                        } else if (currentMode == EXPERT) {
                            currentMode = CUSTOM;
                        } else {
                            currentMode = BEGINNER;
                        }
                    }

                    if (positionInBox(sf::Mouse::getPosition(window), dprevWidthBox.getGlobalBounds())) {
                        if (currentMode == CUSTOM) {
                            customCol = std::max(customCol - 10, 2);
                            customBombs = std::min(customBombs, customRow * customCol / 2);
                        }
                    }

                    if (positionInBox(sf::Mouse::getPosition(window), prevWidthBox.getGlobalBounds())) {
                        if (currentMode == CUSTOM) {
                            customCol = std::max(customCol - 1, 2);
                            customBombs = std::min(customBombs, customRow * customCol / 2);
                        }
                    }

                    if (positionInBox(sf::Mouse::getPosition(window), nextWidthBox.getGlobalBounds())) {
                        if (currentMode == CUSTOM) {
                            customCol = std::min(customCol + 1, 30);
                        }
                    }

                    if (positionInBox(sf::Mouse::getPosition(window), dnextWidthBox.getGlobalBounds())) {
                        if (currentMode == CUSTOM) {
                            customCol = std::min(customCol + 10, 30);
                        }
                    }

                    if (positionInBox(sf::Mouse::getPosition(window), dprevHeightBox.getGlobalBounds())) {
                        if (currentMode == CUSTOM) {
                            customRow = std::max(customRow - 10, 2);
                            customBombs = std::min(customBombs, customRow * customCol / 2);
                        }
                    }

                    if (positionInBox(sf::Mouse::getPosition(window), prevHeightBox.getGlobalBounds())) {
                        if (currentMode == CUSTOM) {
                            customRow = std::max(customRow - 1, 2);
                            customBombs = std::min(customBombs, customRow * customCol / 2);
                        }
                    }

                    if (positionInBox(sf::Mouse::getPosition(window), nextHeightBox.getGlobalBounds())) {
                        if (currentMode == CUSTOM) {
                            customRow = std::min(customRow + 1, 16);
                        }
                    }

                    if (positionInBox(sf::Mouse::getPosition(window), dnextHeightBox.getGlobalBounds())) {
                        if (currentMode == CUSTOM) {
                            customRow = std::min(customRow + 10, 16);
                        }
                    }

                    if (positionInBox(sf::Mouse::getPosition(window), dprevBombsBox.getGlobalBounds())) {
                        if (currentMode == CUSTOM) {
                            customBombs = std::max(customBombs - 10, 1);
                        }
                    }

                    if (positionInBox(sf::Mouse::getPosition(window), prevBombsBox.getGlobalBounds())) {
                        if (currentMode == CUSTOM) {
                            customBombs = std::max(customBombs - 1, 1);
                        }
                    }

                    if (positionInBox(sf::Mouse::getPosition(window), nextBombsBox.getGlobalBounds())) {
                        if (currentMode == CUSTOM) {
                            customBombs = std::min(customBombs + 1, customRow * customCol / 2);
                        }
                    }

                    if (positionInBox(sf::Mouse::getPosition(window), dnextBombsBox.getGlobalBounds())) {
                        if (currentMode == CUSTOM) {
                            customBombs = std::min(customBombs + 10, customRow * customCol / 2);
                        }
                    }

                    if (positionInBox(sf::Mouse::getPosition(window), playBox.getGlobalBounds())) {
                        fs::remove("Data/Local/" + user.getUsername() + "/Save.txt");

                        mode = currentMode;
                        if (currentMode == BEGINNER) {
                            table = Table(9, 9, 10);
                        } else if (currentMode == INTERMEDIATE) {
                            table = Table(16, 16, 40);
                        } else if (currentMode == EXPERT) {
                            table = Table(16, 30, 99);
                        } else {
                            table = Table(customRow, customCol, customBombs);
                        }

                        currentScreen = MAINGAME;
                        return;
                    }

                    leftMouseButtonHoldingInTitleBar = false;
                }

                break;
            }
        }
    }
}