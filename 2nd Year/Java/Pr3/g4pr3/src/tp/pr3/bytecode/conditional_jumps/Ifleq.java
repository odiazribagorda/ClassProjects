package tp.pr3.bytecode.conditional_jumps;

import tp.pr3.bytecode.ByteCode;
import tp.pr3.mv.CPU;

/**
 * Esta clase implementa las funciones del objeto IFLEQ de ConditionalJumps.
 * @author Oscar Diaz Ribagorda y Mateo Garcia Perez.
 *
 */
public class Ifleq extends ConditionalJumps {
	
	public Ifleq(int n) {
		super(n);
	}

	/**
	 * Parsea un objeto de la clase IFLEQ.
	 */
	public ByteCode parseAux(String[] s) {
		if(s[0].equalsIgnoreCase("IFLEQ")){
			return new Ifleq(Integer.parseInt(s[1]));
		}
		else return null;
	}
	
	/**
	 * 
	 * {@inheritDoc}
	 *
	 * En caso de que la subcima sea menor o igual que la cima de la pila, sigue con la 
	 * siguiente instruccion, en caso contrario salta a la posicion indicada.
	 */
	public void execute(int n1, int n2, CPU cpu) {
		if(n2 > n1) cpu.irA(pos);
	}
	
	public String toString(){
		return "IFLEQ " + pos;
	}
}
