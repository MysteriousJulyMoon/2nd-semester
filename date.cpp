#include"date.hpp"
#include <fstream>
#include <chrono>
#include <ctime>


int dateday()
{
    std::time_t t = std::time(0);
    std::tm* now = std::localtime(&t);

    return now->tm_mday;
	
}

int datemon()
{
    std::time_t t = std::time(0);
    std::tm* now = std::localtime(&t);

    return now->tm_mon;

}

int dateyear()
{
    std::time_t t = std::time(0);
    std::tm* now = std::localtime(&t);

    return now->tm_year;

}

int datehour()
{
    std::time_t t = std::time(0);
    std::tm* now = std::localtime(&t);

    return now->tm_hour;

}

int datemin()
{
    std::time_t t = std::time(0);
    std::tm* now = std::localtime(&t);

    return now->tm_min;

}

int datesec()
{
    std::time_t t = std::time(0);
    std::tm* now = std::localtime(&t);

    return now->tm_sec;

}
