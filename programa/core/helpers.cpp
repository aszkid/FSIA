#include "helpers.hpp"

std::string file_rel(std::string file)
{
	switch(_SYS)
	{
	case SYSTEM::Windows:
		return file;
	case SYSTEM::Linux:
		return "./bin/" + file;
	case SYSTEM::MacOS:
		return "./bin/" + file;
	default:
		return file;
	}
}