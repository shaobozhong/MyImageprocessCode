function EuDis=getEuDistance(v1,v2)
%function calcEudis
if size(v1)~=size(v2) 
    error('two vector must have the same size');
end 
sum=0;
lengh=size(v1,1);
if(length<size(v1,2)) length=size(v1,2);
for i=1:length
    sum=sum+(v1(i)-v2(i))^2;
end 
EuDis=sqrt(sum);
end