#pragma once
#include "Vehicle.h"
class Bicycle : public Vehicle {
private:
	int gearCount;
	bool lights;
	bool reflectors;
	bool bell;

	void copy(const Bicycle& bicycle)
	{
		this->gearCount = bicycle.gearCount;
		this->lights = bicycle.lights;
		this->reflectors = bicycle.reflectors;
		this->bell = bicycle.bell;
	}

public:
	Bicycle();
	Bicycle(const char*, const char*, int, int, int, int, bool, bool, bool);
	Bicycle(const Bicycle&);
	Bicycle& operator=(const Bicycle&);

	void move() const override {
		cout << "I am Bicycle. I move at maximum speed: " << this->getMaximumSpeed() << endl;
	}

	void setGearCount(const int gearCount);
	void setLights(const bool lights);
	void setReflectors(const bool reflectors);
	void setBell(const bool bell);

	int getGearCount() const;
	bool getLights() const;
	bool getReflectors() const;
	bool getBell() const;
	
	friend ostream& operator<<(ostream&, const Bicycle&);
};
Bicycle::Bicycle() : Vehicle() {
	this->gearCount = 0;
	this->lights = false;
	this->reflectors = false;
	this->bell = false;
}

Bicycle::Bicycle(const char* color, const char* brand, int yearOfProduction, int passengers, int maximumSpeed, int gearCounts, bool lights, bool reflectors, bool bell) 
	: Vehicle(color, brand, yearOfProduction, passengers, maximumSpeed) {
	this->gearCount = gearCount;
	this->lights = lights;
	this->reflectors = reflectors;
	this->bell = bell;
}

Bicycle::Bicycle(const Bicycle& bicycle) : Vehicle(bicycle) {
	this->copy(bicycle);
}

Bicycle& Bicycle::operator=(const Bicycle& bicycle) {
	if (this != &bicycle) {
		Vehicle::operator=(bicycle);

		this->copy(bicycle);
	}
	return *this;
}

void Bicycle::setGearCount(const int gearCount)
{
	this->gearCount = gearCount;
}

void Bicycle::setLights(const bool lights)
{
	this->lights = lights;
}

void Bicycle::setReflectors(const bool reflectors)
{
	this->reflectors = reflectors;
}

void Bicycle::setBell(const bool bell)
{
	this->bell = bell;
}

int Bicycle::getGearCount() const {
	return this->gearCount;
}

bool Bicycle::getLights() const {
	return this->lights;
}

bool Bicycle::getReflectors() const {
	return this->reflectors;
}

bool Bicycle::getBell() const {
	return this->bell;
}

ostream& operator<<(ostream& output, const Bicycle& bicycle)
{
	output << "Color: " << bicycle.getColor() << endl;
	output << "Brand: " << bicycle.getBrand() << endl;
	output << "Year of production: " << bicycle.getYearOfProduction() << endl;
	output << "Passengers: " << bicycle.getPassengers() << endl;
	output << "Maximum speed: " << bicycle.getMaximumSpeed() << endl;
	output << "Gear count: " << bicycle.gearCount << endl;
	output << "Lights: " << boolalpha << bicycle.lights << endl;
	output << "Reflectors: " << boolalpha << bicycle.reflectors << endl;
	output << "Bell: " << boolalpha << bicycle.bell << endl;
	return output;
}