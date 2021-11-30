function[c,lags]=xcov2(x,bn)
lags=[-bn:bn];
for i= bn+1:(2*bn+1)
cc= cov(x(1+lags(i):end,1), x(1:end-lags(i),1));   
c(i,1)= cc(1,2);
c(bn - lags(i)+1,1)=c(i);
end    
    