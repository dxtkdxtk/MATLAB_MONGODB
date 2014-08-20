function inst = GetAllInstrumentsByDate(dt)
%GETALLINSTRUMENTSBYDATE ��ѯָ�������н��׺�Լ
inst = GetInstrument('');
time = {inst.ExpireDate};
time = cell2mat(cellfun(@(x) str2double(x), time, 'UniformOutput', false));

ind = time >= str2double(datestr(dt, 'yyyymmdd'));

inst = inst(ind);
end

