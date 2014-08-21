function DateNum = BarTime2MatlabTime(bar)
%BARTIME2MATLABTIME 转换bar时间到matlab时间格式
DateNum = arrayfun(@(x) GetTime(x.tradingday, x.time), bar, 'UniformOutput', false);

DateNum = cell2mat(DateNum');
end

function DateNum = GetTime(day, time)
    y = floor(day / 10000);
    day = mod(day, 10000);
    m = floor(day / 100);
    day = mod(day, 100);
    d = day;
    
    time = round(time * 100000);
    h = floor(time / 100000);
    time = mod(time, 100000);
    min = floor(time / 1000);
    time = mod(time, 1000);

    s = time / 10;
    
    DateNum = datenum(y, m, d, h, min, s);
end