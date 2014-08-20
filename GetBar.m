function result = GetBar( varargin )
%GETBAR 
setCollection('bar');
inst = '';
type = 1;
st = datenum(1999, 1, 1);
et = datenum(2099, 1, 1);
if(nargin > 4 || nargin < 1)
    error('参数个数错误');
end
if(nargin >= 1)
    inst = varargin{1};
    if(~ischar(inst))
        error('instrument must be a string!');
    end
end
if(nargin >= 2)
    if(~isnumeric(varargin{2}))
        error('param 2 type error');
    end
    type = varargin{2};
end
if(nargin >= 3)
    if(~isnumeric(varargin{3}))
        error('param 3 type error');
    end
    st = varargin{3};
end
if(nargin >= 4)
    if(~isnumeric(varargin{4}))
        error('param 4 type error');
    end
    et = varargin{4};
end
result = dbmain(7, inst, type, st, et);
end

