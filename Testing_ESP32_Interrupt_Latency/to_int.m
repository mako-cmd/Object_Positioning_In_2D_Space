function out = to_int(in)
    sz = size(in);
    sz = sz(1,2);
    out = 0;
    for i = 1:sz
        value = in(1,i);
        out = out + (value - 48) * (10^(sz-i));
    end
end