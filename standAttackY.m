%这个文件中，真彩图直接取R
clc;
clear all;
close all;
file =dir('E:\快盘\研究生学习\图像相关科研\任务\任务五WLD---A Robust Local Image Descriptor的实现\测试素材\*.tif');%读取文件夹里的所有tif
for i=1:length(file)
    I=imread(['E:\快盘\研究生学习\图像相关科研\任务\任务五WLD---A Robust Local Image Descriptor的实现\测试素材\' ,file(i).name]);%打开单个的tif图像
    if size(I,3)~=1 & size(I,3)~=3%防止非1 和3 通道的情况  这样的情况会运行出错
        I=I(:,:,1);
    end
str=['测试第',num2str(i),'个文件'];  
disp(str);
    
path=['E:\快盘\研究生学习\图像相关科研\任务\任务五WLD---A Robust Local Image Descriptor的实现\测试结果Y\',file(i).name,'.txt'];
fid=fopen(path,'wt');
%计算原图
if size(I,3)==3
    IY=rgb2ycbcr(I);
    matrix=IY(:,:,1);
else
    matrix=I(:,:,1);
end 
histogram=getWLDHistFromMatrix(matrix,6,8,10);

mSum=sum(histogram);%the histogram sum of original image

origin=histogram;
%fprintf('origin:%d\n',histogram);

%测试压缩质量因子从10-90
%cr=[];
disp('压缩测试');

fprintf(fid,'%s\n','压缩测试质量因子从10-90共9个数据');
for i=10:10:90
jpegByImwriteMatrix(I,'tmp.jpg',i);
Ic=imread('tmp.jpg');
if size(I,3)==3
    IY=rgb2ycbcr(Ic);
    matrix=IY(:,:,1);
else
    matrix=Ic(:,:,1);
end 
histogram=getWLDHistFromMatrix(matrix,6,8,10);
intersection=0;
for j=1:size(histogram,2)
    intersection=intersection+min([origin(j),histogram(j)]);
end 
nomalized=intersection./mSum;
fprintf(fid,'%.4f:%f\t',i,nomalized);

%cr=[cr relative];
end
fprintf(fid,'\n');
disp('');

%旋转测试  从0-360° 间隔为10°
fprintf(fid,'%s\n','旋转测试0-360间隔为10°，共37个数据');
disp('旋转测试');
%rr=[];
for i=0:10:360%旋转会出现很多黑色的地方
Ir=imrotate(I,i);
Ir=imrotate(Ir,-1.*i);%又转回去
Ir=imrotate(Ir,size(I,1)./size(Ir,1));%归一化
if size(I,3)==3
    IY=rgb2ycbcr(Ir);
    matrix=IY(:,:,1);
else
    matrix=Ir(:,:,1);
end 

histogram=getWLDHistFromMatrix(matrix,6,8,10);
intersection=0;
for j=1:size(histogram,2)
    intersection=intersection+min([origin(j),histogram(j)]);
end 
nomalized=intersection./mSum;
fprintf(fid,'%.4f:%f\t',i,nomalized);
%rr=[rr relative];
end
fprintf(fid,'\n');
disp('');

%缩放测试 从0.5-2.0  间隔为0.1
disp('缩放测试');
fprintf(fid,'%s\n','缩放测试0.5-2.0间隔为0.1，共16个数据');
%sr=[];
for i=0.5:0.1:2.0
Is=imresize(I,i);
Is=imresize(Is,1/i);%放回去
if size(I,3)==3
    IY=rgb2ycbcr(Is);
    matrix=IY(:,:,1);
else
    matrix=Is(:,:,1);
end 
histogram=getWLDHistFromMatrix(matrix,6,8,10);
intersection=0;
for j=1:size(histogram,2)
    intersection=intersection+min([origin(j),histogram(j)]);
end 
nomalized=intersection./mSum;
fprintf(fid,'%.4f:%f\t',i,nomalized);
%sr=[sr relative];
end
fprintf(fid,'\n');
disp('');


%噪声:选取了高斯噪声 m=0; v=0.001:0.001:0.01
disp('添加高斯噪声');
fprintf(fid,'%s\n','添加高斯噪声测试0.0005:0.0001:0.01间隔为0.1，共10个数据');
%nr=[];
for i=0.0005:0.0001:0.001
In=imnoise(I,'gaussian',0,i);
if size(I,3)==3
    IY=rgb2ycbcr(In);
    matrix=IY(:,:,1);
else
    matrix=In(:,:,1);
end 
histogram=getWLDHistFromMatrix(matrix,6,8,10);
intersection=0;
for j=1:size(histogram,2)
    intersection=intersection+min([origin(j),histogram(j)]);
end 
nomalized=intersection./mSum;
fprintf(fid,'%.4f:%f\t',i,nomalized);
%nr=[nr relative];
end
fprintf(fid,'\n');
disp('');

%低通滤波用高斯低通滤波
disp('高斯低通滤波');
fprintf(fid,'%s\n','高斯低通滤波测试Hsize 用5 mean用0.3:0.1:1.0,共8个数据');
%fr=[];
for i=0.3:0.1:1.0
h=fspecial('gaussian',5,i);
 If(:,:,1)=filter2(h,I(:,:,1));
if size(I,3)==3
     If(:,:,2)=filter2(h,I(:,:,2));
   If(:,:,3)=filter2(h,I(:,:,3));
    IY=rgb2ycbcr(If);
    matrix=IY(:,:,1);
else
    matrix=If(:,:,1);
end 
histogram=getWLDHistFromMatrix(matrix,6,8,10);
intersection=0;
for j=1:size(histogram,2)
    intersection=intersection+min([origin(j),histogram(j)]);
end 
nomalized=intersection./mSum;
fprintf(fid,'%.4f:%f\t',i,nomalized);
%fr=[fr relative];
end
fprintf(fid,'\n');
disp('');

%gama变换
disp('gama变换');
fprintf(fid,'%s\n','gama变化e gama值0.5:0.5:5,共10个数据');
%gr=[];

for i=0.5:0.5:5    
 Ig(:,:,1)=gamaCorrect(I(:,:,1),i);%gama变换
if size(I,3)==3
   
Ig(:,:,2)=gamaCorrect(I(:,:,2),i);%gama变换
Ig(:,:,3)=gamaCorrect(I(:,:,3),i);%gama变换
    IY=rgb2ycbcr(Ig);
    matrix=IY(:,:,1);
else
    matrix=Ig(:,:,1);
end 
histogram=getWLDHistFromMatrix(matrix,6,8,10);
intersection=0;
for j=1:size(histogram,2)
    intersection=intersection+min([origin(j),histogram(j)]);
end 
nomalized=intersection./mSum;
fprintf(fid,'%.4f:%f\t',i,nomalized);
%gr=[gr histogram];
end 

fclose(fid);
end

