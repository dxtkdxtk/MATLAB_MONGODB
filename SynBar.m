function bar = SynBar(tick, type)
%SYNBAR 按tick合成bar

ticklen = length(tick);
isIF = false;
if(ticklen > 0)
    if(strcmp(tick(1).instrument(1:2), 'IF'))
        isIF = true;
    end
end

%清理不在交易时间内数据
if(isIF)
    time = [tick.time];
    ind = time < 9.15 | (time > 11.30 & time < 13.00) | (time > 15.15005); 
    tick(ind) = [];
else
    time = [tick.time];
    ind = (time < 9.00 & time > 2.30) | (time > 11.30 & time < 13.30) | (time > 15 & time < 21)...
        | (time > 10.15 & time < 10.30);
    tick(ind) = [];
end

%逐差处理volume 
ticklen = length(tick);
for itick = ticklen : -1 : 2
    if(tick(itick).time >= 21 && tick(itick - 1).time < 21)
        continue;
    end
    tick(itick).v = tick(itick).v - tick(itick - 1).v;
end

%合成bar
bar = [];
barlen = 0;
if(type == 1440)
    if(~isempty(tick))
        barlen = barlen + 1;
        bar(barlen).tradingday = tick(1).tradingday;
        bar(barlen).time = GenTimeStramp(type, isIF);
        bar(barlen).o = tick(1).c;
        bar(barlen).h = max([tick.c]);
        bar(barlen).l = min([tick.c]);
        bar(barlen).c = tick(end).c;
        bar(barlen).v = sum([tick.v]);
        bar(barlen).i = tick(end).i;
        bar(barlen).type = type;
    end
else
    timeStramp = GenTimeStramp(type, isIF);
    for itime = 1:length(timeStramp) - 1
        time = [tick.time];
        ind = time >= timeStramp(itime) & time < timeStramp(itime + 1);
        tmptick = tick(ind);
        if(~isempty(tmptick))
            barlen = barlen + 1;
            bar(barlen).tradingday = tmptick(1).tradingday;
            bar(barlen).time = timeStramp(itime);
            bar(barlen).o = tmptick(1).c;
            bar(barlen).h = max([tmptick.c]);
            bar(barlen).l = min([tmptick.c]);
            bar(barlen).c = tmptick(end).c;
            bar(barlen).v = sum([tmptick.v]);
            bar(barlen).i = tmptick(end).i;
            bar(barlen).type = type;
        end

    end
end


end

