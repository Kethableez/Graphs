#pragma once

#include <chrono>
#include <string>

#include "List.h"
#include "Matrix.h"

double BF_Alg(std::shared_ptr<G_List> workingGraph, int startingNode);
double BF_Alg(std::shared_ptr<G_Matrix> workingGraph, int startingNode);
void results(std::string pathString[], int distanceStorage[], int nodesAmount, int startingNode);