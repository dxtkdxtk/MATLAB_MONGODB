function inst = GetInstrument(instOrProduct)
%GETINSTRUMENT ��ȡ��Լ����Ʒ��������Ϣ�������Ǿ����Լ��Ҳ������Ʒ��
setCollection('instrument');
old = feature('DefaultCharacterSet', 'UTF8');
if(~ischar(instOrProduct))
    error('�������ʹ���');
end
inst = dbmain(5, instOrProduct);
feature('DefaultCharacterSet', old);

end

