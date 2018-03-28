#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>
#include <vector>
#include <string>
#include "barbershop.h"

// set global variables
std::mutex mutex_awake;  // control the barber awake or not
std::mutex mutex_seat;  // lock of the seat
std::mutex mutex_print;  // lock of printing process
std::condition_variable cv_awake;  
bool barber_awake = false;
int waiting_number = 0;  //how many customers are waiting
std::string leaving;
std::vector<int>waiting_list;  //store the waiting customer's ID

/*------------------------Barber------------------------*/
// to control barber is awake or sleeping
void Barber::sleep_or_awake() {
	std::unique_lock < std::mutex > lk(mutex_awake);
	while (!barber_awake && waiting_number == 0) {
		std::cout << "\nBarber sleeping" << std::endl;
		std::cout << "Waiting room : " << std::endl;
		cv_awake.wait(lk);
	}
}

void Barber::cutting_hair() {
	//barber is awaking and let customer leave the seat
	{
		std::lock_guard<std::mutex> lk(mutex_seat);
		waiting_number -= 1;
	}	

	//cut hair here and notify the barbershop when cutting done
	current_customer = waiting_list[0];
	waiting_list.erase(waiting_list.begin());
	cutting_time = std::rand() % 5000 + 1000; // representing cutting hair need [1:5] seconds
	std::this_thread::sleep_for(std::chrono::milliseconds(cutting_time)); 
	barber_awake = false;  //reset the barber state
}

// to print the state of barber, customers and waiting room
void Barber::print() {
	std::lock_guard<std::mutex> lk(mutex_print);
	std::cout << "\nBarber cutting the hair of customer " << current_customer << std::endl;
	std::cout << "Waiting room : ";
	for (int i = 0; i < waiting_list.size(); i++) {
		std::cout << waiting_list[i] << "  ";
	}
	std::cout << std::endl;
	std::cout << leaving;
	leaving = "";
}


//simulate what the barber does
void Barber::go() {
	while (true) {
		// sleep until customer sends signal
		sleep_or_awake();

		// when customer arrives, barber awakes, let the customer leave the seat and works
		cutting_hair();

		// when cutting done, notify everyone
		print();
	}
}

/*-------------------Customer-------------------*/
// when customer arrives, he take a seat and write down his name on the waiting list
void Customer::wait_and_cut(int x) {
	std::unique_lock < std::mutex > lk(mutex_awake);
	waiting_number += 1;
	barber_awake = true;
	waiting_list.push_back(x);
}

// when all seats are taken, customer told barber he is leaving
void Customer::leave(int x) {
	std::lock_guard<std::mutex> lk(mutex_print);
	leaving = "Customer " + std::to_string(x) + " leaving\n";
}

// simulates what the customers do
void Customer::go(int x, int y) {
	ID = x;
	seats_num = y;

	if (waiting_number < seats_num) {
		wait_and_cut(ID);
		cv_awake.notify_all();
	} else {
		leave(ID);
	}
}

// generating new customers
void Customer::generating(int x) {

	const int threads_number = 100;
	std::thread t[threads_number];

	Customer customer;
	generating_time = 3000;  // every 3 seconds generates a new customer

	for (int i = 0; i < threads_number; i++) {
		std::this_thread::sleep_for(std::chrono::milliseconds(generating_time));
		t[i] = std::thread(&Customer::go, customer, i+1, x);
	}

	for (int i = 0; i < threads_number; i++) {
		t[i].join();
	}
}
