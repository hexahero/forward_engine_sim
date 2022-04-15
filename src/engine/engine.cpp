#include "engine.h"

Engine::Engine(Values vals, float ambientTemperature)
	:
	ambientTemperature(ambientTemperature),
	currentTemperature(ambientTemperature),
	I(vals.I),
	M(vals.M),
	V(vals.V),
	Tmax(vals.T),
	Hm(vals.Hm),
	Hv(vals.Hv),
	C(vals.C),
	iterations(0),
	deltaTime(0.1f),
	currentTorque(0.0f),
	isRunning(false),
	isOverheated(false)
{
	currentV = static_cast<float>(V[0]);

	std::cout
		<< "\n\n\nConfiguration: "
		<< "\nI: " << I
		<< "\nT: " << Tmax
		<< "\nHm: " << Hm
		<< "\nHv: " << Hv
		<< "\nC: " << C
		<< "\nAmbient Temperature: " << ambientTemperature;

	std::cout << "\nM: ";
	for (auto iter : M) std::cout << iter << ' ';
	std::cout << "\nV: ";
	for (auto iter : V) std::cout << iter << ' ';

}

void Engine::start() {
	
	if (!isRunning) isRunning = true;
}

void Engine::shutdown() {

	if (isRunning) isRunning = false;
}

void Engine::update_values() {
	
	std::this_thread::sleep_for(std::chrono::milliseconds(20));

	currentTorque = calculate_torque(currentV, V, M);
	float torqueInertiaRatio = currentTorque / I;

	currentTemperature = currentTemperature + (calculate_cooling_down_speed(currentTorque) + calculate_heating_up_speed()) * deltaTime;
	currentV = currentV + torqueInertiaRatio * deltaTime;

	++iterations;
	
	if (currentTemperature >= Tmax) isOverheated = true;
	
}

bool Engine::is_running() {

	if (isRunning) return true;
	else return false;
}

bool Engine::is_overheated() {

	if (isOverheated) return true;
	else return false;
}

float Engine::calculate_torque(float speed, std::vector<int> V, std::vector<int> M) {

	for (unsigned int i = 0; i != 6; ++i) {

		if (speed >= V[i] && speed <= V[i + 1]) {

			return (speed - V[i]) * (M[i + 1] - M[i]) / (V[i + 1] - V[i]) + M[i];
		}

	}

	return 0.0f;
}

float Engine::calculate_cooling_down_speed(float torque) {

	return torque * Hm + (currentV * currentV) * Hv;
}

float Engine::calculate_heating_up_speed() {

	return C * (ambientTemperature - currentTemperature);
}

unsigned int Engine::get_iterations() const {

	return iterations;
}

float Engine::get_time() const {

	return static_cast<float>(iterations) * deltaTime;
}

float Engine::get_temperature() const {

	return currentTemperature;
}

float Engine::get_currentV() const {

	return currentV;
}

float Engine::get_current_torque() const {
	
	return currentTorque;
}