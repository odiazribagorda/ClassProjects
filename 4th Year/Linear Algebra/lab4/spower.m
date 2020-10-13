function [v,lam,res,k]=spower(A,s,tol,kmax,v)

%function [v,lam,res,k]=spower(A,s,tol,kmax,v)
%
%This function computes an approximation to the eigenvector 
%corresponding to the dominant eigenvalue of A using a shift s,
%v is the starting vector and kmax is the max number of iterations.

n=length(A);
if ~exist('v'),v=ones(n,1);end
if ~exist('kmax'),kmax=n;end
if ~exist('s'),s=0;end
if ~exist('tol'),tol=1e-6;end

v=v/norm(v);E=speye(n);
k=0;
while k<kmax
    k=k+1;
    v=(A-s*E)*v;
    v=v/norm(v);
    lam=v'*A*v;
end

