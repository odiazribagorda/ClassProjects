function [v,lam,res,k]=rqi(A,tol,kmax,v)

%function [v,lam,res,k]=rqi(A,tol,kmax,v)
%
%Rayleight Quotient Iteration: this function computes an
%approximation to an eigenpair (lam,v) using an adaptive shift
%v is the starting vector and kmax is the max number of iterations.

n=length(A);
if ~exist('v'),v=ones(n,1);end
if ~exist('kmax'),kmax=n;end
if ~exist('tol'),tol=1e-6;end

E=speye(n);
v=v(:)/norm(v);
k=0;res=1;lam=v'*A*v;
while res>tol & k<kmax
    k=k+1;
    v=(A-lam*E)\v;
    v=v/norm(v);
    lam=v'*A*v;
    res=norm(A*v-lam*v);
end