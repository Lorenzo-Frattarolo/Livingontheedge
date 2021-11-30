function [theta,alf]=MH_V2_no_a(thetaOld,lam,be,n,z,u)
thetastar=exp(log(thetaOld)-z+2*z*u(:,1));
a=n*log(be)+sum(log(lam))-1;
rho=(thetastar-thetaOld)*a-n*(log(gamma(thetastar))-log(gamma(thetaOld)))+(thetastar-thetaOld);
alf=min([1,exp(rho)]);
uAcc=rand(1,1);
if uAcc<alf
    theta=thetastar;
else
    theta=thetaOld;
end