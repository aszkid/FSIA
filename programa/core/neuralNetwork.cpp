#include "neuralNetwork.hpp"

neuralNetwork::neuralNetwork(size_t nInput, size_t nHidden, size_t nOutput)
	: lHidden(nHidden), lInput(nInput), lOutput(nOutput)
{
	size_t i;

	for(i = 0; i < lHidden.size(); i++)
	{
		
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