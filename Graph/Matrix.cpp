#include "Matrix.h"
#include "List.h"

G_Matrix::G_Matrix(int nodesAmount, double density) :Graph(nodesAmount, static_cast<int>(density* nodesAmount* (nodesAmount - 1)), density), Matrix(std::make_unique<std::unique_ptr<int[]>[]>(nodesAmount)){

	for (int iterNodesCell = 0; iterNodesCell < this->m_NodesAmount; iterNodesCell++){
		Matrix[iterNodesCell] = std::make_unique<int[]>(nodesAmount);
		
		for (int iterNodesCollumn = 0; iterNodesCollumn < this->m_NodesAmount; iterNodesCollumn++){
			if (iterNodesCell == iterNodesCollumn) Matrix[iterNodesCell][iterNodesCollumn] = 0;
			
			else Matrix[iterNodesCell][iterNodesCollumn] = Inf;
			
		}
	}
}


void G_Matrix::Fill(const bool Loops) const{
	if (this->m_Density == 1){
		for (int iterNodesCell = 0; iterNodesCell < this->m_NodesAmount; iterNodesCell++){
			for (int iterNodesCollumn = 0; iterNodesCollumn < this->m_NodesAmount; iterNodesCollumn++){
				if (iterNodesCell != iterNodesCollumn){
					int randValue = rand() % 50 - rVal;
					while (randValue == 0) randValue = rand() % 50 - rVal;
					Matrix[iterNodesCell][iterNodesCollumn] = randValue;
				}
			}
		}
	}
	
	else{
		int iterEdges = this->m_EdgesAmount;
		
		while (iterEdges != 0){
			int cellNode = rand() % this->m_NodesAmount;
			int collumnNode = rand() % this->m_NodesAmount;
			
			if (Matrix[cellNode][collumnNode] == 0 || Matrix[cellNode][collumnNode] == Inf){
				int randValue = rand() % 50 - rVal;
				
				while (randValue == 0) randValue = rand() % 50 - rVal;

				if (cellNode != collumnNode){
					Matrix[cellNode][collumnNode] = randValue;
					--iterEdges;
				}
				else if (Loops){
					Matrix[cellNode][collumnNode] = randValue;
					--iterEdges;
				}
			}
		}
	}
}

void G_Matrix::Show() const{
	std::cout << "\n Matrix represetation of Graph \n\n";
	
	for (int nodeIter = 0; nodeIter < this->m_NodesAmount; nodeIter++)	std::cout << "  " << nodeIter;
	
	std::cout << std::endl << std::endl;
	
	for (int nodeCell = 0; nodeCell < this->m_NodesAmount; nodeCell++){
		std::cout << nodeCell << " *";
		
		for (int nodeCollumn = 0; nodeCollumn < this->m_NodesAmount; nodeCollumn++){
			int temporaryMatrixValue = Matrix[nodeCell][nodeCollumn];
			
			if (temporaryMatrixValue == Inf) std::cout << "#";
			
			else std::cout << temporaryMatrixValue;
			
			std::cout << "  ";

		}
		std::cout << "*" << std::endl;
	}
	std::cout << std::endl;
}

const int G_Matrix::readFile(const std::string fileName)
{
	std::ifstream inFile(fileName);
	
	if (!inFile.is_open()){
		std::cerr << " Input file is not open" << std::endl;
		return -1;
	}
	
	int startingNode, nodeStart, nodeEnd, value;
	
	inFile >> this->m_EdgesAmount >> this->m_NodesAmount >> startingNode;
	
	Matrix = std::make_unique<std::unique_ptr<int[]>[]>(this->m_NodesAmount);
	
	for (int iterNodesCell = 0; iterNodesCell < this->m_NodesAmount; iterNodesCell++){
		Matrix[iterNodesCell] = std::make_unique<int[]>(this->m_NodesAmount);
		
		for (int iterNodesCollumn = 0; iterNodesCollumn < this->m_NodesAmount; iterNodesCollumn++){
			if (iterNodesCell == iterNodesCollumn) Matrix[iterNodesCell][iterNodesCollumn] = 0;
			
			else Matrix[iterNodesCell][iterNodesCollumn] = Inf;
			
		}
	}
	
	for (int iterEdge = 0; iterEdge < this->m_EdgesAmount; iterEdge++){
		inFile >> nodeStart >> nodeEnd >> value;
		Matrix[nodeStart][nodeEnd] = value;
	}
	
	inFile.close();
	return startingNode;
}

void G_Matrix::createInput(const int startNode) const{
	std::ofstream outFile("OutInput.txt");
	
	if (!outFile.is_open()){
		std::cerr << " Output File not Created";
		return;
	}

	outFile << this->m_EdgesAmount << " " << this->m_NodesAmount << " " << startNode << std::endl;
	
	for (int iterNodesCell = 0; iterNodesCell < this->m_NodesAmount; iterNodesCell++){
		for (int iterNodesCollumn = 0; iterNodesCollumn < this->m_NodesAmount; iterNodesCollumn++){
			if (Matrix[iterNodesCell][iterNodesCollumn] != Inf && Matrix[iterNodesCell][iterNodesCollumn] != 0) outFile << iterNodesCell << " " << iterNodesCollumn << " " << Matrix[iterNodesCell][iterNodesCollumn] << std::endl;
		}
	}
	
	outFile.close();
}