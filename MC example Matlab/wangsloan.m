function [y] = wangsloan(xx, a,t)
d = size(xx,2);
tau=t;
a1=a;
y= prod(1+(xx -1/2).*a1.*tau.^([1:d]) ,2);
end
