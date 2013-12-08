#pragma once

#include "base.hpp"

class Demo_1 : public Demo {
public:
	bool prepare();
	void run();
private:
	int foo;
};
