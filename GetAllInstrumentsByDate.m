function inst = GetAllInstrumentsByDate(dt)
%GETALLINSTRUMENTSBYDATE 查询指定日所有交易合约
inst = GetInstrument('');
time = {inst.ExpireDate};
time = cell2mat(cellfun(@(x) str2double(x), time, 'UniformOutput', false));

ind = time >= str2double(datestr(dt, 'yyyymmdd'));

inst = inst(ind);
end

