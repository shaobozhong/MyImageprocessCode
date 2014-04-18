function S=getS(h1,h2)
%%%¼ÆËã±ê×¼Æ«²î
S1=std(h1);
S2=std(h2);
S12=0;
for i=1:length(h1)
    S12=S12+((h1(i)-mean(h1))*(h2(i)-mean(h2)));
end 
S12=S12/(length(h1)-1);
S=S12/(S1*S2+0.0000001);
end