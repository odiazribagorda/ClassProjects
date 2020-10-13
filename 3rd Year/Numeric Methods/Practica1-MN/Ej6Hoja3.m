% Este programa resuelve el ejercicio 6 de la hoja 3 (Practicas)
% Dada una matriz simetrica y definida positiva A y un vector b, calcula
% la factorizacion de Cholesky de A. Ademas saca la solucion del sistema
% Ax = b para cada b introducido y la matriz B del metodo de Cholesky.

M = input('Introduzca la matriz A: ');
b = input('Introduzca el vector b (ENTER para salir): ');
i = 0;
while ~isempty(b)
    [s, B] = calcularB(M,b);
    if i == 0 
        disp('La matriz B es:')
        disp(B)
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

% Si la funcion tiene un argumento de salida saca la solucion al sistema, 
% si tiene dos argumentos de salida, saca la solucion y la matriz B
% utilizada para la factorizacion de Cholesky de la matriz.
function [solucion, B] = calcularB(M, b)
n = size(M, 1);
if nargout == 2
    B(n,n) = 0;
    for i = 1:n
        aux = M(i,i) - B(i, 1:i-1) * B(i, 1:i-1)';
        if aux <= 0
            error('No admite factorizacion de Cholesky');
        end
        B(i, i) = sqrt(aux);
        for j = i+1:n
            B(j,i) = 1 / B(i,i) * (M(i,j) - B(i, 1:i-1) * B(j, 1:i-1)');
        end
    end
elseif nargout == 1
    B = M;
end

% Calculamos la solucion con el metodo de remonte.
% Sacamos la w de la Bw = b.
w(n) = 0;
w(1) = b(1) / B(1,1);
for i = 2:n
    w(i) = 1 / B(i,i) * (b(i) - B(i, 1:i-1) * w(1:i-1)');
end
% Sacamos la u de B'u = w.
u(n) = w(n) / B(n, n);
for i = n-1:-1:1
    u(i) = 1/B(i,i) * (w(i)- B(i+1:n, i)' * u(i+1:n)');
end

solucion = u;
end