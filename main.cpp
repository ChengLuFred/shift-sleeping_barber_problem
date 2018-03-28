#include <iostream>
#include <thread>
#include "barbershop.h"

int main()
{
	//notify user to input seats number
	int seats_num;
	std::cout << "> Please input the seats number of barbershop : ";
	std::cin >> seats_num;

	//create the barber&customer objects also the threads
	Barber barber;
	Customer customer;

	std::thread t1(&Barber::go, barber);
	std::thread t2(&Customer::generating, customer, seats_num);

	t1.join();
	t2.join();
	
	return 0;
}
