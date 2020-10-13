function [x, n] = augsolve(f)
    f = f.';
    m = (size(f, 1) - 1) / 2;
    w = [zeros(1, m), m*ones(1,m)];
    B = [eye(m),eye(m);eye(m),zeros(m)];
    K = [1, w; w.', B];
    b = solverM(f);
    y_next = b;
    norm_it = norm(f - K * y_next);
    norm_f = norm(f);
    i = 1;
    tau = 10 ^ -8;
    while norm_it > tau * norm_f
        y = y_next;
        y_next = b + [0, -m * y(1) * ones(1,m), m * y(1) * ones(1,m)].';
        
        norm_it = norm(f - K * y_next);
        i = i + 1;
    end
    x = y_next(m+2:2*m+1);
    n = 1;
end

function z = solverM(q)
    m = (size(q, 1) - 1) / 2;
    z1 = [q(1); q(m + 2:2*m +1); q(2:m+1) - q(m + 2:2*m +1)];
    z2 = [z1(1)- m*sum(z1(m + 2:2*m +1)); z1(2:2*m+1)];
    z = [z2(1)/(m^3 + 1); z2(2:2*m+1)];
end