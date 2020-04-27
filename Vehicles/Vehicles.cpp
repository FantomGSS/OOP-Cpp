#include "Bicycle.h"
#include "Car.h"

int main()
{
    Vehicle vehicleOne;
    Vehicle vehicleTwo("Black", "Mercedes", 2010, 4, 254);
    Vehicle vehicleThree(vehicleTwo);
    Vehicle vehicleFour = vehicleThree;
    cout << vehicleFour << endl;
    vehicleFour.move();
    vehicleFour.setColor("Red");
    vehicleFour.setMaximumSpeed(300);
    cout << vehicleFour;
    cout << vehicleFour.getColor() << endl;
    cout << endl;

    Bicycle bicycleOne;
    Bicycle bicycleTwo("Gray", "Cross", 2015, 1, 25, 27, true, true, false);
    Bicycle bicycleThree(bicycleTwo);
    Bicycle bicycleFour = bicycleThree;
    cout << bicycleFour << endl;
    bicycleFour.move();
    bicycleFour.setBell(true);
    bicycleFour.setGearCount(21);
    cout << bicycleFour;
    cout << bicycleFour.getBrand() << endl;
    cout << endl;

    Car carOne;
    Car carTwo("Blue", "BMW", 2005, 5, 186, "E364", 5, 300);
    Car carThree(carTwo);
    Car carFour = carThree;
    cout << carFour << endl;
    carFour.move();
    carFour.setMaximumSpeed(200);
    carFour.setYearOfProduction(2006);
    cout << carFour;
    cout << carFour.getEnginePower() << endl;
}
