%����ļ��У����ͼֱ��ȡR
clc;
clear all;
close all;
file =dir('E:\����\�о���ѧϰ\ͼ����ؿ���\����\������WLD---A Robust Local Image Descriptor��ʵ��\�����ز�\*.tif');%��ȡ�ļ����������tif
for i=1:length(file)
    I=imread(['E:\����\�о���ѧϰ\ͼ����ؿ���\����\������WLD---A Robust Local Image Descriptor��ʵ��\�����ز�\' ,file(i).name]);%�򿪵�����tifͼ��
    if size(I,3)~=1 & size(I,3)~=3%��ֹ��1 ��3 ͨ�������  ��������������г���
        I=I(:,:,1);
    end
str=['���Ե�',num2str(i),'���ļ�'];  
disp(str);
    
path=['E:\����\�о���ѧϰ\ͼ����ؿ���\����\������WLD---A Robust Local Image Descriptor��ʵ��\���Խ��Y\',file(i).name,'.txt'];
fid=fopen(path,'wt');
%����ԭͼ
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

%����ѹ���������Ӵ�10-90
%cr=[];
disp('ѹ������');

fprintf(fid,'%s\n','ѹ�������������Ӵ�10-90��9������');
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

%��ת����  ��0-360�� ���Ϊ10��
fprintf(fid,'%s\n','��ת����0-360���Ϊ10�㣬��37������');
disp('��ת����');
%rr=[];
for i=0:10:360%��ת����ֺܶ��ɫ�ĵط�
Ir=imrotate(I,i);
Ir=imrotate(Ir,-1.*i);%��ת��ȥ
Ir=imrotate(Ir,size(I,1)./size(Ir,1));%��һ��
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

%���Ų��� ��0.5-2.0  ���Ϊ0.1
disp('���Ų���');
fprintf(fid,'%s\n','���Ų���0.5-2.0���Ϊ0.1����16������');
%sr=[];
for i=0.5:0.1:2.0
Is=imresize(I,i);
Is=imresize(Is,1/i);%�Ż�ȥ
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


%����:ѡȡ�˸�˹���� m=0; v=0.001:0.001:0.01
disp('��Ӹ�˹����');
fprintf(fid,'%s\n','��Ӹ�˹��������0.0005:0.0001:0.01���Ϊ0.1����10������');
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

%��ͨ�˲��ø�˹��ͨ�˲�
disp('��˹��ͨ�˲�');
fprintf(fid,'%s\n','��˹��ͨ�˲�����Hsize ��5 mean��0.3:0.1:1.0,��8������');
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

%gama�任
disp('gama�任');
fprintf(fid,'%s\n','gama�仯e gamaֵ0.5:0.5:5,��10������');
%gr=[];

for i=0.5:0.5:5    
 Ig(:,:,1)=gamaCorrect(I(:,:,1),i);%gama�任
if size(I,3)==3
   
Ig(:,:,2)=gamaCorrect(I(:,:,2),i);%gama�任
Ig(:,:,3)=gamaCorrect(I(:,:,3),i);%gama�任
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

