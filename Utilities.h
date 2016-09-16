#ifndef UTILITIES_H
#define UTILITIES_H


#include <random>
#include <string>

namespace Utilities
{ 

	inline int getRandomNumber(const int a, const int b)
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> dis(a, b);

		return dis(gen);
	}

	inline std::string getResourcesLocation()
	{
		return "Resources/";
	}

	inline std::string getFontName()
	{
		return "REDFIVE";
	}

	inline int getDefaultFontSize()
	{
		return 16;
	}

	inline int getTitleFontSize()
	{
		return 32;
	}
}
#endif // !UTILITIES_H

