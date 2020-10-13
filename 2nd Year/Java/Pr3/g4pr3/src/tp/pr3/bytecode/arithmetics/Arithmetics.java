package tp.pr3.bytecode.arithmetics;

import tp.pr3.bytecode.ByteCode;
import tp.pr3.exceptions.DivisionByZero;
import tp.pr3.exceptions.ExecutionError;
import tp.pr3.exceptions.StackException;
import tp.pr3.mv.CPU;

/**
 * Esta es una clase abstracta de la cual heredaran todos los objetos que tratan
 * con operaciones aritmeticas.
 * @author Oscar Diaz Ribagorda y Mateo Garcia Perez.
 *
 */
 abstract public class Arithmetics implements ByteCode {
	 
	 /**
	 * {@inheritDoc}
	 */
	 public void execute(CPU cpu) throws ExecutionError {
		 try {
			cpu.comprobarPila();
			execute(cpu.pop(), cpu.pop(), cpu);
		} catch (StackException se) {
			throw new ExecutionError(se.toString());
		} catch (DivisionByZero dbz) {
			throw new ExecutionError(dbz.toString());
		}
			
	 }
	 /**
	  * {@inheritDoc}
	  */
	 public ByteCode parse(String[] s) {
		 if (s.length == 1) {
			 return parseAux(s[0]);
		 }
		 else return null;
	 }
	
	 /**
	  * Función para que cada ByteCode implemente su operacion.
	  * @param n1 int con el primer operador
	  * @param n2 int con el segundo operador
	  * @param cpu CPU con la pila donde se guarda
	  * @throws DivisionByZero Error si se divide entre 0
	  * @throws StackException Error de acceso a pila 
	  */
	 abstract public void execute(int n1, int n2, CPU cpu) throws DivisionByZero, StackException;
	 /**
	  * Parsea una string para ver si se corresponde con un Arithmetics determinado
	  * @param s string a parsear
	  * @return EL bytecode con la informacion o null si no se corresponde con ninguno
	  */
	 abstract public ByteCode parseAux(String s);
}
