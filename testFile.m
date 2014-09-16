% connectdb('198.16.100.88');
connectdb;
Dir = 'F:\rawdata';
list =  dir(Dir); 
list = {list.name}';

listlen = length(list);
for i = 3:listlen
    file = dir(fullfile(Dir, list{i}));
    file = {file.name}';
    filelen = length(file);
    for j = 1:filelen
        File = fullfile(Dir, list{i}, file{j});
        disp(File);
        WriteTick(File);
    end
end
