%LHC({1})
function [mu_hat] = MC_antitheticsimpILH(ndim,f,n)
x_vals=ILHC1RBS(ndim,n,1);
f_vals = f(x_vals');
mu_hat = mean(f_vals);
end









