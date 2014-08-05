function setCollection(collection)
%SETCOLLECTION 设置当前操作集
if(~ischar(collection))
    error('collection must be a string');
end

dbmain(3, collection);

end

