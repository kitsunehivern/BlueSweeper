#include "Core.h"

Core::Core() {
}

bool Core::positionInBox(sf::Vector2i position, sf::FloatRect box) {
    return box.left < position.x && position.x < box.left + box.width && box.top < position.y && position.y < box.top + box.height;
}

sf::Vector2f Core::centerPosition(sf::FloatRect outBound, sf::FloatRect inBound) {
    return sf::Vector2f(outBound.left + (outBound.width - inBound.width) / 2, outBound.top + (outBound.height - inBound.height) / 2);
}

void Core::run() {
    user = User("", "");

    window.create(sf::VideoMode(1024, 800), "BlueSweeper", sf::Style::None);
    window.setFramerateLimit(60);
    
    backgroundTexture.setSmooth(true);
    if (!backgroundTexture.loadFromFile("Images/Background.png")) {
        window.close();
        return;
    }
    
    logoTexture.setSmooth(true);
    if (!logoTexture.loadFromFile("Images/Logo.png")) {
        window.close();
        return;
    }

    musicVolume = soundVolume = 50;
    
    mainMusic.setLoop(true);
    mainMusic.setVolume(musicVolume);
    if (!mainMusic.openFromFile("Musics/Midsummer_Cat.ogg")) {
        window.close();
        return;
    }
     
    if (!font.loadFromFile("Fonts/hyperspace-race-expanded-heavy-italic.otf")) {
        return;
    }

    messageText.setFont(font);
    messageText.setCharacterSize(20);

    auto getGreetings = []() -> std::string {
        time_t rawDate;
        struct tm currentTime;
        time(&rawDate);
        localtime_s(&currentTime, &rawDate);

        if (5 <= currentTime.tm_hour && currentTime.tm_hour < 12) {
            return "Good morning";
        }

        if (12 <= currentTime.tm_hour && currentTime.tm_hour < 18) {
            return "Good afternoon";
        }

        return "Good evening";
    };

    messageText.setString(getGreetings() + ", sensei. You are now in guest mode");
    messageText.setFillColor(sf::Color::Black);
    messageText.setPosition((window.getSize().x - messageText.getGlobalBounds().width) / 2, 2);
    messageClock.restart();

    firstMove = false;
    numFrame = 0, posBombX = posBombY = -1;
    continueUsed = false;

    enableQuestionMark = enableCantWinMode = false;

    currentScreen = GAMEMENU;
    while (window.isOpen()) {
        switch (currentScreen) {
        case GAMEMENU:
            gameMenu();
            break;

        case PROFILE:
            profile();
            break;

        case LOGIN:
            logIn();
            break;

        case SIGNUP:
            signUp();
            break;

        case CHANGEPASSWORD:
            changePassword();
            break;

        case NEWGAME:
            newGame();
            break;

        case MAINGAME:
            mainGame();
            break;

        case RANKING:
            ranking();
            break;

        case SETTINGS:
            settings();
            break;

        case ABOUT:
            about();
            break;
        }
    }

    fs::remove("Data/Local/Save.txt");
}