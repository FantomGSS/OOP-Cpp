#pragma once
#include<iostream>
using namespace std;

int mystrlen(const char* str)
{
    int i = -1;
    while (str[++i]);
    return i;
}

int compareChars(const char* charsOne, const char* charsTwo) 
{
    for (int i = 0; charsOne[i] != '\0'; i++)
    {
        if (charsOne[i] != charsTwo[i]) {
            return 0;
        }
    }
    return 1;
}

class Card {
private:
    char* color;
    char* value;
    char* serialNumber;

    void checkColor(const char* color) 
    {
        if (compareChars(color, "clubs") == 0 && compareChars(color, "diamonds") == 0 
            && compareChars(color, "hearts") == 0  && compareChars(color, "spades") == 0)
        {
            cout << "This color does not exist! Try again.";
            exit(0);
        }
    }

    void checkValue(const char* value) 
    {
        if (value != "2" && value != "3" && value != "4" && value != "5"
            && value != "6" && value != "7" && value != "8" && value != "9"
            && value != "10" && value != "J" && value != "Q" && value != "K" && value != "A")
        {
            cout << "This value does not exist! Try again.";
            exit(0);
        }
    }

    void copy(const Card& card)
    {
        this->color = new char[mystrlen(card.color) + 1];
        strcpy_s(this->color, mystrlen(card.color) + 1, card.color);

        this->value = new char[mystrlen(card.value) + 1];
        strcpy_s(this->value, mystrlen(card.value) + 1, card.value);

        this->serialNumber = new char[mystrlen(card.serialNumber) + 1];
        strcpy_s(this->serialNumber, mystrlen(card.serialNumber) + 1, card.serialNumber);
    }

    void erase()
    {
        delete[] this->color;
        delete[] this->value;
        delete[] this->serialNumber;
    }

public:
    Card();
    Card(const char*, const char*, const char*);
    Card(const Card&);
    Card& operator=(const Card&);
    ~Card();

    void setColor(const char*);
    void setValue(const char*);
    void setSerialNumber(const char*);

    const char* getColor() const;
    const char* getValue() const;
    const char* getSerialNumber() const;

    const int getPoints() const;

    friend ostream& operator<<(std::ostream&, const Card&);
};

Card::Card() {
    this->color = nullptr;
    this->value = nullptr;
    this->serialNumber = nullptr;
}

Card::Card(const char* color, const char* value, const char* serialNumber) {
    checkColor(color);
    checkValue(value);

    this->color = new char[mystrlen(color) + 1];
    strcpy_s(this->color, mystrlen(color) + 1, color);

    this->value = new char[mystrlen(value) + 1];
    strcpy_s(this->value, mystrlen(value) + 1, value);

    this->serialNumber = new char[mystrlen(serialNumber) + 1];
    strcpy_s(this->serialNumber, mystrlen(serialNumber) + 1, serialNumber);
}

Card::Card(const Card& card) {
    this->copy(card);
}

Card& Card::operator=(const Card& card) {
    if (this != &card) {

        if (this->serialNumber != nullptr)      //Проверявам само едната лична променлива, тъй като или трите едновременно са nullptr, или никоя от тях.
        {
            this->erase();
        }

        this->copy(card);
    }
    return *this;
}

Card::~Card() {
    this->erase();
}

void Card::setColor(const char* color) {
    delete[] this->color;
    checkColor(color);

    this->color = new char[mystrlen(color) + 1];
    strcpy_s(this->color, mystrlen(color) + 1, color);
}

void Card::setValue(const char* value) {
    delete[] this->value;
    checkValue(value);

    this->value = new char[mystrlen(value) + 1];
    strcpy_s(this->value, mystrlen(value) + 1, value);
}

void Card::setSerialNumber(const char* serialNumber) {
    delete[] this->serialNumber;
    this->serialNumber = new char[mystrlen(serialNumber) + 1];
    strcpy_s(this->serialNumber, mystrlen(serialNumber) + 1, serialNumber);
}

const char* Card::getColor() const {
    return this->color;
}

const char* Card::getValue() const {
    return this->value;
}

const char* Card::getSerialNumber() const {
    return this->serialNumber;
}

const int Card::getPoints() const
{
    if (compareChars(this->value, "2"))
    {
        return 2;
    }

    else if (compareChars(this->value, "3"))
    {
        return 3;
    }

    else if (compareChars(this->value, "4"))
    {
        return 4;
    }

    else if (compareChars(this->value, "5"))
    {
        return 5;
    }

    else if (compareChars(this->value, "6"))
    {
        return 6;
    }

    else if (compareChars(this->value, "7"))
    {
        return 7;
    }

    else if (compareChars(this->value, "8"))
    {
        return 8;
    }

    else if (compareChars(this->value, "9"))
    {
        return 9;
    }

    else if (compareChars(this->value, "10"))
    {
        return 10;
    }

    else if (compareChars(this->value, "J"))
    {
        return 10;
    }

    else if (compareChars(this->value, "Q"))
    {
        return 10;
    }

    else if (compareChars(this->value, "K"))
    {
        return 10;
    }

    else //if (compareChars(this->value, "A"))
    {
        return 11;
    }
}

ostream& operator<<(std::ostream& output, const Card& card)
{
    output << "Color: " << card.color << endl;
    output << "Value: " << card.value << endl;
    output << "Serial Number: " << card.serialNumber << endl;
    return output;
}