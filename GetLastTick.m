function result = GetLastTick(inst, et)
%获取某合约指定时间最后一根tick
setCollection('tick');
result = dbmain(10, inst, et);
end


