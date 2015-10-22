u = 0:0.01:2;
t = 0:0.01:2;

top = {[1 5]};
bot = {[2 0]};
H = tf(top,bot);

figure;
lsim(H,u,t);
figure;
step(H);
t0 = 0:0.5:5;
x = exp(-5.*t0).*heaviside(t0);
t1 = 0:(1/4):5;
x1 = conv(x,x);
t2= 0:(1/8):5;
x2 = conv(x1,x1);
figure
subplot(3,1,1)
plot(t0,x)
subplot(3,1,2)
plot(t1,x1)
subplot(3,1,3)
plot(t2,x2)
num1 = [1 4 4];
den1 = [1 1];
sys1 = tf(num1,den1);

