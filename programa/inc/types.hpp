#pragma once

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

	uint pitch;
	uint length;
};
