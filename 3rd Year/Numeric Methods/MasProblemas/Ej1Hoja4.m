% Este programa resuelve el Ej1 de la Hoja4 (Practicas). Consiste en a
% partir de una matriz A y un vector b, calcular la solucion al sistema
% Ax=b por el metodo iterativo de Jacobi, teniendo un test de parada que se
% basa en el numero de iteraciones y en la precision buscada.

A = input('Introduzca la matriz A: ');
b = input('Introduzca el vector b (ENTER para salir): ');

while ~isempty(b)
    numMax = input('Introduzca el numero maximo de iteraciones: ');
    prec = input('Introduzca la precision deseada de la solucion: ');

    % Metodo de Jacobi.
    b = b';
    uAnt = zeros(size(A,1), 1);
    normB = norm(b);
    i = 0;
    while i < numMax && (i < 1 || norm(r) >= prec * normB) % Este parentesis
        r = b - A * uAnt;                           % es un arreglo para que la
        d = r ./ diag(A);                           % primera vuelta no pregunte por
        uSig = uAnt + d;                            % el r (no definido todavia)
        
        i = i + 1;
        uAnt = uSig;
    end

    disp('El vector solucion es: ')
    disp(uSig)
    b = input('Introduzca un nuevo vector b (ENTER para salir): ');
end