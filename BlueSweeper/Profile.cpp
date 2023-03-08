#include "Core.h"

void Core::profile() {
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

    bool isGuest = (user.getUsername().empty());
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
        closeButtonSprite.setPosition(960, 0);

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

        // Profile
        sf::Text profileText("Profile", font, 90);
        profileText.setFillColor(sf::Color::Black);
        profileText.setPosition((window.getSize().x - profileText.getGlobalBounds().width) / 2, 90);

        // Log in or Change password
        sf::Sprite firstBox(whiteBoxTexture);
        firstBox.setPosition((window.getSize().x - firstBox.getGlobalBounds().width) / 2, 350);

        sf::Text firstText(isGuest ? "Log in" : "New password", font, 40);
        firstText.setFillColor(sf::Color::Black);
        firstText.setPosition(firstBox.getGlobalBounds().left + (firstBox.getGlobalBounds().width - firstText.getGlobalBounds().width) / 2, 365);

        if (positionInBox(sf::Mouse::getPosition(window), firstBox.getGlobalBounds())) {
            firstBox.setTexture(blueBoxTexture);
            firstText.setFillColor(sf::Color::White);
        }

        // Sign in or Log out
        sf::Sprite secondBox(whiteBoxTexture);
        secondBox.setPosition((window.getSize().x - secondBox.getGlobalBounds().width) / 2, 460);

        sf::Text secondText(isGuest ? "Sign up" : "Log out", font, 40);
        secondText.setFillColor(sf::Color::Black);
        secondText.setPosition(secondBox.getGlobalBounds().left + (secondBox.getGlobalBounds().width - secondText.getGlobalBounds().width) / 2, 475);

        if (positionInBox(sf::Mouse::getPosition(window), secondBox.getGlobalBounds())) {
            secondBox.setTexture(blueBoxTexture);
            secondText.setFillColor(sf::Color::White);
        }

        window.clear();

        window.draw(titleBarBox);
        window.draw(titleBarText);
        window.draw(messageText);
        window.draw(closeButtonSprite);

        window.draw(backgroundSprite);

        window.draw(backButtonSprite);

        window.draw(profileText);

        window.draw(firstBox);
        window.draw(firstText);

        window.draw(secondBox);
        window.draw(secondText);

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
                        currentScreen = SETTINGS;
                        return;
                    }

                    if (positionInBox(sf::Mouse::getPosition(window), firstBox.getGlobalBounds())) {
                        if (isGuest) {
                            currentScreen = LOGIN;
                            return;
                        } else {
                            currentScreen = CHANGEPASSWORD;
                            return;
                        }
                    }

                    if (positionInBox(sf::Mouse::getPosition(window), secondBox.getGlobalBounds())) {
                        if (isGuest) {
                            currentScreen = SIGNUP;
                            return;
                        } else {
                            messageText.setString("Goodbye, " + user.getUsername() + " sensei. See you next time");
                            messageText.setFillColor(sf::Color::Black);
                            messageText.setPosition((window.getSize().x - messageText.getGlobalBounds().width) / 2, 2);
                            messageClock.restart();

                            user = User("", "");
                            currentScreen = GAMEMENU;
                            return;
                        }
                    }

                    leftMouseButtonHoldingInTitleBar = false;
                }

                break;
            }
        }
    }
}