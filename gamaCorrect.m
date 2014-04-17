%This Code can used by anyone without communicate with me.And i won't resposible for any errors
function I=gamaCorrect(I,gama)
%I:a 2 dimenssion matrix
%gama:is the gama
%gama 属于[0.1,5]
%author:Bozhong Shao

%prehanle the transform from color value to gama value
gamaValue=[];%gamavalue的下标 需要减一 才是对应的变换值
preCompensation=1/gama;
for i=1:256
    gamaValue(i)=(i-0.5)/256;%归一化  因为矩阵的下标只能从1 开始所以0-255 改成 1-256  +0.5 改成-0.5  并且-0.5 是 -0.5=-1+0.5
    gamaValue(i)=gamaValue(i)^preCompensation;%预补偿
    gamaValue(i)=gamaValue(i)*256-0.5;%反归一化   
end

sizeI=size(I);
for i=1:sizeI(1)
    for j=1:sizeI(2)
        I(i,j)=gamaValue(I(i,j)+1);%transform direct without calc time and time
    end
end

end
