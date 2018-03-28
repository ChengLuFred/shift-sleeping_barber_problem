#pragma once

class Barber {
private:
	int current_customer;
	int cutting_time;
public:
	void sleep_or_awake();
	void cutting_hair();
	void print();
	void go();
};

class Customer {
private:
	int ID;
	int seats_num;
	int generating_time;
public:
	void wait_and_cut(int x);
	void leave(int x);
	void go(int x, int y);
	void generating(int x);
};