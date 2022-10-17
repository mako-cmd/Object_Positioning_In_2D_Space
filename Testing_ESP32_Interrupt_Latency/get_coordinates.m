function [x_out,y_out] = get_coordinates()
syms x y t;

raw = fopen("mic_1.dat","r");
mic_1 = to_int(fgetl(raw)) * (10^(-6));
fclose(raw);
raw = fopen("mic_2.dat","r");
mic_2 = to_int(fgetl(raw)) * (10^(-6));
fclose(raw);
raw = fopen("mic_3.dat","r");
mic_3 = to_int(fgetl(raw)) * (10^(-6));
fclose(raw);

 %Solve for possible coordinates with simultaneous equations
 eqns = [(x^2) + ((y+0.25)^2) == (330 * ((mic_1)+t))^2, (x^2)+(y^2) ==  (330 * ((mic_2)+t))^2, ((x - 0.25)^2) + (y^2) == (330 * ((mic_3)+t))^2];
 vars = [x,y,t];
 [x_,y_,t_] = solve(eqns,vars);

  x_ = double(x_);
  y_ = double(y_);
  t_ = double(t_);

  for i = 1:2
      if (x_(i) > 0 && y_(i) < 0 && t_(i) > 0) 
        x_out = x_(i);
        y_out = y_(i);
        t_out = t_(i);
      end
  end


