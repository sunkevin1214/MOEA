#include <iostream>
#include <cstdlib>
#include <string>
#include <sstream>
#include <vector>
#include <cassert>
#include <cmath>
#include "mex.h"
#include "ExampleProblems.h"
#include "TransFunctions.h"


//// Used namespaces. ///////////////////////////////////////////////////////


using std::vector;
using std::string;
using namespace WFG::Toolkit;
using namespace WFG::Toolkit::Examples;



double next_double( const double bound = 1.0 )
{
  assert(bound > 0.0);
  return bound * rand() / static_cast< double >( RAND_MAX );
}

vector< double> WFG_1_random_soln( int k,  int l )
{
  vector< double > result;  // the result vector
  for( int i = 0; i < k; i++ )
  {
    result.push_back( pow( next_double(), 50.0 ) );
  }
  for( int i = k; i < k+l; i++ )
  {
    result.push_back( 0.35 );
  }
  for( int i = 0; i < k+l; i++ )
  {
    result[i] *= 2.0*(i+1);
  }
  return result;
}

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    if (nrhs != 4)
    {
        mexErrMsgTxt("The number of the parameters is not correct. Should be 4.");
    }
    double *ptr_problemId = mxGetPr(prhs[0]);
    double *ptr_data = mxGetPr(prhs[1]);
    double *ptr_k = mxGetPr(prhs[2]);
    double *ptr_M = mxGetPr(prhs[3]);
    
    int problem_index = (int)*ptr_problemId;
    int k = (int)*ptr_k;
    int M = (int)*ptr_M;
    
    int n = (int)mxGetN(prhs[1]);
    vector<double> z;
    z.resize(n);
    for (int i = 0; i < n; i ++)
    {
        z[i] = ptr_data[i];
    }
   vector<double> rs = Problems::WFG1( z, k, M );
   
   mxArray *return_rs = mxCreateDoubleMatrix(1,M, mxREAL);
   double *value_ptr = mxGetPr(return_rs);
   for(int i = 0; i < rs.size(); i ++)
   {
       value_ptr[i] = rs[i];
   }
   nlhs = 1;
   plhs[0] = return_rs;
}
