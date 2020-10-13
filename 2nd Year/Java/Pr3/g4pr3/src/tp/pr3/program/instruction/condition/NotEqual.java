package tp.pr3.program.instruction.condition;

import tp.pr3.bytecode.conditional_jumps.Ifneq;
/**
 * Subclase de Condition que representa la condicion distinta
 * @author Oscar Diaz Ribagorda y Mateo Garcia Perez.
 *
 */
public class NotEqual extends Condition {
	/**
	 * {@inheritDoc}
	 */
	public Condition parseAux(String s) {
		if(s.equals("!=")) {
			Condition cond = new NotEqual();
			cond.setCondition(new Ifneq(0));
			return cond;
		}
		else
			return null;
	}
}
