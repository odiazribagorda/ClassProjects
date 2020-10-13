package tp.pr3.bytecode.conditional_jumps;

import tp.pr3.bytecode.ByteCode;
import tp.pr3.exceptions.ExecutionError;
import tp.pr3.exceptions.StackException;
import tp.pr3.mv.CPU;

/**
 * Clase abstracta de la cual heredaran todos los ByteCodes que implementen Saltos Condicionales.
 * @author Oscar Diaz Ribagorda y Mateo Garcia Perez.
 *
 */

 abstract public class ConditionalJumps implements ByteCode{
	 /**
	  * Int con la posicion a la que se salta
	  */
	 protected int pos;
	 
	 public ConditionalJumps(int n){
		 pos =n;
	 }
	 
	 /**
	 * {@inheritDoc}
	 */
	 public void execute(CPU cpu) throws ExecutionError {
		 try {
			cpu.comprobarPila();
		} catch (StackException e) {
			throw new ExecutionError(e.toString());
		}
		 execute(cpu.pop(), cpu.pop(), cpu);
		 
	 }
	 /**
	 * {@inheritDoc}
	 */
	 public ByteCode parse(String[] s) {
		 if (s.length == 2) {
			 return parseAux(s);
		 }
		 else return null;
	 }
	 /**
	  * Setter de la posicion
	  * @param n Int con el valor de la posicion
	  */
	 public void setPos(int n) {
		 pos = n;
	 }
	 
	 /**
	  * Ejecuta cada uno de los ConditionalJumps en especifico
	  * @param n1 Primer numero a comparar
	  * @param n2 Segundo numero a comparar
	  * @param cpu CPU donde se ejecuta
	  */
	 abstract public void execute(int n1, int n2, CPU cpu);
	 /**
	  * Parsea a un ConditionalJumps determinado
	  * @param s Array de Strings a parsear
	  * @return El ByteCode con la informacion o null si no se corresponde con ninguno
	  */
	 abstract public ByteCode parseAux(String[] s);
}
