#pragma once
#include<iostream>
#include "Card.h"
#include "UniqueNumber.h"
using namespace std;

class Deck {
private:
    Card* cards;
    unsigned short int sizeOfArrayOfCards;
    char* series;

    void arrayOfUniqueNumbers(UniqueNumber* &generatedAlphaNums, unsigned short int countCards, const char* series)
    {
        int countUniqueNumbers = 1;
        int countNumbers = 0;
        int countSuccessfulChecks = 0;
        int indexUniqueNumber = 0;

        UniqueNumber generatedNumber = UniqueNumber(series);
        generatedAlphaNums[indexUniqueNumber++] = generatedNumber;

        while (countUniqueNumbers != countCards)
        {
            generatedNumber = UniqueNumber(series);
            countNumbers = countUniqueNumbers;

            for (int i = 0; i < countNumbers; i++)
            {
                if (!compareChars(generatedNumber.getUniqueNumber(), generatedAlphaNums[i].getUniqueNumber()))
                {
                    countSuccessfulChecks++;
                }
            }
            if (countSuccessfulChecks == countNumbers)
            {
                generatedAlphaNums[indexUniqueNumber++] = generatedNumber;
                countUniqueNumbers++;
                countSuccessfulChecks = 0;
            }
        }
    }

    void checkIndexes(bool arrayOfBools[4], int arrayOfInts[4], int &indexColor)
    {
        for (int j = 0; j < 4; j++)
        {
            if (arrayOfInts[j] < 5)
            {
                indexColor = j;
                arrayOfInts[j] += 6;
                arrayOfBools[j] = true;
                break;
            }
            if (j == 3 && arrayOfInts[j] > 5)
            {
                indexColor = (rand() + time(0)) % 4;

                for (int k = 0; k < 4; k++)
                {
                    arrayOfInts[k] -= 6;
                    arrayOfBools[k] = false;
                }

                arrayOfInts[indexColor] += 6;
                arrayOfBools[indexColor] = true;
            }
        }
    }

    void deckCreation(const unsigned short int countCards, const char* series)
    {
        UniqueNumber* generatedAlphaNums = new UniqueNumber[countCards];
        arrayOfUniqueNumbers(generatedAlphaNums, countCards, series);

        const char arrayOfColors[4][9] = { "clubs", "diamonds", "hearts", "spades" };
        int arrayOfInts[4] = { 0, 1, 2, 3 };
        bool arrayOfBools[4] = { false, false, false, false };
        int indexColorCheck = -1;

        int indexColor = -1;

        for (int i = 0; i < countCards; i++)
        {
                if (i % 13 == 0)
                {
                    indexColor++;

                    if (indexColor <= 3)
                    {
                        checkIndexes(arrayOfBools, arrayOfInts, indexColor);
                    }

                    else
                    {
                        indexColorCheck = (rand() + time(0)) % 4;
                        if (arrayOfInts[indexColorCheck] > 5)
                        {
                            checkIndexes(arrayOfBools, arrayOfInts, indexColor);
                        }
                        else 
                        {
                            indexColor = indexColorCheck;                   // Ако след възобновяването на броенето (след използването на всички бои) сме почнали примерно от 3тата боя, 
                            arrayOfInts[indexColor] += 6;                   // след влизане в else-а, ако се падне индекс по-малък от 3
                            arrayOfBools[indexColor] = true;
                        }
                    }
                }
                this->cards[i] = Card(arrayOfColors[indexColor], fromIntToValue(i % 13), generatedAlphaNums[i].getUniqueNumber());
        }
    }

    void shuffleDeck(const unsigned short int countCards) 
    {
        Card card = Card();
        for (int i = 0; i < countCards; i++)
        {
            int cardIndexSurprise = (rand() + time(0)) % countCards;
            card = this->cards[i];
            this->cards[i] = this->cards[cardIndexSurprise];
            this->cards[cardIndexSurprise] = card;
        }
    }

    const char* fromIntToValue(int i)
    {
        switch (i)
        {
        case 0: return "2"; break;
        case 1: return "3"; break;
        case 2: return "4"; break;
        case 3: return "5"; break;
        case 4: return "6"; break;
        case 5: return "7"; break;
        case 6: return "8"; break;
        case 7: return "9"; break;
        case 8: return "10"; break;
        case 9: return "J"; break;
        case 10: return "Q"; break;
        case 11: return "K"; break;
        case 12: return "A"; break;
        default: return "X"; break;
        }
    }

    void copy(const Deck& deck)
    {
        this->cards = deck.cards;
        this->series = new char[mystrlen(deck.series) + 1];
        strcpy_s(this->series, mystrlen(deck.series) + 1, deck.series);
    }

    void erase()
    {
        delete[] this->cards;
        delete[] this->series;
    }

public:
    Deck();
    Deck(const unsigned short int, const char*);
    Deck& operator=(const Deck&);
    ~Deck();

    const Card* getCards() const;
    const char* getSeries() const;
    const int getSizeOfDeck() const;

    const Card draw();
    void swap(const int, const int);
    const int suit_count(const char*);
    const int rank_count(const char*);

    friend ostream& operator<<(std::ostream&, const Deck&);
};

Deck::Deck() {
    this->cards = new Card[52];
    deckCreation(52, "Default");
    shuffleDeck(52);

    this->sizeOfArrayOfCards = 52;
    this->series = new char[mystrlen("Default") + 1];
    strcpy_s(this->series, mystrlen("Default") + 1, "Default");
}

Deck::Deck(const unsigned short int countCards, const char* series) {
    this->cards = new Card[countCards];
    deckCreation(countCards, series);
    shuffleDeck(countCards);

    this->sizeOfArrayOfCards = countCards;
    this->series = new char[mystrlen(series) + 1];
    strcpy_s(this->series, mystrlen(series) + 1, series);
}

Deck& Deck::operator=(const Deck& deck) {
    if (this != &deck) {
        this->erase();
        this->copy(deck);
    }
    return *this;
}

Deck::~Deck() {
    this->erase();
}

const int Deck::getSizeOfDeck() const {
    return this->sizeOfArrayOfCards;
}

const Card* Deck::getCards() const {
    return this->cards;
}

const char* Deck::getSeries() const {
    return this->series;
}

ostream& operator<<(std::ostream& output, const Deck& deck)
{
    output << "Count of cards in the deck: " << deck.sizeOfArrayOfCards << endl;
    output << "Series: " << deck.series << endl;
    return output;
}

const Card Deck::draw() {
    Card card = Card();
    if (this->sizeOfArrayOfCards != 0)
    {
        card = this->cards[0];
        for (int i = 0; i < this->sizeOfArrayOfCards - 1; i++)
        {
            this->cards[i] = this->cards[i + 1];
        }

        this->cards[this->sizeOfArrayOfCards - 1] = card;
        this->sizeOfArrayOfCards -= 1;
        return card;
    }
    else
    {
        cout << "All cards from the deck were drawn!" << endl;
    }
}

void Deck::swap(const int positionOne, const int positionTwo) {
    Card card = Card();
    if (this->sizeOfArrayOfCards != 0)
    {
        if (positionOne < 0 || positionOne > this->sizeOfArrayOfCards - 1
            || positionTwo < 0 || positionTwo > this->sizeOfArrayOfCards - 1)
        {
            cout << "Numbers must be in the range 0 to " << this->sizeOfArrayOfCards - 1 << endl;
            exit(0);
        }

        card = this->cards[positionOne];
        this->cards[positionOne] = this->cards[positionTwo];
        this->cards[positionTwo] = card;
    }
    else
    {
        cout << "All cards from the deck were drawn!" << endl;
    }
}

const int Deck::suit_count(const char* color) {
    int count = 0;
    for (int i = 0; i < this->sizeOfArrayOfCards; i++)
    {
        if (compareChars(color, this->cards[i].getColor()))
        {
            count++;
        }
    }
    return count;
}

const int Deck::rank_count(const char* value) {
    int count = 0;
    for (int i = 0; i < this->sizeOfArrayOfCards; i++)
    {
        if (compareChars(value, this->cards[i].getValue()))
        {
            count++;
        }
    }
    return count;
}