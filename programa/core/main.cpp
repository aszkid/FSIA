#include <ctime>
#include <chrono>
#include <thread>
#include <map>
#include <random>
#include "neuralNetwork.hpp"
#include "tinyxml2.h"

typedef std::mt19937 randEng;
typedef std::uniform_int_distribution<> D;

randEng engine(time(NULL));

int int_rand_range(int low, int up)
{
	return D(low, up)(engine);
}

#define XML_FOREACH_NODE(node, parent, nodeName) for(XMLNode* node = parent->FirstChildElement(nodeName); node; node = node->NextSiblingElement(nodeName))

int main(int argc, char** argv)
{
	array<uint, 3> topology;
	topology[0] = 3;
	topology[1] = 3;
	topology[2] = 3;

	neuralNetwork n(topology);

	return EXIT_SUCCESS;
}

