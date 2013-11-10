#include <iostream>
#include <vector>
#include <cstdlib>
#include <cassert>
#include <cmath>

using std::cout;
using std::endl;
using std::vector;

#define OUT(x) cout << x << endl

class Neuron;
typedef unsigned int uint;
typedef vector<Neuron> Layer;

double randWeight()
{
	return rand() / double(RAND_MAX);
}

struct Connection
{
	double weight;
	double deltaWeight;
};

class Neuron
{
public:
	Neuron(uint numOuts, uint _nIndex);
	~Neuron();
	
	void feedForward(const Layer& prevLayer);
	
	void setOutVal(double val) { outVal = val; };
	const double getOutVal() { return outVal };
	
private:
	double outVal;
	vector<Connection> outWeights;
	uint nIndex;
	
	static double transferFunc(double x);
	static double transferFuncDerivative(double x);
};

Neuron::Neuron(uint numOuts, uint _nIndex)
{
	for(uint c = 0; c < numOuts; ++c)
	{
		outWeights.push_back(Connection());
		outWeights.back().weight = randWeight();
	}
	
	nIndex = _nIndex;
}
Neuron::~Neuron()
{}
void Neuron::feedForward(const Layer& prevLayer)
{
	double sum = 0.0;
	
	for(uint n = 0; n < prevLayer.size(); ++n)
	{
		sum += prevLayer[n].getOutVal() * prevLayer[n].outWeights[nIndex].weight;
	}
	
	outVal = Neuron::transferFunc(sum);
}

double Neuron::transferFunc(double x)
{
	return tanh(x);
}
double Neuron::transferFuncDerivative(double x)
{
	return 1.0 - x*x;
}

class Net
{
public:
	Net(const vector<uint> &topology);
	~Net();
	
	void feedForward(const vector<double> &inputs);
	void backProp(const vector<double> &targets);
	const void getResults(vector<double> &results);
	
private:
	vector<Layer> layers;
	double error;
	double recentAverageSmoothingFactor
	double recentAverageError;
};

Net::Net(const vector<uint> &topology)
{
	uint numLayers = topology.size();
	
	for(uint layerNum = 0; layerNum < numLayers; ++layerNum)
	{
		layers.push_back(Layer());
		uint numOuts = (layerNum == numLayers - 1 ? 0 : topology[layerNum + 1]);
		
		for(uint neuronNum = 0; neuronNum < topology[layerNum] + 1; ++neuronNum)
		{
			OUT("Creating neuron (" << neuronNum << ")...");
			layers.back().push_back(Neuron(numOuts, neuronNum));
		}
	}
}
Net::~Net()
{}

void Net::feedForward(const vector<double> &inputs)
{
	assert(inputs.size() == layers[0].size() - 1);
	
	for(uint i = 0; i < inputs.size(); ++i)
	{
		layers[0][i].setOutVal(inputs[i]);
	}
	
	for(uint layerNum = 1; layerNum < layers.size(); ++layerNum)
	{
		Layer& prevLayer = layers[layerNum - 1];
		
		for(uint n = 0; n < layers[layerNum].size() - 1; ++n)
		{
			layers[layerNum][n].feedForward(prevLayer);
		}
	}
}
void Net::backProp(const vector<double> &targets)
{
	Layer& outLayer = layers.back();
	error = 0.0;
	
	for(uint n = 0; n < outLayer.size() - 1; ++n)
	{
		double delta = targets[n] - outLayer[n].getOutVal();
		error += delta * delta;
	}
	
	error /= outLayer.size() - 1;
	error = sqrt(error);
	
	recentAverageError = 
		(recentAverageError * recentAverageSmoothingFactor + error) / 
		(recentAverageSmoothingFactor + 1.0);
	
	for(uint n = 0; n < outLayer.size() - 1; ++n)
	{
		outLayer[n].calcOutGradients(targets);
	}
	
	for(uint layerNum = layers.size() - 2; layerNum > 0; --layerNum)
	{
		Layer& hiddenLayer = layers[layerNum];
		Layer& nextLayer = layers[layerNum + 1];
		
		for(uint n = 0; n < hiddenLayer.size(); ++n)
		{
			hiddenLayer[n].calcHiddenGradients(nextLayer);
		}
	}
	
	for(uint layerNum = layers.size() - 1; layerNum > 0; --layerNum)
	{
		Layer& layer = layers[layerNum];
		Layer& prevLayer = layers[layerNum - 1];
		
		for(uint n = 0; n < layer.size() - 1; ++n)
		{
			
		}
	}
	
}
const void Net::getResults(vector<double> &results)
{
	
}

int main()
{
	srand(time(NULL));

	vector<uint> topology = {3, 2, 1};
	Net n(topology);
	
	vector<double> inputs;
	vector<double> targets;
	vector<double> results;
	
	n.feedForward(inputs);
	n.backProp(targets);
	n.getResults(results);
	
	return 0;
}
