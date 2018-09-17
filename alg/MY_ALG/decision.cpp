#include "decision.h"

DecisionVariable::DecisionVariable(int num)
{
	num_of_values = num;
	values.resize(num, 0.0);
	converted_values.resize(num, 0.0);
};


