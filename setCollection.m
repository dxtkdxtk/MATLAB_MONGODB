function setCollection(collection)
%SETCOLLECTION ���õ�ǰ������
if(~ischar(collection))
    error('collection must be a string');
end

dbmain(3, collection);

end

