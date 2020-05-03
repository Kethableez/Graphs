#include "List.h"

void G_List::Fill(const bool Loops) const{
	if (this->m_Density == 1){
		int flag = 0;
		
		for (int iterstart_Node = 0; iterstart_Node < this->m_NodesAmount; iterstart_Node++){
			for (int iterend_Node = 0; iterend_Node < this->m_NodesAmount; iterend_Node++){
				if (iterstart_Node != iterend_Node){
					int valueOfConnection = rand() % 50 - rVal;
					
					while (valueOfConnection == 0) valueOfConnection = rand() % 50 - rVal;
					
					addEdge(iterstart_Node, iterend_Node, valueOfConnection, flag);
					flag++;
				}
			}
		}
	}
	
	else
	{
		for (int iterEdges = 0; iterEdges < this->m_EdgesAmount; iterEdges++){
			int randStartNode = rand() % this->m_NodesAmount;
			int randEndNode = rand() % this->m_NodesAmount;
			
			if (!this->isExisting(randStartNode, randEndNode)){
				int valueOfConnection = rand() % 50 - rVal;
				
				while (valueOfConnection == 0) valueOfConnection = rand() % 50 - rVal;
				
				if (randStartNode != randEndNode) addEdge(randStartNode, randEndNode, valueOfConnection, iterEdges);
				
				else if (Loops) addEdge(randStartNode, randEndNode, valueOfConnection, iterEdges);
			}
		}
	}
}

void G_List::Show() const {
	std::cout << " \n \n List representation of Graph \n \n ";
	
	for (int iterStartNode = 0; iterStartNode < this->m_NodesAmount; iterStartNode++){
		std::cout << iterStartNode;
		
		for (int iterEdge = 0; iterEdge < this->m_EdgesAmount; iterEdge++){
			if (this->in_Edge[iterEdge].start_Node == iterStartNode) std::cout << "->" << in_Edge[iterEdge].end_Node << "|" << in_Edge[iterEdge].value << "]";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

const int G_List::readFile(const std::string Filename){
	std::ifstream inFile(Filename);
	
	if (!inFile.is_open()){
		std::cerr << "File is not open" << std::endl;
		return -1; 
	}
	
	int startingAlgNode, startNode, endNode, value;
	inFile >> m_EdgesAmount >> m_NodesAmount >> startingAlgNode;
	this->in_Edge = new Edge[m_EdgesAmount];

	for (int iterEdge = 0; iterEdge < this->m_EdgesAmount; iterEdge++){
		inFile >> startNode >> endNode >> value;
		addEdge(startNode, endNode, value, iterEdge);
	}
	
	inFile.close();
	return startingAlgNode;
}

void G_List::createInput(const int startNode) const {
	std::ofstream out_file("out_input.txt");
	
	if (!out_file.is_open()){
		std::cerr << "File not open" << std::endl;
		return;
	}
	
	out_file << this->m_EdgesAmount << this->m_NodesAmount << startNode << std::endl;
	
	for (int iterEdge = 0; iterEdge < m_EdgesAmount; iterEdge++){
		out_file << in_Edge[iterEdge].start_Node << " " << in_Edge[iterEdge].end_Node << " " << in_Edge[iterEdge].value << "\n";
	}
	
	out_file.close();
}

void G_List::addEdge(int start_Node, int end_Node, int value, int flag) const{
	this->in_Edge[flag].start_Node = start_Node;
	this->in_Edge[flag].end_Node = end_Node;
	this->in_Edge[flag].value = value;
}

bool G_List::isExisting(int start_Node, int end_Node) const{
	for (int iterEdges = 0; iterEdges < this->m_EdgesAmount; iterEdges++){
		if (this->in_Edge[iterEdges].start_Node == start_Node && this->in_Edge[iterEdges].end_Node == end_Node) return true;
	}

	return false;
}