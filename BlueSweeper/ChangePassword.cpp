#include "Core.h"

void Core::changePassword() {
#define NONE        0
#define OLDPASSWORD 1
#define NEWPASSWORD 2

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
    int currentText = OLDPASSWORD;
    std::string oldPassword, newPassword;
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

        // Change password
        sf::Text signInText("New password", font, 90);
        signInText.setFillColor(sf::Color::Black);
        signInText.setPosition((window.getSize().x - signInText.getGlobalBounds().width) / 2, 80);

        // Old password
        sf::Sprite oldPasswordBox(whiteBoxTexture);
        oldPasswordBox.setPosition((window.getSize().x - oldPasswordBox.getGlobalBounds().width) / 2, 300);

        sf::Text oldPasswordText(oldPassword.empty() ? "Old password" : std::string(oldPassword.size(), '*'), font, 40);
        oldPasswordText.setFillColor(oldPassword.empty() ? sf::Color(169, 169, 169) : sf::Color::Black);
        oldPasswordText.setPosition(oldPasswordBox.getGlobalBounds().left + (oldPasswordBox.getGlobalBounds().width - oldPasswordText.getGlobalBounds().width) / 2, 315);

        if (positionInBox(sf::Mouse::getPosition(window), oldPasswordBox.getGlobalBounds())) {
            oldPasswordBox.setTexture(blueBoxTexture);
            oldPasswordText.setFillColor(oldPassword.empty() ? sf::Color(169, 169, 169) : sf::Color::White);
        }

        // New password
        sf::Sprite newPasswordBox(whiteBoxTexture);
        newPasswordBox.setPosition((window.getSize().x - newPasswordBox.getGlobalBounds().width) / 2, 410);

        sf::Text newPasswordText(newPassword.empty() ? "New password" : std::string(newPassword.size(), '*'), font, 40);
        newPasswordText.setFillColor(newPassword.empty() ? sf::Color(169, 169, 169) : sf::Color::Black);
        newPasswordText.setPosition(newPasswordBox.getGlobalBounds().left + (newPasswordBox.getGlobalBounds().width - newPasswordText.getGlobalBounds().width) / 2, 425);

        if (positionInBox(sf::Mouse::getPosition(window), newPasswordBox.getGlobalBounds())) {
            newPasswordBox.setTexture(blueBoxTexture);
            newPasswordText.setFillColor(newPassword.empty() ? sf::Color(169, 169, 169) : sf::Color::White);
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

        window.draw(signInText);

        window.draw(oldPasswordBox);
        window.draw(oldPasswordText);

        window.draw(newPasswordBox);
        window.draw(newPasswordText);

        window.draw(confirmBox);
        window.draw(confirmText);

        bool valid = true;
        std::string tmpMessage;
        if (oldPassword.empty()) {
            tmpMessage = "Old password cannot be empty, sensei";
            valid = false;
        }

        if (valid && !oldPassword.empty() && oldPassword != user.getPassword()) {
            tmpMessage = "Old password is invalid, sensei";
            valid = false;
        }

        if (valid && newPassword.empty()) {
            tmpMessage = "New password cannot be empty, sensei";
            valid = false;
        }

        if (insertionClock.getElapsedTime() > sf::seconds(1.f)) {
            insertionClock.restart();
        }

        if (currentText != NONE && insertionClock.getElapsedTime() < sf::seconds(0.5f)) {
            sf::RectangleShape insertionPoint(sf::Vector2f(2, oldPasswordText.getCharacterSize()));
            insertionPoint.setFillColor(sf::Color::Black);

            if (currentText == OLDPASSWORD) {
                if (positionInBox(sf::Mouse::getPosition(window), oldPasswordBox.getGlobalBounds())) {
                    insertionPoint.setFillColor(sf::Color::White);
                }

                if (oldPassword.empty()) {
                    insertionPoint.setPosition(oldPasswordBox.getGlobalBounds().left + oldPasswordBox.getGlobalBounds().width / 2, oldPasswordBox.getGlobalBounds().top + (oldPasswordBox.getGlobalBounds().height - insertionPoint.getGlobalBounds().height) / 2);
                } else {
                    insertionPoint.setPosition(oldPasswordText.getGlobalBounds().left + oldPasswordText.getGlobalBounds().width, oldPasswordBox.getGlobalBounds().top + (oldPasswordBox.getGlobalBounds().height - insertionPoint.getGlobalBounds().height) / 2);            
                }
            }

            if (currentText == NEWPASSWORD) {
                if (positionInBox(sf::Mouse::getPosition(window), newPasswordBox.getGlobalBounds())) {
                    insertionPoint.setFillColor(sf::Color::White);
                }

                if (newPassword.empty()) {
                    insertionPoint.setPosition(newPasswordBox.getGlobalBounds().left + newPasswordBox.getGlobalBounds().width / 2, newPasswordBox.getGlobalBounds().top + (newPasswordBox.getGlobalBounds().height - insertionPoint.getGlobalBounds().height) / 2);
                } else {
                    insertionPoint.setPosition(newPasswordText.getGlobalBounds().left + newPasswordText.getGlobalBounds().width, newPasswordBox.getGlobalBounds().top + (newPasswordBox.getGlobalBounds().height - insertionPoint.getGlobalBounds().height) / 2);            
                }
            }

            window.draw(insertionPoint);
        }

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

                    if (positionInBox(sf::Mouse::getPosition(window), oldPasswordBox.getGlobalBounds())) {
                        insertionClock.restart();
                        currentText = OLDPASSWORD;
                    } else if (positionInBox(sf::Mouse::getPosition(window), newPasswordBox.getGlobalBounds())) {
                        insertionClock.restart();
                        currentText = NEWPASSWORD;
                    } else {
                        currentText = NONE;
                    }

                    if (positionInBox(sf::Mouse::getPosition(window), confirmBox.getGlobalBounds())) {
                        if (valid) {
                            messageText.setString("Your password was changed, sensei");
                            messageText.setFillColor(sf::Color::Black);
                            messageText.setPosition((window.getSize().x - messageText.getGlobalBounds().width) / 2, 2);
                            messageClock.restart();

                            std::string usernam = user.getUsername();
                            std::ofstream fout(("Data/Local/" + usernam + "/Password.txt").c_str());
                            fout << newPassword;
                            fout.close();

                            user = User(usernam, newPassword);
                            currentScreen = PROFILE;
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
                    if (currentText == OLDPASSWORD) {
                        if (oldPassword.size() < 20) {
                            oldPassword.push_back(character);
                        }
                    } else if (currentText == NEWPASSWORD) {
                        if (newPassword.size() < 20) {
                            newPassword.push_back(character);
                        }
                    }
                } else if (event.key.code == 59) { // Backspace
                    if (currentText == OLDPASSWORD) {
                        if (!oldPassword.empty()) {
                            oldPassword.pop_back();
                        }
                    } else if (currentText == NEWPASSWORD) {
                        if (!newPassword.empty()) {
                            newPassword.pop_back();
                        }
                    }
                }

                break;
            }
        }
    }

#undef NONE
#undef OLDPASSWORD
#undef NEWPASSWORD
}