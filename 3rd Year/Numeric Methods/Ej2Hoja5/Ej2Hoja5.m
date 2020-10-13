% Este programa, resuelve el ejercicio 2 de la Hoja 2, que consiste en
% aproximar mediante funcion spline (de tipo 1 o tipo 2), o bien una tabla
% de valores o bien una funcion (en su forma anonima).

opcion = input('¿Desea interpolar a spline cubica mediante una tabla (0) o mediante una funcion (1)?: ');
abscisas = input('Introduzca un vector con los puntos sobre los que interpolar:\n');
n = length(abscisas);
if opcion == 0
    ordenadas = input('Introduzca un vector con los valores de la funcion en los puntos indicados:\n');
    plot(abscisas,ordenadas,'rx');
else
    f = input('Introduzca la funcion que se quiere interpolar (funcion anonima): ');
    ordenadas = f(abscisas);
    fplot(f, [min(abscisas),max(abscisas)],'g');
end
hold on;

% Calcular Momentos.
[momentos ,h] = calcularMomentos(abscisas, ordenadas, opcion);

% Calcular y dibujar funcion spline cubica.
for j=1:n-1
    spl = calcularSpline(abscisas, ordenadas, h, momentos, j);
    puntos = abscisas(j):((abscisas(j+1) - abscisas(j)) / 100):abscisas(j+1);
    plot(puntos,polyval(spl,puntos),'b');
end
