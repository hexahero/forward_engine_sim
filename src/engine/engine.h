#pragma once

#include <iostream>
#include <sstream>
#include <vector>
#include <thread>

struct Values {

	unsigned int I{ 0 };
	unsigned int T{ 0 };
	float Hm{ 0 };
	float Hv{ 0 };
	float C{ 0 };
	std::vector<int> M;
	std::vector<int> V;

};

class Engine {

public:

	Engine(Values vals, float ambientTemperature);

	//Control
	void start();
	void shutdown();
	void update_values();

	//State
	bool is_running();
	bool is_overheated();

	//Get
	unsigned int get_iterations() const;
	float get_time() const;
	float get_temperature() const;
	float get_currentV() const;
	float get_current_torque() const;

private:

	//General data
	bool isRunning;
	bool isOverheated;

	unsigned int iterations;
	float deltaTime;

	float currentTemperature;
	float ambientTemperature;

	//Calculation data
	float currentV;
	float currentTorque;
	unsigned int I;
	std::vector<int> M;
	std::vector<int> V;
	unsigned int Tmax;
	float Hm;
	float Hv;
	float C;

	//Calculations
	float calculate_torque(float speed, std::vector<int> V, std::vector<int> M);
	float calculate_cooling_down_speed(float torque);
	float calculate_heating_up_speed();

};