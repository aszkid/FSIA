#pragma once

#include <iostream>
#include <memory>
#include <string>
#include <sstream>

using std::string;
using std::istringstream;

#define LOG(a, x) std::cout << "[" << a << "] " << x << std::endl
#define LOGE(x) LOG("ERROR", x)
#define LOGD(x) LOG("DEBUG", x)
#define LOGI(x) LOG("INFO", x)
#define LOGW(x) LOG("WARNING", x)


template<typename T, typename... Args>
std::unique_ptr<T> make_unique(Args&&... args)
{
	return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}

template<typename T>
T str_to(string d)
{
	T ret;
	istringstream(d) >> ret;
	return ret;
}
