# Some tips of using optical flow algorithm for action video datasets.

There are many available optical flow algorithm implementations online now. To choose which algorithms the best for you is your experimental efforts. In this repo, I will summarize some good implementations right now.

* [mex_OF](http://lmb.informatik.uni-freiburg.de/resources/binaries/eccv2004Matlab.zip) implemented from Brox ECCV2004 is not fast enough, but the results are good.
* Opencv implemented [Brox ECCV2004](http://docs.opencv.org/master/d7/d18/classcv_1_1cuda_1_1BroxOpticalFlow.html#gsc.tab=0) is fast, but not accurate engough. There might be a bug with Opencv implementation.
* Opencv implemented [TVL1](http://docs.opencv.org/master/d6/d39/classcv_1_1cuda_1_1OpticalFlowDual__TVL1.html#gsc.tab=0) is the best so far.