%function plotsol(x,fem,alpha)
%
%USAGE: plotsol(x,fem) or plotsol(x,fem,alpha).
%
%DESCRIPTION: Plot finite element function x, using the mesh description in the structure fem. 
%
%INPUT: x: vector containing the nodal values of a FEM function such as the FEM solution 
%       of a BVP or the FEM eigenvector of an operator eigenvalue problem
%       fem: structure containing mesh information.
%       alpha: transparency parameter for the surface plot; alpha is a numerical
%       value between 0 and 1. Its default value is 1 if you use plotsol(x,fem).