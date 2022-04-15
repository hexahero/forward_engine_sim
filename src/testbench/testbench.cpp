#include "testbench.h"

HANDLE Testbench::consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
std::ofstream Testbench::ofstr = std::ofstream("bin/log.txt");

void Testbench::simulate(Engine engine) {
	
	if (!ofstr) {

		std::cout << "Data export error\n";
		return;
	}

	ofstr << "==========Simulation Initiated==========\n";

	engine.start();

	while (engine.is_running()) {

		engine.update_values();
		print_engine_data(engine);
		log_engine_data(engine);

		if (engine.is_overheated()) {

			engine.shutdown();
			
			std::stringstream sstr;
			sstr << "Sumilation stopped. Engine overheated in: "
				 << engine.get_time()
				 << "\nIterations: "
				 << engine.get_iterations();

			std::cout << sstr.str() << "\n(See bin/log.txt file for detailed information)";
			ofstr << sstr.str();
	
		}

	}

	ofstr.close();
}

void Testbench::print_engine_data(Engine engine) {

	SetConsoleCursorPosition(consoleHandle, COORD{ 0, 0 });

	std::stringstream sstr;

	sstr << "---------------------------------------\t\n"
		 << "Engine temperature:\t\t" << engine.get_temperature() << "\t\t\n"
		 << "Time since engine start:\t" << engine.get_time() << "\t\t\n"
		 << "---------------------------------------\t\n";

	std::cout << sstr.str();

}

void Testbench::log_engine_data(Engine engine) {
	
	ofstr
		<< "Temp: " << engine.get_temperature()
		<< " V: " << engine.get_currentV() << " M: "
		<< engine.get_current_torque()
		<< '\n';
		
}