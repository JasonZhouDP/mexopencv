/**
 * @file bilateralFilter.cpp
 * @brief mex interface for bilateralFilter
 * @author Kota Yamaguchi
 * @date 2011
 * @details
 *
 * Usage:
 * @code
 *   result = bilateralFilter(img, 'Diameter', 7, ...)
 * @endcode
 */
#include "cvmx.hpp"
#include <string.h>
using namespace cv;

/**
 * Main entry called from Matlab
 * @param nlhs number of left-hand-side arguments
 * @param plhs pointers to mxArrays in the left-hand-side
 * @param nrhs number of right-hand-side arguments
 * @param prhs pointers to mxArrays in the right-hand-side
 */
void mexFunction( int nlhs, mxArray *plhs[],
                  int nrhs, const mxArray *prhs[] )
{
	// Check the number of arguments
	if (nrhs<1 || ((nrhs%2)!=1) || nlhs>1)
        mexErrMsgIdAndTxt("bilateralFilter:invalidArgs","Wrong number of arguments");
	
	// Option processing
	int d = 7;
	double sigmaColor = 50.0;
	double sigmaSpace = 50.0;
	int borderType = BORDER_DEFAULT;
	for (int i=1; i<nrhs; i+=2) {
		if (mxGetClassID(prhs[i])==mxCHAR_CLASS) {
			std::string key(cvmxArrayToString(prhs[i]));
			mxClassID classid = mxGetClassID(prhs[i+1]);
			if (key=="Diameter" && classid==mxDOUBLE_CLASS)
				d = static_cast<int>(mxGetScalar(prhs[i+1]));
			else if (key=="SigmaColor" && classid==mxDOUBLE_CLASS)
				sigmaColor = mxGetScalar(prhs[i+1]);
			else if (key=="SigmaSpace" && classid==mxDOUBLE_CLASS)
				sigmaSpace = mxGetScalar(prhs[i+1]);
			else if (key=="BorderType" && classid==mxCHAR_CLASS)
				borderType = BorderType::get(prhs[i+1]);
			else
				mexErrMsgIdAndTxt("bilateralFilter:invalidOption","Unrecognized option");
		}
		else
			mexErrMsgIdAndTxt("bilateralFilter:invalidOption","Unrecognized option");
	}
	
	// Process
	Mat img = cvmxArrayToMat(prhs[0],CV_32F);
	Mat dst;
	bilateralFilter(img, dst, d, sigmaColor, sigmaSpace, borderType);
	plhs[0] = cvmxArrayFromMat(dst,mxGetClassID(prhs[0]));
}