#include <stdlib.h>
#include <math.h>
#include "mex.h"
void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
    /* input data is a m*n matrix in which each row denotes one data, total m  datas. This function will filter the index of ono-dominated solutions*/
    double *data = mxGetPr(prhs[0]);
    int m = (int)mxGetM(prhs[0]);
    int n = (int)mxGetN(prhs[0]);
     /* return data*/
    mxArray *tdata_ptr = mxCreateDoubleMatrix((size_t)1, (size_t)m, mxREAL);
    double *tdata = mxGetPr(tdata_ptr);
    /* initialize to zeros*/
    int i, j, k;
    int num_less, num_equal, num_large;
    double d1, d2;
    for (i = 0; i <m; i++)
    {
        for (k = 0; k <m; k++)
        {
            if (i != k)
            {
                num_less = 0;
                num_equal = 0;
                num_large = 0;
                for (j = 0; j <n; j++)
                {
                    d1 = data[j*m+i];
                    d2 = data[j*m+k];
                    if (d1<d2)
                    {
                    	num_less = num_less + 1;
                    }
                    else if (d1==d2)
                    {
                    	num_equal = num_equal + 1;
                    }
                    else 
                    {
                        num_large = num_large + 1;
                    }
                    
                }
                if (num_less == 0 && num_large > 0)
                {
                    tdata[i] = tdata[i] + 1;
                }
            }
        }   
    }
    /* find the non-dominated solution's id*/
    int total_number, counter;
    total_number = 0;
    counter = 0;
    for(i = 0; i <m; i++)
    {
        if(tdata[i] == 0)
        {
            total_number = total_number + 1;
        }
    }
    mxArray *rdata_ptr = mxCreateDoubleMatrix((size_t)1, (size_t)total_number, mxREAL);
    double *rdata = mxGetPr(rdata_ptr);
    for(i = 0; i < m; i++)
    {
        if(tdata[i] == 0)
        {
            rdata[counter] = i+1;
            counter = counter+1;
        }
    }
    nlhs = 1;
    plhs[0] = rdata_ptr;
}