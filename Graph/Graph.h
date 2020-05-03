#pragma once

#include <fstream>
#include <cstdlib>
#include <iostream>
#include <ctime>
#include <string>

#include "Edge.h"

class Graph{
protected:
	int m_NodesAmount;
	int m_EdgesAmount;
	double m_Density;
public:
	const int Get_Node(){
		return this->m_NodesAmount;
	}
	const int Get_Edge(){
		return this->m_EdgesAmount;
	}

	virtual void Fill(const bool Loops) const = 0;
	virtual void Show() const = 0;
	virtual const int readFile(const std::string Filename) = 0;
	virtual void createInput(const int startNode) const = 0;

	virtual ~Graph() {};
	Graph(int in_Nodes, int in_Edges, double in_density) : m_NodesAmount(in_Nodes), m_EdgesAmount(in_Edges), m_Density(in_density) {};
	Graph() {};

};