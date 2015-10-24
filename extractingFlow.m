%% UCF101 dataset
addpath( genpath( '../Code' ) )
datasetFolder = '/home/tranlaman/Public/data/video/UCF101_img/';
outFolder = '/home/tranlaman/Public/data/video/UCF101_flow';

%% get classes of segmentation of first split.
params.infopath = '/home/tranlaman/Public/data/video/UCF101/ucfTrainTestlist';
fid = fopen(fullfile(params.infopath, 'classInd.txt'), 'r');
actions = textscan(fid, '%*d %s');
actions = actions{1};
fclose(fid);
l = length(actions);
assert(l == 101, 'BoW_main something wrong with reading classes files');

%% extract flow
for ind = 1:length(actions)
    d = dir(fullfile(datasetFolder, actions{ind}));
    videoFiles = {d(:).name}';
    videoFiles(ismember(videoFiles, {'.','..'})) = [];
    
    for i = 1:length(videoFiles)
        vidPath = fullfile(datasetFolder, actions{ind}, videoFiles{i});
        flowSavePath = fullfile(outFolder, actions{ind}, videoFiles{i});
        if ~exist(flowSavePath, 'dir')
            mkdir(flowSavePath);
        else
            continue;
        end
        extractFlowVideo(vidPath, flowSavePath);
    end
end