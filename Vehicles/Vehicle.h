#pragma once
#include<iostream>
#include<cstring>

using namespace std;
class Vehicle {
private:
	char* color;
	char* brand;
	int yearOfProduction;
	int passengers;
	int maximumSpeed;

	void copy(const Vehicle& vehicle)
	{
		this->color = new char[strlen(vehicle.color) + 1];
		strcpy_s(this->color, strlen(vehicle.color) + 1, vehicle.color);

		this->brand = new char[strlen(vehicle.brand) + 1];
		strcpy_s(this->brand, strlen(vehicle.brand) + 1, vehicle.brand);

		this->yearOfProduction = vehicle.yearOfProduction;
		this->passengers = vehicle.passengers;
		this->maximumSpeed = vehicle.maximumSpeed;
	}

public:
	Vehicle();
	Vehicle(const char*, const char*, int, int, int);
	Vehicle(const Vehicle& other);
	Vehicle& operator=(const Vehicle&);
	~Vehicle();

	virtual void move() const {
		cout << "I am Vehicle. I move at maximum speed: " << this->maximumSpeed << endl;
	}

	void setColor(const char* color);
	void setBrand(const char* brand);
	void setYearOfProduction(const int yearOfProduction);
	void setPassengers(const int passengers);
	void setMaximumSpeed(const int maximumSpeed);

	const char* getColor() const;
	const char* getBrand() const;
	int getYearOfProduction() const;
	int getPassengers() const;
	int getMaximumSpeed() const;

	friend ostream& operator<<(std::ostream&, const Vehicle&);
};

Vehicle::Vehicle() {
	this->color = nullptr;
	this->brand = nullptr;
	this->yearOfProduction = 0;
	this->passengers = 0;
	this->maximumSpeed = 0;
}

Vehicle::Vehicle(const char* color, const char* brand, int yearOfProduction, int passengers, int maximumSpeed) {
	this->color = new char[strlen(color) + 1];
	strcpy_s(this->color, strlen(color) + 1, color);

	this->brand = new char[strlen(brand) + 1];
	strcpy_s(this->brand, strlen(brand) + 1, brand);

	this->yearOfProduction = yearOfProduction;
	this->passengers = passengers;
	this->maximumSpeed = maximumSpeed;
}

Vehicle::Vehicle(const Vehicle& vehicle) {
	this->copy(vehicle);
}

Vehicle& Vehicle::operator=(const Vehicle& vehicle) {
	if (this != &vehicle) {
		delete[] this->color;
		delete[] this->brand;

		this->copy(vehicle);
	}
	return *this;
}

Vehicle::~Vehicle() {
	delete[] this->color;
	delete[] this->brand;
}

void Vehicle::setColor(const char* color)
{
	delete[] this->color;
	this->color = new char[strlen(color) + 1];
	strcpy_s(this->color, strlen(color) + 1, color);
}

void Vehicle::setBrand(const char* brand)
{
	delete[] this->brand;
	this->brand = new char[strlen(brand) + 1];
	strcpy_s(this->brand, strlen(brand) + 1, brand);
}

void Vehicle::setYearOfProduction(const int yearOfProduction)
{
	this->yearOfProduction = yearOfProduction;
}

void Vehicle::setPassengers(const int passengers)
{
	this->passengers = passengers;
}

void Vehicle::setMaximumSpeed(const int maximumSpeed)
{
	this->maximumSpeed = maximumSpeed;
}

const char* Vehicle::getColor() const {
	return this->color;
}

const char* Vehicle::getBrand() const {
	return this->brand;
}

int Vehicle::getYearOfProduction() const {
	return this->yearOfProduction;
}

int Vehicle::getPassengers() const {
	return this->passengers;
}

int Vehicle::getMaximumSpeed() const {
	return this->maximumSpeed;
}

ostream& operator<<(std::ostream& output, const Vehicle& vehicle)
{
	output << "Color: " << vehicle.color << endl;
	output << "Brand: " << vehicle.brand << endl;
	output << "Year of production: " << vehicle.yearOfProduction << endl;
	output << "Passengers: " << vehicle.passengers << endl;
	output << "Maximum speed: " << vehicle.maximumSpeed << endl;
	return output;
}