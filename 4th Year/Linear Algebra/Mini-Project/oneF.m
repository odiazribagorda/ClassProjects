clear all

%setup geometry and mesh:
fem.nv=6;%number of vertices
fem.xcoords=[0 2 2 1 1 0];%x coordinates for each vertex listed anti-clockwise
fem.ycoords=[0 0 1 1 2 2];%y coordinates for each vertex listed anti-clockwise
fem.Hmax=[];%maximum initial mesh parameter: set to inf to get uniform mesh on unit square
fem.level=3;%refinement level
%setup PDE data
fem.a=10e-5;%diffusion coefficient: has to be a constant
fem.c=@(x,y) 1+x+y;%reaction coefficient: has to be a function
fem.f=@(x,y) (1+x+y).*(x+y);%right hand side: has to be a function
fem.g=@(x,y) x+y;%boundary condition: has to be a function
%fem.g=@(x,y)0+heaviside(x-0.5)+0*y;

[K,fem] = femsol(fem);
A = K.A;
D_inv = diag(diag(K.M).^-1);
f = K.RHS;
x_k = zeros(size(A,1),1);
r_k = f - A * x_k;
z_k = D_inv * r_k;

max_error = 10^-6 * norm(f);
num_it = 0;

while norm(f - A * x_k) > max_error
    w_k = A * z_k;
    h_k = (z_k' * r_k) / (z_k' * w_k);
    x_k = x_k + z_k * h_k;
    r_k = r_k - w_k * h_k;
    z_k = D_inv * r_k;
    
    num_it = num_it + 1;
end

disp(x_k)
disp(num_it)

meshplot(fem)

return


%some useful commands:
%plotsol(X,fem) % plot vector X (FEM solution or FEM eigenvector) defined on fem.mesh
%meshplot(fem) % displays mesh used by the FEM. Do not use on highly-refined meshes