addpath('/home/tranlaman/Desktop/cv-workspace/OpticalFlow/brox_eccv2004')

% video_path = '/home/tranlaman/Public/data/video/SaliencyMap/UCF101/ApplyEyeMakeup/v_ApplyEyeMakeup_g01_c02';
video_path = '/home/tranlaman/Public/data/video/UCF101_img/ApplyEyeMakeup/v_ApplyEyeMakeup_g01_c02';

save_path = 'output';
if ~exist(save_path, 'dir')
    mkdir(save_path);
end

tic
extractFlowVideo(video_path, save_path, 1);
% extractFlowVideo2(video_path, save_path);
toc