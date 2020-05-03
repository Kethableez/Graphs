#pragma once

#include<memory>

#include "Graph.h"

static int Inf = 10000000;
static int nInf = -10000000;

class G_Matrix : public Graph {
	std::unique_ptr<std::unique_ptr<int[]>[]> Matrix;
public:
	void Fill(const bool Loops) const override;
	void Show() const override;
	
	const int readFile(const std::string fileName) override;
	void createInput(const int startNode) const override;

	const int getValue(int Arg1, int Arg2) const { return this->Matrix[Arg1][Arg2]; }

	G_Matrix(int nodesAmount, double density);

	G_Matrix() :Graph() {};
};