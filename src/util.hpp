#pragma once

#include <iostream>
#include <Windows.h>
#include <fstream>
#include <nlohmann/json.hpp>
#include "engine/engine.h"

Values load_values(std::string path) {

	char buffer[MAX_PATH];
	GetModuleFileNameA(NULL, buffer, MAX_PATH);
	std::string::size_type pos = std::string(buffer).find_last_of("\\/");

	std::string fullPath = std::string(buffer).substr(0, pos);

	nlohmann::json jsn;
	std::ifstream ifstr(fullPath + path);

	jsn = nlohmann::json::parse(ifstr);

	nlohmann::json arrM = jsn["M"];
	nlohmann::json arrV = jsn["V"];

	auto iter1 = arrM.begin();
	auto iter2 = arrV.begin();

	std::vector<int> vctrM;
	std::vector<int> vctrV;

	while (iter1 != arrM.end()) {

		vctrM.emplace_back(iter1.value());
		vctrV.emplace_back(iter2.value());

		++iter1;
		++iter2;
	}

	return Values{

		jsn["I"].get<unsigned int>(),
		jsn["T"].get<unsigned int>(),
		jsn["Hm"].get<float>(),
		jsn["Hv"].get<float>(),
		jsn["C"].get<float>(),
		vctrM,
		vctrV

	};
}