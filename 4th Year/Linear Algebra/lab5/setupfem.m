clear all
%setup geometry and mesh:
fem.nv=4;%number of vertices
fem.xcoords=[0 1 1 0];%x coordinates for each vertex listed anti-clockwise
fem.ycoords=[0 0 1 1];%y coordinates for each vertex listed anti-clockwise
fem.Hmax=inf;%maximum initial mesh parameter: set to inf to get uniform mesh on unit square
fem.level=4;%refinement level
%setup PDE data
fem.a=1;%diffusion coefficient: has to be a constant
fem.c=@(x,y) 0*x.^2+0*y.^2;%reaction coefficient: has to be a function
fem.f=@(x,y) 1+0*x+0*y;%right hand side: has to be a function
fem.g=@(x,y) 0+0*x+0*y;%boundary condition: has to be a function
%fem.g=@(x,y)0+heaviside(x-0.5)+0*y;

return
%some useful commands:
plotsol(X,fem) % plot vector X (FEM solution or FEM eigenvector) defined on fem.mesh
meshplot(fem) % displays mesh used by the FEM. Do not use on highly-refined meshes