% Oscar Diaz Ribagorda (ID:1966444)

% This solution takes h_t to be 2/lambda(M-1*K) and for the Euler´s
% method, it does an iteration for every timestep h_t until it reaches time
% t = T = 5. Both of these, cause the algorithm to be very slow since the
% method for fem.level 6 is going to have a very small h_t and therefore is
% going to make the number of iterations very high. This could be solved by
% establishing a bigger h_t, but it hasn´t been done in this solution to
% keep the h_t in the range calculated in part (e) of this exercise.

clear all

%setup geometry and mesh:
fem.nv=4;%number of vertices
fem.xcoords=[0 1 1 0];%x coordinates for each vertex listed anti-clockwise
fem.ycoords=[0 0 1 1];%y coordinates for each vertex listed anti-clockwise
fem.Hmax=inf;%maximum initial mesh parameter: set to inf to get uniform mesh on unit square

%setup PDE data
fem.a=10e-2; %diffusion coefficient: has to be a constant
fem.c=@(x,y) 1+x+y; %reaction coefficient: has to be a function
fem.f=@(x,y) 1; %right hand side: has to be a function
fem.g=@(x,y) 0; %boundary condition: has to be a function

for i=1:3

fem.level=3+i; %refinement level

[K, fem] = femsol(fem);
A = K.A;
M = K.M;
f = K.RHS;

Q = M\A;

%Power method for computing eigenvalues
error = 1;
x=Q(:,1);
n=10;
max_error = 10^-6;

while error > max_error
y = Q * x;
error = abs(norm(x) - n);
n = norm(x);
x = y/n;
end

vec=x;
value=n;

% Suitable value for h_t. (Based on part (e) of the exercise)
% Have to keep in mind, the bigger h_t is, the faster it will be.
h_t = 2/value;

% Euler`s method.
T = 5;
t = 0;
u_k = ones(size(A, 1), 1);
q = M\f;

while t < T
 u_k = u_k + h_t * (q - Q * u_k);
 t = t + h_t;
end

disp("Norm for subdivision with fem.level " + (3 + i) + ": ")
disp(norm(u_k - A\f))

end

% The values obtained for the different levels are the following:
% With fem.level = 4: Norm = 0.0012
% With fem.level = 5: Norm = 9.7743e-5 (takes a bit to calculate)
% With fem.level = 6: Norm = 5.2336e-6 (takes very long to calculate)

return