%% Import CSV Files

from_mic_1 = readtable("/Results/From_Mic_1.csv");
from_mic_2 = readtable("/Results/From_Mic_2.csv");
from_mic_3 = readtable("/Results/From_Mic_3.csv");
from_centre = readtable("/Results/From_Centre.csv");
from_corner = readtable("/Results/From_Corner.csv");

%% Generate plot for Source @ mic 2
data = from_mic_2;
syms x y t
for i = 1:6
    %get coordinates
    mic_1 = data(i,2).Variables * 10^(-6);
    mic_2 = data(i,3).Variables * 10^(-6);
    mic_3 = data(i,4).Variables * 10^(-6);
    
    %Solve for possible coordinates with simultaneous equations
    eqns = [(x^2) + ((y+0.25)^2) == (330 * ((mic_1)+t))^2, (x^2)+(y^2) ==  (330 * ((mic_2)+t))^2, ((x - 0.25)^2) + (y^2) == (330 * ((mic_3)+t))^2];
    vars = [x,y,t];
    [x_,y_,t_] = solve(eqns,vars);
    
    %Convert answers from symbols to numeric values
    x_ = double(x_);
    y_ = double(y_);
    t_ = double(t_);
    
    %Determine solutions that are within target region
    % RULES
    % X must be greater than 0
    % Y must be less than 0
    % t must be greater than 0 

    for j = 1:2
        %is x positive? if true go to next test else move to next value in
        %array
        if x_(j) > 0
            % is y negative if true go to next test else move to next value in
            if y_(j) < 0
                % if t positive if true select this index as correct and
                % exit
                if t_(j) > 0
                    select = j;
                    j = 2;
                end
            end
        end
    end
    
    figure(1);
    axis([0 0.25 -0.25 0]);
    plot(x_(select),y_(select),'*');
    hold on;
    

end

%% Generate plot for Source @ mic 3
data = from_mic_3;
syms x y t
for i = 1:6
    %get coordinates
    mic_1 = data(i,2).Variables * 10^(-6);
    mic_2 = data(i,3).Variables * 10^(-6);
    mic_3 = data(i,4).Variables * 10^(-6);
    
    %Solve for possible coordinates with simultaneous equations
    eqns = [(x^2) + ((y+0.25)^2) == (330 * ((mic_1)+t))^2, (x^2)+(y^2) ==  (330 * ((mic_2)+t))^2, ((x - 0.25)^2) + (y^2) == (330 * ((mic_3)+t))^2];
    vars = [x,y,t];
    [x_,y_,t_] = solve(eqns,vars);
    
    %Convert answers from symbols to numeric values
    x_ = double(x_);
    y_ = double(y_);
    t_ = double(t_);
    
    %Determine solutions that are within target region
    % RULES
    % X must be greater than 0
    % Y must be less than 0
    % t must be greater than 0 

    for j = 1:2
        %is x positive? if true go to next test else move to next value in
        %array
        if x_(j) > 0
            % is y negative if true go to next test else move to next value in
            if y_(j) < 0
                % if t positive if true select this index as correct and
                % exit
                if t_(j) > 0
                    select = j;
                    j = 2;
                end
            end
        end
    end
    
    figure(1);
    axis([0 0.25 -0.25 0]);
    plot(x_(select),y_(select),'*');
    hold on;
    

end

%% Generate plot for Source @ mic 1
data = from_mic_1;
syms x y t
for i = 1:6
    %get coordinates
    mic_1 = data(i,2).Variables * 10^(-6);
    mic_2 = data(i,3).Variables * 10^(-6);
    mic_3 = data(i,4).Variables * 10^(-6);
    
    %Solve for possible coordinates with simultaneous equations
    eqns = [(x^2) + ((y+0.25)^2) == (330 * ((mic_1)+t))^2, (x^2)+(y^2) ==  (330 * ((mic_2)+t))^2, ((x - 0.25)^2) + (y^2) == (330 * ((mic_3)+t))^2];
    vars = [x,y,t];
    [x_,y_,t_] = solve(eqns,vars);
    
    %Convert answers from symbols to numeric values
    x_ = double(x_);
    y_ = double(y_);
    t_ = double(t_);
    
    %Determine solutions that are within target region
    % RULES
    % X must be greater than 0
    % Y must be less than 0
    % t must be greater than 0 

    for j = 1:2
        %is x positive? if true go to next test else move to next value in
        %array
        if x_(j) > 0
            % is y negative if true go to next test else move to next value in
            if y_(j) < 0
                % if t positive if true select this index as correct and
                % exit
                if t_(j) > 0
                    select = j;
                    j = 2;
                end
            end
        end
    end
    
    figure(1);
    axis([0 0.25 -0.25 0]);
    plot(x_(select),y_(select),'*');
    hold on;
    

end

%% Generate plot for Source @ centre
data = from_centre;
syms x y t
for i = 1:6
    %get coordinates
    mic_1 = data(i,2).Variables * 10^(-6);
    mic_2 = data(i,3).Variables * 10^(-6);
    mic_3 = data(i,4).Variables * 10^(-6);
    
    %Solve for possible coordinates with simultaneous equations
    eqns = [(x^2) + ((y+0.25)^2) == (330 * ((mic_1)+t))^2, (x^2)+(y^2) ==  (330 * ((mic_2)+t))^2, ((x - 0.25)^2) + (y^2) == (330 * ((mic_3)+t))^2];
    vars = [x,y,t];
    [x_,y_,t_] = solve(eqns,vars);
    
    %Convert answers from symbols to numeric values
    x_ = double(x_);
    y_ = double(y_);
    t_ = double(t_);
    
    %Determine solutions that are within target region
    % RULES
    % X must be greater than 0
    % Y must be less than 0
    % t must be greater than 0 

    for j = 1:2
        %is x positive? if true go to next test else move to next value in
        %array
        if x_(j) > 0
            % is y negative if true go to next test else move to next value in
            if y_(j) < 0
                % if t positive if true select this index as correct and
                % exit
                if t_(j) > 0
                    select = j;
                    j = 2;
                end
            end
        end
    end
    
    figure(1);
    axis([0 0.25 -0.25 0]);
    plot(x_(select),y_(select),'*');
    hold on;
    

end

%% Generate plot for Source @ cornermic 1
data = from_corner;
syms x y t
for i = 1:6
    %get coordinates
    mic_1 = data(i,2).Variables * 10^(-6);
    mic_2 = data(i,3).Variables * 10^(-6);
    mic_3 = data(i,4).Variables * 10^(-6);
    
    %Solve for possible coordinates with simultaneous equations
    eqns = [(x^2) + ((y+0.25)^2) == (330 * ((mic_1)+t))^2, (x^2)+(y^2) ==  (330 * ((mic_2)+t))^2, ((x - 0.25)^2) + (y^2) == (330 * ((mic_3)+t))^2];
    vars = [x,y,t];
    [x_,y_,t_] = solve(eqns,vars);
    
    %Convert answers from symbols to numeric values
    x_ = double(x_);
    y_ = double(y_);
    t_ = double(t_);
    
    %Determine solutions that are within target region
    % RULES
    % X must be greater than 0
    % Y must be less than 0
    % t must be greater than 0 

    for j = 1:2
        %is x positive? if true go to next test else move to next value in
        %array
        if x_(j) > 0
            % is y negative if true go to next test else move to next value in
            if y_(j) < 0
                % if t positive if true select this index as correct and
                % exit
                if t_(j) > 0
                    select = j;
                    j = 2;
                end
            end
        end
    end
    
    figure(1);
    axis([0 0.25 -0.25 0]);
    plot(x_(select),y_(select),'*');
    hold on;

end

