package tp.pr3.bytecode.instructions;

import tp.pr3.bytecode.ByteCode;
import tp.pr3.mv.CPU;

/**
 * Esta clase implementa las funciones del objeto Goto de ByteCode.
 * @author Oscar Diaz Ribagorda y Mateo Garcia Perez.
 *
 */
public class Goto implements ByteCode {
	/**
	 * Int con la posicion a la que se salta
	 */
	private int n;
	
	public Goto(int parseInt) {
		n= parseInt;
	}

	/**
	 * 
	 * {@inheritDoc}
	 *
	 * Va a la instruccion en la posicion indicada
	 */
	public void execute(CPU cpu){
		cpu.irA(n);
	}
	
	/**
	 * {@inheritDoc}
	 */
	public ByteCode parse(String[] s){
		if (s.length==2 && s[0].equalsIgnoreCase("GOTO")){
			return new Goto(Integer.parseInt(s[1]));
			
			}
		else return null;
	}
	/**
	 * Setter de la posicion
	 * @param pos int con el valor que se le va a dar a n
	 */
	public void setPos(int pos) {
		this.n = pos;
	}
	
	public String toString(){
		return "GOTO " + n;
	}
}
