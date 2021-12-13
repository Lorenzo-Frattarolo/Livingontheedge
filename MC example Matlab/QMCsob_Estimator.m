%Quasi-Monte Carlo
function mu_hat = QMCsob_Estimator(ndim,f,n,q)
p = sobolset(ndim);
q = qrandstream(p);
x_vals=qrand(q,n);
f_vals =f(x_vals);
mu_hat = mean(f_vals);
end









