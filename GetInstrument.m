function inst = GetInstrument(instOrProduct)
%GETINSTRUMENT ��ȡ��Լ����Ʒ��������Ϣ�������Ǿ����Լ��Ҳ������Ʒ��
setCollection('instrument');
if(~ischar(instOrProduct))
    error('�������ʹ���');
end
inst = dbmain(5, instOrProduct);

end

