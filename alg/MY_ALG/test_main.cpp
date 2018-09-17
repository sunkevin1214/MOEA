#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <time.h>
#include <direct.h>
#include <cstdlib>
#include <cassert>
#include <cmath>
#include "decision.h"
#include "estimate_var.h"
#include "individual.h"
#include "population.h"
#include "problem_DTLZ.h"
#include "nondominated_sort.h"
#include "environmental_selection.h"
#include "reference_point.h"
#include "wfg/ExampleProblems.h"
#include "wfg/TransFunctions.h"
using namespace WFG::Toolkit;
using namespace WFG::Toolkit::Examples;


//#define POP_SIZE 300
//#include "config.h"

using namespace std;


//** Using a uniform random distribution, generate a number in [0,bound]. ***

double next_double(const double bound = 1.0)
{
	assert(bound > 0.0);

	return bound * rand() / static_cast< double >(RAND_MAX);
}


//** Create a random Pareto optimal solution for WFG1. **********************

vector< double > WFG_1_random_soln(const int k, const int l)
{
	vector< double > result;  // the result vector


	//---- Generate a random set of position parameters.

	for (int i = 0; i < k; i++)
	{
		// Account for polynomial bias.
		result.push_back(pow(next_double(), 50.0));
	}


	//---- Set the distance parameters.

	for (int i = k; i < k + l; i++)
	{
		result.push_back(0.35);
	}


	//---- Scale to the correct domains.

	for (int i = 0; i < k + l; i++)
	{
		result[i] *= 2.0*(i + 1);
	}


	//---- Done.

	return result;
}


//** Create a random Pareto optimal solution for WFG2-WFG7. *****************

vector< double > WFG_2_thru_7_random_soln(const int k, const int l)
{
	vector< double > result;  // the result vector


	//---- Generate a random set of position parameters.

	for (int i = 0; i < k; i++)
	{
		result.push_back(next_double());
	}


	//---- Set the distance parameters.

	for (int i = k; i < k + l; i++)
	{
		result.push_back(0.35);
	}


	//---- Scale to the correct domains.

	for (int i = 0; i < k + l; i++)
	{
		result[i] *= 2.0*(i + 1);
	}


	//---- Done.

	return result;
}


//** Create a random Pareto optimal solution for WFG8. **********************

vector< double > WFG_8_random_soln(const int k, const int l)
{
	vector< double > result;  // the result vector


	//---- Generate a random set of position parameters.

	for (int i = 0; i < k; i++)
	{
		result.push_back(next_double());
	}


	//---- Calculate the distance parameters.

	for (int i = k; i < k + l; i++)
	{
		const vector< double >  w(result.size(), 1.0);
		const double u = TransFunctions::r_sum(result, w);

		const double tmp1 = fabs(floor(0.5 - u) + 0.98 / 49.98);
		const double tmp2 = 0.02 + 49.98*(0.98 / 49.98 - (1.0 - 2.0*u)*tmp1);

		result.push_back(pow(0.35, pow(tmp2, -1.0)));
	}


	//---- Scale to the correct domains.

	for (int i = 0; i < k + l; i++)
	{
		result[i] *= 2.0*(i + 1);
	}


	//---- Done.

	return result;
}


//** Create a random Pareto optimal solution for WFG9. **********************

vector< double > WFG_9_random_soln(const int k, const int l)
{
	vector< double > result(k + l);  // the result vector


	//---- Generate a random set of position parameters.

	for (int i = 0; i < k; i++)
	{
		result[i] = next_double();
	}


	//---- Calculate the distance parameters.

	result[k + l - 1] = 0.35;  // the last distance parameter is easy

	for (int i = k + l - 2; i >= k; i--)
	{
		vector< double > result_sub;
		for (int j = i + 1; j < k + l; j++)
		{
			result_sub.push_back(result[j]);
		}

		const vector< double > w(result_sub.size(), 1.0);
		const double tmp1 = TransFunctions::r_sum(result_sub, w);

		result[i] = pow(0.35, pow(0.02 + 1.96*tmp1, -1.0));
	}


	//---- Scale to the correct domains.

	for (int i = 0; i < k + l; i++)
	{
		result[i] *= 2.0*(i + 1);
	}


	//---- Done.

	return result;
}




/*
the the type of the problem based on its' name
*/
string get_problem_type(string problem_name)
{
	const char *pname = problem_name.c_str();
	char result[10] = { '\0' };
	int leng_name = problem_name.length();
	for (int i = 0; i != leng_name; i++)
	{
		if (pname[i] > 47 && pname[i] < 59) {
			break;
		}
		else {
			result[i] = pname[i];
		}
	}
	string problem_type(result);
	if (problem_type != "dtlz" && problem_type != "wfg")
	{
		cout << "Error problem type: " << problem_type << endl;
		system("pause");
	}
	return problem_type;
}


void fill_empty_position(vector<vector<double>> *new_var, vector<double> padding, int k, int l, int obj)
{
	int num_decision_variable = k + l;
	// fill the left position 
	for (int i = 0; i < new_var->size(); i++) {
		new_var->at(i).resize(num_decision_variable);
		for (int j = k; j != num_decision_variable; j++) {
			(*new_var)[i][j] = padding[j - k];
		}
	}
}


void evaluate_x(string problem_name, CPopulation &pop, vector<vector<double>> *new_var, int k, int l, int obj)
{
	int num_decision_variable = k + l;
	pop.resize(new_var->size());
	for (int i = 0; i != new_var->size(); i++) 
	{
		
		CIndividual indiv(num_decision_variable, obj);
		for (int j = 0; j != num_decision_variable; j++) {
			indiv.vars()[j] = (*new_var)[i][j];
		}
		// evalue
		if (problem_name == "dtlz1") {
			CProblemDTLZ1 dtlz(obj, 5);
			dtlz.Evaluate(&indiv);
		}
		else if (problem_name == "dtlz2") {
			CProblemDTLZ2 dtlz(obj, 10);
			dtlz.Evaluate(&indiv);
		}
		else if (problem_name == "dtlz3") {
			CProblemDTLZ3 dtlz(obj, 10);
			dtlz.Evaluate(&indiv);
		}
		else if (problem_name == "dtlz4") {
			CProblemDTLZ4 dtlz(obj, 10);
			dtlz.Evaluate(&indiv);
		}
		else if (problem_name == "dtlz5") {
			CProblemDTLZ5 dtlz(obj, 10);
			dtlz.Evaluate(&indiv);
		}
		else if (problem_name == "dtlz6") {
			CProblemDTLZ6 dtlz(obj, 10);
			dtlz.Evaluate(&indiv);
		}
		else if (problem_name == "dtlz7") {
			CProblemDTLZ7 dtlz(obj, 20);
			dtlz.Evaluate(&indiv);
		}
		else if (problem_name == "wfg1") {
			 const vector<double> & f = WFG::Toolkit::Examples::Problems::WFG1((*new_var)[i], k, obj);
			 for (int j = 0; j != obj; j++) {
				 indiv.objs()[j] = f[j];
			 }
		}
		else if (problem_name == "wfg2") {
			const vector<double> & f = WFG::Toolkit::Examples::Problems::WFG2((*new_var)[i], k, obj);
			for (int j = 0; j != obj; j++) {
				indiv.objs()[j] = f[j];
			}
		}
		else if (problem_name == "wfg3") {
			
			const vector<double> & f = WFG::Toolkit::Examples::Problems::WFG3((*new_var)[i], k, obj);
			for (int j = 0; j != obj; j++) {
				indiv.objs()[j] = f[j];
			}
		}
		else if (problem_name == "wfg4") {
			const vector<double> & f = WFG::Toolkit::Examples::Problems::WFG4((*new_var)[i], k, obj);
			for (int j = 0; j != obj; j++) {
				indiv.objs()[j] = f[j];
			}
		}
		else if (problem_name == "wfg5") {
			const vector<double> & f = WFG::Toolkit::Examples::Problems::WFG5((*new_var)[i], k, obj);
			for (int j = 0; j != obj; j++) {
				indiv.objs()[j] = f[j];
			}
		}
		else if (problem_name == "wfg6") {
			const vector<double> & f = WFG::Toolkit::Examples::Problems::WFG6((*new_var)[i], k, obj);
			for (int j = 0; j != obj; j++) {
				indiv.objs()[j] = f[j];
			}
		}
		else if (problem_name == "wfg7") {
			const vector<double> & f = WFG::Toolkit::Examples::Problems::WFG7((*new_var)[i], k, obj);
			for (int j = 0; j != obj; j++) {
				indiv.objs()[j] = f[j];
			}
		}
		else if (problem_name == "wfg8") {
			const vector<double> & f = WFG::Toolkit::Examples::Problems::WFG8((*new_var)[i], k, obj);
			for (int j = 0; j != obj; j++) {
				indiv.objs()[j] = f[j];
			}
		}
		else if (problem_name == "wfg9") {
			const vector<double> & f = WFG::Toolkit::Examples::Problems::WFG9((*new_var)[i], k, obj);
			for (int j = 0; j != obj; j++) {
				indiv.objs()[j] = f[j];
			}
		}
		else {
			cout << "Invalid problem name : " << problem_name << endl;
			system("pause");
		}
		pop[i] = indiv;
	}

}

void rebuilt_padding(vector<double> &padding, string problem_name, int l, int k)
{
	if (problem_name == "dtlz1" || problem_name == "dtlz2" || problem_name == "dtlz3" || problem_name == "dtlz4") {
		for (int i = 0; i < l; i++)
		{
			padding[i] = 0.4999;
		}
	}
	

}

void execute(int counter, string problem_name, int obj, int pop_size, vector<size_t> div_decision, vector<size_t> div_objective, int k, int l, string problem_type, double step_size)
{
	// giving the path of the file where is the semi-finished solutions
	
	string result_path = problem_name+"\\log_" + to_string(counter);
	
	cout << result_path << endl;
	// read the semi-finished solutions to variables for further processing
	int num_decision_variable = k + l;
	vector<double> padding(l, 0.0);
	vector<DecisionVariable*> dvs;
	ifstream fin(result_path);
	//cout << result_path << endl;
	if (!fin) {
		cout << "file path of semi finished solutions  error\n"; system("pause");
	}
	double temp_line;
	long total_readed_count = -1;
	long line_count = 0;
	DecisionVariable* dv = NULL;
	while (fin >> temp_line) {
		total_readed_count += 1;
		int curr_pos = total_readed_count%num_decision_variable;
		if (curr_pos < k) {
			if (curr_pos == 0) {
				line_count++;
				dv = new DecisionVariable(k);
			}
			dv->vars()[curr_pos] = temp_line;
			if (curr_pos == k - 1) {
				dvs.push_back(dv);
			}
		}
		else
		{
			padding[curr_pos-k] += temp_line;
		}
	}
	fin.close();
	for (int i = 0; i != l; i++) padding[i] = padding[i] / line_count;
	// rebuilt padding(with some priori)
	rebuilt_padding(padding, problem_name, l, k);
	// estimate new solution in decision space
	vector<double> lower, upper;
	lower.resize(k);
	upper.resize(k);
	for (int i = 0; i != k; i++)
	{
		lower[i] = 0.0001;
		upper[i] = 0.990998; // for DTLZ, mean
	}
	EstimateVar estimate(k, div_decision, lower, upper, step_size);
	estimate.translate_objs(dvs);
//	estimate.find_extreme_points(dvs);
	estimate.find_intercepts(dvs);
	vector<vector<double>> *new_var = new vector<vector<double>>();
	cout << "Generating ...(" << problem_name << "," << obj << " objectives)" << endl;
	estimate.generate(new_var);
	//cout << new_var->size() << endl;
	 // fill elements
	fill_empty_position(new_var, padding, k, l, obj);
	// evaluate
	cout << "Evaluating (" << new_var->size() << ")..." << endl;
	CPopulation pop; //string problem_name, CPopulation &pop, vector<vector<double>> *new_var, int k, int l, int obj
	evaluate_x(problem_name, pop, new_var, k, l, obj);
	// non dominated sort
	CNondominatedSort::TFronts fronts = NondominatedSort(pop);
	// need the solutions in front#1
	vector<size_t> non_dominated_index = fronts[0];

	if (non_dominated_index.size() < pop_size) {
		cout << "Please adjust the step size so as to enough individuals be generated " << endl;
		system("pause");
	}
	else
	{
		cout << "Selection (" << non_dominated_index.size() << ")..." << endl;
		CPopulation non_dominated_pop;
		non_dominated_pop.resize(non_dominated_index.size());
		for (int s1 = 0; s1 != non_dominated_index.size(); s1++)
		{
			non_dominated_pop[s1] = pop[non_dominated_index[s1]];
		}
		

		vector<CReferencePoint> *rps = new vector<CReferencePoint>;
		GenerateReferencePoints(rps, obj, div_objective);
		CPopulation next;
		EnvironmentalSelection(&next, &non_dominated_pop, *rps, pop_size);
		// save to file
		string save_dir = "D:\\experiments\\group1\\MY\\";
		string to_path = save_dir;
		_mkdir(to_path.c_str());
		to_path += problem_name;
		_mkdir(to_path.c_str());
		to_path += "\\objs";
		to_path += to_string(obj);
		_mkdir(to_path.c_str());
		//cout << to_path << endl;

		to_path += "\\FUN.";
		stringstream str_to_counter;
		str_to_counter << (counter + 1);
		to_path += str_to_counter.str();
		to_path += ".txt";

		string var_path = save_dir;
		var_path += problem_name;
		var_path += "\\objs";
		var_path += to_string(obj);
		var_path += "\\VAR.";
		var_path += str_to_counter.str();
		var_path += ".txt";

		ofstream fun_out(to_path);
		ofstream var_out(var_path);
		for (int i = 0; i < next.size(); i++) {
			for (int j = 0; j < obj; j++) {
				fun_out << next[i].objs()[j] << " ";
			}
			fun_out << endl;
			for (int j = 0; j < num_decision_variable; j++) {
				var_out << next[i].vars()[j] << " ";
			}
			var_out << endl;
		}
		fun_out.flush();
		fun_out.close();
		var_out.flush();
		var_out.close();

		// need to delete
		for (int i = 0; i < dvs.size(); i++) {
			DecisionVariable* dv = dvs[i];
			if (dv != NULL) {
				delete dv;
			}
		}
		delete new_var;

	}
}

int main()
{
	ifstream exp_list("explist.ini");
	if (!exp_list) { cout << "We need the explist.ini file." << endl; return 1; }
	string exp_name;;
	while (exp_list >> exp_name) {
		ifstream exp_ini("Experiments\\" + exp_name);
		if (!exp_ini) { cout << exp_name << " file does not exist." << endl; continue; }
		string dummy = "";
		string problem_name = "";
		int obj = 0;
		int div1_decision, div2_decision, div1_objective, div2_objective;
		int pop_size = 0;
		int k, l;
		double step_size;
		exp_ini >> dummy >> dummy >> problem_name;
		exp_ini >> dummy >> dummy >> obj;
		exp_ini >> dummy >> dummy >> div1_decision >> div2_decision;
		exp_ini >> dummy >> dummy >> div1_objective >> div2_objective;
		exp_ini >> dummy >> dummy >> pop_size;
		exp_ini >> dummy >> dummy >> k;
		exp_ini >> dummy >> dummy >> l;
		exp_ini >> dummy >> dummy >> step_size;
		//l = 10;
		string problem_type = get_problem_type(problem_name);
		vector<size_t> div_vector_decision, div_vector_objective;
		div_vector_decision.push_back(div1_decision);
		if (div2_decision > 0) { div_vector_decision.push_back(div2_decision); div_vector_decision.resize(2); }
		div_vector_objective.push_back(div1_objective);
		if (div2_objective > 0) { div_vector_objective.push_back(div2_objective); div_vector_objective.resize(2); }

		for (int i = 0; i != 2; i++)
		{
			clock_t start, finish;
			double totaltime;
			start = clock();
			// execute the main part
			execute(i, problem_name, obj, pop_size, div_vector_decision, div_vector_objective, k, l, problem_type, step_size);
			// execution finished
			finish = clock();
			totaltime = (double)(finish - start) / CLOCKS_PER_SEC;
			cout << problem_name << "(" << obj << ")" << " run " << (i + 1) << " completed(" << totaltime << "S)" << endl;
		}


		exp_ini.close();
	}

	exp_list.close();
	return 0;
}


vector< double > problem_random_soln
(
const int k,
const int l,
const std::string fn
)
{
	if (fn == "WFG1")
	{
		return WFG_1_random_soln(k, l);
	}
	else if
		(
		fn == "WFG2" ||
		fn == "WFG3" ||
		fn == "WFG4" ||
		fn == "WFG5" ||
		fn == "WFG6" ||
		fn == "WFG7"
		)
	{
		return WFG_2_thru_7_random_soln(k, l);
	}
	else if (fn == "WFG8")
	{
		return WFG_8_random_soln(k, l);
	}
	else if (fn == "WFG9")
	{
		return WFG_9_random_soln(k, l);
	}
	
	else
	{
		assert(false);
		return vector< double >();
	}
}

//** Calculate the fitness for a problem given some parameter set. **********

vector< double > problem_calc_fitness
(
const vector< double >& z,
const int k,
const int M,
const std::string fn
)
{
	if (fn == "WFG1")
	{
		return Problems::WFG1(z, k, M);
	}
	else if (fn == "WFG2")
	{
		return Problems::WFG2(z, k, M);
	}
	else if (fn == "WFG3")
	{
		return Problems::WFG3(z, k, M);
	}
	else if (fn == "WFG4")
	{
		return Problems::WFG4(z, k, M);
	}
	else if (fn == "WFG5")
	{
		return Problems::WFG5(z, k, M);
	}
	else if (fn == "WFG6")
	{
		return Problems::WFG6(z, k, M);
	}
	else if (fn == "WFG7")
	{
		return Problems::WFG7(z, k, M);
	}
	else if (fn == "WFG8")
	{
		return Problems::WFG8(z, k, M);
	}
	else if (fn == "WFG9")
	{
		return Problems::WFG9(z, k, M);
	}
	else
	{
		assert(false);
		return vector< double >();
	}
}




