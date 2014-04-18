function Ir=imRotateRreserveData(I,angle)
sizeI=size(I);
I=imrotate(I,angle);
I=imrotate(I,-angle);

sizeIt=size(I);

rOff=floor((sizeIt(1)-sizeI(1)+1)./2);
cOff=floor((sizeIt(2)-sizeI(2)+1)./2);
if size(I,3)==3
    Ir=zeros(sizeI(1),sizeI(2),3);
else 
    Ir=zeros(sizeI(1),sizeI(2));
end 
for i=1:sizeI(1)
    for j=1:sizeI(2)
        Ir(i,j,1)=I(rOff+i,cOff+j,1);
        if size(I,3)==3
            Ir(i,j,2)=I(rOff+i,cOff+j,2);
            Ir(i,j,3)=I(rOff+i,cOff+j,3);
        end
    end
end 
Ir=uint8(Ir);
end 