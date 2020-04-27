#pragma once
#include<iostream>
#include <cmath>
using namespace std;

class Player {
private:
    char* name;
    unsigned short int age;
    unsigned short int victories;
    unsigned short int gamesPlayed;
    float winRate;
    unsigned short int currentPoints;

    void checkName(const char* name)
    {
        int indexInterval = 0;
        int countIntervals = 0;
        for (int i = 0; i < mystrlen(name) + 1; i++)
        {
            if (name[i] == ' ')
            {
                if (indexInterval == 0)
                {
                    indexInterval = i;
                }
                countIntervals++;
            }
        }

        if (!(name[0] >= 'A' && name[0] <= 'Z' && countIntervals == 1 && name[indexInterval + 1] >= 'A' && name[indexInterval + 1] <= 'Z'))
        {
            cout << "The name must contain two words, whose first letters are capital and exactly one space!" << endl;
            exit(0);
        }
    }

    void checkAge(const unsigned short int age)
    {
        if (age < 18)
        {
            cout << "You are still a minor in order to play this game. I'm sorry, but you have to come back in: " << 18 - age << "years" << endl;
            exit(0);
        }
        else if (age > 90)
        {
            cout << "We're sorry, but the health of our players is important to us. Emotions will not affect you well at this age!" << endl;
            exit(0);
        }
    }

    void copy(const Player& player)
    {
        this->name = new char[mystrlen(player.name) + 1];
        strcpy_s(this->name, mystrlen(player.name) + 1, player.name);

        this->age = player.age;
        this->victories = player.victories;
        this->gamesPlayed = player.gamesPlayed;
        this->winRate = player.winRate;
        this->currentPoints = player.currentPoints;
    }

    void erase()
    {
        delete[] this->name;
    }

public:
    Player();
    Player(const char*, const unsigned short int);
    Player(const Player&);
    Player& operator=(const Player&);
    ~Player();

    void setName(const char*);
    void setAge(const unsigned short int);
    void setCurrentPoints(const unsigned short int);

    void increaseVictories();
    void increaseGamesPlayed();

    const char* getName() const;
    const unsigned short int getAge() const;
    const unsigned short int getVictories() const;
    const unsigned short int getGamesPlayed() const;
    const float getWinRate() const;
    const unsigned short int getCurrentPoints() const;

    friend ostream& operator<<(std::ostream&, const Player&);
};

Player::Player() {
    this->name = nullptr;
    this->age = 18;
    this->victories = 0;
    this->gamesPlayed = 0;
    this->winRate = 0;
    this->currentPoints = 0;
}

Player::Player(const char* name, const unsigned short int age) {
    checkName(name);
    checkAge(age);

    this->name = new char[mystrlen(name) + 1];
    strcpy_s(this->name, mystrlen(name) + 1, name);

    this->age = age;
    this->victories = 0;
    this->gamesPlayed = 0;
    this->winRate = 0;
    this->currentPoints = 0;
}

Player::Player(const Player& player) {
    this->copy(player);
}

Player& Player::operator=(const Player& player) {
    if (this != &player) {
        if (this->name != nullptr)
        {
            this->erase();
        }

        this->copy(player);
    }
    return *this;
}

Player::~Player() {
    this->erase();
}

void Player::setName(const char* name) {
    this->erase();
    checkName(name);

    this->name = new char[mystrlen(name) + 1];
    strcpy_s(this->name, mystrlen(name) + 1, name);
}

void Player::setAge(const unsigned short int age) {
    checkAge(age);
    this->age = age;
}

void Player::setCurrentPoints(const unsigned short int currentPoints) {
    this->currentPoints = currentPoints;
}

void Player::increaseVictories() {
    this->victories++;
}

void Player::increaseGamesPlayed() {
    this->gamesPlayed++;

    this->winRate = (float)floor(((float)this->victories * 10 / this->gamesPlayed) + 0.5) / 10;
}

const char* Player::getName() const {
    return this->name;
}

const unsigned short int Player::getAge() const {
    return this->age;
}

const unsigned short int Player::getVictories() const {
    return this->victories;
}

const unsigned short int Player::getGamesPlayed() const {
    return this->gamesPlayed;
}

const float Player::getWinRate() const {
    return this->winRate;
}

const unsigned short int Player::getCurrentPoints() const {
    return this->currentPoints;
}

ostream& operator<<(std::ostream& output, const Player& player)
{
    output << "Name: " << player.name << endl;
    output << "Age: " << player.age << endl;
    output << "Victories: " << player.victories << endl;
    output << "Count of games played: " << player.gamesPlayed << endl;
    output << "*Win rate*: " << player.winRate << endl;
    output << "Current points from the last game: " << player.currentPoints << endl;
    return output;
}