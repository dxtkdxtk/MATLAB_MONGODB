function WriteBar( bar )
%WRITEBAR 写入数据库bar数据
setCollection('bar');
bar = ToEpoch(bar);
dbmain(6, bar);
end

