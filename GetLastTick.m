function result = GetLastTick(inst, et)
%��ȡĳ��Լָ��ʱ�����һ��tick
setCollection('tick');
result = dbmain(10, inst, et);
end


