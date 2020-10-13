function [momentos, h] = calcularMomentos(abscisas, ordenadas, opcion)
n = length(abscisas);
h = zeros(n,1);
for j=1:n-1
    h(j+1) = abscisas(j+1) - abscisas(j);
end
land = zeros(n,1);
mu = zeros(n,1);
d = zeros(n,1);
for j=2:n-1
    land(j) = h(j+1) / (h(j)+h(j+1));
    mu(j) = 1 - land(j);
    d(j) = (6/(h(j)+h(j+1)))*(((ordenadas(j+1)-ordenadas(j))/h(j+1))-((ordenadas(j)-ordenadas(j-1))/h(j)));
end
tipo = input('Quieres que la funcion sea de Tipo 1 o de Tipo 2 (1 / 2): ');
if tipo == 1
    land(1) = 0;
    mu(n) = 0;
    d(1) = 0;
    d(n) = 0;
else
    if tipo == 2
        land(1) = 1;
        mu(n) = 1;
        if opcion == 0
            y_prima0 = input(['Introduzca el valor de la derivada en ', num2str(abscisas(1)), ': ']);
            y_primaN = input(['Introduzca el valor de la derivada en ', num2str(abscisas(n)), ': ']);
        else
            fpvec=vectorize(diff(sym(f)));
            fprima=eval(['@(x) ' fpvec]);
            y_prima0 = fprima(abscisas(1));
            y_primaN = fprima(abscisas(n));
        end
        d(1) = (6/h(2))*(((ordenadas(2)-ordenadas(1))/h(2)) - y_prima0);
        d(n) = (6/h(n))*(y_primaN - (ordenadas(n)-ordenadas(n-1))/h(n));
    end
end
A = diag(diag(2 * eye(n))) + diag(land(1:n-1),1) + diag(mu(2:n),-1);
momentos = calcularSol(A, d);

end