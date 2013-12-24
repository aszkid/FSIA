#pragma once

#include "helpers.hpp"

#include <SFML/System.hpp>

class Demo
{
public:
	Demo();
	virtual ~Demo();
	
	virtual bool prepare();
	virtual void run();
};
