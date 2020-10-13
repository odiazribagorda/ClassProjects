% Este programa resuelve el ejercicio 8 de la hoja 3 (Practicas)
% Dada una matriz tridiagonal A y un vector b, devuelve la solucion
% al sistema Ax = b.

M = input('Introduzca la matriz A (tridiagonal): ');
b = input('Introduzca el vector b (ENTER para salir): ');
i = 0;
while ~isempty(b)
    s = calcularSol(M,b);
    if i > 0
        disp('La nueva solucion del sistema es:')
    else
        disp('La solucion del sistema es:')
    end
    disp(s)
    
    i = i + 1;
    b = input('Introduzca un nuevo vector b (ENTER para salir): ');
end


function [x] = calcularSol(M, b)
n = size(M, 1);

% Se utilizan las formulas del ejercicio 7 Hoja3 (problemas).
m(n) = 0;
g(n) = 0;
m(1) = M(1,1);
g(1) = b(1) / M(1);
for i = 2:n
    m(i) = M(i,i) - (M(i-1, i) / m(i-1)) * M(i, i-1);
    g(i) = (b(i) - g(i-1) * M(i, i-1)) / m(i);
end
x(n) = g(n);
for i = n-1:-1:1
    x(i) = g(i) - (M(i, i+1) / m(i)) * x(i + 1);
end

end