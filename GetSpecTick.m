function result = GetSpecTick(inst, st, et)
%获取特定时间内tick

result = GetTick(inst, st + 4 / 24 - 0.0000001, et + 4 / 24 - 1 + 0.0000001);
end

