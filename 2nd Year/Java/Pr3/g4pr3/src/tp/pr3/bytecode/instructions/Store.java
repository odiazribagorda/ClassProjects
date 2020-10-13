package tp.pr3.bytecode.instructions;

import tp.pr3.bytecode.ByteCode;
import tp.pr3.exceptions.ExecutionError;
import tp.pr3.exceptions.StackException;
import tp.pr3.mv.CPU;
/**
 * Esta clase implementa las funciones del objeto Store de ByteCode.
 * @author Oscar Diaz Ribagorda y Mateo Garcia Perez.
 *
 */
public class Store implements ByteCode{
	/**
	 * Int con la posicion en la que se almacena
	 */
	private int pos;
	
	

	public Store(int parseInt) {
		pos = parseInt;
	}

	/**
	 * {@inheritDoc}
	 *
	 * Guarda en la posicion dada de memoria el ultimo elemento de la pila.
	 */
	public void execute(CPU cpu) throws ExecutionError{
		try {
			cpu.store(pos);
		} catch (StackException e) {
			throw new ExecutionError(e.toString());
		}
	}
	
	/**
	 * {@inheritDoc}
	 */
	public ByteCode parse(String[] s){
		if (s.length==2 && s[0].equalsIgnoreCase("STORE")){
			return new Store(Integer.parseInt(s[1]));
			}
		else return null;
	}
	
	public String toString(){
		return "STORE " + pos;
	}
	/**
	 * Setter de la posicion
	 * @param n int con el valor que se le va a dar a pos
	 */
	public void setPos(int n){
		pos=n;
	}
}
