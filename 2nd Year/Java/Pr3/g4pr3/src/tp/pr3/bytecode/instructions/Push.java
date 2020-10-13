package tp.pr3.bytecode.instructions;

import tp.pr3.bytecode.ByteCode;
import tp.pr3.exceptions.ExecutionError;
import tp.pr3.exceptions.StackException;
import tp.pr3.mv.CPU;

/**
 * Esta clase implementa las funciones del objeto Push de ByteCode.
 * @author Oscar Diaz Ribagorda y Mateo Garcia Perez.
 *
 */
public class Push implements ByteCode{
	/**
	 * Int con el numero que se pushea
	 */
	private int num;
	

	public Push(int parseInt) {
		num = parseInt;
	}

	/**
	 * {@inheritDoc}
	 *
	 * Mete en la ultima posicion de la pila el elemento dado.
	 */
	public void execute(CPU cpu) throws ExecutionError {
		try {
			cpu.push(num);
		} catch (StackException e) {
			throw new ExecutionError(e.toString());
		}
	}
	
	/**
	 * {@inheritDoc}
	 */
	public ByteCode parse(String[] s){
		if (s.length==2 && s[0].equalsIgnoreCase("PUSH")){
			return new Push(Integer.parseInt(s[1]));
			}
		else return null;
	}
	
	public String toString(){
		return "PUSH " + num;
	}
	/**
	 * Setter del numero
	 * @param n int al que se iguala num
	 */
	public void setNum(int n){
		num= n;
	}
}
