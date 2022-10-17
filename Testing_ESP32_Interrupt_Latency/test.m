function x = test()
% Generate plot for Source @ mic 2
fun = @sys_x;
options = optimoptions('fsolve','Algorithm','levenberg-marquardt','Display','iter','MaxFunctionEvaluations',3000000,MaxIterations=4000000);

% Get solutions, get variety by varying starting point in different quadrants of xyz plane 
x0 = [0,-100,0];
x1 = fsolve(fun,x0,options);

x0 = [-100,0,0];
x2 = fsolve(fun,x0,options);

x0 = [0,0,-100];
x3 = fsolve(fun,x0,options);

x0 = [0,100,0];
x4 = fsolve(fun,x0,options);

x0 = [100,0,0];
x5 = fsolve(fun,x0,options);

x0 = [0,0,100];
x6 = fsolve(fun,x0,options);

% figure(1);
% plot(x1(1),x1(2),'o',LineWidth=5,Color='r');
% hold on;
% plot(x2(1),x2(2),'o',LineWidth=5,Color='g');
% hold on;
% plot(x3(1),x3(2),'o',LineWidth=5,Color='b');
% hold on;
% plot(x4(1),x4(2),'o',LineWidth=5,Color='c');
% hold on;
% plot(x5(1),x5(2),'o',LineWidth=5,Color='m');
% hold on;
% plot(x6(1),x6(2),'o',LineWidth=5,Color='y');
% axis([0 0.3 -0.3 0]);

% Init output var
x = 0;

% Select valid solution:  A valid solution will have x as positive, y as
% negativ and t as positive (duh)
% ***Remember x(1) = x, x(2) = y, x(3) = t
if (x1(1) > 0 && x1(2) < 0 && x1(3) > 0)
    x = x1;
elseif (x2(1) > 0 && x2(2) < 0 && x2(3) > 0)
    x = x2;
elseif (x3(1) > 0 && x3(2) < 0 && x3(3) > 0)
    x = x3;
elseif (x4(1) > 0 && x4(2) < 0 && x4(3) > 0)
    x = x4;
elseif (x5(1) > 0 && x5(2) < 0 && x5(3) > 0)
    x = x5;
elseif (x6(1) > 0 && x6(2) < 0 && x6(3) > 0)
    x = x6;   
end

if x == 0
    disp("ERROR: Invalid data!")
else
    figure(1);
    plot(x(1),x(2),'o',LineWidth=5,Color='r');
    axis([0 0.3 -0.3 0]);
end