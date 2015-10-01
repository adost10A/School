clear all;

f = 400;
Tsample = 1/f;
t = 0:Tsample:1;
A = 1;
x = sin(2*pi*t);
y1 = x.^2;
y2 = x.*(1+2*x);
y3 = x.*sin(2*pi*350.*t);
plot(t,y1,t,y2,t,y3);
n1 = .5;
x2 = 12*n1 + 12*n1 - 24*n1; %Proves Linearity

%Because all three yx's meet at the center at .5
%-------------------------------------------------------------------------%
p = -1:.001:1;
p1 = conv(p,p);
p2 = conv(p1,p1);
