
clc
clear 
close all
%Script comparing MSE from the integration of Wang and Sloan function,
%sampling from MC QMC and LHC({1}).

%Suffix of the output filename
filename = 'new';
% Sobol Set
qmc_set ='s';
set_name = {'Sobol Set'};
k=1;
addpath(genpath('..\'))
for dims =  [100];
avec=[0.1,1,10];
tauvec=[0.1,0.5,0.8,0.9,1];
sp1=length(avec);
sp2=length(tauvec);
% Computation of Effective Dimensions
k=0;
for i=1:length(avec)
    for j=1:length(tauvec)
        k=k+1;
        a(k)=avec(i);
        tau(k)=tauvec(j);
        [dt(k),ds(k)]=effectivedimwangsloan(dims,0.99,a(k),tau(k));        
        fnames{k}=['$$(p_t=',num2str(dt(k)),',p_s=',num2str(ds(k)),')$$']  ;
    end
end
functions = [1:k];
num_ns = 3; % number of N values to consider
num_reps = 10000; % number of replicates to consider
%% Compute the results first:   
num_dims = length(dims);
num_functions = length(functions);
%Initialize standard erros and time matrices
se_MC = zeros(num_dims,num_functions,num_ns,num_reps);
se_QMC = zeros(num_dims,num_functions,num_ns,num_reps);
se_MC_anti= zeros(num_dims,num_functions,num_ns,num_reps);
time_MC=zeros(num_dims,num_functions,num_ns,num_reps);
time_QMC=zeros(num_dims,num_functions,num_ns,num_reps);
time_MC_anti=zeros(num_dims,num_functions,num_ns,num_reps);
for d = 1:num_dims % dimensionality of the problem
    dim = dims(1);
    multiWaitbar('Dimension',d/num_dims);
    for index = functions % different test functions
        multiWaitbar('Test Function',index/length(functions));
        for rep = 1:num_reps % replicates
            multiWaitbar('Replicate',rep/num_reps);
            
            %% Define the test function
            startingpoint = zeros(1,dim); %the lower limits of the integral
            endingpoint = ones(1,dim); %the upper limits of the integral
            hyperbox = [startingpoint;endingpoint]; % the integration interval
            %Selected function handle
            f= @(x) wangsloan(x,a(index),tau(index));
            %True value of the integral
            I=1;
            %% Numerical integration
            nint=10;
            nn = repmat([1:nint]./nint,num_ns-1,1)'.*repmat(10.^(2:num_ns),nint,1);
            n_vals{d} = [10;nn(:)];
            for ni = 1:length(n_vals{d})
                n = n_vals{d}(ni);

                 tic    
                 mu_hat_MC =MC_Estimator(dim,f,n); % standard MC
                 time_MC(d,index,ni,rep)=toc;
                 tic
                 mu_hat_QMC = QMCsob_Estimator(dim,f,n,1); % Sobol QMC
                 time_QMC(d,index,ni,rep)=toc;
                tic
                mu_hat_MC_anti=MC_antithetic(dim,f,n);
                 time_MC_anti(d,index,ni,rep)=toc;
                 % square error QMC
                se_MC(d,index,ni,rep) = (mu_hat_MC - I)^2; 
                se_QMC(d,index,ni,rep) = (mu_hat_QMC - I)^2;
                se_MC_anti(d,index,ni,rep) = (mu_hat_MC_anti - I)^2; 
            end
        end
    end 
    orient(gcf,'landscape')
print(gcf,strcat('MSE_paper_GENZfun_scramble',num2str(dims),'.pdf'),'-dpdf','-fillpage')
end
hold off
multiWaitbar( 'CloseAll' );
%% Display the results
mse_QMC = mean(se_QMC,4);
mse_MC= mean(se_MC,4);
mse_MC_anti= mean(se_MC_anti,4);


mtime_QMC = mean(time_QMC,4);
mtime_MC= mean(time_MC,4);
mtime_MC_anti= mean(time_MC_anti,4);



%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
se_mse_QMC = std(se_QMC,0,4) / sqrt(num_reps); % standard error of the MSE
se_mse_MC = std(se_MC,0,4) / sqrt(num_reps);
se_mse_MC_anti = std(se_MC_anti,0,4) / sqrt(num_reps);           
shape = {'o','^','s','*'};
col=colormap(hsv(7));
vie=[1,2,3];
figure(1)
leg=[{'MC'},{'QMC Sobol'},{'$LH$ $C_{d}\left(\left\{1\right\}\right)$'}];
leg=leg(vie);
for index = functions
    subplot(sp1,sp2,index)
    hold on
    d=1;  
         errorbar(squeeze(mtime_MC(:,index,2:end)*10^3),squeeze(mse_MC(d,index,2:end)),...
                 squeeze(se_mse_MC(d,index,2:end)),'Color','r','LineStyle','-','Marker','s');
         errorbar(squeeze(mtime_QMC(:,index,2:end)*10^3),squeeze(mse_QMC(d,index,2:end)),...
                 squeeze(se_mse_QMC(d,index,2:end)),'Color','k','LineStyle','--','Marker','o');
         errorbar(squeeze(mtime_MC_anti(:,index,2:end)*10^3),squeeze(mse_MC_anti(d,index,2:end)),...
                 squeeze(se_mse_MC_anti(d,index,2:end)),'Color','b','LineStyle',':','Marker','h');                      
% %     
    
    
    
%          errorbar(n_vals{d}(2:end),squeeze(mse_MC(d,index,2:end)),...
%                  squeeze(se_mse_MC(d,index,2:end)),'Color','r','LineStyle','-','Marker','s');
%          errorbar(n_vals{d}(2:end),squeeze(mse_QMC(d,index,2:end)),...
%                  squeeze(se_mse_QMC(d,index,2:end)),'Color','k','LineStyle','--','Marker','o');    
%           errorbar(n_vals{d}(2:end),squeeze(mse_MC_anti(d,index,2:end)),...
%                 squeeze(se_mse_MC_anti(d,index,2:end)),'Color','b','LineStyle',':','Marker','h');                
        set(gca,'YScale','log'); % set the X axis in log scale.
    annotation('textbox',[0.5 0.9 0.1 0.1],'String',strcat('p=', num2str(dims) ),'FitBoxToText','on','Interpreter','latex');
    hl=legend(leg,'Box','off','interpreter','latex','Orientation','horizontal');
    newPosition = [0.47 0. 0.1 0.05];
     newUnits = 'normalized';
     set(hl,'Position', newPosition,'Units', newUnits);
    title([fnames{index}],'interpreter','latex')
    %xlabel('$$d$$','Interpreter','latex')
    xlabel('t(sec)$$\times 10^3$$','Interpreter','latex')
    ylabel('Mean Square Error','Interpreter','latex')
    box on;
    grid on
end
orient(gcf,'landscape')
print(gcf,strcat('MSE_vs_time_paper_scramble',filename,num2str(dims),'.pdf'),'-dpdf','-bestfit')
end





