function WriteBar( bar )
%WRITEBAR д�����ݿ�bar����
setCollection('bar');
bar = ToEpoch(bar);
dbmain(6, bar);
end

