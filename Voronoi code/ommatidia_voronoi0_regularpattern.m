Row=10;Line=Row;NumberofDot=Row*Line;
Tmax=20;Xmax=100;Xint=Xmax/Row;
InitYint=0.5;Yint=Xint*InitYint;
X=zeros(1,NumberofDot); Y=zeros(1,NumberofDot);
figure('Position',[1800 1000 1500 1200]);
Yex=0.2;
for t=1:Tmax
    for r=1:Row
        for l=1:Line
            i=(r-1)*Row+l;
            Yhalf=Yint*Row/2;
            X(1,i)=(r-1)*Xint+Xint/2;
            Y(1,i)=(((l-1)*Yint+Yint/2+Yint/2*mod(r+1,2))-Yhalf)*(1+(t-1)*Yex)+Yhalf+25;         
        end
    end
    actualYint=Yint*(1+(t-1)*Yex);
    subplot(4,5,t);voronoi(X,Y);axis([0 100 0 100]);axis equal;xticks([]);yticks([]);
    title(strcat('ƒ¢X=10, ƒ¢Y=',num2str(actualYint), ' :ƒ¢Y/ƒ¢X=', num2str(actualYint/10)));
    %pause(1);
end


