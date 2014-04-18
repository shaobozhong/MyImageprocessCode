function jpegByImwriteImage(inputPath,outPath,QF)
I=imread(inputPath);
imwrite(I,outPath,'jpg','Quality',QF);
end