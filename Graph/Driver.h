#pragma once

#include <iostream>

#include "Graph.h"
#include "BF_Algorithm.h"

template<typename T>
std::string Driver(int(&Vert_Tab)[5], double(&Dens_Tab)[4], int loops) {
	std::string result;

	for (auto density : Dens_Tab) {
		for (auto verticles : Vert_Tab) {
			double Time = 0;

			for (int iterLoops = 0; iterLoops < loops; iterLoops++) {
				std::shared_ptr<T> nGraph = std::make_shared<T>(verticles, density);
				int startingNode = rand() % verticles;

				nGraph->Fill(false);

				Time += BF_Alg(std::move(nGraph), startingNode);
			}

			result += std::to_string((Time * 100 / loops) + 1);
			result += ",";

			std::cout << verticles << " verticles done " << std::endl;
		}
		std::cout << density << " density done " << std::endl;
	}
	return result;
}