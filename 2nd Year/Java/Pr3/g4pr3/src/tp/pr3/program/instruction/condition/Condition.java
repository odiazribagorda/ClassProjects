package tp.pr3.program.instruction.condition;

import tp.pr3.bytecode.conditional_jumps.ConditionalJumps;
import tp.pr3.exceptions.ArrayException;
import tp.pr3.exceptions.NotFoundException;
import tp.pr3.program.LexicalParser;
import tp.pr3.program.instruction.term.Term;
import tp.pr3.program.instruction.term.TermParser;
import tp.pr3.program.Compiler;
/**
 * Clase abstracta que representa las diferntes condiciones que puede haber en el programa
 * @author Oscar Diaz Ribagorda y Mateo Garcia Perez.
 *
 */
abstract public class Condition {
	/**
	 * Term que representa el primer termino de la comparacion
	 */
	private Term term1;
	/**
	 * Term que representa el segundo termino de la comparacion
	 */
	private Term term2;
	/**
	 * ConditionalJumps que guarda el bytecode correspondiente a la condicion dada
	 */
	private ConditionalJumps condition;
	/**
	 * Dados los parametros de entrada se parsea cada uno para generar un objeto Condition
	 * @param t1 String con el primer termino de la comparacion
	 * @param op simbolo de la comparacion
	 * @param t2 String con el segundo termino de la comparacion
	 * @param parser LexicalParse que parsea el programa, se necesita aqui para poder aumentar su contador al acabar
	 * @return Condition ya parseada o null si no se corresponde con ninguna
	 */
	public Condition parse(String t1, String op, String t2, LexicalParser parser) {
		Condition cond = parseAux(op);
		if(cond != null) {
			cond.term1 = TermParser.parse(t1);
			cond.term2 = TermParser.parse(t2);
			parser.increaseProgramCounter();
		}
		return cond;
	}
	/**
	 * Genera el bytcode asociado y lo introduce en el Compiler
	 * @param compiler Objeto de la clase compiler donde se guardan los bytecodes asociados
	 * @throws NotFoundException Error si no se encuentra un elemento necesario en un array
	 * @throws ArrayException Erro si no se pudo acceder a la posicion del array
	 */
	public void compile(Compiler compiler) throws NotFoundException, ArrayException{
		term1.compile(compiler);
		term2.compile(compiler);
		condition.setPos(compiler.getCurrentNumberOfByteCodes());
		compiler.addByteCode(condition);
	}
	/**
	 * Setter del ConditionalJumps de Condition
	 * @param cond ConditionalJumps al cual se iguala el condition
	 */
	public void setCondition(ConditionalJumps cond) {
		this.condition = cond;
	}
	/**
	 * Establece la posicion a la que salta el ContionalJumps
	 * @param jump int con la posicion a la que se salta
	 */
	public void setJump(int jump) {
		this.condition.setPos(jump);
	}
	/**
	 * Metodo para ver a que objeto que hereda de Condition se corresponde la condicion
	 * @param s String con el simbolo de comparacion
	 * @return Objeto de una subclase de Condition  o null si no se corresponde
	 */
	abstract public Condition parseAux(String s);
}
