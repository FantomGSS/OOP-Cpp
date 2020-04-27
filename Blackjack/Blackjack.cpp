#include <iostream>
#include <fstream>
#include "Deck.h"
#include "Player.h"

const int MAX_SIZE_LINE = 100;
const int MAX_SIZE_WORD = 30;
const int WORDS_PLAYER_INFO = 22;

void printErrorMessage(const char* filePath) {
    cerr << "\n";
    cerr << "There was a problem opening file with name: " << filePath << endl;
    cerr << "\n";
}

void printSuccessMessage(const char* filePath) {
    cout << "\n";
    cout << "===========================================================" << endl;
    cout << "All changes are saved successfully in the file " << filePath << "!" << endl;
    cout << "===========================================================" << endl;
    cout << "\n";
}

void saveNewPlayerInfoInFile(const char* filePath, Player &player) {
    ofstream outputFileStream;
    outputFileStream.open(filePath, ios::app);
    if (outputFileStream.is_open()) {
        outputFileStream << endl;
        outputFileStream << player;
        outputFileStream.close();
        printSuccessMessage(filePath);
    }
    else {
        printErrorMessage(filePath);
    }
}

void overwriteFile(const char* filePath, Player* players, int playersCount) {
    ofstream outputFileStream;
    outputFileStream.open(filePath, ios::out);
    if (outputFileStream.is_open()) {
        for (int i = 0; i < playersCount; i++)
        {
            outputFileStream << players[i];
            if (i < playersCount - 1)
            {
                outputFileStream << endl;
            } 
        }
        outputFileStream.close();
        printSuccessMessage(filePath);
    }
    else {
        printErrorMessage(filePath);
    }
}

const char* readName(char** words, int indexName) 
{
    char* name = new char[mystrlen(words[indexName]) + 1 + mystrlen(words[indexName + 1]) + 1];
    for (int i = 0; i < mystrlen(words[indexName]) + 1; i++)
    {
        if (i != mystrlen(words[indexName]))
        {
            name[i] = words[indexName][i];
        }
        else
        {
            name[i] = ' ';
        }
    }
    
    int counter = 0;
    for (int i = mystrlen(words[indexName]) + 1; i < mystrlen(words[indexName]) + 1 + mystrlen(words[indexName + 1]) + 1; i++)
    {
        name[i] = words[indexName + 1][counter++];
    }

    return name;
}

const unsigned short int readNum(char** words, int indexNum)
{
    unsigned short int num = 0;
    int sizeNum = mystrlen(words[indexNum]);
    for (int i = 0; i < sizeNum; i++)
    {
        num += (unsigned short int)((words[indexNum][i] - 48) * pow(10, sizeNum - i - 1));
    }

    return num;
}

const char* fullNameValues(const char* value)
{
    if (compareChars(value, "A"))
    {
        return "Ace";
    }
    else if (compareChars(value, "K"))
    {
        return "King";
    }
    else if (compareChars(value, "Q"))
    {
        return "Queen";
    }
    else if (compareChars(value, "J"))
    {
        return "Jack";
    }
    else
    {
        return value;
    }
    
}

void playerDrawInfo(Card* cardsPlayer, int pointsPlayer, int countCardsPlayer)
{
    for (int i = 0; i < countCardsPlayer; i++)
    {
        cout << cardsPlayer[i].getValue() << "(" << cardsPlayer[i].getColor() << ") ";
    }
    cout << "(Points: " << pointsPlayer << ")" << endl;
}

void dealerDrawInfo(Card* cardsDealer, int pointsDealer, int countCardsDealer) 
{
    cout << "The dealer's draw: ";
    for (int i = 0; i < countCardsDealer; i++)
    {
        if (i == countCardsDealer - 1)
        {
            cout << fullNameValues(cardsDealer[i].getValue()) << "(" << cardsDealer[i].getColor() << ") ";
            break;
        }
        cout << fullNameValues(cardsDealer[i].getValue()) << "(" << cardsDealer[i].getColor() << ")" << ", ";
    }
    cout << "(Points: " << pointsDealer << ")" << endl;
}

const char* fromPointsToValue(int i)
{
    switch (i)
    {
    case 1: return "A"; break;
    case 2: return "2"; break;
    case 3: return "3"; break;
    case 4: return "4"; break;
    case 5: return "5"; break;
    case 6: return "6"; break;
    case 7: return "7"; break;
    case 8: return "8"; break;
    case 9: return "9"; break;
    case 11: return "A"; break;
    default: return "X"; break;
    }
}

void startGame(Player& player, Deck &deck)
{
    cout << "Start!" << endl;
    Card firstCard = deck.draw();
    Card* cardsPlayer = new Card[11];
    Card* cardsDealer = new Card[11];
    int pointsPlayer = 0;
    int pointsDealer = 0;
    int countCardsPlayer = 0;
    cardsPlayer[countCardsPlayer++] = firstCard;
    pointsPlayer += firstCard.getPoints();
    cout << firstCard.getValue() << "(" << firstCard.getColor() << ") " << "(Points: " << pointsPlayer << ")" << endl;

    bool gameOver = false;
    while (!gameOver)
    {
        char* command = new char[MAX_SIZE_WORD];
        cout << "Hit/Stand/Probability" << endl;
        cin >> command;

        if (compareChars(command, "Hit"))
        {
            cardsPlayer[countCardsPlayer] = deck.draw();
            pointsPlayer += cardsPlayer[countCardsPlayer].getPoints();
            if (compareChars(cardsPlayer[countCardsPlayer++].getValue(), "A") && pointsPlayer > 21)
            {
                pointsPlayer -= 10;
            }
            
            playerDrawInfo(cardsPlayer, pointsPlayer, countCardsPlayer);
            if (pointsPlayer > 21)
            {
                player.increaseGamesPlayed();
                player.setCurrentPoints(pointsPlayer);
                cout << "You lose!" << endl;
                gameOver = true;
            }
        }
        else if (compareChars(command, "Stand"))
        {
            int counter = 0;
            int countCardsDealer = 0;
            while (pointsDealer < 17)
            {
                cardsDealer[countCardsDealer] = deck.draw();
                pointsDealer += cardsDealer[countCardsDealer].getPoints();
                if (compareChars(cardsDealer[countCardsDealer++].getValue(), "A") && pointsDealer > 21)
                {
                    pointsDealer -= 10;
                }
            }

            if (pointsDealer > 21)
            {
                player.increaseVictories();
                player.increaseGamesPlayed();
                player.setCurrentPoints(pointsPlayer);
                dealerDrawInfo(cardsDealer, pointsDealer, countCardsDealer);
                cout << "You win! Congratulations!" << endl;
            }
            else
            {
                dealerDrawInfo(cardsDealer, pointsDealer, countCardsDealer);
                if (pointsDealer > pointsPlayer)
                {
                    player.increaseGamesPlayed();
                    player.setCurrentPoints(pointsPlayer);
                    cout << "You lose!" << endl;
                }
                else
                {
                    player.increaseVictories();
                    player.increaseGamesPlayed();
                    player.setCurrentPoints(pointsPlayer);
                    cout << "You win! Congratulations!" << endl;
                }
            }

            gameOver = true;
        }
        else if (compareChars(command, "Probability"))
        {
            double probability = 0;
            int needValue = 21 - pointsPlayer;
            if (needValue != 10)
            {
                probability = deck.rank_count(fromPointsToValue(needValue));
            }
            else
            {
                int countCardsWithTenPoints = 0;
                countCardsWithTenPoints += deck.rank_count("10");
                countCardsWithTenPoints += deck.rank_count("J");
                countCardsWithTenPoints += deck.rank_count("Q");
                countCardsWithTenPoints += deck.rank_count("K");
            }

            probability /= deck.getSizeOfDeck();
            cout << floor(probability * 100 + 0.5) / 100 << endl;
        }
    }
}

void createDeck(Player& player)
{
    bool gameFinished = false;
    cout << "You will play as " << player.getName() << ". Choose the size of the deck:" << endl;

    char* sizeAndMayBeSeries = new char[MAX_SIZE_LINE];
    cin.getline(sizeAndMayBeSeries, MAX_SIZE_LINE);

    int indexInterval = 0;
    int sizeSeries = 1;  // '\0'  -> +1
    for (int i = 0; i < mystrlen(sizeAndMayBeSeries); i++)
    {
        if (indexInterval != 0)
        {
            sizeSeries++;
        }
        if (sizeAndMayBeSeries[i] == ' ')
        {
            indexInterval = i;
        }
    }

    if (indexInterval > 0)
    {
        char* countCardsChars = new char[indexInterval + 1];
        for (int i = 0; i < indexInterval + 1; i++)
        {
            countCardsChars[i] = sizeAndMayBeSeries[i];
        }
        countCardsChars[indexInterval] = '\0';

        unsigned short int countCards = 0;
        int sizeOfCardsChars = mystrlen(countCardsChars);
        for (int i = 0; i < sizeOfCardsChars; i++)
        {
            countCards += (unsigned short int)((countCardsChars[i] - 48) * pow(10, sizeOfCardsChars - i - 1));
        }

        char* series = new char[sizeSeries];
        int counter = mystrlen(countCardsChars) + 1;
        for (int i = 0; i < sizeSeries; i++)
        {
            series[i] = sizeAndMayBeSeries[counter++];
        }

        Deck deck = Deck(countCards, series);
        startGame(player, deck);
    }
    else
    {
        unsigned short int countCards = 0;
        int sizeOfCardsChars = mystrlen(sizeAndMayBeSeries);
        for (int i = 0; i < sizeOfCardsChars; i++)
        {
            countCards += (unsigned short int)((sizeAndMayBeSeries[i] - 48) * pow(10, sizeOfCardsChars - i - 1));
        }

        if (countCards == 52)
        {
            Deck deck = Deck();
            startGame(player, deck);
        }
        else
        {
            Deck deck = Deck(countCards, "Custom");
            startGame(player, deck);
        }
    }
}

int getPlayersCountFromFile(const char* filePath)
{
    int lineCounter = 0;
    ifstream inputFileStream;
    inputFileStream.open(filePath, ios::in);

    if (inputFileStream.is_open())
    {
        char lineFromFile[MAX_SIZE_LINE];
        while (!inputFileStream.eof())
        {
            inputFileStream.getline(lineFromFile, MAX_SIZE_LINE);
            lineCounter++;
        }
        inputFileStream.close();
    }
    else
    {
        printErrorMessage(filePath);
        return -1;
    }

    return lineCounter / 7;
}

void getWordsFromFile(const char* filePath, char** &words, int wordsInFile)
{
    ifstream inputFileStream;
    inputFileStream.open(filePath, ios::in);
    int wordCounter = 0;
    if (inputFileStream.is_open())
    {
        char wordFromFile[MAX_SIZE_WORD];
        while (!inputFileStream.eof()) {
            inputFileStream >> wordFromFile;
            while (wordCounter != wordsInFile)
            {
                strcpy_s(words[wordCounter], MAX_SIZE_WORD, wordFromFile);
                wordCounter++;
                break;
            }
        }
        inputFileStream.close();
    }
    else
    {
        printErrorMessage(filePath);
    }
}

void getPlayersFromFile(char**& words, Player*& players, int playersCount)
{
    int indexName = 1;
    int indexAge = 4;
    int indexVictories = 6;
    int indexGamesPlayed = 11;
    int indexCurrentPoints = 21;
    for (int i = 0; i < playersCount; i++)
    {
        players[i].setName(readName(words, indexName));
        players[i].setAge(readNum(words, indexAge));

        for (int j = 0; j < readNum(words, indexVictories); j++)
        {
            players[i].increaseVictories();
        }

        for (int k = 0; k < readNum(words, indexGamesPlayed); k++)
        {
            players[i].increaseGamesPlayed();
        }

        players[i].setCurrentPoints(readNum(words, indexCurrentPoints));

        indexName += WORDS_PLAYER_INFO;
        indexAge += WORDS_PLAYER_INFO;
        indexVictories += WORDS_PLAYER_INFO;
        indexGamesPlayed += WORDS_PLAYER_INFO;
        indexCurrentPoints += WORDS_PLAYER_INFO;
    }
}

int main()
{
    const char* filePath = "Players.txt";
    int playersCount = getPlayersCountFromFile(filePath);

    int wordsInFile = playersCount * WORDS_PLAYER_INFO;
    char** words = new char* [wordsInFile];
    for (int i = 0; i < wordsInFile; ++i)
        words[i] = new char[MAX_SIZE_WORD];
    getWordsFromFile(filePath, words, wordsInFile);
    
    Player* players = new Player[playersCount];
    getPlayersFromFile(words, players, playersCount);
    
    for (int i = 0; i < playersCount; i++)
    {
        cout << players[i].getName() << " " << players[i].getVictories() << " " << players[i].getWinRate() << endl;
    }

    cout << "Choose a player or enter a new player:" << endl;

    char* name = new char[MAX_SIZE_LINE];
    cin.getline(name, MAX_SIZE_LINE);
    
    int registeredPlayerIndex = -1;
    for (int i = 0; i < playersCount; i++)
    {
        if (compareChars(name, players[i].getName()))
        {
            registeredPlayerIndex = i;
        }
    }

    if (registeredPlayerIndex == -1)
    {
        Player newPlayer = Player();
        newPlayer.setName(name);
        cout << "Enter your age: " << endl;
        unsigned short int age = 0;
        cin >> age;
        cin.ignore();
        newPlayer.setAge(age);
        createDeck(newPlayer);
        saveNewPlayerInfoInFile(filePath, newPlayer);
    }
    else 
    {
        createDeck(players[registeredPlayerIndex]);
        overwriteFile(filePath, players, playersCount);
    }
}
