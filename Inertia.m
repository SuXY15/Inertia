clc;
clear;
close all;
%%
pic = imread('input.jpg');
graph = pic(:,:,1);

pic_r = pic(:,:,1);
pic_g = pic(:,:,2);
pic_b = pic(:,:,3);

judge( bsxfun(@and,(pic_b <= 100),(pic_g <= 100)) ) = 1;
judge = logical(judge);
graph(judge) = 0;
graph(~judge) = 255;

imshow(graph);hold on;

%%
unit = 0.01;
Size = size(graph);
Xsize = Size(1);
Ysize = Size(2);
Sx= 0;  Ix = 0;
Sy= 0;  Iy = 0;
Ixy = 0;
A = 0;

%%
for px = 1:Xsize
    for py = 1:Ysize
        if graph(px,py)==0
            A = A + unit^2;
            x = px*unit;
            y = py*unit;
            Sx= Sx+y*unit^2;
            Sy= Sy+x*unit^2;
            Ix = Ix+y^2*unit^2;
            Iy = Iy+x^2*unit^2;
            Ixy = Ixy + x*y*unit^2;
        end
    end
end

Xc = Sx/A;  Pxc = Xc/unit;
Yc = Sy/A;  Pyc = Yc/unit;
Ixc = Ix - A*Xc.^2;
Iyc = Iy - A*Yc.^2;
Ixyc=Ixy-Xc*Yc*A;

if Ix ~= Iy
    sita = atan(2*Ixyc/(Ix-Iy))/2;
else
    sita = 0;
end
Ix0 = (Ixc+Iyc)/2 + 1/2*sqrt((Ixc-Iyc)^2+4*Ixyc^2);
Iy0 = (Ixc+Iyc)/2 - 1/2*sqrt((Ixc-Iyc)^2+4*Ixyc^2);

distance = 5;
dotNum = 100;
min = -dotNum*distance/2; max = dotNum*distance/2;
MainX = zeros(1,max-min);
MainY = zeros(1,max-min);
Main2X = zeros(1,max-min);
Main2Y = zeros(1,max-min);

for i = 1:dotNum
    I = i*distance;
    MainX(i) = Pxc + (min + I)*cos(sita);
    MainY(i) = Pyc + (min + I)*sin(sita);
    Main2X(i) = Pxc + (min + I)*cos(sita+pi/2);
    Main2Y(i) = Pyc + (min + I)*sin(sita+pi/2);
end

plot(Pxc,Pyc,'r*');hold on;
text(Xsize-150,Ysize-10,['unit:',num2str(unit)],'Color','b','FontSize',20);
text(Pxc,Pyc,['(Xc,Yc)=',num2str(Xc),' , ',num2str(Yc)],'Color','b','FontSize',20);
text(0,10,['(Ix,Iy)=',num2str(Ix),' , ',num2str(Iy)],'Color','g','FontSize',20);
text(0,40,['(Ixc,Iyc)=',num2str(Ixc),' , ',num2str(Iyc)],'Color','g','FontSize',20);
text(0,70,['sita=',num2str(sita*180/pi),'deg'],'Color','g','FontSize',20);
text(0,100,['Ixyc=',num2str(Ixyc)],'Color','g','FontSize',20);
text(0,130,['(Ix0,Iy0)=',num2str(Ix0),' , ',num2str(Iy0)],'Color','g','FontSize',20);
line([0 Xsize],[Yc/unit Yc/unit],'lineStyle','-.','Color','r');
line([Xc/unit Xc/unit],[0 Ysize],'lineStyle','-.','Color','r');
plot(MainX,MainY,'.y');
plot(Main2X,Main2Y,'.g');