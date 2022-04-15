#include <iostream>
#include <vector>
#include "engine/engine.h"
#include "testbench/testbench.h"
#include "util.hpp"

int main() {

	float ambientTemp { 0.0f };

	std::cout << "Please, enter ambient temperature>";
	std::cin >> ambientTemp;

	Engine engine(load_values("\\config.json"), ambientTemp);

	Testbench::simulate(engine);

	return 0;
}