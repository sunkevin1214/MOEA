#ifndef ESTIMATE_H
#define ESTIMATE_H

#include <vector>
#include "decision.h"

using namespace std;

class EstimateVar{
public:
	int num;
	vector<size_t> divs;
	vector<double> ideal_points;
	vector<int> extrme_point_ind;
	vector<double> intercepts;
	vector<double> norm_vector;
	vector<double> lower, upper;
	double step;
	EstimateVar(int n, vector<size_t> d, vector<double> low, vector<double> up, double s){
		num = n;
		ideal_points.resize(n);
		extrme_point_ind.resize(n);
		intercepts.resize(n);
		norm_vector.resize(n);
		divs = d;
		lower = low;
		upper = up;
		step = s;
	};
	void translate_objs(vector<DecisionVariable *> & dvs);
	double ASF(DecisionVariable* dv, vector<double> &weight);
	//void find_extreme_points(vector<DecisionVariable *> & dvs);
	void find_intercepts(vector<DecisionVariable *> & dvs);
	vector<double> EstimateVar::FindMaxObjectives(vector<DecisionVariable *> & dvs);
	void generate(vector<vector<double>> *new_var);
	vector<double> EstimateVar::FindNormVector(vector<DecisionVariable *> & dvs);
};
bool larger_than(vector<double> v1, vector<double> v2);
bool less_than(vector<double> v1, vector<double> v2);
double max_v(vector<double> v);
double min_v(vector<double> v);
vector<double> normalize_vector(vector<double> v);
#endif