function [ v ] = SAsymVarTH(x,bn)
%Tukey–Hanning
a=1/4;
%%%%%%%%%%%%%%
[c,lags] = xcov2(x,bn);
%parzen
%w=(1 - abs(lags).^q)./bn.^q;
%Blackman–Tukey
w=1 - 2*a + 2*a*cos(pi*abs(lags)/bn);
v= w*c;
end

