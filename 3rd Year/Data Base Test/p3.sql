/abolish
/duplicates on

create table programadores(dni string primary key, nombre string, direcci�n string, tel�fono string);
insert into programadores values('1','Jacinto','Jazm�n 4','91-8888888');
insert into programadores values('2','Herminia','Rosa 4','91-7777777');
insert into programadores values('3','Calixto','Clavel 3','91-1231231');
insert into programadores values('4','Teodora','Petunia 3','91-6666666');

create table analistas(dni string primary key, nombre string, direcci�n string, tel�fono string);
insert into analistas values('4','Teodora','Petunia 3','91-6666666');
insert into analistas values('5','Evaristo','Luna 1','91-1111111');
insert into analistas values('6','Luciana','J�piter 2','91-8888888');
insert into analistas values('7','Nicodemo','Plut�n 3',NULL);

create table distribuci�n(c�digoPr string, dniEmp string, horas int, primary key (c�digoPr, dniEmp));
insert into distribuci�n values('P1','1',10);
insert into distribuci�n values('P1','2',40);
insert into distribuci�n values('P1','4',5);
insert into distribuci�n values('P2','4',10);
insert into distribuci�n values('P3','1',10);
insert into distribuci�n values('P3','3',40);
insert into distribuci�n values('P3','4',5);
insert into distribuci�n values('P3','5',30);
insert into distribuci�n values('P4','4',20);
insert into distribuci�n values('P4','5',10);

create table proyectos(c�digo string primary key, descripci�n string, dniDir string);
insert into proyectos values('P1','N�mina','4');
insert into proyectos values('P2','Contabilidad','4');
insert into proyectos values('P3','Producci�n','5');
insert into proyectos values('P4','Clientes','5');
insert into proyectos values('P5','Ventas','6');

--Vista 1: Dni de todos los empleados:
create view vista1(dni) as select dni from programadores union select dni from analistas;

--Vista 2: Dni de los empleados que son programadores y analistas:
create view vista2(dni) as select dni from programadores intersect select dni from analistas;

--Vista 3: Dni de los empleados sin trabajo:
create view dniemp(dni) as select dni from programadores union select dni from analistas;
create view dnitrab(dni) as select dniDir from proyectos union select dniEmp from distribuci�n;
create view vista3(dni) as select dni from dniemp except select dni from dnitrab;

--Vista 4: C�digo de proyectos sin analistas asignados (no se cuenta el director):
create view vista4(c�digo) as select c�digo from proyectos except select c�digoPr from distribuci�n join analistas on distribuci�n.dniEmp= analistas.dni;

--Vista 5: Dni de los analistas que dirijan proyectos pero no sean programadores:
create view progyana(dni) as select dni from programadores intersect select dni from analistas;
create view ana_no_prog(dni) as select dni from analistas except select dni from progyana;
create view vista5(dni) as select distinct dni from ana_no_prog join proyectos on dni = dniDir;

--Vista 6: Descripci�n de los proyectos con los nombres de los programadores y horas asignados a ellos:
create view vista6(descripci�n,nombre,horas) as  select descripci�n, nombre, horas from proyectos join distribuci�n join programadores on proyectos.c�digo= distribuci�n.c�digoPr and dni=dniEmp;

--Vista 7: Listado de tel�fonos compartidos por empleado:
create view tef_emp(dni,tel�fono) as select dni,tel�fono from programadores union select dni,tel�fono from analistas;
create view vista7(telefono) as select distinct tef1.tel�fono from tef_emp tef1, tef_emp tef2 where tef1.tel�fono = tef2.tel�fono and tef1.dni != tef2.dni;

--Vista 8: Dni de los empleados que son a la vez programadores y analistas:
create view vista8(dni) as select dni from programadores natural join analistas;

--Vista 9: Dni y horas que trabaja cada empleado:
create view  vista9(dni,horas) as select dniEmp,sum(horas) as sum from distribuci�n group by dniEmp;
 
--Vista 10:Dni(de todos), nombre y proyecto al que est�n asignados los empleados:
 create view todos(dni,nombre) as select dni,nombre from programadores union select dni,nombre from analistas;
 create view vista10(dni,nombre,proyecto) as select dni,nombre,c�digoPr from todos left join distribuci�n on dni=dniEmp;

--Vista 11: Dni y nombre de empleados sin tel�fono:
create view emp(dni, nombre, direcci�n, tel�fono) as select * from programadores union select * from analistas;
create view vista11(dni, nombre) as select dni, nombre from emp where tel�fono is null;

--Vista 12: Empleados cuyo total de horas dividido entre el n�mero de proyectos en que trabaja es menor que la media del total de horas por proyecto
-- dividido entre su n�mero de empleados:
create view media_emp( dniEmp,horas_media) as select dniEmp, avg(horas) as avg from distribuci�n group by dniEmp ;
create view media_proy(c�digo, media_horas) as select c�digoPr, avg(horas) as avg from distribuci�n group by c�digoPr;
create view vista12(dni) as select dniEmp from media_emp, (select avg(media_horas) as media from media_proy) where horas_media < media ;
 
--Vista 13: DNI de los empleados que trabajan en al menos los mismos proyectos que Evaristo: 
create view evaristo(dniEmp,nombre) as select dni,nombre from programadores where nombre= 'Evaristo'  union select dni,nombre from analistas where nombre = 'Evaristo';
create view proy_evaristo(c�digoPr) as select c�digoPr from distribuci�n natural join evaristo;
create view trab_y_proy(dniEmp,c�digoPr) as select dniEmp, c�digoPr from distribuci�n;
create view vista13(dni) as select dniEmp from trab_y_proy division proy_evaristo;

--Vista 14: DNI de los empleados que trabajan en al menos los mismos proyectos que Evaristo:
create view evaristo(dniEmp,nombre) as select dni,nombre from programadores where nombre= 'Evaristo'  union select dni,nombre from analistas where nombre = 'Evaristo';
create view proy_evaristo(c�digoPr) as select c�digoPr from distribuci�n natural join evaristo;
create view trabajadores(dniEmp) as select distinct dniEmp from distribuci�n;
create view no_compa�eros(dniEmp,c�digoPr) as select dniEmp, c�digoPr from trabajadores join proy_evaristo except select dniEmp,c�digoPr from distribuci�n;
create view vista14(dni) as select dniEmp from trabajadores except select dniEmp from no_compa�eros;

--Vista 15: Ampliar un 20% el n�mero de horas que trabajan los que no son compa�eros de Evaristo:
create view dni_ev(dni) as select dni from (select dni,nombre from programadores union select dni, nombre from analistas) where nombre = 'Evaristo';
create view proy_ev(c�digoPr) as (select c�digoPr from distribuci�n join dni_ev where dniEmp = dni) union (select c�digo from proyectos join dni_ev where dniDir = dni);
create view comp_ev(dniEmp) as select distinct dniEmp from distribuci�n natural join proy_ev;
create view nocomp(dniEmp) as select dniEmp from distribuci�n except select dniEmp from comp_ev;
create view vista15(c�digoPr, dni,horas) as select c�digoPr, dniEmp,horas*1.20 from distribuci�n natural join nocomp ;

--Vista 16: Nombres de los empleados que dependen de Evaristo:
create view dni_evaristo(dni) as select dni from (select dni,nombre from programadores union select dni, nombre from analistas) where nombre = 'Evaristo';
create view jefe_emp(dniDir, dniEmp) as select distinct dniDir, dniEmp from distribuci�n, proyectos where c�digoPr = c�digo and dniEmp != dniDir;
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
