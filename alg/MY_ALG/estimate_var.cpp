#include <limits>
#include <algorithm>
#include <iostream>
#include <fstream>
#include "estimate_var.h"
#include "utils.h"
#include "reference_point.h"

using namespace std;

void EstimateVar::translate_objs(vector<DecisionVariable *> & dvs){
	for (int i = 0; i < num; i++) {
		double minf = numeric_limits<double>::max();
		for (int j = 0; j < dvs.size(); j++) {
			minf = min(minf, dvs[j]->vars()[i]);
		}
		ideal_points[i] = minf;

		for (int j = 0; j < dvs.size(); j++) {
			dvs[j]->converted_vals()[i] = dvs[j]->vars()[i] - ideal_points[i];
		}
	}
}

double EstimateVar::ASF(DecisionVariable* dv, vector<double> &weight) {
	double max_ratio = -numeric_limits<double>::max();
	for (int i = 0; i < num; i++) {
		double w = weight[i] ? weight[i] : 1e-6;
		max_ratio = max(max_ratio, dv->converted_vals()[i] / w);
	}
	return max_ratio;
}
/*
void EstimateVar::find_extreme_points(vector<DecisionVariable *> & dvs) {
	for (int i = 0; i < num; i++) {
		vector<double> w(num, 1e-6);
		w[i] = 1;
		double min_ASF = numeric_limits<double>::max();
		int min_ind = -1;
		for (int j = 0; j < dvs.size(); j++) {
			double asf = EstimateVar::ASF(dvs[j], w);
			if (asf < min_ASF) {
				min_ASF = asf;
				min_ind = j;
			}
		}
		extrme_point_ind[i] = min_ind;
	}
}*/


void EstimateVar::find_intercepts(vector<DecisionVariable *> & dvs){

	/*bool duplicate = false;
	for (int i = 0; !duplicate && i<extrme_point_ind.size(); i += 1)
	{
		for (int j = i + 1; !duplicate && j<extrme_point_ind.size(); j += 1)
		{
			duplicate = (extrme_point_ind[i] == extrme_point_ind[j]);
		}
	}
	bool negative_intercept = false;
	if (!duplicate) {
		// Find the equation of the hyperplane
		vector<double> b(num, 1.0);
		vector< vector<double> > A;
		for (int p = 0; p<extrme_point_ind.size(); p += 1) {
			A.push_back(dvs[extrme_point_ind[p]]->converted_vals()); // v1.11: objs() -> conv_objs()
		}
		vector<double> x;
		MathAux::GuassianElimination(&x, A, b);

		// Find intercepts
		for (int f = 0; f<intercepts.size(); f += 1) {
			intercepts[f] = 1.0 / x[f];
			if (x[f] < 0) {
				negative_intercept = true;
				break;
			}
		}
	}
	if (duplicate || negative_intercept) 
	{
		vector<double> max_objs = FindMaxObjectives(dvs);
		for (size_t f = 0; f<intercepts.size(); f += 1)
		{
			intercepts[f] = max_objs[f];
		}
	}*/
	vector<double> max_objs = FindMaxObjectives(dvs);
	for (size_t f = 0; f<intercepts.size(); f += 1)
	{
		intercepts[f] = max_objs[f];
	}
}

// 找到hyperplane的法向量
vector<double> EstimateVar::FindNormVector(vector<DecisionVariable *> & dvs) 
{
	// 先找到每个维度的最小值(已经保存在ideal_point中了)，再找到在每个维度上都最大的那个点，接着就可以求解了
	vector<vector<double>> simplex;
	vector<double> normal;
	
	simplex.resize(num);
	for (int i = 0; i < num; i++) {
		simplex[i].resize(num);
	}
	normal.resize(num);

	vector<double> vmin(num);
	// simplex对应位置初始化为intercept，vmin全为0，因为这个地方截距本来就是最大值，最小值本来也就是0
	for (int i = 0; i < num; i++) {
		simplex[i][i] = intercepts[i];
	}


	/*for (int i = 0; i < num; i++) {
		vmin[i] = 1.0E100;
	}
	for (int i = 0; i < num; i++) {
		simplex[i][i] = -1.0E100;
	}

	for (int i = 0; i < dvs.size(); i++) {
		for (int j = 0; j < num; j++) {
			if (dvs[i]->vars()[j] > simplex[j][j]) {
				simplex[j] = dvs[i]->vars();
				for (int k = 0; k < num; k++) {
					if (simplex[j][k] < vmin[k]) {
						vmin[k] = simplex[j][k];
					}
				}
			}
		}
	}*/
	
	// 找到了一些点，下面就可以开始计算了
	double norm = 0.0;
	for (int i = 0; i<num; i++)
	{
		normal[i] = 0.0;
		for (int k = 0; k<num; k++) normal[i] += simplex[k][i] - vmin[i];
	}
	for (int i = 0; i<num; i++) norm += normal[i] * normal[i];
	for (int i = 0; i<num; i++) normal[i] /= sqrt(norm);
	norm_vector = normal;
	return normal;
}

vector<double> EstimateVar::FindMaxObjectives(vector<DecisionVariable *> & dvs)
{
	vector<double> max_point(num, -numeric_limits<double>::max());
	for (size_t i = 0; i<dvs.size(); i += 1)
	{
		for (size_t f = 0; f<num; f += 1)
		{
			max_point[f] = max(max_point[f], dvs[i]->vars()[f]);
		}
	}
	return max_point;
}

void EstimateVar::generate(vector<vector<double>> *new_var) {
	// generate reference points
	vector<CReferencePoint> *rps = new vector<CReferencePoint>;
	GenerateReferencePoints(rps, num, divs);
	/*ofstream fun_out("D:\\rf.txt");
	//cout << rps->size() << endl;
	for (int i = 0; i < rps->size(); i++) {
		for (std::size_t j = 0; j < num; j++) {
			fun_out << rps->at(i).pos()[j] << "  ";
		}
		fun_out << endl;
		
		
	}
	fun_out.flush();
	fun_out.close();*/

	// change these references to the origianl space
	vector<vector<double>> original_ref_points;
	original_ref_points.resize(rps->size());
	//ofstream tf("D:\\tf.txt");
	
	for (int i = 0; i != original_ref_points.size(); i++ ) {
		original_ref_points[i].resize(num);
		for (int j = 0; j < num; j++) {
			original_ref_points[i][j] = ((rps->at(i)).pos()[j])*(intercepts[j] - ideal_points[j]) + ideal_points[j];
			//tf << original_ref_points[i][j] << " ";
			
		}
		//tf << endl;
		
	}
	//tf.flush();
	//tf.close();
	
	/*ofstream intercept_f("D:\\intercept.txt");
	ofstream ideal_f("d:\\ideal.txt");
	for (int i = 0; i < num; i++) {
		intercept_f << intercepts[i] << "";
		ideal_f << ideal_points[i] << "";
		intercept_f << endl;
		ideal_f << endl;
	}
	intercept_f.flush();
	intercept_f.close();
	ideal_f.flush();
	ideal_f.close();*/

	delete rps;
	
	// generate new solution[insert to pop, and the select...]
	for (int i = 0; i < original_ref_points.size(); i++) {
		//cout << i << endl;
		vector<double> this_ref(original_ref_points[i].begin(), original_ref_points[i].end());
		new_var->push_back(this_ref);

		vector<double> temp_up(original_ref_points[i].begin(), original_ref_points[i].end());
		// get vector with unit length
		vector<double> norm_v = normalize_vector(temp_up); // 只有在边界的时候，才是这样子，沿着坐标轴运动（近似坐标轴）。其余情况是沿着法线方向
		/*if (i > 0 && i < (original_ref_points.size() - 1))
		{
			norm_v = norm_vector;
		}*/
		// for +
		while (larger_than(upper, temp_up) && less_than(lower, temp_up)) {
			for (int j = 0; j != temp_up.size(); j++) {
				temp_up[j] += step*norm_v[j];
			}
			vector<double> new_ref(temp_up.begin(), temp_up.end());
			if (larger_than(upper, temp_up) && less_than(lower, temp_up)) {
				new_var->push_back(new_ref);
			}
		}
		// for -
		vector<double> temp_down(original_ref_points[i].begin(), original_ref_points[i].end());
		while (larger_than(upper, temp_down) && less_than(lower, temp_down)) {
			for (int j = 0; j != temp_down.size(); j++) {
				temp_down[j] -= step*norm_v[j];
			}
			vector<double> new_ref(temp_down.begin(), temp_down.end());
			if (larger_than(upper, temp_down) && less_than(lower, temp_down)) {
				new_var->push_back(new_ref);
			}
		}

	}


	/*保存下此时产生的solution*/
}

bool larger_than(vector<double> v1, vector<double> v2)
{
	int size = v1.size();
	for (int i = 0; i != size; i++)
	{
		if (v1[i] < v2[i]) return false;
	}
	return true;
}

bool less_than(vector<double> v1, vector<double> v2)
{
	int size = v1.size();
	for (int i = 0; i != size; i++)
	{
		if (v1[i] > v2[i]) return false;
	}
	return true;
}

double max_v(vector<double> v) {
	double m = -numeric_limits<double>::max();
	for (int i = 0; i != v.size(); i++) {
		m = max(m, v[i]);
	}
	return m;
}

double min_v(vector<double> v) {
	double m = numeric_limits<double>::max();
	for (int i = 0; i != v.size(); i++) {
		m = min(m, v[i]);
	}
	return m;
}

vector<double> normalize_vector(vector<double> v) {
	double l = 0.0;
	for (int i = 0; i < v.size(); i++) {
		l += pow(v[i], 2);
	}
	l = sqrt(l);
	for (int i = 0; i < v.size(); i++) {
		v[i] = v[i] / l;
	}
	return v;
}