#ifndef DECISION_H
#define DECISION_H
#include <vector>

using namespace std;

class DecisionVariable
{
private:
	vector<double> values;
	vector<double> converted_values;
public:
	int num_of_values;
	DecisionVariable(int num);
	vector<double> &vars(){ return values; }
	vector<double> &converted_vals() { return converted_values; }
};
#endif