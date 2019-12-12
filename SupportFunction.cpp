#include "SupportFunction.h"

int randomNumber(int minValue, int maxValue)
{
	std::random_device r; 
	std::mt19937 gen(r()); 
	std::uniform_int_distribution<>dis(minValue, maxValue); 
	return dis(gen); 
}
