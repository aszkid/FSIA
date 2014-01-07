#pragma once

#include <iostream>
#include <memory>
#include <string>
#include <sstream>

using std::string;
using std::istringstream;
using std::ostringstream;

#define LOG(a, x) std::cout << "[" << a << "] " << x << std::endl
#define LOGE(x) LOG("ERROR", x)
#define LOGD(x) LOG("DEBUG", x)
#define LOGI(x) LOG("INFO", x)
#define LOGW(x) LOG("WARNING", x)

#define STREAM(ITEMS)                                             \
  ( ( dynamic_cast<ostringstream &> (                             \
         ostringstream() . seekp( 0, std::ios_base::cur ) << ITEMS )   \
    ) . str() )

enum SYSTEM {
	Windows,
	Linux,
	MacOS
};


#ifdef _WIN32
	static const unsigned int _SYS = SYSTEM::Windows;
#elif __linx__
	static const unsigned int _SYS = SYSTEM::Linux;
#elif __APPLE__ && __MACH__
	static const unsigned int _SYS = SYSTEM::MacOS;
#endif

/*template<typename T, typename... Args>
std::unique_ptr<T> make_unique(Args&&... args)
{
	return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}*/

template<typename T>
T str_to(string d)
{
	T ret;
	istringstream(d) >> ret;
	return ret;
}

std::string file_rel(std::string file);