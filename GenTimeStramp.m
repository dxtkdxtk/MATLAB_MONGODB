function result = GenTimeStramp(min, isIF)
%GENTIMESTRAMP 生成分钟数据timestramp
result = [];
if(~isIF)
    if(min == 60)
        result = [9, 10, 11.15, 14.15, 15.00005, 21, 22, 23, 23.599, 0, 1, 2, 2.3];
    elseif(min == 30)
        result = [9, 9.30, 10, 10.45, 11.15, 13.45, 14.15, 14.45, 15.00005];
        result = [result, 21 : 0.3 : 21.599];
        result = [result, 22 : 0.3 : 22.599];
        result = [result, 23 : 0.3 : 23.599, 24];
        result = [result, 0 : 0.3 : 0.599];
        result = [result, 1 : 0.3 : 1.599];
        result = [result, 2 : 0.3 : 2.3];
    elseif(min == 1440)
        result = 9;
    else
        result = [result,9 : min/100 : 9.599];
        result = [result,10 : min/100 : 10.149];
        result = [result,10.3 : min/100 : 10.599];
        result = [result,11 : min/100 : 11.299];
        result = [result,13.3 : min/100 : 13.599];
        result = [result,14 : min/100 : 14.599];
        result = [result,21 : min/100 : 21.599];
        result = [result,22 : min/100 : 22.599];
        result = [result,23 : min/100 : 23.599, 24];
        result = [result,0 : min/100 : 0.599];
        result = [result,1 : min/100 : 1.599];
        result = [result,2 : min/100 : 2.30];
    end
    
else
    if(min == 60)
        result = [9.15, 10.15, 11.15, 13.45, 14.45, 15.15];
        
    elseif(min == 30)
        result = [9.15, 9.45, 10.15, 10.45, 11.15, 13.15, 13.45, 14.15, 14.45, 15.15];
    elseif(min == 1440)
        result = 9.15;
    else
        result = [result,9.15 : min/100 : 9.599];
        result = [result,10 : min/100 : 10.599];
        result = [result,11 : min/100 : 11.299];
        result = [result,13 : min/100 : 13.599];
        result = [result,14 : min/100 : 14.599];
        result = [result,15 : min/100 : 15.149, 15.150051];
    end
end
end

