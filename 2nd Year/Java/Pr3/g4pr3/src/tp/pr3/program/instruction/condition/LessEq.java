package tp.pr3.program.instruction.condition;

import tp.pr3.bytecode.conditional_jumps.Ifleq;
/**
 * Subclase de Condition que representa la condicion menor o igual
 * @author Oscar Diaz Ribagorda y Mateo Garcia Perez.
 *
 */
public class LessEq extends Condition{
	/**
	 * {@inheritDoc}
	 */
	public Condition parseAux(String s) {
		if(s.equals("<=")) {
			Condition cond = new LessEq();
			cond.setCondition(new Ifleq(0));
			return cond;
		}
		else
			return null;
	}
}
