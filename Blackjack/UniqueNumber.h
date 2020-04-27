#pragma once
#include<iostream>
#include <ctime>
using namespace std;

class UniqueNumber {
private:
    char* uniqueNumber;

    void checkSeries(const char* series) 
    {
        if (mystrlen(series) > 10)
        {
            cout << "The series must be a maximum of 10 characters";
            exit(0);
        }
    }

    char* generateAlphaNum() 
    {
        const char chars[] =
            "0123456789"
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
            "abcdefghijklmnopqrstuvwxyz";

        char* alphaNum = new char[5 + 1];

        for (int i = 0; i < 5 + 1; i++)
        {
            alphaNum[i] = chars[(rand() + time(0)) % 62];
        }

        alphaNum[5] = '\0';
        return alphaNum;
    }

    void copy(const UniqueNumber& unNum)
    {
        this->uniqueNumber = new char[mystrlen(unNum.uniqueNumber) + 1];
        strcpy_s(this->uniqueNumber, mystrlen(unNum.uniqueNumber) + 1, unNum.uniqueNumber);
    }

    void erase()
    {
        delete[] this->uniqueNumber;
    }

public:
    UniqueNumber();
    UniqueNumber(const char*);
    UniqueNumber(const UniqueNumber&);
    UniqueNumber& operator=(const UniqueNumber&);
    ~UniqueNumber();

    const char* getUniqueNumber() const;
};

UniqueNumber::UniqueNumber() {
    this->uniqueNumber = nullptr;
}

UniqueNumber::UniqueNumber(const char* series) {
    
    checkSeries(series);
    char* generatedNumber = generateAlphaNum();

    this->uniqueNumber = new char[mystrlen(series) + mystrlen(generatedNumber) + 1];
    for (int i = 0; i < mystrlen(series) + 1; i++)
    {
        this->uniqueNumber[i] = series[i];
    }

    int index = 0;

    for (int i = mystrlen(series); i < mystrlen(series) + mystrlen(generatedNumber) + 1; i++)
    {
        this->uniqueNumber[i] = generatedNumber[index++];
    }
}

UniqueNumber::UniqueNumber(const UniqueNumber& uniqueNumber) {
    this->copy(uniqueNumber);
}

UniqueNumber& UniqueNumber::operator=(const UniqueNumber& unNum) {
    if (this != &unNum) {
        if (this->uniqueNumber != nullptr)
        {
            this->erase();
        }
        
        this->copy(unNum);
    }
    return *this;
}

UniqueNumber::~UniqueNumber() {
    this->erase();
}

const char* UniqueNumber::getUniqueNumber() const {
    return this->uniqueNumber;
}