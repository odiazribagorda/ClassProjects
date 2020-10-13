%Power method for computing eigenvalues
Q = [1 0 3; 0 2 0; 3 0 3];

error = 1;
x=Q(:,1);
n=10;
max_error = 10^-5;
while error > max_error
y = Q * x;
error = abs(norm(x) - n);
n = norm(x);
x = y/n;
end
vec=x;
value=n;
disp(vec)
disp(value)

disp(eig(Q))