#pragma once

#include "helpers.hpp"

class Demo
{
public:
	Demo();
	virtual ~Demo();
	
	virtual bool prepare();
	virtual void run();
};
