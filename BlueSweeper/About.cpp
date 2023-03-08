#include "Core.h"

void Core::about() {
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

    sf::Texture whiteBoxTexture;
    whiteBoxTexture.setSmooth(true);
    if (!whiteBoxTexture.loadFromFile("Images/WhiteBox824x400.png")) {
        window.close();
        return;
    }

    sf::Texture SFMLLogoTexture;
    SFMLLogoTexture.setSmooth(true);
    if (!SFMLLogoTexture.loadFromFile("Images/SFMLLogo.png")) {
        window.close();
        return;
    }

    sf::Texture BlueArchiveLogoTexture;
    BlueArchiveLogoTexture.setSmooth(true);
    if (!BlueArchiveLogoTexture.loadFromFile("Images/BlueArchiveLogo.png")) {
        window.close();
        return;
    }

    sf::Texture meLogoTexture;
    meLogoTexture.setSmooth(true);
    if (!meLogoTexture.loadFromFile("Images/meLogo.png")) {
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

        // Back
        sf::Sprite backButtonSprite(blackBackButtonTexture);
        backButtonSprite.setPosition(20, 52);

        if (positionInBox(sf::Mouse::getPosition(window), backButtonSprite.getGlobalBounds())) {
            backButtonSprite.setTexture(whiteBackButtonTexture);
        }

        // Logo
        sf::Sprite LogoSprite(logoTexture);
        LogoSprite.setPosition((window.getSize().x - LogoSprite.getGlobalBounds().width) / 2, 30);

        // Box
        sf::Sprite whiteBox(whiteBoxTexture);
        whiteBox.setPosition(100, 280);

        // Created by
        sf::Text createdByText("Created by", font, 40);
        createdByText.setFillColor(sf::Color::Black);
        createdByText.setPosition(120, 300);

        sf::Sprite meLogo(meLogoTexture);
        meLogo.setPosition(504, 300);

        // Supported by
        sf::Text supportedByText("Supported by", font, 40);
        supportedByText.setFillColor(sf::Color::Black);
        supportedByText.setPosition(120, 450);

        sf::Sprite SFMLLogo(SFMLLogoTexture);
        SFMLLogo.setPosition(504, 410);

        // Inspired by
        sf::Text inspiredByText("Inspired by", font, 40);
        inspiredByText.setFillColor(sf::Color::Black);
        inspiredByText.setPosition(120, 600);

        sf::Sprite BlueArchiveLogo(BlueArchiveLogoTexture);
        BlueArchiveLogo.setPosition(504, 550);

        window.clear();

        window.draw(titleBarBox);
        window.draw(titleBarText);
        window.draw(messageText);
        window.draw(closeButtonSprite);

        window.draw(backgroundSprite);

        window.draw(backButtonSprite);

        window.draw(LogoSprite);

        window.draw(whiteBox);

        window.draw(createdByText);
        window.draw(meLogo);

        window.draw(supportedByText);
        window.draw(SFMLLogo);

        window.draw(inspiredByText);
        window.draw(BlueArchiveLogo);

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

                    leftMouseButtonHoldingInTitleBar = false;
                }

                break;
            }
        }
    }
}