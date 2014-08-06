function inst = GetInstrument(instOrProduct)
%GETINSTRUMENT 获取合约或者品种所有信息，可以是具体合约，也可以是品种
setCollection('instrument');
if(~ischar(instOrProduct))
    error('参数类型错误');
end
inst = dbmain(5, instOrProduct);

end

