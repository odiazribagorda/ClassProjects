package tp.pr3.program.instruction;

import tp.pr3.exceptions.ArrayException;
import tp.pr3.exceptions.LexicalAnalysisException;
import tp.pr3.exceptions.NotFoundException;
import tp.pr3.program.LexicalParser;
import tp.pr3.program.ParsedProgram;
import tp.pr3.program.instruction.condition.Condition;
import tp.pr3.program.instruction.condition.ConditionParser;
import tp.pr3.program.Compiler;

/**
 * Clase que contiene objetos del tipo IfThen, que continen una condicion que si cumple,
 * prosigue a ejecutar el cuerpo del If y si no salta a la siguiente instruccion.
 * @author Oscar Diaz Ribagorda y Mateo Garcia Perez.
 *
 */
public class IfThen implements Instruction{
	private Condition condition;
	private ParsedProgram ifBody;
	
	/**
	 * Constructor de la clase IfThen.
	 */
	public IfThen() {
		condition = null;
		ifBody = new ParsedProgram();
	}
	
	/**
	 * {@inheritDoc}
	 * Parsea la condicion y luego el cuerpo.
	 */
	public Instruction lexParse(String[] words, LexicalParser lexparser) throws LexicalAnalysisException{
		if (words[0].equalsIgnoreCase("if")) {
			IfThen i = new IfThen();
			i.condition = ConditionParser.parse(words[1], words[2], words[3], lexparser);
			if (i.condition == null) throw new LexicalAnalysisException("Condicion incorrecta.");
			
			lexparser.lexicalParser(i.ifBody,"ENDIF");
			lexparser.increaseProgramCounter();
			return i;
		}
		else return null;
	}
	
	/**
	 * {@inheritDoc}
	 * Compila la condicion y el cuerpo.
	 */
	public void compile(Compiler compile) throws ArrayException, NotFoundException {
		this.condition.compile(compile);
		compile.compile(this.ifBody);
		int jump = compile.getCurrentNumberOfByteCodes();
		this.condition.setJump(jump);
	}
}
