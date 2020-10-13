package tp.pr3.bytecode.conditional_jumps;

import tp.pr3.bytecode.ByteCode;
import tp.pr3.mv.CPU;

/**
 * Esta clase implementa las funciones del objeto IFNEQ de ConditionalJumps.
 * @author Oscar Diaz Ribagorda y Mateo Garcia Perez.
 *
 */
public class Ifneq extends ConditionalJumps {
	public Ifneq(int n) {
		super(n);
	}

	/**
	 * {@inheritDoc}
	 */
	public ByteCode parseAux(String[] s) {
		if(s[0].equalsIgnoreCase("IFNEQ")){
			return new Ifneq(Integer.parseInt(s[1]));
		}
		else return null;
	}
	
	/**
	 * {@inheritDoc}
	 *
	 * En caso de que sean dos numeros distintos, sigue con la siguiente instruccion,
	 * en caso contrario salta a la posicion indicada.
	 */
	public void execute(int n1, int n2, CPU cpu) {
		if(n2 == n1) cpu.irA(pos);
	}
	
	public String toString(){
		return "IFNEQ " + pos;
	}
}
