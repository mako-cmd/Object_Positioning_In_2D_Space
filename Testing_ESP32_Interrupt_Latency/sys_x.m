function F = sys_x(x)
    % x = x(1)
    % y = x(2)
    % t = x(3)
    F = [0,0,0];
    raw = fopen("mic_1.dat","r");
    mic_1 = to_int(fgetl(raw)) * (10^(-6));
    fclose(raw);
    raw = fopen("mic_2.dat","r");
    mic_2 = to_int(fgetl(raw)) * (10^(-6));
    fclose(raw);
    raw = fopen("mic_3.dat","r");
    mic_3 = to_int(fgetl(raw)) * (10^(-6));
    fclose(raw);
    
    F(1) = (x(1)^2) + ((x(2)+0.25)^2) - ((330 * ((mic_1)+x(3)))^2);
    F(2) = (x(1)^2)+(x(2)^2) - ((330 * ((mic_2)+x(3)))^2);
    F(3) = ((x(1) - 0.25)^2) + (x(2)^2) - ((330 * ((mic_3)+x(3)))^2);
end