/*#include <iostream>
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
	void calcOutputGradients(double targetVal);
	void calcHiddenGradients(const Layer& nextLayer);
	
private:
	double outVal;
	vector<Connection> outWeights;
	uint nIndex;
	double gradient;
	
	static double transferFunc(double x);
	static double transferFuncDerivative(double x);
	const double sumDOW(const Layer& nextLayer);
	
	
	static double randWeight() { return rand() / double(RAND_MAX); }
};

Neuron::Neuron(uint numOuts, uint _nIndex)
{
	for(uint c = 0; c < numOuts; ++c)
	{
		outWeights.push_back(Connection());
		outWeights.back().weight = Neuron::randWeight();
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
	// Tangent hiperbòlica
	return tanh(x);
}
double Neuron::transferFuncDerivative(double x)
{
	// Aproximació a la derivativa de tanh (1-tanh^2x)
	return 1.0 - x*x;
}
void Neuron::calcOutputGradients(double targetVal)
{
	double delta = targetVal - outVal;
	gradient = delta * Neuron::transferFunctionDerivative(outVal);
}
void Neuron::calcHiddenGradients(const Layer& nextLayer)
{
	double dow = sumDOW(nextLayer);
	gradient = dow * Neuron::transferFunctionDerivative(outVal);
}
const double Neuron::sumDOW(const Layer& nextLayer)
{
	double sum = 0.0;
	
	for(uint n = 0; n < 
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
			layer[n].updateInputWeights(prevLayer);
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
}*/



#include <ctime>
#include <chrono>
#include <thread>
#include <random>
#include "neuralNetwork.hpp"
#include "tinyxml2.h"
//#include "tinyxml2.cpp"

using std::vector;
using tinyxml2::XMLDocument;
using tinyxml2::XMLNode;
using tinyxml2::XMLError;
using tinyxml2::XMLElement;

typedef std::mt19937 G;
typedef std::uniform_int_distribution<> D;

G engine(time(NULL));

#define RAND_RANGE(low, up) D(low, up)(engine)

#define XML_FOREACH_NODE(node, parent, nodeName) for(XMLNode* node = parent->FirstChildElement(nodeName); node; node = node->NextSiblingElement(nodeName))
#define XML_NODE_CHILD_TEXT(node, child) node->FirstChildElement(child)->GetText()

enum key_mode_e {
	MAJOR,
	MINOR
};

struct note_s
{
	enum accidental_e {
		SHARP,
		FLAT,
		NATURAL,
		NONE
	};
	enum type_e {
		SIXTEENTH,
		EIGHTH,
		QUARTER,
		HALF,
		WHOLE
	};
	
	note_s()
		: duration(0), voice(0), p_step('0'), p_octave(0), accidental(accidental_e::NONE), type(type_e::HALF)
	{}

	int duration;
	int voice;
	char p_step;
	int p_octave;
	int accidental;
	int type;
};

#define ACCIDENTAL_TOTEXT(note) (note.accidental == note_s::accidental_e::FLAT ? "-Flat" : (note.accidental == note_s::accidental_e::SHARP ? "-Sharp" : ""))
#define TYPE_TOTEXT(note) (note.type == note_s::type_e::EIGHTH ? "Eighth" : (note.type == note_s::type_e::HALF ? "Half" : (note.type == note_s::type_e::QUARTER ? "Quarter" : (note.type == note_s::type_e::SIXTEENTH ? "Sixteenth" : "Whole"))))

int main(int argc, char** argv)
{
	XMLDocument doc;
	XMLError e = doc.LoadFile("test.xml");
	if(e != XMLError::XML_SUCCESS)
	{
		LOG("Failed to load file");
		return EXIT_FAILURE;
	}

	XMLNode* score = doc.FirstChildElement("score-partwise");
	XMLNode* part = score->FirstChildElement("part");

	vector<note_s> notes;
	XMLNode* attribs;
	XMLElement* key_e;
	int key_mode = key_mode_e::MAJOR;
	int key_fifths = 0;
	const char key_sharps_a[7] = {'F', 'C', 'G', 'D', 'A', 'E', 'B'};
	const char key_flats_a[7] = {'B', 'D', 'A', 'D', 'G', 'C', 'F'};

	XML_FOREACH_NODE(measure, part, "measure")
	{
		if(measure->FirstChildElement("attributes") != NULL)
		{
			LOG("Found new attribures for measure " << measure->ToElement()->Attribute("number"));
			attribs = measure->FirstChildElement("attributes");

			key_e = attribs->FirstChildElement("key");
			LOG("Key fifths: " << key_e->FirstChildElement("fifths")->GetText() << " in " << key_e->FirstChildElement("mode")->GetText() << " mode");

			std::string key_mode_t = key_e->FirstChildElement("mode")->GetText();
			if(key_mode_t.compare("major") == 0)
				key_mode = key_mode_e::MAJOR;
			else
				key_mode = key_mode_e::MINOR;

			key_e->FirstChildElement("fifths")->QueryIntText(&key_fifths);
		}
	

		XML_FOREACH_NODE(note, measure, "note")
		{
			XMLElement* note_e = note->ToElement();
			bool is_rest = false;

			XML_FOREACH_NODE(rest, note, "rest")
				is_rest = true;
			
			if(is_rest)
				break;

			note_s n;
			XMLElement* pitch_e = note->FirstChildElement("pitch");
			XMLElement* accid_e = note->FirstChildElement("accidental");
			XMLElement* type_e = note->FirstChildElement("type");

			if(accid_e != NULL)
			{
				std::string accid_t = accid_e->GetText();

				if(accid_t.compare("natural") == 0)
					n.accidental = note_s::accidental_e::NATURAL;
				else if(accid_t.compare("sharp") == 0)
					n.accidental = note_s::accidental_e::SHARP;
				else if(accid_t.compare("flat") == 0)
					n.accidental = note_s::accidental_e::FLAT;
			}
			
			n.p_step = pitch_e->FirstChildElement("step")->GetText()[0];

			for(int key_i = 0; key_i < key_fifths; key_i++)
			{
				if(key_mode == key_mode_e::MAJOR)
				{
					if(n.p_step == key_sharps_a[key_i] && n.accidental != note_s::accidental_e::NATURAL)
						n.accidental = note_s::accidental_e::SHARP;
				}
				else if(key_mode == key_mode_e::MINOR)
				{
					if(n.p_step == key_flats_a[key_i] && n.accidental != note_s::accidental_e::NATURAL)
						n.accidental = note_s::accidental_e::FLAT;
				}
			}

			if(n.accidental == note_s::accidental_e::NONE)
				n.accidental = note_s::accidental_e::NATURAL;

			std::string type_t = type_e->GetText();

			if(type_t.compare("half") == 0)
				n.type = note_s::type_e::HALF;
			else if(type_t.compare("quarter") == 0)
				n.type = note_s::type_e::QUARTER;
			else if(type_t.compare("eighth") == 0)
				n.type = note_s::type_e::EIGHTH;
			else if(type_t.compare("whole") == 0)
				n.type = note_s::type_e::WHOLE;
			else if(type_t.compare("16th") == 0)
				n.type = note_s::type_e::SIXTEENTH;

			note_e->FirstChildElement("duration")->QueryIntText(&n.duration);
			note_e->FirstChildElement("voice")->QueryIntText(&n.voice);
			pitch_e->FirstChildElement("octave")->QueryIntText(&n.p_octave);

			notes.push_back(n);
		}
	}

	for(note_s& note : notes)
	{


		LOG(TYPE_TOTEXT(note) << " " << note.p_step << ACCIDENTAL_TOTEXT(note) << " at octave " << note.p_octave);
	}

	/*for(int time_i = 0; time_i != -1; time_i++)
	{
		std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();



		// work
		//std::this_thread::sleep_for(std::chrono::milliseconds(RAND_RANGE(476, 528)));
		// end work

		std::chrono::high_resolution_clock::duration spent = std::chrono::high_resolution_clock::now() - start;
		uint todo = 1000 - std::chrono::duration_cast<std::chrono::milliseconds>(spent).count();
		if(todo > 0)
			std::this_thread::sleep_for(std::chrono::milliseconds(todo));
		std::chrono::high_resolution_clock::duration spent_final = std::chrono::high_resolution_clock::now() - start;
	}*/

	/*XML_FOREACH_NODE(part, score, "part")
	{
		LOG("Part " << part->ToElement()->Attribute("id"));

		XML_FOREACH_NODE(measure, part, "measure")
		{
			LOG("Measure " << measure->ToElement()->Attribute("number"));

			XML_FOREACH_NODE(note, measure, "note")
			{
				LOG("voice (" << XML_NODE_CHILD_TEXT(note, "voice") << ")");
			}
		}
	}*/

	neuralNetwork n(3, 3, 1);

	return EXIT_SUCCESS;
}

