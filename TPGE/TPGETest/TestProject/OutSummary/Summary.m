x = [16^3, 32^3, 64^3, 128^3];
t = [1.014 8.749 65.286 533.368];
m = [8.44922 17.1523 86.3164 640.863];

figure(1);
plot(x,t,'r');
hold on;
scatter(x,t);
xlabel('Dimension');
ylabel('Laufzeit [s]');
legend('Laufzeit');
figure(2);
plot(x,m,'g');
hold on;
scatter(x,m);
xlabel('Dimension');
ylabel('Speicheraufwand [MB]');
legend('Speicheraufwand');