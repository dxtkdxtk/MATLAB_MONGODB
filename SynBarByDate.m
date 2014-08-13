function SynBarByDate(dt)
%SYNBARBYDATE �ϳ��ض��������к�Լbar����
instruments = GetAllInstrumentsByDate(dt);
len = length(instruments);
type = [1, 3, 5, 10, 15, 30, 60, 120, 1440];
for i = 1:len
    tick = GetTick(instruments{i}, dt, dt);
    for j = 1:length(type)
        WriteBar(SynBar(tick, type(j)));
    end
    
end

end

