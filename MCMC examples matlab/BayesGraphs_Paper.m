clc
clear all
close all
a=load('BayesTables20-5000-1000.mat');
no_a=load('BayesTables20-5000-1000_no_a.mat');
%names=[{'PVILH(1)MC'},{'PVMC'},{'ILH(3)MC'}];
%names=[{'$ LH  C_{d}\left(\left\{ 1 \right\}\right)$'}];
names=[{'with antithetic acceptance rate'},{'without antithetic acceptance rate'} ];
Dmax=20;
figure(1)
subplot(1,2,1)
allrep=296;
malpha=squeeze(mean(a.tablealpha(1:allrep,:,:),1));
valpha=squeeze(std(a.tablealpha(1:allrep,:,:),1));
malpha_no_a=squeeze(mean(no_a.tablealpha_noa(1:allrep,:,:),1));
valpha_no_a=squeeze(std(no_a.tablealpha_noa(1:allrep,:,:),1));
hold on
%plot([2:10]',malpha(:,1),'--p');
errorbar([2:Dmax]',malpha(:,1),...
                 valpha(:,1),'LineStyle','--','Marker','h');   
errorbar([2:Dmax]',malpha_no_a(:,1),...
                 valpha_no_a(:,1),'LineStyle','-','Marker','h');
% errorbar([2:Dmax]',malpha(:,3),...
%                  valpha(:,3),'LineStyle',':','Marker','h');
title('$\alpha$ Hierarchical Poisson','interpreter','latex');
%legend(names);
xlabel('$d$','Interpreter','latex')
ylabel('(var anthitetic) / (var i.i.d)')
hold off
% orient(gcf,'landscape')
% print(gcf,strcat('alphaHP20-5000-1000_normalrep.pdf'),'-dpdf','-fillpage')
% 
% figure(2)
subplot(1,2,2)
mbeta=squeeze(mean(a.tablebeta(1:allrep,:,:),1));
vbeta=squeeze(std(a.tablebeta(1:allrep,:,:),1));
mbeta_no_a=squeeze(mean(no_a.tablebeta_noa(1:allrep,:,:),1));
vbeta_no_a=squeeze(std(no_a.tablebeta_noa(1:allrep,:,:),1));
hold on
% plot([2:10]',mbeta(:,1),'--p');
% plot([2:10]',mbeta(:,2),'-h');
% plot([2:10]',mbeta(:,3),':*');
errorbar([2:Dmax]',mbeta(:,1),...
                 vbeta(:,1),'LineStyle','--','Marker','h');  
             
errorbar([2:Dmax]',mbeta_no_a(:,1),...
                 vbeta_no_a(:,1),'LineStyle','-','Marker','h');
% errorbar([2:Dmax]',mbeta(:,3),...
%                  vbeta(:,3),'LineStyle',':','Marker','h');
title('$\beta$ Hierarchical Poisson','interpreter','latex');
legend(names,'Interpreter','latex');
xlabel('$d$','Interpreter','latex')
ylabel('(var anthitetic) / (var i.i.d)')
hold off
orient(gcf,'landscape')
print(gcf,strcat('HP_20-5000-1000_circ.pdf'),'-dpdf','-fillpage')


for rep =1:allrep 
for anti=1:2   
tablebeta0(rep,:,anti)=a.tablebetaprob(rep,1).table(:,anti);
end
end

% for rep =1:allrep 
% for anti=1:2   
% tablebeta0_no_a(rep,:,anti)=no_a.tablebetaprob(rep,1).table(:,anti);
% end
% end

figure(2)
subplot(1,3,1)
mbeta=squeeze(mean(tablebeta0(1:allrep,:,:),1));
vbeta=squeeze(std(tablebeta0(1:allrep,:,:),1));
% mbeta_no_a=squeeze(mean(tablebeta0_no_a(1:allrep,:,:),1));
% vbeta_no_a=squeeze(std(tablebeta0_no_a(1:allrep,:,:),1));
hold on
% plot([2:10]',mbeta(:,1),'--p');
% plot([2:10]',mbeta(:,2),'-h');
% plot([2:10]',mbeta(:,3),':*');
errorbar([2:Dmax]',mbeta(:,1),...
                 vbeta(:,1),'LineStyle','--','Marker','h');   
%errorbar([2:Dmax]',mbeta_no_a(:,1),...
%                 vbeta_no_a(:,1),'LineStyle','-','Marker','h');
% errorbar([2:Dmax]',mbeta(:,3),...
%                  vbeta(:,3),'LineStyle',':','Marker','h');
title('$\beta_0$ Bayesian Probit','interpreter','latex');
%legend(names);
xlabel('$d$','Interpreter','latex')
ylabel('(var anthitetic) / (var i.i.d)')
hold off
%orient(gcf,'landscape')
%print(gcf,strcat('beta_0BP20-5000-1000_normalrep.pdf'),'-dpdf','-fillpage')


for rep =1:allrep 
for anti=1:3   
tablebeta1(rep,:,anti)=a.tablebetaprob(rep,2).table(:,anti);
end
end

% for rep =1:allrep 
% for anti=1:3   
% tablebeta1_no_a(rep,:,anti)=no_a.tablebetaprob(rep,2).table(:,anti);
% end
% end

subplot(1,3,2)
mbeta=squeeze(mean(tablebeta1(1:allrep,:,:),1));
vbeta=squeeze(std(tablebeta1(1:allrep,:,:),1));
%mbeta_no_a=squeeze(mean(no_a.tablebeta1(1:allrep,:,:),1));
%vbeta_no_a=squeeze(std(no_a.tablebeta1(1:allrep,:,:),1));
hold on
% plot([2:10]',mbeta(:,1),'--p');
% plot([2:10]',mbeta(:,2),'-h');
% plot([2:10]',mbeta(:,3),':*');
errorbar([2:Dmax]',mbeta(:,1),...
                 vbeta(:,1),'LineStyle','--','Marker','h');   
%errorbar([2:Dmax]',mbeta_no_a(:,1),...
 %                vbeta_no_a(:,1),'LineStyle','-','Marker','h');
% errorbar([2:Dmax]',mbeta(:,3),...
%                  vbeta(:,3),'LineStyle',':','Marker','h');
title('$\beta_1$ Bayesian Probit','interpreter','latex');
%legend(names);
xlabel('$d$','Interpreter','latex')
ylabel('(var anthitetic) / (var i.i.d)')
hold off
%orient(gcf,'landscape')
%print(gcf,strcat('beta_1BP20-5000-1000_normalrep.pdf'),'-dpdf','-fillpage')


for rep =1:allrep 
for anti=1:3   
tablebeta2(rep,:,anti)=a.tablebetaprob(rep,3).table(:,anti);
end
end

% for rep =1:allrep 
% for anti=1:3   
% tablebeta2_no_a(rep,:,anti)=no_a.tablebetaprob(rep,3).table(:,anti);
% end
% end

subplot(1,3,3)
mbeta=squeeze(mean(tablebeta2(1:allrep,:,:),1));
vbeta=squeeze(std(tablebeta2(1:allrep,:,:),1));
%mbeta_no_a=squeeze(mean(tablebeta2_no_a(1:allrep,:,:),1));
%vbeta_no_a=squeeze(std(tablebeta2_no_a(1:allrep,:,:),1));
hold on
% plot([2:10]',mbeta(:,1),'--p');
% plot([2:10]',mbeta(:,2),'-h');
% plot([2:10]',mbeta(:,3),':*');
errorbar([2:Dmax]',mbeta(:,1),...
                 vbeta(:,1),'LineStyle','--','Marker','h');   
%errorbar([2:Dmax]',mbeta_no_a(:,1),...
%                 vbeta_no_a(:,1),'LineStyle','-','Marker','h');
% errorbar([2:Dmax]',mbeta(:,3),...
%                  vbeta(:,3),'LineStyle',':','Marker','h');
title('$\beta_2$ Bayesian Probit','interpreter','latex');
%legend(names,'Interpreter','latex');
xlabel('$d$','Interpreter','latex')
ylabel('(var anthitetic) / (var i.i.d)')
hold off
orient(gcf,'landscape')
print(gcf,strcat('BP_20-5000-1000_circ.pdf'),'-dpdf','-fillpage')
