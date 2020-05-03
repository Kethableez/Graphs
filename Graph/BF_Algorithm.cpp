#include "BF_Algorithm.h"

double BF_Alg(std::shared_ptr<G_List> workingGraph, int startingNode){
	std::string* pathStorage = new std::string[workingGraph->Get_Node()];
	
	auto startTime = std::chrono::high_resolution_clock::now();
	int* distanceStorage = new int[workingGraph->Get_Node()];

	for (int iterNodes = 0; iterNodes < workingGraph->Get_Node(); iterNodes++) distanceStorage[iterNodes] = Inf;
	
	distanceStorage[startingNode] = 0;
	
	for (int iterNodes = 1; iterNodes < workingGraph->Get_Node(); iterNodes++){
		for (int iterEdges = 0; iterEdges < workingGraph->Get_Edge(); iterEdges++){
			int temstart_Node = workingGraph->edgeGetter()[iterEdges].start_Node;
			int temend_Node = workingGraph->edgeGetter()[iterEdges].end_Node;
			int temValue = workingGraph->edgeGetter()[iterEdges].value;

			if (distanceStorage[temstart_Node] + temValue < distanceStorage[temend_Node]) distanceStorage[temend_Node] = distanceStorage[temstart_Node] + temValue;
			

			pathStorage[temend_Node].clear();
			pathStorage[temend_Node].append(pathStorage[temstart_Node] + std::to_string(temstart_Node) + "->");
		}
	}
	
	for (int iterNodes = 1; iterNodes < workingGraph->Get_Node(); iterNodes++){
		for (int iterEdges = 0; iterEdges < workingGraph->Get_Edge(); iterEdges++){
			int temstart_Node = workingGraph->edgeGetter()[iterEdges].start_Node;
			int temend_Node = workingGraph->edgeGetter()[iterEdges].end_Node;
			int temValue = workingGraph->edgeGetter()[iterEdges].value;

			if (distanceStorage[temstart_Node] + temValue < distanceStorage[temend_Node]){
				if (distanceStorage[temstart_Node] > Inf / 2) distanceStorage[temstart_Node] = Inf;

				else distanceStorage[temend_Node] = nInf;
				
			}
			else if (distanceStorage[temstart_Node] > Inf / 2) distanceStorage[temstart_Node] = Inf;
		}
	}

	auto endTime = std::chrono::high_resolution_clock::now();

	results(std::move(pathStorage), std::move(distanceStorage), workingGraph->Get_Node(), startingNode);
	delete[] pathStorage;
	delete[] distanceStorage;

	return std::chrono::duration<double, std::milli>(endTime - startTime).count();
}

double BF_Alg(std::shared_ptr<G_Matrix> workingGraph, int startingNode){
	std::string* pathStorage = new std::string[workingGraph->Get_Node()];
	auto startTime = std::chrono::high_resolution_clock::now();
	int* distanceStorage = new int[workingGraph->Get_Node()];

	for (int iterNodes = 0; iterNodes < workingGraph->Get_Node(); iterNodes++) distanceStorage[iterNodes] = Inf;
	
	distanceStorage[startingNode] = 0;
	
	for (int iterNodes = 1; iterNodes < workingGraph->Get_Node(); iterNodes++){
		for (int iterNodeCell = 0; iterNodeCell < workingGraph->Get_Node(); iterNodeCell++){
			for (int iterNodeCollumn = 0; iterNodeCollumn < workingGraph->Get_Node(); iterNodeCollumn++){
				int temstart_Node = iterNodeCell;
				int temend_Node = iterNodeCollumn;
				int temValue = workingGraph->getValue(iterNodeCell, iterNodeCollumn);
				
				if (distanceStorage[temstart_Node] + temValue < distanceStorage[temend_Node]){
					distanceStorage[temend_Node] = distanceStorage[startingNode] + temValue;
					pathStorage[temend_Node].clear();
					pathStorage[temend_Node].append(pathStorage[temstart_Node] + std::to_string(temstart_Node) + "->");
				}
			}
		}
	}
	
	for (int iterNodes = 1; iterNodes < workingGraph->Get_Node(); iterNodes++){
		for (int iterNodeCell = 0; iterNodeCell < workingGraph->Get_Node(); iterNodeCell++){
			for (int iterNodeCollumn = 0; iterNodeCollumn < workingGraph->Get_Node(); iterNodeCollumn++){
				int temstart_Node = iterNodeCell;
				int temend_Node = iterNodeCollumn;
				int temValue = workingGraph->getValue(iterNodeCell, iterNodeCollumn);
				
				if (distanceStorage[temstart_Node] + temValue < distanceStorage[temend_Node]){
					if (distanceStorage[temstart_Node] > Inf / 2) distanceStorage[temstart_Node] = Inf;
					
					else if (temValue == Inf) continue;
					
					else distanceStorage[temend_Node] = nInf;
					
				}
				else if (distanceStorage[temstart_Node] > Inf / 2) distanceStorage[temstart_Node] = Inf;	
			}
		}
	}
	
	auto endTime = std::chrono::high_resolution_clock::now();

	results(std::move(pathStorage), std::move(distanceStorage), workingGraph->Get_Node(), startingNode);
	delete[] pathStorage;
	delete[] distanceStorage;

	return std::chrono::duration<double, std::milli>(endTime - startTime).count();
}

void results(std::string pathString[], int distanceStorage[], int nodesAmount, int startingNode){
	std::ofstream resultsFile("Results.txt");
	resultsFile << "\n           Results            \n\n";
	resultsFile << "Starting node was : " << startingNode << std::endl;
	
	for (int itrNodes = 0; itrNodes < nodesAmount; itrNodes++){
		if (distanceStorage[itrNodes] == Inf){
			resultsFile << itrNodes << "-> inf" << std::endl;
			continue;
		}
		
		else if (distanceStorage[itrNodes] == nInf){
			resultsFile << itrNodes << "-> -inf" << std::endl;
			continue;
		}
		
		else{
			resultsFile << itrNodes << "->" << distanceStorage[itrNodes] << std::endl;
		}

		resultsFile << "  ";

		if ((distanceStorage[itrNodes] >= 100 && distanceStorage[itrNodes] < 1000) || (-100 > distanceStorage[itrNodes] && distanceStorage[itrNodes] <= -10)) {
			resultsFile << " The shortest path: " << pathString[itrNodes] << itrNodes;
		}
		
		else if (0 <= distanceStorage[itrNodes] && distanceStorage[itrNodes] < 10) {
			resultsFile << "   The shortest path: " << pathString[itrNodes] << itrNodes;
		}
		
		else if ((distanceStorage[itrNodes] >= 10 && distanceStorage[itrNodes] < 100) || (-10 < distanceStorage[itrNodes] && distanceStorage[itrNodes] < 0)) {
			resultsFile << "  The shortest path: " << pathString[itrNodes] << itrNodes;
		}
		
		else {
			resultsFile << "The shortest path: " << pathString[itrNodes] << itrNodes;
		}
		
	}

	resultsFile << std::endl;
}