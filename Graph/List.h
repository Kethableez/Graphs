#pragma once

#include "Graph.h"

static int rVal = -1;

class G_List : public Graph{
private:
	Edge* in_Edge;
public:
	void Fill(const bool Loops) const override;
	void Show() const override;
	
	const int readFile(const std::string Filename)  override;
	void createInput(const int startNode) const override;

	const Edge* edgeGetter() { return this->in_Edge; }
	void addEdge(int nodeStart, int nodeEnd, int value, int flag) const;
	bool isExisting(int nodeStart, int nodeEnd) const;
	
	~G_List() { delete[] in_Edge; }
	G_List() :Graph() {};
	G_List(int in_amountOfNodes, int in_density) : Graph(in_amountOfNodes, in_density* in_amountOfNodes* (in_amountOfNodes - 1), in_density), in_Edge(new Edge[in_density * in_amountOfNodes * (in_amountOfNodes - 1)]) {}
};