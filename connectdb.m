function connectdb(varargin)
%MCONNECT �������ݿ�
server = 'localhost';
database = 'MarketData';
if(nargin == 1)
    server = varargin{1};
elseif(nargin == 2)
    server = varargin{1};
    database = varargin{1};
elseif(nargin > 2)
    error('��������');
end

dbmain(1, server, database);
end
