#include "helpers.hpp"

std::string file_rel(std::string file)
{
	switch(_SYS)
	{
	case SYSTEM::Windows:
		return file;
	case SYSTEM::Linux:
		return file;
	case SYSTEM::MacOS:
		return file;
	default:
		return file;
	}
}
