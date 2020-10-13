package tp.pr3.bytecode.instructions;

import tp.pr3.bytecode.ByteCode;
import tp.pr3.exceptions.ExecutionError;
import tp.pr3.exceptions.StackException;
import tp.pr3.mv.CPU;

/**
 * Esta clase implementa las funciones del objeto Out de ByteCode.
 * @author Oscar Diaz Ribagorda y Mateo Garcia Perez.
 *
 */
public class Out implements ByteCode{
	
	/**
	 * {@inheritDoc}
	 *
	 * Muestra por pantalla el ultimo elemento de la pila.
	 */
	public void execute(CPU cpu) throws ExecutionError {
		try {
			cpu.out();
		} catch (StackException e) {
			throw new ExecutionError(e.toString());
		}
	}
	
	/**
	 * {@inheritDoc}
	 */
	public ByteCode parse(String[] s){
		if (s.length==1 && s[0].equalsIgnoreCase("OUT")){
			return new Out();
			}
		else return null;
	}
	
	public String toString(){
		return "OUT";
	}

}
