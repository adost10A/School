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
t = -2:1/1000:2;
t1 = -2:1/2000:2;
t2 = -2:1/4000:2;
p = (heaviside(t+1) - heaviside(t-1));
p1 = (10^-3)*conv(p,p);
p2 = (10^-3)*conv(p1,p1);
subplot(3,1,1);
plot(t,p);
subplot(3,1,2);
plot(t1,p1);
subplot(3,1,3);
plot(t2,p2);
