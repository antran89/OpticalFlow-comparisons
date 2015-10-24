% Copyright (C) 2015 Tran Lam An.
% This code is for research, please do not distribute it.

function extractFlowVideo2( video_path, flowSavePath )
%EXTRACTFLOWVIDEO Summary of this function goes here
%   Detailed explanation goes here

d = dir(fullfile(video_path, '*.jpg'));

im1 = imread(fullfile(video_path, d(1).name));
for ind = 2:length(d)
    im2 = imread(fullfile(video_path, d(ind).name));
    flow = mex_OF(double(im1), double(im2));
    im1 = im2;

    scale = 16;
    mag = sqrt(flow(:,:,1).^2+flow(:,:,2).^2)*scale+128;
    mag = min(mag, 255);
    flow = flow*scale+128;
    flow = min(flow,255);
    flow = max(flow,0);

    [x,y,z] = size(flow);
    flow_image = zeros(x,y,3);
    flow_image(:,:,1:2) = flow;
    flow_image(:,:,3) = mag;

    flow_image = uint8(flow_image);
    imwrite(flow_image, fullfile(flowSavePath, num2str(ind-1, '%04d.jpg')));
end

end