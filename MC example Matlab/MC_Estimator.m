% Standard Monte Carlo
function mu_hat = MC_Estimator(ndim,f,n)
x_vals = rand(n,ndim);
f_vals =f(x_vals);
mu_hat = mean(f_vals);
end









