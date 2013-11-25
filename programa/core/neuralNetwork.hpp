#pragma once

#include <iostream>
#include <vector>
#include <array>
#include <cmath>

#define LOG(x) std::cout << x << std::endl

using std::vector;
using std::array;

struct neuron;

typedef unsigned int uint;
typedef vector<neuron> layer;

struct connection
{
	double weight;
};

struct neuron
{
	vector<double> weights;
	double value;
};


class neuralNetwork
{
public:
	neuralNetwork(const size_t nInput, const size_t nHidden, const size_t nOutput);
	~neuralNetwork();

	void learn(vector<double> dInput, vector<double> dOutput);
	vector<double> get(vector<double> dInput);

private:
	layer lHidden;
	layer lInput;
	layer lOutput;

	array<layer, 3> network;

	static double transferFunction(double x);
	static double transferFunctionDerivative(double x);
};
