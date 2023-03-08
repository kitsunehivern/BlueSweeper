#include "Core.h"

void Core::updateLocalRanking(int newTime) {
    if (user.getUsername().empty() || mode == CUSTOM) {
        return;
    }

    std::string strMode;
    if (mode == BEGINNER) {
        strMode = "Beginner";
    } else if (mode == INTERMEDIATE) {
        strMode = "Intermediate";
    } else {
        strMode = "Expert";
    }
    
    std::vector <std::vector <std::string> > ranking;
    if (fs::exists("Data/Local/" + user.getUsername() + "/" + strMode + "Ranking.txt")) {
        std::ifstream fin;
        fin.open("Data/Local/" + user.getUsername() + "/" + strMode + "Ranking.txt");
        
        int size;
        fin >> size;

        while (size--) {
            std::string username, time, date;
            fin >> username >> time >> date;

            ranking.push_back({username, time, date});
        }

        fin.close();
    }

    time_t rawDate;
    struct tm currentDate;
    time(&rawDate);
    localtime_s(&currentDate, &rawDate);

    auto formatNumber = [](int number, int size) -> std::string {
        std::string res = std::to_string(number);
        res = std::string(size - res.size(), '0') + res;
        return res;
    };

    ranking.push_back({user.getUsername(), std::to_string(newTime), formatNumber(currentDate.tm_mday, 2) + "/" + formatNumber(currentDate.tm_mon + 1, 2) + "/" + formatNumber(1900 + currentDate.tm_year, 4)});

    for (int i = ranking.size() - 1; i >= 1; i--) {
        if (std::stoi(ranking[i][1]) < std::stoi(ranking[i - 1][1])) {
            std::swap(ranking[i], ranking[i - 1]);
        }
    }

    if (ranking.size() > 10) {
        ranking.pop_back();
    }

    std::ofstream fout;
    fout.open("Data/Local/" + user.getUsername() + "/" + strMode + "Ranking.txt");

    fout << ranking.size() << "\n";
    for (int i = 0; i < ranking.size(); i++) {
        fout << ranking[i][0] << "\t\t" << ranking[i][1] << "\t" << ranking[i][2] << "\n";
    }

    fout.close();
}

void Core::updateGlobalRanking(int newTime) {
    if (user.getUsername().empty() || mode == CUSTOM) {
        return;
    }

    std::string strMode;
    if (mode == BEGINNER) {
        strMode = "Beginner";
    } else if (mode == INTERMEDIATE) {
        strMode = "Intermediate";
    } else {
        strMode = "Expert";
    }

    std::vector <std::vector <std::string> > ranking;
    if (fs::exists("Data/Global/" + strMode + "Ranking.txt")) {
        std::ifstream fin;
        fin.open("Data/Global/" + strMode + "Ranking.txt");

        int size;
        fin >> size;

        while (size--) {
            std::string username, time, date;
            fin >> username >> time >> date;

            ranking.push_back({username, time, date});
        }

        fin.close();
    }

    time_t rawDate;
    struct tm currentDate;
    time(&rawDate);
    localtime_s(&currentDate, &rawDate);

    auto formatNumber = [](int number, int size) -> std::string {
        std::string res = std::to_string(number);
        res = std::string(size - res.size(), '0') + res;
        return res;
    };

    ranking.push_back({user.getUsername(), std::to_string(newTime), formatNumber(currentDate.tm_mday, 2) + "/" + formatNumber(currentDate.tm_mon + 1, 2) + "/" + formatNumber(1900 + currentDate.tm_year, 4)});

    for (int i = ranking.size() - 1; i >= 1; i--) {
        if (std::stoi(ranking[i][1]) < std::stoi(ranking[i - 1][1])) {
            std::swap(ranking[i], ranking[i - 1]);
        }
    }

    bool appeared = false;
    for (int i = 0; i < ranking.size(); i++) {
        if (ranking[i][0] == user.getUsername()) {
            if (!appeared) {
                appeared = true;
            } else {
                ranking.erase(ranking.begin() + i);
                break;
            }
        }
    } 

    if (ranking.size() > 10) {
        ranking.pop_back();
    }

    std::ofstream fout;
    fout.open("Data/Global/" + strMode + "Ranking.txt");

    fout << ranking.size() << "\n";
    for (int i = 0; i < ranking.size(); i++) {
        fout << ranking[i][0] << "\t\t" << ranking[i][1] << "\t" << ranking[i][2] << "\n";
    }

    fout.close();
}

void Core::ranking() {
#define LOCAL  0
#define GLOBAL 1

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

    sf::Texture whiteBox450x80Texture;
    whiteBox450x80Texture.setSmooth(true);
    if (!whiteBox450x80Texture.loadFromFile("Images/WhiteBox450x80.png")) {
        window.close();
        return;
    }

    sf::Texture whiteLeftBox350x80Texture;
    whiteLeftBox350x80Texture.setSmooth(true);
    if (!whiteLeftBox350x80Texture.loadFromFile("Images/WhiteLeftBox350x80.png")) {
        window.close();
        return;
    }

    sf::Texture blueLeftBox350x80Texture;
    blueLeftBox350x80Texture.setSmooth(true);
    if (!blueLeftBox350x80Texture.loadFromFile("Images/BlueLeftBox350x80.png")) {
        window.close();
        return;
    }

    sf::Texture whiteRightBox350x80Texture;
    whiteRightBox350x80Texture.setSmooth(true);
    if (!whiteRightBox350x80Texture.loadFromFile("Images/WhiteRightBox350x80.png")) {
        window.close();
        return;
    }

    sf::Texture blueRightBox350x80Texture;
    blueRightBox350x80Texture.setSmooth(true);
    if (!blueRightBox350x80Texture.loadFromFile("Images/BlueRightBox350x80.png")) {
        window.close();
        return;
    }

    sf::Texture whiteBox824x40Texture;
    whiteBox824x40Texture.setSmooth(true);
    if (!whiteBox824x40Texture.loadFromFile("Images/WhiteBox824x40.png")) {
        window.close();
        return;
    }

    sf::Texture blueBox824x40Texture;
    blueBox824x40Texture.setSmooth(true);
    if (!blueBox824x40Texture.loadFromFile("Images/BlueBox824x40.png")) {
        window.close();
        return;
    }

    auto inputRanking = [](std::vector <std::vector <std::string> > &ranking, std::string path) -> void {
        ranking.assign(10, std::vector <std::string> (3));

        if (!fs::exists(path)) {
            return;
        }

        std::ifstream fin;
        fin.open(path);

        int size;
        fin >> size;

        for (int i = 0; i < size; i++) {
            std::string username, time, date;
            fin >> username >> time >> date;

            ranking[i] = {username, time, date};
        }

        fin.close();
    };

    std::vector <std::vector <std::string> > localBeginnerRanking, localIntermediateRanking, localExpertRanking;
    inputRanking(localBeginnerRanking, "Data/Local/" + user.getUsername() + "/BeginnerRanking.txt");
    inputRanking(localIntermediateRanking, "Data/Local/" + user.getUsername() + "/IntermediateRanking.txt");
    inputRanking(localExpertRanking, "Data/Local/" + user.getUsername() + "/ExpertRanking.txt");

    std::vector <std::vector <std::string> > globalBeginnerRanking, globalIntermediateRanking, globalExpertRanking;
    inputRanking(globalBeginnerRanking, "Data/Global/BeginnerRanking.txt");
    inputRanking(globalIntermediateRanking, "Data/Global/IntermediateRanking.txt");
    inputRanking(globalExpertRanking, "Data/Global/ExpertRanking.txt");
	
    int currentMode = BEGINNER;
    bool leftMouseButtonHoldingInTitleBar = false;
    int distanceX = 0, distanceY = 0;
    int currentRanking = GLOBAL;
    std::vector <std::vector <std::string> > currentData;
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

        // Ranking
        sf::Text rankingText("Ranking", font, 90);
        rankingText.setFillColor(sf::Color::Black);
        rankingText.setPosition((window.getSize().x - rankingText.getGlobalBounds().width) / 2, 90);

        // Mode
        sf::Sprite modeBox(whiteBox450x80Texture);
        modeBox.setPosition(100, 220);

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
        }

        modeText.setPosition(modeBox.getGlobalBounds().left + (modeBox.getGlobalBounds().width - modeText.getGlobalBounds().width) / 2, 235);

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

        // Local ranking
        sf::Sprite localRankingBox(whiteLeftBox350x80Texture);
        localRankingBox.setPosition(574, 220);

        sf::Text localRankingText("Local", font, 40);
        localRankingText.setFillColor(sf::Color::Black);
        localRankingText.setPosition(600, 235);

        if (currentRanking == LOCAL || positionInBox(sf::Mouse::getPosition(window), localRankingBox.getGlobalBounds())) {
            localRankingBox.setTexture(blueLeftBox350x80Texture);
            localRankingText.setFillColor(sf::Color::White);
        }

        // Global ranking
        sf::Sprite globalRankingBox(whiteRightBox350x80Texture);
        globalRankingBox.setPosition(724, 220);

        sf::Text globalRankingText("Global", font, 40);
        globalRankingText.setFillColor(sf::Color::Black);
        globalRankingText.setPosition(760, 235);

        if (currentRanking == GLOBAL || positionInBox(sf::Mouse::getPosition(window), globalRankingBox.getGlobalBounds())) {
            globalRankingBox.setTexture(blueRightBox350x80Texture);
            globalRankingText.setFillColor(sf::Color::White);
        }

        if (currentRanking == LOCAL) {
            if (currentMode == BEGINNER) {
                currentData = localBeginnerRanking;
            } else if (currentMode == INTERMEDIATE) {
                currentData = localIntermediateRanking;
            } else {
                currentData = localExpertRanking;
            }
        } else {
            if (currentMode == BEGINNER) {
                currentData = globalBeginnerRanking;
            } else if (currentMode == INTERMEDIATE) {
                currentData = globalIntermediateRanking;
            } else {
                currentData = globalExpertRanking;
            }            
        }

        std::vector <sf::Sprite> tableBox(1 + currentData.size());
        std::vector <std::vector <sf::Text> > tableText(tableBox.size());
        for (int ithRow = 0; ithRow < tableBox.size(); ithRow++) {
            tableBox[ithRow].setTexture(ithRow % 2 == 0 ? blueBox824x40Texture : whiteBox824x40Texture);
            tableBox[ithRow].setPosition((window.getSize().x - tableBox[ithRow].getGlobalBounds().width) / 2, 330 + 40 * ithRow);

            tableText[ithRow].resize(3);
            if (ithRow == 0) {
                tableText[ithRow][0].setString("Username");
                tableText[ithRow][1].setString("Time");
                tableText[ithRow][2].setString("Date");
            } else {
                tableText[ithRow][0].setString(currentData[ithRow - 1][0]);
                tableText[ithRow][1].setString(currentData[ithRow - 1][1]);
                tableText[ithRow][2].setString(currentData[ithRow - 1][2]);
            }

            for (int ithCol = 0; ithCol < 3; ithCol++) {
                tableText[ithRow][ithCol].setFont(font);
                tableText[ithRow][ithCol].setFillColor(sf::Color::Black);
                tableText[ithRow][ithCol].setCharacterSize(30);
            }

            tableText[ithRow][0].setPosition(tableBox[ithRow].getGlobalBounds().left + 20, tableBox[ithRow].getGlobalBounds().top);
            tableText[ithRow][1].setPosition(tableBox[ithRow].getGlobalBounds().left + 400, tableBox[ithRow].getGlobalBounds().top);
            tableText[ithRow][2].setPosition(tableBox[ithRow].getGlobalBounds().left + 570, tableBox[ithRow].getGlobalBounds().top);
        }

        window.clear();

        window.draw(titleBarBox);
        window.draw(titleBarText);
        window.draw(messageText);
        window.draw(closeButtonSprite);

        window.draw(backgroundSprite);

        window.draw(backButtonSprite);

        window.draw(rankingText);

        window.draw(modeBox);
        window.draw(modeText);
        window.draw(prevModeSprite);
        window.draw(nextModeSprite);

        window.draw(localRankingBox);
        window.draw(localRankingText);

        window.draw(globalRankingBox);
        window.draw(globalRankingText);

        for (int ithRow = 0; ithRow < tableBox.size(); ithRow++) {
            window.draw(tableBox[ithRow]);
            for (int ithCol = 0; ithCol < 3; ithCol++) {
                window.draw(tableText[ithRow][ithCol]);
            }
        }

        if (currentData[0][0].empty()) {
            sf::Text noDataText("No data", font, 30);
            noDataText.setFillColor(sf::Color::Black);
            noDataText.setPosition(tableBox[1].getGlobalBounds().left + (tableBox[1].getGlobalBounds().width - noDataText.getGlobalBounds().width) / 2, tableBox[1].getGlobalBounds().top);
            window.draw(noDataText);
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
                        currentScreen = GAMEMENU;
                        return;
                    }

                    if (positionInBox(sf::Mouse::getPosition(window), prevModeBox.getGlobalBounds())) {
                        if (currentMode == INTERMEDIATE) {
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
                        } else {
                            currentMode = BEGINNER;
                        }
                    }

                    if (positionInBox(sf::Mouse::getPosition(window), localRankingBox.getGlobalBounds())) {
                        if (user.getUsername().empty()) {
                            messageText.setString("There is no local ranking in guest mode, sensei");
                            messageText.setFillColor(sf::Color::Black);
                            messageText.setPosition((window.getSize().x - messageText.getGlobalBounds().width) / 2, 2);
                            messageClock.restart(); 
                        } else {
                            currentRanking = LOCAL;
                        }
                    }

                    if (positionInBox(sf::Mouse::getPosition(window), globalRankingBox.getGlobalBounds())) {
                        currentRanking = GLOBAL;
                    }

                    leftMouseButtonHoldingInTitleBar = false;
                }
            }
        }
    }

#undef LOCAL
#undef GLOBAL
}