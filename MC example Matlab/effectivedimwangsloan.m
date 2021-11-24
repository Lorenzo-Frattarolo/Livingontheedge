function[dt,ds]=effectivedimwangsloan(d,alpha,a,tau)


sigma2=prod((1+a^2*tau.^(2*[1:d]')/12))-1;
        dt=1;
        sigma2t=prod((1+a^2*tau.^(2*[1:dt]')/12))-1;
        while sigma2t < alpha*sigma2
            dt=dt+1;
            sigma2t=prod((1+a^2*tau.^(2*[1:dt]')/12))-1;
        end      
        T=zeros(d,d);
        for ii=1:d
           
            T(ii,ii)=    prod(a^2*tau.^(2*[1:ii]')/12) ;
             T(ii,1)=    sum(a^2*tau.^(2*[1:ii]')/12) ;
        end
        for ii=3:d
            for m=2:d
                T(ii,m)=T(ii-1,m)+ (a^2*tau.^(2*ii)/12)*T(ii-1,m-1);
            end
        end
        ds=1;
        sigma2s=sum(T(d,1),2);        
         while sigma2s < alpha*sigma2
               ds=ds+1;
             sigma2s=sum(T(d,1:ds),2);
         end
end