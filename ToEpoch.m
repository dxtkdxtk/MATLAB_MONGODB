function resbar = ToEpoch(bar)
resbar = bar;
for i = 1:length(resbar)
    tradingday = resbar(i).tradingday;
    y = round(tradingday / 10000);
    tradingday = mod(tradingday, 10000);
    m = round(tradingday / 100);
    tradingday = mod(tradingday, 100);
    d = tradingday;
    
    time = round(resbar(i).time * 100000);
    h = floor(time / 100000);

    time = mod(time, 100000);

    min = floor(time / 1000);
    time = mod(time, 1000);

    s = time / 10;
    
    matlab_time = datenum(y, m, d, h, min, s);
    resbar(i).time = round(8.64e7 * (matlab_time - datenum('1970', 'yyyy')));
    
end
end