function matrix=get2DImage(imagePath)
I=imread(imagePath);
%º∆À„‘≠Õº
if size(I,3)==3
    IY=rgb2ycbcr(I);
    matrix=IY(:,:,1);
else
    matrix=I(:,:,1);
end 
end