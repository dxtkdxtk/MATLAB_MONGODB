function SynBarByDate(dt)
%SYNBARBYDATE 合成特定日期所有合约bar数据
instruments = GetAllInstrumentsByDate(dt);
instruments = {instruments.InstrumentID};
len = length(instruments);
type = [1, 3, 5, 15, 30, 60, 1440];
for i = 1:len
    disp(['processing: ', instruments{i}]);
    tick = GetTick(instruments{i}, dt, dt);
    for j = 1:length(type)
        WriteBar(SynBar(tick, type(j)));
    end
    
end

end

