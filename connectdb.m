function connectdb(varargin)
%MCONNECT 连接数据库
server = 'localhost';
database = 'MarketData';
if(nargin == 1)
    server = varargin{1};
elseif(nargin == 2)
    server = varargin{1};
    database = varargin{1};
elseif(nargin > 2)
    error('参数过多');
end

dbmain(1, server, database);
end

