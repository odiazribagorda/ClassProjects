% Este programa resuelve el ejercicio 4 de la hoja 3 (Practicas)
% Dada una matriz B y una serie de vectores b, el programa contiene una
% funcion que devuelve la solucion al sistema Ax = b por el metodo de
% factorizacion LU y ademas devuelve la factorizacion LU de A.

M = input('Introduzca la matriz: ');
b = input('Introduzca el vector b (ENTER para salir): ');
i = 0;
while ~isempty(b)
    [s, LU] = calcularLU(M,b);
    if i == 0 
        disp('La matriz LU es:')
        disp(LU)
    end
    if i > 0
        disp('La nueva solucion del sistema es:')
    else
        disp('La solucion del sistema es:')
    end
    disp(s)
    
    i = i + 1;
    b = input('Introduzca un nuevo vector b (ENTER para salir): ');
end


% Esta funcion devuelve la solucion y la matriz LU por el metodo de
% factorizacion LU, si solo tiene un argumento de salida, solo devuelve
% la solucion del sistema.
function [solucion, LU] = calcularLU(M, b)
n = size(M, 1);
if nargout == 2
    LU(n,n) = 0;
    for i = 1:n
        for j = i:n
            LU(i,j) = M(i, j) - LU(i, 1:i-1) * LU(1:i-1,j);
        end
        if LU(i, i) ~= 0
            for j = i+1:n
                LU(j,i) = 1 / LU(i, i) * (M(j,i) - LU(j,1:i-1) * LU(1:i-1,i));
            end
        else
            error('La matriz no admite factorizacion LU');
        end
    end
elseif nargout == 1
    LU = M;
end

% Calculamos la solucion con el metodo de remonte.

% Sacamos la w de la Lw = b.
w(n) = 0;
w(1) = b(1);
for i = 2:n
    w(i) = b(i) - LU(i, 1:i-1) * w(1:i-1)';
end
% Sacamos la u de Uu = w.
u(n) = w(n) / LU(n, n);
for i = n-1:-1:1
    u(i) = 1/LU(i,i) * (w(i)- LU(i,i+1:n) * u(i+1:n)');
end

solucion = u;
end