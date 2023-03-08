#include "Core.h"

void Core::logIn() {
#define NONE     0
#define USERNAME 1
#define PASSWORD 2

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

    sf::Clock insertionClock;
    int currentText = USERNAME;
    std::string username, password;
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

        // Log in
        sf::Text logInText("Log in", font, 90);
        logInText.setFillColor(sf::Color::Black);
        logInText.setPosition((window.getSize().x - logInText.getGlobalBounds().width) / 2, 90);

        // Username
        sf::Sprite usernameBox(whiteBoxTexture);
        usernameBox.setPosition((window.getSize().x - usernameBox.getGlobalBounds().width) / 2, 300);

        sf::Text usernameText(username.empty() ? "Username" : username, font, 40);
        usernameText.setFillColor(username.empty() ? sf::Color(169, 169, 169) : sf::Color::Black);
        usernameText.setPosition(usernameBox.getGlobalBounds().left + (usernameBox.getGlobalBounds().width - usernameText.getGlobalBounds().width) / 2, 315);

        if (positionInBox(sf::Mouse::getPosition(window), usernameBox.getGlobalBounds())) {
            usernameBox.setTexture(blueBoxTexture);
            usernameText.setFillColor(username.empty() ? sf::Color(169, 169, 169) : sf::Color::White);
        }

        // Password
        sf::Sprite passwordBox(whiteBoxTexture);
        passwordBox.setPosition((window.getSize().x - passwordBox.getGlobalBounds().width) / 2, 410);

        sf::Text passwordText(password.empty() ? "Password" : std::string(password.size(), '*'), font, 40);
        passwordText.setFillColor(password.empty() ? sf::Color(169, 169, 169) : sf::Color::Black);
        passwordText.setPosition(passwordBox.getGlobalBounds().left + (passwordBox.getGlobalBounds().width - passwordText.getGlobalBounds().width) / 2, 425);

        if (positionInBox(sf::Mouse::getPosition(window), passwordBox.getGlobalBounds())) {
            passwordBox.setTexture(blueBoxTexture);
            passwordText.setFillColor(password.empty() ? sf::Color(169, 169, 169) : sf::Color::White);
        }

        // Confirm
        sf::Sprite confirmBox(whiteBoxTexture);
        confirmBox.setPosition((window.getSize().x - confirmBox.getGlobalBounds().width) / 2, 520);

        sf::Text confirmText("Confirm", font, 40);
        confirmText.setFillColor(sf::Color::Black);
        confirmText.setPosition(confirmBox.getGlobalBounds().left + (confirmBox.getGlobalBounds().width - confirmText.getGlobalBounds().width) / 2, 535);

        if (positionInBox(sf::Mouse::getPosition(window), confirmBox.getGlobalBounds())) {
            confirmBox.setTexture(blueBoxTexture);
            confirmText.setFillColor(sf::Color::White);
        }

        window.clear();

        window.draw(titleBarBox);
        window.draw(titleBarText);
        window.draw(messageText);
        window.draw(closeButtonSprite);

        window.draw(backgroundSprite);

        window.draw(backButtonSprite);

        window.draw(logInText);

        window.draw(usernameBox);
        window.draw(usernameText);

        window.draw(passwordBox);
        window.draw(passwordText);

        bool valid = true;
        std::string tmpMessage;
        if (username.empty()) {
            tmpMessage = "Username cannot be empty, sensei";
            valid = false;
        }

        if (valid && !fs::exists("Data/Local/" + username)) {
            tmpMessage = "Username is invalid, sensei";
            valid = false;
        }

        if (valid && password.empty()) {
            tmpMessage = "Password cannot be empty, sensei";
            valid = false;
        }

        if (valid && !password.empty()) {
            std::ifstream finp(("Data/Local/" + username + "/Password.txt").c_str());
            std::string validPassword;
            finp >> validPassword;
            finp.close();

            if (password != validPassword) {
                valid = false;
                tmpMessage = "Password is invalid, sensei";
            }            
        }

        if (insertionClock.getElapsedTime() > sf::seconds(1.f)) {
            insertionClock.restart();
        }

        if (currentText != NONE && insertionClock.getElapsedTime() < sf::seconds(0.5f)) {
            sf::RectangleShape insertionPoint(sf::Vector2f(2, usernameText.getCharacterSize()));
            insertionPoint.setFillColor(sf::Color::Black);

            if (currentText == USERNAME) {
                if (positionInBox(sf::Mouse::getPosition(window), usernameBox.getGlobalBounds())) {
                    insertionPoint.setFillColor(sf::Color::White);
                }

                if (username.empty()) {
                    insertionPoint.setPosition(usernameBox.getGlobalBounds().left + usernameBox.getGlobalBounds().width / 2, usernameBox.getGlobalBounds().top + (usernameBox.getGlobalBounds().height - insertionPoint.getGlobalBounds().height) / 2);
                } else {
                    insertionPoint.setPosition(usernameText.getGlobalBounds().left + usernameText.getGlobalBounds().width, usernameBox.getGlobalBounds().top + (usernameBox.getGlobalBounds().height - insertionPoint.getGlobalBounds().height) / 2);            
                }
            }

            if (currentText == PASSWORD) {
                if (positionInBox(sf::Mouse::getPosition(window), passwordBox.getGlobalBounds())) {
                    insertionPoint.setFillColor(sf::Color::White);
                }

                if (password.empty()) {
                    insertionPoint.setPosition(passwordBox.getGlobalBounds().left + passwordBox.getGlobalBounds().width / 2, passwordBox.getGlobalBounds().top + (passwordBox.getGlobalBounds().height - insertionPoint.getGlobalBounds().height) / 2);
                } else {
                    insertionPoint.setPosition(passwordText.getGlobalBounds().left + passwordText.getGlobalBounds().width, passwordBox.getGlobalBounds().top + (passwordBox.getGlobalBounds().height - insertionPoint.getGlobalBounds().height) / 2);            
                }
            }

            window.draw(insertionPoint);
        }

        window.draw(confirmBox);
        window.draw(confirmText);

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
                        currentScreen = PROFILE;
                        return;
                    }

                    if (positionInBox(sf::Mouse::getPosition(window), usernameBox.getGlobalBounds())) {
                        insertionClock.restart();
                        currentText = USERNAME;
                    } else if (positionInBox(sf::Mouse::getPosition(window), passwordBox.getGlobalBounds())) {
                        insertionClock.restart();
                        currentText = PASSWORD;
                    } else {
                        currentText = NONE;
                    }

                    if (positionInBox(sf::Mouse::getPosition(window), confirmBox.getGlobalBounds())) {
                        if (valid) {
                            messageText.setString("Welcome back, " + username + " sensei");
                            messageText.setFillColor(sf::Color::Black);
                            messageText.setPosition((window.getSize().x - messageText.getGlobalBounds().width) / 2, 2);
                            messageClock.restart();

                            fs::remove("Data/Local/Save.txt");

                            user = User(username, password);
                            currentScreen = GAMEMENU;
                            return;
                        }

                        messageText.setString(tmpMessage);
                        messageText.setFillColor(sf::Color::Black);
                        messageText.setPosition((window.getSize().x - messageText.getGlobalBounds().width) / 2, 2);
                        messageClock.restart();
                    }

                    leftMouseButtonHoldingInTitleBar = false;
                }

                break;

            case sf::Event::KeyPressed:
                if (0 <= event.key.code && event.key.code <= 35) { // From A to Z and from 0 to 9
                    char character = event.key.code + (event.key.code <= 25 ? 'A' : '0' - 26);
                    if (currentText == USERNAME) {
                        if (username.size() < 10) {
                            username.push_back(character);
                        }
                    } else if (currentText == PASSWORD) {
                        if (password.size() < 20) {
                            password.push_back(character);
                        }
                    }
                } else if (event.key.code == 59) { // Backspace
                    if (currentText == USERNAME) {
                        if (!username.empty()) {
                            username.pop_back();
                        }
                    } else if (currentText == PASSWORD) {
                        if (!password.empty()) {
                            password.pop_back();
                        }
                    }
                }

                break;
            }
        }
    }

#undef NONE
#undef USERNAME
#undef PASSWORD
}