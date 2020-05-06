#pragma once
#include<iostream>
using namespace std;

class Hero {
private:
	string name;
	int healthPoints;
	int damage;
	int armor;

	void copy(const Hero& hero)
	{
		this->name = hero.name;
		this->healthPoints = hero.healthPoints;
		this->damage = hero.damage;
		this->armor = hero.armor;
	}

public:
	Hero();
	Hero(string, int, int, int);
	Hero(const Hero&);
	Hero& operator=(const Hero&);

	void setName(string);
	void setHealthPoints(int);
	void setDamage(int);
	void setArmor(int);

	const string getName() const;
	const int getHealthPoints() const;
	const int getDamage() const;
	const int getArmor() const;

	friend ostream& operator<<(ostream&, const Hero&);
};

Hero::Hero() {
	this->name = "";
	this->healthPoints = 0;
	this->damage = 0;
	this->armor = 0;
}

Hero::Hero(string name, int healthPoints, int damage, int armor) {
	this->name = name;
	this->healthPoints = healthPoints;
	this->damage = damage;
	this->armor = armor;
}

Hero::Hero(const Hero& hero) {
	this->copy(hero);
}

Hero& Hero::operator=(const Hero& hero) {
	if (this != &hero) {
		this->copy(hero);
	}
	return *this;
}

void Hero::setName(string name) {
	this->name = name;
}

void Hero::setHealthPoints(int healthPoints) {
	this->healthPoints = healthPoints;
}

void Hero::setDamage(int damage) {
	this->damage = damage;
}

void Hero::setArmor(int armor) {
	this->armor = armor;
}

const string Hero::getName() const {
	return this->name;
}

const int Hero::getHealthPoints() const {
	return this->healthPoints;
}

const int Hero::getDamage() const {
	return this->damage;
}

const int Hero::getArmor() const {
	return this->armor;
}

ostream& operator<<(ostream& output, const Hero& hero)
{
	output << hero.name << " - hp: " << hero.healthPoints << ", dmg: " << hero.damage << ", armor: " << hero.armor << endl;
	return output;
}