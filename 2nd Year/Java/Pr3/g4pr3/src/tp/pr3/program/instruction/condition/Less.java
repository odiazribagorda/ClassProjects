package tp.pr3.program.instruction.condition;

import tp.pr3.bytecode.conditional_jumps.Ifle;
/**
 * Subclase de Condition que representa la condicion menor
 * @author Oscar Diaz Ribagorda y Mateo Garcia Perez.
 *
 */
public class Less extends Condition{
	/**
	 * {@inheritDoc}
	 */
	public Condition parseAux(String s) {
		if(s.equals("<")) {
			Condition cond = new Less();
			cond.setCondition(new Ifle(0));
			return cond;
		}
		else
			return null;
	}
}
