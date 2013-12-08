#include "neuralNetwork.hpp"

randDouble::randDouble(double up, double down)
	: gen(rd()), dist(up, down)
{}
double randDouble::generate()
{
	return dist(gen);
}

neuralNetwork::neuralNetwork(const array<uint, 3> topology)
	: rand(0.0, 1.0)
{
	lInput = vector<neuron>(topology[0]);
	lHidden = vector<neuron>(topology[1]);
	lOutput = vector<neuron>(topology[2]);

	LOGI("TOPOLOGY of the neural network:");
	LOGI("INPUTS:\t" << lInput.size());
	LOGI("OUTPUTS:\t" << lOutput.size());
	LOGI("HIDDEN:\t" << lHidden.size());

	neuron* n;
	for(size_t i = 0; i < lInput.size(); i++)
	{
		n = &lInput[i];
		LOGD("Initializing input '" << i << "' with random weight " << rand.generate());
	}
	for(size_t i = 0; i < lOutput.size(); i++)
	{
		n = &lOutput[i];
		LOGD("Initializing output '" << i << "' with random weight " << rand.generate());
	}
}
neuralNetwork::~neuralNetwork()
{

}


double neuralNetwork::transferFunction(double x)
{
	return tanh(x);
}
double neuralNetwork::transferFunctionDerivative(double x)
{
	return 1.0 - x*x;
}
vector<double> neuralNetwork::get(vector<double> dInput)
{
	return vector<double>();
}
