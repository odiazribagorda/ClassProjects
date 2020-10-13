package tp.pr3.bytecode.conditional_jumps;

import tp.pr3.bytecode.ByteCode;
import tp.pr3.mv.CPU;

/**
 * Esta clase implementa las funciones del objeto IFEQ de ConditionalJumps.
 * @author Oscar Diaz Ribagorda y Mateo Garcia Perez.
 *
 */
public class Ifeq extends ConditionalJumps{
	public Ifeq(int n) {
		super(n);
	}

	/**
	 * {@inheritDoc}
	 */
	public ByteCode parseAux(String[] s) {
		if(s[0].equalsIgnoreCase("IFEQ")){
			return new Ifeq(Integer.parseInt(s[1]));
	
		}
		else return null;
	}

	 /**
	  * {@inheritDoc}
	  */
	public void execute(int n1, int n2, CPU cpu) {
		if(n2 != n1) cpu.irA(pos);
	}
	
	public String toString(){
		return "IFEQ " + pos;
	}
}
