#pragma once

#include <windows.h>
#include <fstream>
#include "../engine/engine.h"

class Testbench {

public:

	//Simulation routines
	static void simulate(Engine engine);
	static void print_engine_data(Engine engine);
	static void log_engine_data(Engine engine);

private:

	static HANDLE consoleHandle;
	static std::ofstream ofstr;

};