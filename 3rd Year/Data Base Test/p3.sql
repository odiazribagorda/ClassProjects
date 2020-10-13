/abolish
/duplicates on

create table programadores(dni string primary key, nombre string, dirección string, teléfono string);
insert into programadores values('1','Jacinto','Jazmín 4','91-8888888');
insert into programadores values('2','Herminia','Rosa 4','91-7777777');
insert into programadores values('3','Calixto','Clavel 3','91-1231231');
insert into programadores values('4','Teodora','Petunia 3','91-6666666');

create table analistas(dni string primary key, nombre string, dirección string, teléfono string);
insert into analistas values('4','Teodora','Petunia 3','91-6666666');
insert into analistas values('5','Evaristo','Luna 1','91-1111111');
insert into analistas values('6','Luciana','Júpiter 2','91-8888888');
insert into analistas values('7','Nicodemo','Plutón 3',NULL);

create table distribución(códigoPr string, dniEmp string, horas int, primary key (códigoPr, dniEmp));
insert into distribución values('P1','1',10);
insert into distribución values('P1','2',40);
insert into distribución values('P1','4',5);
insert into distribución values('P2','4',10);
insert into distribución values('P3','1',10);
insert into distribución values('P3','3',40);
insert into distribución values('P3','4',5);
insert into distribución values('P3','5',30);
insert into distribución values('P4','4',20);
insert into distribución values('P4','5',10);

create table proyectos(código string primary key, descripción string, dniDir string);
insert into proyectos values('P1','Nómina','4');
insert into proyectos values('P2','Contabilidad','4');
insert into proyectos values('P3','Producción','5');
insert into proyectos values('P4','Clientes','5');
insert into proyectos values('P5','Ventas','6');

--Vista 1: Dni de todos los empleados:
create view vista1(dni) as select dni from programadores union select dni from analistas;

--Vista 2: Dni de los empleados que son programadores y analistas:
create view vista2(dni) as select dni from programadores intersect select dni from analistas;

--Vista 3: Dni de los empleados sin trabajo:
create view dniemp(dni) as select dni from programadores union select dni from analistas;
create view dnitrab(dni) as select dniDir from proyectos union select dniEmp from distribución;
create view vista3(dni) as select dni from dniemp except select dni from dnitrab;

--Vista 4: Código de proyectos sin analistas asignados (no se cuenta el director):
create view vista4(código) as select código from proyectos except select códigoPr from distribución join analistas on distribución.dniEmp= analistas.dni;

--Vista 5: Dni de los analistas que dirijan proyectos pero no sean programadores:
create view progyana(dni) as select dni from programadores intersect select dni from analistas;
create view ana_no_prog(dni) as select dni from analistas except select dni from progyana;
create view vista5(dni) as select distinct dni from ana_no_prog join proyectos on dni = dniDir;

--Vista 6: Descripción de los proyectos con los nombres de los programadores y horas asignados a ellos:
create view vista6(descripción,nombre,horas) as  select descripción, nombre, horas from proyectos join distribución join programadores on proyectos.código= distribución.códigoPr and dni=dniEmp;

--Vista 7: Listado de teléfonos compartidos por empleado:
create view tef_emp(dni,teléfono) as select dni,teléfono from programadores union select dni,teléfono from analistas;
create view vista7(telefono) as select distinct tef1.teléfono from tef_emp tef1, tef_emp tef2 where tef1.teléfono = tef2.teléfono and tef1.dni != tef2.dni;

--Vista 8: Dni de los empleados que son a la vez programadores y analistas:
create view vista8(dni) as select dni from programadores natural join analistas;

--Vista 9: Dni y horas que trabaja cada empleado:
create view  vista9(dni,horas) as select dniEmp,sum(horas) as sum from distribución group by dniEmp;
 
--Vista 10:Dni(de todos), nombre y proyecto al que están asignados los empleados:
 create view todos(dni,nombre) as select dni,nombre from programadores union select dni,nombre from analistas;
 create view vista10(dni,nombre,proyecto) as select dni,nombre,códigoPr from todos left join distribución on dni=dniEmp;

--Vista 11: Dni y nombre de empleados sin teléfono:
create view emp(dni, nombre, dirección, teléfono) as select * from programadores union select * from analistas;
create view vista11(dni, nombre) as select dni, nombre from emp where teléfono is null;

--Vista 12: Empleados cuyo total de horas dividido entre el número de proyectos en que trabaja es menor que la media del total de horas por proyecto
-- dividido entre su número de empleados:
create view media_emp( dniEmp,horas_media) as select dniEmp, avg(horas) as avg from distribución group by dniEmp ;
create view media_proy(código, media_horas) as select códigoPr, avg(horas) as avg from distribución group by códigoPr;
create view vista12(dni) as select dniEmp from media_emp, (select avg(media_horas) as media from media_proy) where horas_media < media ;
 
--Vista 13: DNI de los empleados que trabajan en al menos los mismos proyectos que Evaristo: 
create view evaristo(dniEmp,nombre) as select dni,nombre from programadores where nombre= 'Evaristo'  union select dni,nombre from analistas where nombre = 'Evaristo';
create view proy_evaristo(códigoPr) as select códigoPr from distribución natural join evaristo;
create view trab_y_proy(dniEmp,códigoPr) as select dniEmp, códigoPr from distribución;
create view vista13(dni) as select dniEmp from trab_y_proy division proy_evaristo;

--Vista 14: DNI de los empleados que trabajan en al menos los mismos proyectos que Evaristo:
create view evaristo(dniEmp,nombre) as select dni,nombre from programadores where nombre= 'Evaristo'  union select dni,nombre from analistas where nombre = 'Evaristo';
create view proy_evaristo(códigoPr) as select códigoPr from distribución natural join evaristo;
create view trabajadores(dniEmp) as select distinct dniEmp from distribución;
create view no_compañeros(dniEmp,códigoPr) as select dniEmp, códigoPr from trabajadores join proy_evaristo except select dniEmp,códigoPr from distribución;
create view vista14(dni) as select dniEmp from trabajadores except select dniEmp from no_compañeros;

--Vista 15: Ampliar un 20% el número de horas que trabajan los que no son compañeros de Evaristo:
create view dni_ev(dni) as select dni from (select dni,nombre from programadores union select dni, nombre from analistas) where nombre = 'Evaristo';
create view proy_ev(códigoPr) as (select códigoPr from distribución join dni_ev where dniEmp = dni) union (select código from proyectos join dni_ev where dniDir = dni);
create view comp_ev(dniEmp) as select distinct dniEmp from distribución natural join proy_ev;
create view nocomp(dniEmp) as select dniEmp from distribución except select dniEmp from comp_ev;
create view vista15(códigoPr, dni,horas) as select códigoPr, dniEmp,horas*1.20 from distribución natural join nocomp ;

--Vista 16: Nombres de los empleados que dependen de Evaristo:
create view dni_evaristo(dni) as select dni from (select dni,nombre from programadores union select dni, nombre from analistas) where nombre = 'Evaristo';
create view jefe_emp(dniDir, dniEmp) as select distinct dniDir, dniEmp from distribución, proyectos where códigoPr = código and dniEmp != dniDir;
create view nombres(dni,nombre) as select dni,nombre from programadores union select dni,nombre from analistas;
create view vista16(nombre) as with rpl (dniDir, dniEmp) as (select root.dniDir, root.dniEmp from jefe_emp root where root.dniDir = (select * from dni_evaristo) union all select child.dniDir, child.dniEmp from rpl parent, jefe_emp child where parent.dniEmp = child.dniDir) select nombre from rpl, nombres where dni = dniEmp group by nombre;

--Pruebas
select * from vista1; 
select * from vista2;
select * from vista3;
select * from vista4;
select * from vista5;
select * from vista6;
select * from vista7;
select * from vista8;
select * from vista9;
select * from vista10;
select * from vista11;
select * from vista12;
select * from vista13;
select * from vista14;
select * from vista15;
select * from vista16;
