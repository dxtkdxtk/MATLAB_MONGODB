connectdb('198.16.100.88');
% connectdb;
Dir = 'F:\rawdata';
list =  dir(Dir); 
list = {list.name}';

listlen = length(list);
for i = 3:listlen
    file = dir(fullfile(Dir, list{i}));
    file = {file.name}';
    filelen = length(file);
    for j = 1:filelen
        if(length(file{j}) < 17)
            continue;
        end
        ind = find(file{j} == '_');
        inst = file{j}(1 : ind(1) -1);
        dt = file{j}(ind(1) + 1 : ind(2) -1);
        disp(['É¾³ý', inst, dt, 'ÖÐ']);
        DeleteTick(inst, datenum(dt, 'yyyymmdd'), datenum(dt, 'yyyymmdd'));
        File = fullfile(Dir, list{i}, file{j});
        disp(File);
        WriteTick(File);
    end
end
