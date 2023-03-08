#include "Core.h"

void Core::settings() {
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

        // Settings
        sf::Text settingsText("Settings", font, 90);
        settingsText.setFillColor(sf::Color::Black);
        settingsText.setPosition((window.getSize().x - settingsText.getGlobalBounds().width) / 2, 90);

        // Profile
        sf::Sprite profileBox(whiteBoxTexture);
        profileBox.setPosition((window.getSize().x - profileBox.getGlobalBounds().width) / 2, 230);

        sf::Text profileText("Profile", font, 40);
        profileText.setFillColor(sf::Color::Black);
        profileText.setPosition(profileBox.getGlobalBounds().left + (profileBox.getGlobalBounds().width - profileText.getGlobalBounds().width) / 2, 245);

        if (positionInBox(sf::Mouse::getPosition(window), profileBox.getGlobalBounds())) {
            profileBox.setTexture(blueBoxTexture);
            profileText.setFillColor(sf::Color::White);
        }

        // Music
        sf::Sprite musicBox(whiteBoxTexture);
        musicBox.setPosition((window.getSize().x - musicBox.getGlobalBounds().width) / 2, 340);

        sf::Text musicText("Music", font, 40);
        musicText.setFillColor(sf::Color::Black);
        musicText.setPosition(musicBox.getGlobalBounds().left + 20, 355);

        sf::RectangleShape dprevMusicBox(sf::Vector2f(80, 80));
        dprevMusicBox.setPosition(musicBox.getGlobalBounds().left + 180, 340);

        sf::Sprite dprevMusicSprite;
        if (musicVolume == 0) {
            dprevMusicSprite.setTexture(grayButtonsTexture);
        } else if (positionInBox(sf::Mouse::getPosition(window), dprevMusicBox.getGlobalBounds())) {
            dprevMusicSprite.setTexture(blueButtonsTexture);
        } else {
            dprevMusicSprite.setTexture(blackButtonsTexture);
        }

        dprevMusicSprite.setTextureRect(sf::IntRect(0, 0, 80, 80));
        dprevMusicSprite.setPosition(centerPosition(dprevMusicBox.getGlobalBounds(), dprevMusicSprite.getGlobalBounds()));

        sf::RectangleShape prevMusicBox(sf::Vector2f(80, 80));
        prevMusicBox.setPosition(musicBox.getGlobalBounds().left + 260, 340);

        sf::Sprite prevMusicSprite;
        if (musicVolume == 0) {
            prevMusicSprite.setTexture(grayButtonsTexture);
        } else if (positionInBox(sf::Mouse::getPosition(window), prevMusicBox.getGlobalBounds())) {
            prevMusicSprite.setTexture(blueButtonsTexture);
        } else {
            prevMusicSprite.setTexture(blackButtonsTexture);
        }

        prevMusicSprite.setTextureRect(sf::IntRect(80, 0, 80, 80));
        prevMusicSprite.setPosition(centerPosition(prevMusicBox.getGlobalBounds(), prevMusicSprite.getGlobalBounds()));

        sf::RectangleShape customMusicBox(sf::Vector2f(100, 80));
        customMusicBox.setPosition(musicBox.getGlobalBounds().left + 340, 340);

        sf::Text customMusicText(std::to_string(musicVolume), font, 40);
        customMusicText.setFillColor(sf::Color::Black);
        customMusicText.setPosition(customMusicBox.getPosition().x + (customMusicBox.getSize().x - customMusicText.getGlobalBounds().width) / 2, 355);

        sf::RectangleShape nextMusicBox(sf::Vector2f(80, 80));
        nextMusicBox.setPosition(musicBox.getGlobalBounds().left + 440, 340);

        sf::Sprite nextMusicSprite;
        if (musicVolume == 100) {
            nextMusicSprite.setTexture(grayButtonsTexture);
        } else if (positionInBox(sf::Mouse::getPosition(window), nextMusicBox.getGlobalBounds())) {
            nextMusicSprite.setTexture(blueButtonsTexture);
        } else {
            nextMusicSprite.setTexture(blackButtonsTexture);
        }

        nextMusicSprite.setTextureRect(sf::IntRect(160, 0, 80, 80));
        nextMusicSprite.setPosition(centerPosition(nextMusicBox.getGlobalBounds(), nextMusicSprite.getGlobalBounds()));

        sf::RectangleShape dnextMusicBox(sf::Vector2f(80, 80));
        dnextMusicBox.setPosition(musicBox.getGlobalBounds().left + 520, 340);

        sf::Sprite dnextMusicSprite;
        if (musicVolume == 100) {
            dnextMusicSprite.setTexture(grayButtonsTexture);
        } else if (positionInBox(sf::Mouse::getPosition(window), dnextMusicBox.getGlobalBounds())) {
            dnextMusicSprite.setTexture(blueButtonsTexture);
        } else {
            dnextMusicSprite.setTexture(blackButtonsTexture);
        }

        dnextMusicSprite.setTextureRect(sf::IntRect(240, 0, 80, 80));
        dnextMusicSprite.setPosition(centerPosition(dnextMusicBox.getGlobalBounds(), dnextMusicSprite.getGlobalBounds()));

        // Sound
        sf::Sprite soundBox(whiteBoxTexture);
        soundBox.setPosition((window.getSize().x - soundBox.getGlobalBounds().width) / 2, 450);

        sf::Text soundText("Sound", font, 40);
        soundText.setFillColor(sf::Color::Black);
        soundText.setPosition(soundBox.getGlobalBounds().left + 20, 465);

        sf::RectangleShape dprevSoundBox(sf::Vector2f(80, 80));
        dprevSoundBox.setPosition(soundBox.getGlobalBounds().left + 180, 450);

        sf::Sprite dprevSoundSprite;
        if (soundVolume == 0) {
            dprevSoundSprite.setTexture(grayButtonsTexture);
        } else if (positionInBox(sf::Mouse::getPosition(window), dprevSoundBox.getGlobalBounds())) {
            dprevSoundSprite.setTexture(blueButtonsTexture);
        } else {
            dprevSoundSprite.setTexture(blackButtonsTexture);
        }

        dprevSoundSprite.setTextureRect(sf::IntRect(0, 0, 80, 80));
        dprevSoundSprite.setPosition(centerPosition(dprevSoundBox.getGlobalBounds(), dprevSoundSprite.getGlobalBounds()));

        sf::RectangleShape prevSoundBox(sf::Vector2f(80, 80));
        prevSoundBox.setPosition(soundBox.getGlobalBounds().left + 260, 450);

        sf::Sprite prevSoundSprite;
        if (soundVolume == 0) {
            prevSoundSprite.setTexture(grayButtonsTexture);
        } else if (positionInBox(sf::Mouse::getPosition(window), prevSoundBox.getGlobalBounds())) {
            prevSoundSprite.setTexture(blueButtonsTexture);
        } else {
            prevSoundSprite.setTexture(blackButtonsTexture);
        }

        prevSoundSprite.setTextureRect(sf::IntRect(80, 0, 80, 80));
        prevSoundSprite.setPosition(centerPosition(prevSoundBox.getGlobalBounds(), prevSoundSprite.getGlobalBounds()));

        sf::RectangleShape customSoundBox(sf::Vector2f(100, 80));
        customSoundBox.setPosition(soundBox.getGlobalBounds().left + 340, 450);

        sf::Text customSoundText(std::to_string(soundVolume), font, 40);
        customSoundText.setFillColor(sf::Color::Black);
        customSoundText.setPosition(customSoundBox.getPosition().x + (customSoundBox.getSize().x - customSoundText.getGlobalBounds().width) / 2, 465);

        sf::RectangleShape nextSoundBox(sf::Vector2f(80, 80));
        nextSoundBox.setPosition(soundBox.getGlobalBounds().left + 440, 450);

        sf::Sprite nextSoundSprite;
        if (soundVolume == 100) {
            nextSoundSprite.setTexture(grayButtonsTexture);
        } else if (positionInBox(sf::Mouse::getPosition(window), nextSoundBox.getGlobalBounds())) {
            nextSoundSprite.setTexture(blueButtonsTexture);
        } else {
            nextSoundSprite.setTexture(blackButtonsTexture);
        }

        nextSoundSprite.setTextureRect(sf::IntRect(160, 0, 80, 80));
        nextSoundSprite.setPosition(centerPosition(nextSoundBox.getGlobalBounds(), nextSoundSprite.getGlobalBounds()));

        sf::RectangleShape dnextSoundBox(sf::Vector2f(80, 80));
        dnextSoundBox.setPosition(soundBox.getGlobalBounds().left + 520, 450);
        
        sf::Sprite dnextSoundSprite;
        if (soundVolume == 100) {
            dnextSoundSprite.setTexture(grayButtonsTexture);
        } else if (positionInBox(sf::Mouse::getPosition(window), dnextSoundBox.getGlobalBounds())) {
            dnextSoundSprite.setTexture(blueButtonsTexture);
        } else {
            dnextSoundSprite.setTexture(blackButtonsTexture);
        }

        dnextSoundSprite.setTextureRect(sf::IntRect(240, 0, 80, 80));
        dnextSoundSprite.setPosition(centerPosition(dnextSoundBox.getGlobalBounds(), dnextSoundSprite.getGlobalBounds()));

        // Question mark
        sf::Sprite questionMarkBox(whiteBoxTexture);
        questionMarkBox.setPosition((window.getSize().x - questionMarkBox.getGlobalBounds().width) / 2, 560);

        sf::Text questionMarkText("Question mark", font, 40);
        questionMarkText.setFillColor(sf::Color::Black);
        questionMarkText.setPosition(questionMarkBox.getGlobalBounds().left + 20, 575);

        sf::Text questionMarkStatusText(enableQuestionMark ? ": ON" : ": OFF", font, 40);
        questionMarkStatusText.setFillColor(sf::Color::Black);
        questionMarkStatusText.setPosition(questionMarkBox.getGlobalBounds().left + 450, 575);

        if (positionInBox(sf::Mouse::getPosition(window), questionMarkBox.getGlobalBounds())) {
            questionMarkBox.setTexture(blueBoxTexture);
            questionMarkText.setFillColor(sf::Color::White);
            questionMarkStatusText.setFillColor(sf::Color::White);
        }

        // Question mark
        sf::Sprite cantWinModeBox(whiteBoxTexture);
        cantWinModeBox.setPosition((window.getSize().x - cantWinModeBox.getGlobalBounds().width) / 2, 670);

        sf::Text cantWinModeText("Don't, please", font, 40);
        cantWinModeText.setFillColor(sf::Color::Black);
        cantWinModeText.setPosition(cantWinModeBox.getGlobalBounds().left + 20, 685);

        sf::Text cantWinModeStatusText(enableCantWinMode ? ": ON" : ": OFF", font, 40);
        cantWinModeStatusText.setFillColor(sf::Color::Black);
        cantWinModeStatusText.setPosition(cantWinModeBox.getGlobalBounds().left + 450, 685);

        if (positionInBox(sf::Mouse::getPosition(window), cantWinModeBox.getGlobalBounds())) {
            cantWinModeBox.setTexture(blueBoxTexture);
            cantWinModeText.setFillColor(sf::Color::White);
            cantWinModeStatusText.setFillColor(sf::Color::White);
        }

        window.clear();

        window.draw(titleBarBox);
        window.draw(titleBarText);
        window.draw(messageText);
        window.draw(closeButtonSprite);

        window.draw(backgroundSprite);

        window.draw(backButtonSprite);

        window.draw(settingsText);

        window.draw(profileBox);
        window.draw(profileText);

        window.draw(musicBox);
        window.draw(musicText);
        window.draw(dprevMusicSprite);
        window.draw(prevMusicSprite);
        window.draw(customMusicText);
        window.draw(nextMusicSprite);
        window.draw(dnextMusicSprite);

        window.draw(soundBox);
        window.draw(soundText);
        window.draw(dprevSoundSprite);
        window.draw(prevSoundSprite);
        window.draw(customSoundText);
        window.draw(nextSoundSprite);
        window.draw(dnextSoundSprite);

        window.draw(questionMarkBox);
        window.draw(questionMarkText);
        window.draw(questionMarkStatusText);

        window.draw(cantWinModeBox);
        window.draw(cantWinModeText);
        window.draw(cantWinModeStatusText);

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

                    if (positionInBox(sf::Mouse::getPosition(window), profileBox.getGlobalBounds())) {
                        currentScreen = PROFILE;
                        return;
                    }

                    if (positionInBox(sf::Mouse::getPosition(window), dprevMusicBox.getGlobalBounds())) {
                        musicVolume = std::max(musicVolume - 20, 0);
                    }

                    if (positionInBox(sf::Mouse::getPosition(window), prevMusicBox.getGlobalBounds())) {
                        musicVolume = std::max(musicVolume - 5, 0);
                    }

                    if (positionInBox(sf::Mouse::getPosition(window), nextMusicBox.getGlobalBounds())) {
                        musicVolume = std::min(musicVolume + 5, 100);
                    }

                    if (positionInBox(sf::Mouse::getPosition(window), dnextMusicBox.getGlobalBounds())) {
                        musicVolume = std::min(musicVolume + 20, 100);
                    }

                    mainMusic.setVolume(musicVolume);

                    if (positionInBox(sf::Mouse::getPosition(window), dprevSoundBox.getGlobalBounds())) {
                        soundVolume = std::max(soundVolume - 20, 0);
                    }

                    if (positionInBox(sf::Mouse::getPosition(window), prevSoundBox.getGlobalBounds())) {
                        soundVolume = std::max(soundVolume - 5, 0);
                    }

                    if (positionInBox(sf::Mouse::getPosition(window), nextSoundBox.getGlobalBounds())) {
                        soundVolume = std::min(soundVolume + 5, 100);
                    }

                    if (positionInBox(sf::Mouse::getPosition(window), dnextSoundBox.getGlobalBounds())) {
                        soundVolume = std::min(soundVolume + 20, 100);
                    }

                    if (positionInBox(sf::Mouse::getPosition(window), questionMarkBox.getGlobalBounds())) {
                        messageText.setString("Sorry, sensei. Question mark is unavailable");
                        messageText.setFillColor(sf::Color::Black);
                        messageText.setPosition((window.getSize().x - messageText.getGlobalBounds().width) / 2, 2);
                        messageClock.restart();
                    }

                    if (positionInBox(sf::Mouse::getPosition(window), cantWinModeBox.getGlobalBounds())) {
                        enableCantWinMode ^= true;
                    }

                    leftMouseButtonHoldingInTitleBar = false;
                }

                break;
            }
        }
    }
}