package tp.pr3.bytecode.arithmetics;

import tp.pr3.bytecode.ByteCode;
import tp.pr3.exceptions.StackException;
import tp.pr3.mv.CPU;

/**
 * Esta clase implementa las funciones del objeto ADD de Arithmetics.
 * @author Oscar Diaz Ribagorda y Mateo Garcia Perez.
 *
 */
public class Add extends Arithmetics{
	
	/**
	 * 
	 * {@inheritDoc}
	 *
	 * Suma dos numeros y los guarda en la pila.
	 */
	public void execute(int a, int b, CPU cpu) throws StackException {
		try {
			cpu.push(a + b);
		} catch (StackException e) {
			throw e;
		}
	}
	
	/**
	 * {@inheritDoc}
	 */
	public ByteCode parseAux(String s){
		if (s.equalsIgnoreCase("ADD")){
			return new Add();
		}
		else return null;
	}
	
	/**
	 * Devuelve el nombre de un objeto de la clase Add.
	 */
	public String toString() {
		return "ADD";
	}
	
}
