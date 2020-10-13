package tp.pr3.program.instruction.condition;

import tp.pr3.bytecode.conditional_jumps.Ifeq;
/**
 * Subclase de Condition que representa la condicion igual
 * @author Oscar Diaz Ribagorda y Mateo Garcia Perez.
 *
 */
public class Equal extends Condition{
	/**
	 * {@inheritDoc}
	 */
	public Condition parseAux(String s) {
		if(s.equals("=")) {
			Condition cond = new Equal();
			cond.setCondition(new Ifeq(0));
			return cond;
		}
		else
			return null;
	}
}
