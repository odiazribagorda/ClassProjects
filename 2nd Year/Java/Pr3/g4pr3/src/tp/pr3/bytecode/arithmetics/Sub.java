package tp.pr3.bytecode.arithmetics;

import tp.pr3.bytecode.ByteCode;
import tp.pr3.exceptions.StackException;
import tp.pr3.mv.CPU;

/**
 * Esta clase implementa las funciones del objeto Sub de Arithmetics.
 * @author Oscar Diaz Ribagorda y Mateo Garcia Perez.
 *
 */
public class Sub extends Arithmetics {
	
	/**
	 * {@inheritDoc}
	 */
	public ByteCode parseAux(String s){
		if (s.equalsIgnoreCase("SUB")){
			return new Sub();
		}
		else return null;
	}
	
	/**
	 * {@inheritDoc}
	 *
	 * Resta dos numeros y los guarda en la pila. 
	 */
	public void execute(int n1, int n2, CPU cpu) throws StackException {
		try {
			cpu.push(n2 - n1);
		} catch (StackException e) {
			throw e;
		}
	}
	
	/**
	 * Devuelve el nombre de un objeto de la clase Sub.
	 */
	public String toString() {
		return "SUB";
	}

}
