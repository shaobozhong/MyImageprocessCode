%This Code can used by anyone without communicate with me.And i won't resposible for any errors
function I=gamaCorrect(I,gama)
%I:a 2 dimenssion matrix
%gama:is the gama
%gama ����[0.1,5]
%author:Bozhong Shao

%prehanle the transform from color value to gama value
gamaValue=[];%gamavalue���±� ��Ҫ��һ ���Ƕ�Ӧ�ı任ֵ
preCompensation=1/gama;
for i=1:256
    gamaValue(i)=(i-0.5)/256;%��һ��  ��Ϊ������±�ֻ�ܴ�1 ��ʼ����0-255 �ĳ� 1-256  +0.5 �ĳ�-0.5  ����-0.5 �� -0.5=-1+0.5
    gamaValue(i)=gamaValue(i)^preCompensation;%Ԥ����
    gamaValue(i)=gamaValue(i)*256-0.5;%����һ��   
end

sizeI=size(I);
for i=1:sizeI(1)
    for j=1:sizeI(2)
        I(i,j)=gamaValue(I(i,j)+1);%transform direct without calc time and time
    end
end

end
