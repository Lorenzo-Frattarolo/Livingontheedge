clc
clear all
close all
%Script for comparing sampling times of the different constructions
N=5000;
DD=10;
for rep=1:5000
for D=2:DD
D
k=0;
for T=3:4
    k=k+1;
 tic   
[U]=ILHFaster(N,D,T);
t(rep,k,D-1)=toc;
clear U
end
tic
[U]=ILHGAJ(N,D,2,1);
t(rep,k+1,D-1)=toc;
clear U
tic
[U]=ILHSimpFaster(N,D,1);
t(rep,k+2,D-1)=toc;
clear U
tic
[U]=randomC_1(N,D);
t(rep,k+3,D-1)=toc;
clear U
tic
[U]=ILHSimpFaster(N,D,0);
t(rep,k+4,D-1)=toc;
clear U
end
end
mt=squeeze(mean(t,1));
figure
col = colormap(lines(12));
mk={'h','h','h','*','s','s'};
ls={'-','-','-.','-.',':',':'};
sel=flip([1:6]);
colind=[7,1:5];
hold on 
mt2=mt;
for pp=1:size(sel,2)
sel(pp)    
plot([2:DD],mt2(sel(pp),:)','Color',col(colind(pp),:),'Marker',mk{pp},'LineStyle',ls{pp} )
end
hold off
leg={'$C_{d}(\{1\})$ $RBS$','$C_{d}(\{1\})$ $SEG$','$LH$ $C_d(\{1\})$','$LH$ $AJ$','$ILH(4)$','$ILH(3)$'};
legend(leg(flip(sel)),'interpreter','latex','Location','northwest')
ylabel('Time (sec) $\times\rho_{\min}/\rho$','interpreter','latex')
xlabel('$d$','interpreter','latex')

orient(gcf,'landscape')
print(gcf,strcat('samplingtime.pdf'),'-dpdf','-fillpage')


