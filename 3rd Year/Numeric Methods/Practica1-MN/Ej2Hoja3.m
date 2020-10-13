% Este programa resuelve el ejercicio 2 de la hoja 3 (Practicas)
% en el que introduces una matriz A (dimension y elementos) y el programa
% te saca la factorizacion LU, por el metodo de eliminacion gaussiana,
% de A (en una unica matriz). Ademas puedes introducir vectores b para que
% el programa resuelva el sistema Ax = b y saque la solucion x.

n = input('Introduzca la dimension de la matriz: ');
M = input('Introduzca la matriz: ');
punt(n) = 0; % Vector de punteros
for i = 1:n
    punt(i) = i;
end
% Metodo de la eliminacion gaussiana con punteros.
for i = 1:n
   [maximo, pos] = max(M(punt(i:n), i)); % Se coge el valor mas grande de la columna.
   pos = punt(pos + i - 1);
   if maximo ~= 0
       punt(pos) = i; % Se cambian los valores del vector punteros.
       punt(i) = pos;
       for j = 1:n % Se establece los valores de todas las posiciones mayores que la fila.
           if punt(j) > i
               M(j, i) = M(j, i) / M(pos, i); 
               for k = i+1:n % Se realiza la operacion correspondiente en el resto de elementos de la fila.
                   M(j,k) = M(j,k) - M(j,i) * M(pos,k);
               end
           end
       end
   else
       error('Esta matriz no es invertible!')
   end
end
disp(punt)
disp('La matriz LU es:')
disp(M)


% Metodo de remonte con punteros para para obtener la solucion del sistema.
w(n) = 0; % Se crean los vectores antes porque la dimension no cambia.
u(n) = 0;
% Se pide un vector b y se calcula la solucion correspondiente.
b = input('Introduzca el vector b (ENTER para salir): ');
while ~isempty(b)
    % Calculo de la w para Lw = Pb. (Con las ecuaciones del libro)
    w(1) = b(punt(1));
    for i=2:n
        w(i) = b(punt(i)) - (M(punt(i),1:i-1) * w(1:i-1)');
    end

    % Calculo de la u para Uu = w. (Con las ecuaciones del libro)
    u(n) = w(n) / M(punt(n),n);
    for i = n-1:-1:1
        u(i) = 1/M(punt(i),i) * (w(i) - M(punt(i), i+1:n) * u(i+1:n)');
    end

    % Se muestran los resultados
    disp('La w: ')
    disp(w)
    disp('La u (solucion del sistema): ')
    disp(u)
    
    b = input('Introduzca un nuevo vector b (ENTER para salir): ');
end
