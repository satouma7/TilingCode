function varargout = ommatidia(varargin)
% OMMATIDIA MATLAB code for ommatidia.fig
%      OMMATIDIA, by itself, creates a new OMMATIDIA or raises the existing
%      singleton*.
%
%      H = OMMATIDIA returns the handle to a new OMMATIDIA or the handle to
%      the existing singleton*.
%
%      OMMATIDIA('CALLBACK',hObject,eventData,handles,...) calls the local
%      function named CALLBACK in OMMATIDIA.M with the given input arguments.
%
%      OMMATIDIA('Property','Value',...) creates a new OMMATIDIA or raises the
%      existing singleton*.  Starting from the left, property value pairs are
%      applied to the GUI before ommatidia_OpeningFcn gets called.  An
%      unrecognized property name or invalid value makes property application
%      stop.  All inputs are passed to ommatidia_OpeningFcn via varargin.
%
%      *See GUI Options on GUIDE's Tools menu.  Choose "GUI allows only one
%      instance to run (singleton)".
%
% See also: GUIDE, GUIDATA, GUIHANDLES

% Edit the above text to modify the response to help ommatidia

% Last Modified by GUIDE v2.5 10-Jul-2017 13:48:29

% Begin initialization code - DO NOT EDIT
gui_Singleton = 1;
gui_State = struct('gui_Name',       mfilename, ...
                   'gui_Singleton',  gui_Singleton, ...
                   'gui_OpeningFcn', @ommatidia_OpeningFcn, ...
                   'gui_OutputFcn',  @ommatidia_OutputFcn, ...
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


% --- Executes just before ommatidia is made visible.
function ommatidia_OpeningFcn(hObject, eventdata, handles, varargin)
% This function has no output args, see OutputFcn.
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% varargin   command line arguments to ommatidia (see VARARGIN)

% Choose default command line output for ommatidia
handles.output = hObject;
global dx dt T Tmax Xmax Ymax boxsize N Nmax Box BoxImage ImgA ImgB filename boxcolor scanarea data_tif data_lsm;

dx=1.0378e-07;dt=1.9287;
T=1;Tmax=30;Xmax=512;Ymax=512;
boxsize=30;Nmax=3;N=1;scanarea=101;scanoffset=20;%(scanarea+1)/2;
Box=ones(Nmax,Tmax,2)*round((Xmax-boxsize)/2);
BoxImage=zeros(Nmax,Tmax,boxsize,boxsize);
ImgA=zeros(Xmax,Ymax);filename='filename';ImgB=zeros(boxsize,boxsize);
boxcolor=['w' 'r' 'c' 'y' 'm' 'g' 'k' 'b' 'w' 'r'];

Box(1,:,1)=308;Box(1,:,2)=267;%Box(1,:,1)=355;Box(1,:,2)=290;
Box(2,:,1)=202;Box(2,:,2)=354;
Box(3,:,1)=200;Box(3,:,2)=183;
filename='default.lsm';%filename='ommatidia.lsm';

set(handles.time_text, 'String', num2str(T));
set(handles.time_slider, 'Value', T);set(handles.time_slider, 'Max', Tmax);
set(handles.time_slider, 'SliderStep', [1/Tmax 5/Tmax]);
set(handles.boxsize_text, 'String', num2str(boxsize));
set(handles.boxsize_slider, 'Value', boxsize);set(handles.boxsize_slider,'Max',50);
set(handles.boxsize_slider, 'SliderStep', [1/50 0.1]);
set(handles.boxnumber_text, 'String', num2str(Nmax));
set(handles.boxnumber_slider, 'Value', Nmax);set(handles.boxnumber_slider,'Max',10);
set(handles.boxnumber_slider, 'SliderStep', [0.1 0.5]);
set(handles.X_slider,'Value',round((Xmax-boxsize)/2));
set(handles.X_slider,'Max',Xmax-boxsize-scanoffset);set(handles.X_slider,'Min',scanoffset);
set(handles.X_slider, 'SliderStep', [1/Xmax 10/Xmax]);
set(handles.Y_slider,'Value',round((Ymax-boxsize)/2));
set(handles.Y_slider,'Max',Ymax-boxsize-scanoffset);set(handles.Y_slider,'Min',scanoffset);
set(handles.Y_slider, 'SliderStep', [1/Ymax 10/Ymax]);
set(handles.box1X_text, 'String', num2str(Box(1,1,1)));
set(handles.box1Y_text, 'String', num2str(Box(1,1,2)));
set(handles.box2X_text, 'String', num2str(Box(2,1,1)));
set(handles.box2Y_text, 'String', num2str(Box(2,1,2)));
set(handles.box3X_text, 'String', num2str(Box(3,1,1)));
set(handles.box3Y_text, 'String', num2str(Box(3,1,2)));
set(handles.pixelsize, 'String', num2str(dx*1000000000));
set(handles.timeinterval, 'String', num2str(dt));
set(handles.filename_text, 'String', filename);

data_tif = lsmread(filename);data_lsm = lsminfo(filename);
dx=data_lsm.VoxelSizeX;dt=data_lsm.TimeInterval;
Tmax=data_lsm.TIMESTACKSIZE;
Xmax=data_lsm.DimensionX;Ymax=data_lsm.DimensionY;
ImgA(:,:)=data_tif(T,1,1,:,:);
X=Box(1,1,1);Y=Box(1,1,2);
set(handles.X_slider,'Value',X);
set(handles.Y_slider,'Value',Y);
ImgB(:,:)=ImgA(Y:Y+boxsize-1,X:X+boxsize-1);
axes(handles.boximage);imagesc(ImgB);set(gca,'YDir','normal','FontName','Arial','FontSize',7);
axes(handles.mainimage);imagesc(ImgA);set(gca,'YDir','normal','FontName','Arial','FontSize',7);hold on;
for n=1:Nmax
    X=Box(n,T,1);Y=Box(n,T,2);
    rectangle('Position',[X Y boxsize-1 boxsize-1],'EdgeColor',boxcolor(n));
end
hold off;
axes(handles.result);
plot(1:Tmax,Box(1,:,1),'k',1:Tmax,Box(1,:,2),'k--',1:Tmax,Box(2,:,1),'r',1:Tmax,Box(2,:,2),'r--',1:Tmax,Box(3,:,1),'c',1:Tmax,Box(3,:,2),'c--');
set(gca,'YDir','normal','FontName','Arial','FontSize',7);
% Update handles structure
guidata(hObject, handles);

% UIWAIT makes ommatidia wait for user response (see UIRESUME)
% uiwait(handles.figure1);


% --- Outputs from this function are returned to the command line.
function varargout = ommatidia_OutputFcn(hObject, eventdata, handles) 
% varargout  cell array for returning output args (see VARARGOUT);
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Get default command line output from handles structure
varargout{1} = handles.output;


% --- Executes on slider movement.
function time_slider_Callback(hObject, eventdata, handles)
% hObject    handle to time_slider (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'Value') returns position of slider
%        get(hObject,'Min') and get(hObject,'Max') to determine range of slider
global T  N Box BoxImage boxsize ImgA ImgB data_tif Nmax boxcolor;
T=round(get(hObject,'Value'));
set(handles.time_text, 'String', num2str(T));
set(handles.time_slider, 'Value', T);

ImgA(:,:)=data_tif(T,1,1,:,:);
axes(handles.mainimage);imagesc(ImgA);set(gca,'YDir','normal','FontName','Arial','FontSize',7);hold on;
for n=1:Nmax
    X=Box(n,T,1);Y=Box(n,T,2);
    rectangle('Position',[X Y boxsize-1 boxsize-1],'EdgeColor',boxcolor(n));
end
hold off;
X=Box(N,T,1);Y=Box(N,T,2);
BoxImage(N,T,:,:)=ImgA(Y:Y+boxsize-1,X:X+boxsize-1);
ImgB(:,:)=BoxImage(N,T,:,:);
axes(handles.boximage);imagesc(ImgB);set(gca,'YDir','normal','FontName','Arial','FontSize',7);
    set(handles.box1X_text, 'String', num2str(Box(1,T,1)));
    set(handles.box1Y_text, 'String', num2str(Box(1,T,2)));
    set(handles.box2X_text, 'String', num2str(Box(2,T,1)));
    set(handles.box2Y_text, 'String', num2str(Box(2,T,2)));
    set(handles.box3X_text, 'String', num2str(Box(3,T,1)));
    set(handles.box3Y_text, 'String', num2str(Box(3,T,2))); 
guidata(hObject, handles);

% --- Executes during object creation, after setting all properties.
function time_slider_CreateFcn(hObject, eventdata, handles)
% hObject    handle to time_slider (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: slider controls usually have a light gray background.
if isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor',[.9 .9 .9]);
end

% --- Executes on slider movement.
function boxsize_slider_Callback(hObject, eventdata, handles)
% hObject    handle to boxsize_slider (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'Value') returns position of slider
%        get(hObject,'Min') and get(hObject,'Max') to determine range of slider
global boxsize scanarea ImgA ImgB data_tif T Nmax N BoxImage Xmax Ymax Box boxcolor Tmax;
boxsize=round(get(hObject,'Value'));scanoffset=20;%(scanarea+1)/2;
set(handles.boxsize_text, 'String', num2str(boxsize));
set(handles.boxsize_slider, 'Value', boxsize);
set(handles.X_slider,'Max',Xmax-boxsize-scanoffset);set(handles.X_slider,'Min',scanoffset);
set(handles.Y_slider,'Max',Ymax-boxsize-scanoffset);set(handles.Y_slider,'Min',scanoffset);

ImgA(:,:)=data_tif(T,1,1,:,:);
axes(handles.mainimage);imagesc(ImgA);set(gca,'YDir','normal','FontName','Arial','FontSize',7);hold on;
for n=1:Nmax
    X=Box(n,T,1);Y=Box(n,T,2);
    rectangle('Position',[X Y boxsize-1 boxsize-1],'EdgeColor',boxcolor(n));
end
hold off;
X=Box(N,T,1);Y=Box(N,T,2);
ImgB=zeros(boxsize,boxsize);BoxImage=zeros(Nmax,Tmax,boxsize,boxsize);
ImgB(:,:)=ImgA(Y:Y+boxsize-1,X:X+boxsize-1);
axes(handles.boximage);imagesc(ImgB);set(gca,'YDir','normal','FontName','Arial','FontSize',7);

guidata(hObject, handles);

% --- Executes during object creation, after setting all properties.
function boxsize_slider_CreateFcn(hObject, eventdata, handles)
% hObject    handle to boxsize_slider (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: slider controls usually have a light gray background.
if isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor',[.9 .9 .9]);
end


% --- Executes on slider movement.
function boxnumber_slider_Callback(hObject, eventdata, handles)
% hObject    handle to boxnumber_slider (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'Value') returns position of slider
%        get(hObject,'Min') and get(hObject,'Max') to determine range of slider

%global Nmax;
%Nmax=round(get(hObject,'Value'));
%set(handles.boxnumber_text, 'String', num2str(Nmax));
%set(handles.boxnumber_slider, 'Value', Nmax);

guidata(hObject, handles);


% --- Executes during object creation, after setting all properties.
function boxnumber_slider_CreateFcn(hObject, eventdata, handles)
% hObject    handle to boxnumber_slider (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: slider controls usually have a light gray background.
if isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor',[.9 .9 .9]);
end

function uibuttongroup1_SelectionChangedFcn(hObject, eventdata, handles)
% hObject    handle to the selected object in uibuttongroup1 
% eventdata  structure with the following fields
%	EventName: string 'SelectionChanged' (read only)
%	OldValue: handle of the previously selected object or empty
%	NewValue: handle of the currently selected object
% handles    structure with handles and user data (see GUIDATA)
global N Box BoxImage ImgA boxsize ImgB data_tif T;
switch get(eventdata.NewValue,'Tag') % Get Tag of selected object.
    case 'radiobutton1'
        N=1;
        set(handles.box1X_text, 'String', num2str(Box(1,T,1)));
        set(handles.box1Y_text, 'String', num2str(Box(1,T,2)));
    case 'radiobutton2'
        N=2;
        set(handles.box2X_text, 'String', num2str(Box(2,T,1)));
        set(handles.box2Y_text, 'String', num2str(Box(2,T,2)));
    case 'radiobutton3'
        N=3;
        set(handles.box3X_text, 'String', num2str(Box(3,T,1)));
        set(handles.box3Y_text, 'String', num2str(Box(3,T,2)));
end
set(handles.X_slider,'Value',round(Box(N,T,1)));
set(handles.Y_slider,'Value',round(Box(N,T,2)));
X=Box(N,T,1);Y=Box(N,T,2);
ImgA(:,:)=data_tif(T,1,1,:,:);
BoxImage(N,T,:,:)=ImgA(Y:Y+boxsize-1,X:X+boxsize-1);
ImgB(:,:)=BoxImage(N,T,:,:);
axes(handles.boximage);imagesc(ImgB);set(gca,'YDir','normal','FontName','Arial','FontSize',7);
guidata(hObject, handles);

% --- Executes on button press in radiobutton1.
function radiobutton1_Callback(hObject, eventdata, handles)
% hObject    handle to radiobutton1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of radiobutton1


% --- Executes on button press in radiobutton2.
function radiobutton2_Callback(hObject, eventdata, handles)
% hObject    handle to radiobutton2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of radiobutton2


% --- Executes on button press in radiobutton3.
function radiobutton3_Callback(hObject, eventdata, handles)
% hObject    handle to radiobutton3 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of radiobutton3


% --- Executes on button press in start_pushbutton.
function start_pushbutton_Callback(hObject, eventdata, handles)
% hObject    handle to start_pushbutton (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
global data_tif Tmax N Nmax Box boxsize boxcolor ImgA scanarea T X2 Y2;
Img1=zeros(boxsize,boxsize);Img2=zeros(boxsize,boxsize);Img0=zeros(boxsize,boxsize,Nmax);
Fitness=zeros(scanarea,scanarea);scanoffset=20;%(scanarea+1)/2;%scanoffset=51
T=get(handles.time_slider, 'Value');
ImgA(:,:)=data_tif(T,1,1,:,:);coresize=18;corestart=round((boxsize-coresize)/2);
ImgS=zeros(boxsize,boxsize);ImgScore=zeros(coresize,coresize);
axes(handles.mainimage);imagesc(ImgA);set(gca,'YDir','normal','FontName','Arial','FontSize',7);hold on;
for n=1:Nmax
    X=Box(n,T,1);Y=Box(n,T,2);
    rectangle('Position',[X Y boxsize-1 boxsize-1],'EdgeColor',boxcolor(n));
    Img0(:,:,n)=data_tif(T,1,1,Y:Y+boxsize-1,X:X+boxsize-1);
end
hold off;
Tinit=get(handles.time_slider, 'Value');
for T=Tinit:Tmax-1
    pause(0.001);
    ImgA(:,:)=data_tif(T+1,1,1,:,:);
    imagesc(ImgA);set(gca,'YDir','normal','FontName','Arial','FontSize',7);hold on;
    for n=1:Nmax
        X=Box(n,T,1);Y=Box(n,T,2);
        for I=1:scanarea
            X2=X+I-scanoffset;%X2=X-50:X+50
            for J=1:scanarea
                Y2=Y+J-scanoffset;%Y2=Y-50:Y+50
                Xlim=X2+boxsize-1;Ylim=Y2+boxsize-1;
                Img1(:,:)=data_tif(T,1,1,Y:Y+boxsize-1,X:X+boxsize-1);
                if Ylim>511
                    Ylim=511;
                end
                if Xlim>511
                    Xlim=511;
                end
                Img2=zeros(boxsize,boxsize);
                Img2(1:Ylim-Y2+1,1:Xlim-X2+1)=data_tif(T+1,1,1,Y2:Ylim,X2:Xlim);
                %ImgS=abs(Img1-Img2);
                ImgS=abs(Img0(:,:,n)-Img2);
                %ImgScore=ImgS(corestart+1:corestart+coresize,corestart+1:corestart+coresize);%
                %Fitness(I,J)= sum(sum(ImgS))+2*sum(sum(ImgScore));
                Fitness(I,J)= sum(sum(ImgS));
            end
        end
        [row,col] = find(Fitness == min(Fitness(:)));
        Box(n,T+1,1)=row(1)+X-scanoffset;X=Box(n,T+1,1);
        Box(n,T+1,2)=col(1)+Y-scanoffset;Y=Box(n,T+1,2);
        rectangle('Position',[X Y boxsize-1 boxsize-1],'EdgeColor',boxcolor(n));    
    end
    hold off;
    set(handles.box1X_text, 'String', num2str(Box(1,T+1,1)));
    set(handles.box1Y_text, 'String', num2str(Box(1,T+1,2)));
    set(handles.box2X_text, 'String', num2str(Box(2,T+1,1)));
    set(handles.box2Y_text, 'String', num2str(Box(2,T+1,2)));
    set(handles.box3X_text, 'String', num2str(Box(3,T+1,1)));
    set(handles.box3Y_text, 'String', num2str(Box(3,T+1,2))); 

    set(handles.time_text, 'String', num2str(T));
    set(handles.time_slider, 'Value', T);
end
axes(handles.result);
plot(1:Tmax,Box(1,:,1),'k',1:Tmax,Box(1,:,2),'k--',1:Tmax,Box(2,:,1),'r',1:Tmax,Box(2,:,2),'r--',1:Tmax,Box(3,:,1),'c',1:Tmax,Box(3,:,2),'c--');
set(gca,'YDir','normal','FontName','Arial','FontSize',7);
guidata(hObject, handles);

% --- Executes on button press in load_pushbutton.
function load_pushbutton_Callback(hObject, eventdata, handles)
% hObject    handle to load_pushbutton (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
global filename data_tif data_lsm ImgA dx dt Tmax Xmax Ymax N ImgB BoxImage Box boxsize boxcolor Nmax T;
T=1;
filename=uigetfile('*.lsm');
set(handles.filename_text, 'String', filename);
data_tif = lsmread(filename);
data_lsm = lsminfo(filename);
dx=data_lsm.VoxelSizeX;dt=data_lsm.TimeInterval;
Tmax=data_lsm.TIMESTACKSIZE;
Xmax=data_lsm.DimensionX;Ymax=data_lsm.DimensionY;
ImgA(:,:)=data_tif(T,1,1,:,:);
axes(handles.mainimage);imagesc(ImgA);set(gca,'YDir','normal','FontName','Arial','FontSize',7);hold on;
for n=1:Nmax
    X=Box(n,T,1);Y=Box(n,T,2);
    rectangle('Position',[X Y boxsize-1 boxsize-1],'EdgeColor',boxcolor(n));
end
hold off;
X=Box(N,T,1);Y=Box(N,T,2);
BoxImage(N,T,:,:)=ImgA(Y:Y+boxsize-1,X:X+boxsize-1);
ImgB(:,:)=BoxImage(N,T,:,:);
axes(handles.boximage);imagesc(ImgB);set(gca,'YDir','normal','FontName','Arial','FontSize',7);
set(handles.pixelsize, 'String', num2str(dx*1000000000));
set(handles.timeinterval, 'String', num2str(dt));

set(handles.time_text, 'String', num2str(T));
set(handles.time_slider, 'Value', T);
guidata(hObject, handles);

% --- Executes on button press in save_pushbutton.
function save_pushbutton_Callback(hObject, eventdata, handles)
% hObject    handle to save_pushbutton (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
global Box Tmax Nmax dx dt Data filename;
Data=zeros(Tmax+1,4*Nmax);
%Data{1,1}='box1 X';Data{1,2}='box1 Y';
%Data{1,3}='box1 X speed';Data{1,4}='box1 Y speed';
%Data{1,5}='box2 X';Data{1,6}='box2 Y';
%Data{1,7}='box2 X speed';Data{1,8}='box2 Y speed';
%Data{1,9}='box3 X';Data{1,10}='box3 Y';
%Data{1,11}='box3 X speed';Data{1,12}='box3 Y speed';
for n=1:Nmax
    Data(2:Tmax+1,n*4-3)=Box(n,:,1);%X
    Data(2:Tmax+1,n*4-2)=Box(n,:,2);%Y
    Data(3:Tmax+1,n*4-1)=(Box(n,2:Tmax,1)-Box(n,1:Tmax-1,1))*dx*1000000000/dt;%X speed
    Data(3:Tmax+1,n*4  )=(Box(n,2:Tmax,2)-Box(n,1:Tmax-1,2))*dx*1000000000/dt;%Y speed
end
warning off MATLAB:xlswrite:AddSheet;
%savename=strcat('ommatidia_', datestr(now,'mmdd_HHMM'), '.xls');
[path,savename,ext]=fileparts(filename);
xlswrite(savename, Data);
guidata(hObject, handles);

% --- Executes on slider movement.
function X_slider_Callback(hObject, eventdata, handles)
% hObject    handle to X_slider (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'Value') returns position of slider
%        get(hObject,'Min') and get(hObject,'Max') to determine range of slider
global Box N BoxImage ImgA ImgB boxsize boxcolor Nmax T Tmax;
X=round(get(hObject,'Value'));
set(handles.X_slider,'Value',X);
switch N
    case 1
        Box(1,T,1)=X;set(handles.box1X_text, 'String', num2str(Box(1,T,1)));
    case 2
        Box(2,T,1)=X;set(handles.box2X_text, 'String', num2str(Box(2,T,1)));
    case 3
        Box(3,T,1)=X;set(handles.box3X_text, 'String', num2str(Box(3,T,1)));
end
X=Box(N,T,1);Y=Box(N,T,2);
ImgB(:,:)=ImgA(Y:Y+boxsize-1,X:X+boxsize-1);
axes(handles.boximage);imagesc(ImgB);set(gca,'YDir','normal','FontName','Arial','FontSize',7);
axes(handles.mainimage);imagesc(ImgA);set(gca,'YDir','normal','FontName','Arial','FontSize',7);hold on;
for n=1:Nmax
    X=Box(n,T,1);Y=Box(n,T,2);
    rectangle('Position',[X Y boxsize-1 boxsize-1],'EdgeColor',boxcolor(n));
end
hold off;
axes(handles.result);
plot(1:Tmax,Box(1,:,1),'k',1:Tmax,Box(1,:,2),'k--',1:Tmax,Box(2,:,1),'r',1:Tmax,Box(2,:,2),'r--',1:Tmax,Box(3,:,1),'c',1:Tmax,Box(3,:,2),'c--');
set(gca,'YDir','normal','FontName','Arial','FontSize',7);
guidata(hObject, handles);

% --- Executes during object creation, after setting all properties.
function X_slider_CreateFcn(hObject, eventdata, handles)
% hObject    handle to X_slider (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: slider controls usually have a light gray background.
if isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor',[.9 .9 .9]);
end


% --- Executes on slider movement.
function Y_slider_Callback(hObject, eventdata, handles)
% hObject    handle to Y_slider (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'Value') returns position of slider
%        get(hObject,'Min') and get(hObject,'Max') to determine range of slider
global Box N BoxImage ImgA ImgB boxsize boxcolor Nmax T Tmax;
Y=round(get(hObject,'Value'));
set(handles.Y_slider, 'Value', Y);
switch N
    case 1
        Box(1,T,2)=Y;set(handles.box1Y_text, 'String', num2str(Box(1,T,2)));
    case 2
        Box(2,T,2)=Y;set(handles.box2Y_text, 'String', num2str(Box(2,T,2)));
    case 3
        Box(3,T,2)=Y;set(handles.box3Y_text, 'String', num2str(Box(3,T,2)));
end
X=Box(N,T,1);Y=Box(N,T,2);
ImgB(:,:)=ImgA(Y:Y+boxsize-1,X:X+boxsize-1);
axes(handles.boximage);imagesc(ImgB);set(gca,'YDir','normal','FontName','Arial','FontSize',7);
axes(handles.mainimage);imagesc(ImgA);set(gca,'YDir','normal','FontName','Arial','FontSize',7);hold on;
for n=1:Nmax
    X=Box(n,T,1);Y=Box(n,T,2);
    rectangle('Position',[X Y boxsize-1 boxsize-1],'EdgeColor',boxcolor(n));
end
hold off;
axes(handles.result);
plot(1:Tmax,Box(1,:,1),'k',1:Tmax,Box(1,:,2),'k--',1:Tmax,Box(2,:,1),'r',1:Tmax,Box(2,:,2),'r--',1:Tmax,Box(3,:,1),'c',1:Tmax,Box(3,:,2),'c--');
set(gca,'YDir','normal','FontName','Arial','FontSize',7);
guidata(hObject, handles);

% --- Executes during object creation, after setting all properties.
function Y_slider_CreateFcn(hObject, eventdata, handles)
% hObject    handle to Y_slider (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: slider controls usually have a light gray background.
if isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor',[.9 .9 .9]);
end


% --- Executes on button press in movie_pushbutton.
function movie_pushbutton_Callback(hObject, eventdata, handles)
% hObject    handle to movie_pushbutton (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
global T Tmax N Box BoxImage boxsize ImgA ImgB data_tif Nmax boxcolor filename;
T=1;N=1;
%moviename=strcat('ommatidia_', datestr(now,'mmdd_HHMM'), '.mp4');
[path,moviename,ext]=fileparts(filename);
moviename=strcat(moviename, '.mp4');
mov=VideoWriter(moviename, 'MPEG-4');
mov.FrameRate = 3;open(mov);
for T=1: Tmax
    set(handles.time_text, 'String', num2str(T));
    set(handles.time_slider, 'Value', T);
    
    ImgA(:,:)=data_tif(T,1,1,:,:);
    axes(handles.mainimage);imagesc(ImgA);set(gca,'YDir','normal','FontName','Arial','FontSize',7);hold on;
    for n=1:Nmax
        X=Box(n,T,1);Y=Box(n,T,2);
        rectangle('Position',[X Y boxsize-1 boxsize-1],'EdgeColor',boxcolor(n));
    end
    hold off;
    X=Box(N,T,1);Y=Box(N,T,2);
    BoxImage(N,T,:,:)=ImgA(Y:Y+boxsize-1,X:X+boxsize-1);
    ImgB(:,:)=BoxImage(N,T,:,:);
    axes(handles.boximage);imagesc(ImgB);set(gca,'YDir','normal','FontName','Arial','FontSize',7);
    set(handles.box1X_text, 'String', num2str(Box(1,T,1)));
    set(handles.box1Y_text, 'String', num2str(Box(1,T,2)));
    set(handles.box2X_text, 'String', num2str(Box(2,T,1)));
    set(handles.box2Y_text, 'String', num2str(Box(2,T,2)));
    set(handles.box3X_text, 'String', num2str(Box(3,T,1)));
    set(handles.box3Y_text, 'String', num2str(Box(3,T,2))); 
    
    writeVideo(mov, getframe(gcf));
end
close(mov);
guidata(hObject, handles);
