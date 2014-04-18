function waitDot()
dotNum=floor(5*rand());
output=['wait'];
for i=1:dotNum
    output=[output,'.'];
end 
clc;
disp(output);
end 