% Esta funcion calcula la funcion spline en el intervalo [j,j+1].
% Para hacer esto, lo que se utiliza es una expresión explícita de los
% coeficientes del polinomio (despejamos de la formula). Tomando que,
% spl = t4 + t1*(x-x(j)) + t2*(x-x(j))^2 + t3*(x-x(j))^3, podemos despejar
% spl = t3*x^3 + (t2-3*x(j)*t3)*x^2 + (t1-2*x(j)*t2+3*(x(j)^2)*t3)*x +
% t4-t1*x(j)+t2*x(j)^2-t3*x(j)^3.

function [spl] = calcularSpline(x, y, h, m, j)
t1 = (y(j+1) - y(j))/h(j+1) - (2*m(j)+m(j+1))*h(j+1)/6;
t2 = m(j)/2;
t3 = (m(j+1)-m(j))/(6*h(j+1));
t4 = y(j);

spl = [t3, t2-3*x(j)*t3, t1-2*x(j)*t2+3*(x(j)^2)*t3, t4-t1*x(j)+t2*x(j)^2-t3*x(j)^3];
end

