%function [K,fem]=femsol(fem)
%
%DESCRIPTION: Finite element code for second order 2D BVP of the form
%       /-------------------------------\
%       | -a Delta u + c u = f in Omega,| 
%       |                u = g on Gamma.|
%       \-------------------------------/
%The domain, coefficients and boundary condition need to be specified in
%the input structure fem (see example file setupfem.m)
%INPUT: fem: structure containing the description of a polygonal domain and
%       the data for the BVP
%OUTPUT: K: structure containing the finite element matrices A and M and the 
%        right hand side vector RHS corresponding to the forcing function f in the BVP.
%        fem: structure containing the domain and mesh information; can be
%        used for further processing, e.g., plot solution or eigenvectors etc.
