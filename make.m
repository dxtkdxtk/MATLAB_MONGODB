% ������Ŀ
boostPath = 'E:\boost_1_55_0_32';
mongoPath = 'E:\mongo-cxx-driver-32';
mex(fullfile(['-I', mongoPath], 'include'), ...
    fullfile(['-L', mongoPath], 'lib'), ...
    fullfile(['-I', boostPath]),...
    fullfile(['-L', boostPath], 'lib32-msvc-12.0'),...
    'dbmain.cpp');
clear boostPath mongoPath
