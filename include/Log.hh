#ifndef LOG_HH
#define LOG_HH

#include <chrono>
#include <stdio.h>
#include <ctime>


static void log(const char* message, ...)
{
#if _DEBUG
	auto now = std::chrono::system_clock::now();
	std::time_t time = std::chrono::system_clock::to_time_t(now);
	printf("[Simplex3D][%s]:%s", std::ctime(&time), message);
#endif
}




#endif //LOG_HH