package tp.pr3.bytecode.instructions;

import tp.pr3.bytecode.ByteCode;
import tp.pr3.exceptions.ExecutionError;
import tp.pr3.exceptions.StackException;
import tp.pr3.mv.CPU;

/**
 * Esta clase implementa las funciones del objeto Load de ByteCode.
 * @author Oscar Diaz Ribagorda y Mateo Garcia Perez.
 *
 */
public class Load implements ByteCode{
	/**
	 * Int con la poscion de la memoria donde se carga
	 */
	private int pos;
	

	public Load(int parseInt) {
		pos = parseInt;
	}

	/**
	 * {@inheritDoc}
	 *
	 * Carga en la pila la posicion de memoria indicada.
	 */
	public void execute(CPU cpu) throws ExecutionError {
		try {
			cpu.load(pos);
		} catch (StackException e) {
			throw new ExecutionError(e.toString());
		}
	}
	
	/**
	 * {@inheritDoc}
	 */
	public ByteCode parse(String[] s){
		if (s.length==2 && s[0].equalsIgnoreCase("LOAD")){
			return new Load(Integer.parseInt(s[1]));
			}
		else return null;
	}
	
	public String toString(){
		return "LOAD " + pos;
	}
	/**
	 * Setter de la posicion
	 * @param n Int que tiene el valor de la posicion
	 */
	public void setPos(int n){
		pos = n;
	}
}
