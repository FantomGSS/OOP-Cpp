#pragma once
#include "Vehicle.h"
class Car : public Vehicle {
private:
	char* model;
	int carDoors;
	int enginePower;

	void copy(const Car& car)
	{
		this->model = new char[strlen(car.model) + 1];
		strcpy_s(this->model, strlen(car.model) + 1, car.model);

		this->carDoors = car.carDoors;
		this->enginePower = car.enginePower;
	}

public:
	Car();
	Car(const char*, const char*, int, int, int, const char*, int, int);
	Car(const Car&);
	Car& operator=(const Car&);
	~Car();

	void move() const override {
		cout << "I am Car. I move at maximum speed: " << this->getMaximumSpeed() << endl;
	}

	void setModel(const char* model);
	void setCarDoors(const int carDoors);
	void setEnginePower(const int enginePower);

	const char* getModel() const;
	int getCarDoors() const;
	int getEnginePower() const;

	friend ostream& operator<<(ostream&, const Car&);
};
Car::Car() : Vehicle() {
	this->model = nullptr;
	this->carDoors = 0;
	this->enginePower = 0;
}

Car::Car(const char* color, const char* brand, int yearOfProduction, int passengers, int maximumSpeed, const char* model, int carDoors, int enginePower)
	: Vehicle(color, brand, yearOfProduction, passengers, maximumSpeed) {
	this->model = new char[strlen(model) + 1];
	strcpy_s(this->model, strlen(model) + 1, model);

	this->carDoors = carDoors;
	this->enginePower = enginePower;
}

Car::Car(const Car& car) : Vehicle(car) {
	this->copy(car);
}

Car& Car::operator=(const Car& car) {
	if (this != &car) {
		Vehicle::operator=(car);

		this->copy(car);
	}
	return *this;
}

Car::~Car() {
	delete[] this->model;
}

void Car::setModel(const char* model)
{
	delete[] this->model;
	this->model = new char[strlen(model) + 1];
	strcpy_s(this->model, strlen(model) + 1, model);
}

void Car::setCarDoors(const int carDoors)
{
	this->carDoors = carDoors;
}

void Car::setEnginePower(const int enginePower)
{
	this->enginePower = enginePower;
}

const char* Car::getModel() const {
	return this->model;
}

int Car::getCarDoors() const {
	return this->carDoors;
}

int Car::getEnginePower() const {
	return this->enginePower;
}

ostream& operator<<(ostream& output, const Car& car)
{
	output << "Color: " << car.getColor() << endl;
	output << "Brand: " << car.getBrand() << endl;
	output << "Year of production: " << car.getYearOfProduction() << endl;
	output << "Passengers: " << car.getPassengers() << endl;
	output << "Maximum speed: " << car.getMaximumSpeed() << endl;
	output << "Model: " << car.model << endl;
	output << "Car Doors: " << car.carDoors << endl;
	output << "Engine Power: " << car.enginePower << endl;
	return output;
}