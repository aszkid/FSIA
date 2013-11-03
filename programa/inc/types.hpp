#pragma once

#include <iostream>
#include <string>
#include <sstream>

inline void _LOG(std::string flag, std::string data)
{
	std::cout << '[' << flag << "] " << data << std::endl;
}

#define STREAM(ITEMS)                                             \
  ( ( dynamic_cast<std::ostringstream &> (                             \
         std::ostringstream() . seekp( 0, std::ios_base::cur ) << ITEMS )   \
    ) . str() )

#define L_INFO "INFO"
#define L_ERROR "ERROR"
#define L_DEBUG "DEBUG"
#define LOG(type, data) _LOG(type, STREAM(data))

typedef unsigned int uint;

struct note
{
	enum {
		C = 1 << 0,
		D = 1 << 1,
		E = 1 << 2,
		F = 1 << 3,
		G = 1 << 4,
		A = 1 << 5,
		B = 1 << 6,
		Sharp	= 1 << 7,
		Flat	= 1 << 8
	};

	uint height;
	float length;
	float intensity;
};

