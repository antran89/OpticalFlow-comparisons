/*
 * Copyright (C) 2015 An Tran.
 * This code is for research, please do not distribute it.
 *
 */


#include <mex.h>
#include <opencv2/opencv.hpp>
#include <opencv2/cudaoptflow.hpp>
#include "mexopencv.hpp"

using namespace cv;

/**
 * @brief myCudaBroxOpticalFlow
 *      To compute dense optical flow using Thomas Brox algorithm.
 *
 * @param prev_grey
 * @param grey
 * @param flow
 */
void myCudaBroxOpticalFlow(const Mat prev_grey, const Mat grey, Mat& flow)
{
    cuda::GpuMat d_prev_grey, d_grey, d_flow;
    d_prev_grey.upload( prev_grey );
    d_grey.upload( grey );

    Ptr<cuda::BroxOpticalFlow> broxFlow = cuda::BroxOpticalFlow::create();
    broxFlow->calc(d_prev_grey, d_grey, d_flow);

    d_flow.download( flow );
    //MedianBlurFlow( flow, 5 );
}

/**
 * @brief myCudaOpticalFlowDual_TVL1
 * TVL1 optical flow seems to be also accurate in large displacement optical flow.
 *
 * @param prev_grey
 * @param grey
 * @param flow
 */
void myCudaOpticalFlowDual_TVL1(const Mat prev_grey, const Mat grey, Mat& flow)
{
    cuda::GpuMat d_prev_grey, d_grey, d_flow;
    d_prev_grey.upload( prev_grey );
    d_grey.upload( grey );

    // create algo with default parameters
    Ptr<cuda::OpticalFlowDual_TVL1> tvl1Flow = cuda::OpticalFlowDual_TVL1::create();
    tvl1Flow->calc(d_prev_grey, d_grey, d_flow);
    //MedianBlurFlow(flow, 5);

    d_flow.download( flow );
}

/**
 * @brief Mex function to get TVL1 optical flow from a paire of images
 * [flows] = cpuOpticalFlow(image_filename1, image_filename2);
 *
 */
void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
    // Check the number of arguments
    if (nrhs < 2)
        mexErrMsgIdAndTxt("gpuOpticalFlow:error", "Wrong number of arguments");

    MxArray input = MxArray(prhs[0]);
    if (!input.isChar())        // focus when coding
        mexErrMsgIdAndTxt("gpuOpticalFlow:error", "Image1 input argument is not a string");
    std::string img1File = input.toString();
    
    MxArray output = MxArray(prhs[1]);
    if (!output.isChar())        // focus when coding
        mexErrMsgIdAndTxt("gpuOpticalFlow:error", "Image2 folder argument is not a string");
    std::string img2File = output.toString();

    bool isTVL1 = true;
    if (nrhs == 3) {
    MxArray useTVL1 = MxArray(prhs[2]);
    if (!useTVL1.isDouble())
        mexErrMsgIdAndTxt("gpuOpticalFlow:error", "useTVL1 must be a double");
        isTVL1 = useTVL1.toBool();
    }

    // compute optical flow
    Mat grey1, grey2, flow;
    Mat img1 = imread(img1File);
    cvtColor(img1, grey1, CV_BGR2GRAY);
    Mat img2 = imread(img2File);
    cvtColor(img2, grey2, CV_BGR2GRAY);

    if (isTVL1) {
        myCudaOpticalFlowDual_TVL1(grey1, grey2, flow);
    }
    else {
        grey1.convertTo(grey1, CV_32FC1);
        grey2.convertTo(grey2, CV_32FC1);
        myCudaBroxOpticalFlow(grey1, grey2, flow);
    }

    // assgin cv::Mat back to Matlab
    plhs[0] = MxArray(flow);
}
