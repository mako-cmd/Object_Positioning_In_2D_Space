raw = fopen("mic_1.dat","r");
    mic_1 = (fgetl(raw));
    fclose(raw);
    raw = fopen("mic_2.dat","r");
    mic_2 = fgetl(raw);
    fclose(raw);
    raw = fopen("mic_3.dat","r");
    mic_3 = str2num(fgetl(raw)) * (10^(-6));
    fclose(raw);

%%
in = '254252';
sz = size(in);
sz = sz(1,2);
out = 0;
for i = 1:sz
   value = in(1,i);
   out = out + (value - 48) * (10^(sz-i));
end