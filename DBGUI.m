function varargout = DBGUI(varargin)
% DBGUI MATLAB code for DBGUI.fig
%      DBGUI, by itself, creates a new DBGUI or raises the existing
%      singleton*.
%
%      H = DBGUI returns the handle to a new DBGUI or the handle to
%      the existing singleton*.
%
%      DBGUI('CALLBACK',hObject,eventData,handles,...) calls the local
%      function named CALLBACK in DBGUI.M with the given input arguments.
%
%      DBGUI('Property','Value',...) creates a new DBGUI or raises the
%      existing singleton*.  Starting from the left, property value pairs are
%      applied to the GUI before DBGUI_OpeningFcn gets called.  An
%      unrecognized property name or invalid value makes property application
%      stop.  All inputs are passed to DBGUI_OpeningFcn via varargin.
%
%      *See GUI Options on GUIDE's Tools menu.  Choose "GUI allows only one
%      instance to run (singleton)".
%
% See also: GUIDE, GUIDATA, GUIHANDLES

% Edit the above text to modify the response to help DBGUI

% Last Modified by GUIDE v2.5 21-Aug-2014 09:59:58

% Begin initialization code - DO NOT EDIT
gui_Singleton = 1;
gui_State = struct('gui_Name',       mfilename, ...
                   'gui_Singleton',  gui_Singleton, ...
                   'gui_OpeningFcn', @DBGUI_OpeningFcn, ...
                   'gui_OutputFcn',  @DBGUI_OutputFcn, ...
                   'gui_LayoutFcn',  [] , ...
                   'gui_Callback',   []);
if nargin && ischar(varargin{1})
    gui_State.gui_Callback = str2func(varargin{1});
end

if nargout
    [varargout{1:nargout}] = gui_mainfcn(gui_State, varargin{:});
else
    gui_mainfcn(gui_State, varargin{:});
end
% End initialization code - DO NOT EDIT


% --- Executes just before DBGUI is made visible.
function DBGUI_OpeningFcn(hObject, eventdata, handles, varargin)
% This function has no output args, see OutputFcn.
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% varargin   command line arguments to DBGUI (see VARARGIN)

% Choose default command line output for DBGUI
handles.output = hObject;
connectdb;
set(handles.bartimemenu, 'Enable', 'off');

cla(handles.baraxes,'reset');
set(handles.baraxes,'XTickLabel',[]);
set(handles.baraxes,'YTickLabel',[]);
set(handles.baraxes,'XTick',[]);
set(handles.baraxes,'YTick',[]);

cla(handles.volumeaxes,'reset');
set(handles.volumeaxes,'XTickLabel',[]);
set(handles.volumeaxes,'YTickLabel',[]);
set(handles.volumeaxes,'XTick',[]);
set(handles.volumeaxes,'YTick',[]);

cla(handles.techaxes,'reset');
set(handles.techaxes,'XTickLabel',[]);
set(handles.techaxes,'YTickLabel',[]);
set(handles.techaxes,'XTick',[]);
set(handles.techaxes,'YTick',[]);
% Update handles structure
guidata(hObject, handles);

% UIWAIT makes DBGUI wait for user response (see UIRESUME)
% uiwait(handles.figure1);


% --- Outputs from this function are returned to the command line.
function varargout = DBGUI_OutputFcn(hObject, eventdata, handles) 
% varargout  cell array for returning output args (see VARARGOUT);
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Get default command line output from handles structure
varargout{1} = handles.output;


function bartimemenu_Callback(hObject, eventdata, handles)
instrument = get(handles.instrument, 'String');
period = get(handles.bartimemenu, 'Value');
st = [];
et = [];
st = [st, get(handles.styear, 'String')];
st = [st, get(handles.stmonth, 'String')];
st = [st, get(handles.stday, 'String')];
st = datenum(st, 'yyyymmdd');
et = [et, get(handles.etyear, 'String')];
et = [et, get(handles.etmonth, 'String')];
et = [et, get(handles.etday, 'String')];
et = datenum(et, 'yyyymmdd');
cla(handles.baraxes, 'reset');
axes(handles.baraxes);
% 获取数据
switch(period)
    case 1
        data = GetBar(instrument, 1, st, et);
    case 2
        data = GetBar(instrument, 3, st, et);
    case 3
        data = GetBar(instrument, 5, st, et);
    case 4
        data = GetBar(instrument, 15, st, et);
    case 5
        data = GetBar(instrument, 30, st, et);
    case 6
        data = GetBar(instrument, 60, st, et);
    case 7
        data = GetBar(instrument, 1440, st, et);
    case 8
        data = GetTick(instrument, st, et);
end
%显示行情数据
if(period < 8 )
    MT_candle([data.h]', [data.l]', [data.c]', [data.o]', [], BarTime2MatlabTime(data));
else
    plot([data.c]);
end
cla(handles.volumeaxes, 'reset');
axes(handles.volumeaxes);
MT_VolumePlot([data.o]', [data.h]', [data.l]', [data.c]', [data.v]');


function bartimemenu_CreateFcn(hObject, eventdata, handles)

% Hint: popupmenu controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


function instrument_Callback(hObject, eventdata, handles)


function instrument_CreateFcn(hObject, eventdata, handles)

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


function styear_Callback(hObject, eventdata, handles)


function styear_CreateFcn(hObject, eventdata, handles)

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


function stmonth_Callback(hObject, eventdata, handles)


function stmonth_CreateFcn(hObject, eventdata, handles)

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


function stday_Callback(hObject, eventdata, handles)


function stday_CreateFcn(hObject, eventdata, handles)

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


function etyear_Callback(hObject, eventdata, handles)


function etyear_CreateFcn(hObject, eventdata, handles)

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


function etmonth_Callback(hObject, eventdata, handles)


function etmonth_CreateFcn(hObject, eventdata, handles)

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


function etday_Callback(hObject, eventdata, handles)


function etday_CreateFcn(hObject, eventdata, handles)

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


function getbutton_Callback(hObject, eventdata, handles)
st = [];
et = [];
st = [st, get(handles.styear, 'String')];
st = [st, get(handles.stmonth, 'String')];
st = [st, get(handles.stday, 'String')];
st = datenum(st, 'yyyymmdd');
et = [et, get(handles.etyear, 'String')];
et = [et, get(handles.etmonth, 'String')];
et = [et, get(handles.etday, 'String')];
et = datenum(et, 'yyyymmdd');
instrument = get(handles.instrument, 'String');
period = get(handles.bartimemenu, 'Value');

% bar = GetBar(instrument, 5, st, et);
% cla(handles.baraxes, 'reset');
% axes(handles.baraxes);
% MT_candle([bar.h]', [bar.l]', [bar.c]', [bar.o]', [], BarTime2MatlabTime(bar));
% hold on;
cla(handles.baraxes, 'reset');
axes(handles.baraxes);
% 获取数据
switch(period)
    case 1
        data = GetBar(instrument, 1, st, et);
    case 2
        data = GetBar(instrument, 3, st, et);
    case 3
        data = GetBar(instrument, 5, st, et);
    case 4
        data = GetBar(instrument, 15, st, et);
    case 5
        data = GetBar(instrument, 30, st, et);
    case 6
        data = GetBar(instrument, 60, st, et);
    case 7
        data = GetBar(instrument, 1440, st, et);
    case 8
        data = GetTick(instrument, st, et);
end
%显示行情数据
if(period < 8 )
    MT_candle([data.h]', [data.l]', [data.c]', [data.o]', [], BarTime2MatlabTime(data));
else
    plot([data.c]);
end
cla(handles.volumeaxes, 'reset');
axes(handles.volumeaxes);
MT_VolumePlot([data.o]', [data.h]', [data.l]', [data.c]', [data.v]');

set( handles.bartimemenu, 'Enable',  'on');


function figure1_DeleteFcn(hObject, eventdata, handles)
disconnectdb;
