% Este programa resuelve el Ej2 de la Hoja4 (Practicas). Consiste en a
% partir de una matriz A, un vector b un parametro de relajacion, calcular
% la solucion al sistema Ax=b por el metodo iterativo de relajacion,
% teniendo un test de parada que se basa en el numero de iteraciones y en
% la precision buscada.

A = input('Introduzca la matriz A: ');
b = input('Introduzca el vector b (ENTER para salir): ');

while ~isempty(b)
    w = input('Introduzca el parametro de relajacion: ');
    numMax = input('Introduzca el numero maximo de iteraciones: ');
    prec = input('Introduzca la precision deseada de la solucion: ');

    % Metodo de relajacion.
    b = b';
    n = size(A, 1);
    uAnt = zeros(size(A,1), 1);
    uSig = zeros(size(A,1), 1);
    r = b;
    d = zeros(size(A,1), 1);
    normB = norm(b);
    k = 0;
    while (k < numMax) && (norm(r) >= prec * normB)
        for i = 1:n
            r(i) = b(i) - A(i, 1:i-1) * uSig(1:i-1) - A(i,i:n) * uAnt(i:n);
            d(i) = w * (r(i) / A(i, i));
            uSig(i) = uAnt(i) + d(i);
        end
        k = k + 1;
        uAnt = uSig;
    end

    disp('El vector solucion es: ')
    disp(uSig)
    fprintf('Se han utilizado %d iteraciones.\n', k);
    b = input('Introduzca un nuevo vector b (ENTER para salir): ');
end