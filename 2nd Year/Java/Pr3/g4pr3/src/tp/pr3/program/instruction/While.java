package tp.pr3.program.instruction;

import tp.pr3.bytecode.instructions.Goto;
import tp.pr3.exceptions.ArrayException;
import tp.pr3.exceptions.LexicalAnalysisException;
import tp.pr3.exceptions.NotFoundException;
import tp.pr3.program.LexicalParser;
import tp.pr3.program.ParsedProgram;
import tp.pr3.program.instruction.condition.Condition;
import tp.pr3.program.instruction.condition.ConditionParser;
import tp.pr3.program.Compiler;

/**
 * Clase que contiene objetos del tipo While, con una condicion que mientras se cumpla, permitira
 * ejecutar el codigo de dentro del cuerpo hasta que la condicion deje de cumplirse.
 * @author Oscar Diaz Ribagorda y Mateo Garcia Perez.
 *
 */
public class While implements Instruction{
	
	/**
	 * Atributo condicion que es un objeto de la clase Condition.
	 */
	private Condition condition;
	/**
	 * Atributo cuerpo que es un objeto de la clase ParsedProgram.
	 */
	private ParsedProgram whileBody;
	
	/**
	 * Constructor de la clase While.
	 */
	public While() {
		condition = null;
		whileBody = new ParsedProgram();
	}
	
	/**
	 * {@inheritDoc}
	 * Parsea la condicion y la guarda como atributo y luego parsea el cuerpo y lo guarda
	 * como atributo.
	 */
	public Instruction lexParse(String[] words, LexicalParser lexparser) throws LexicalAnalysisException{
		if (words[0].equalsIgnoreCase("while")) {
			While w = new While();
			w.condition = ConditionParser.parse(words[1], words[2], words[3], lexparser);
			if (w.condition == null) throw new LexicalAnalysisException("Condicion incorrecta.");
			
			lexparser.lexicalParser(w.whileBody,"ENDWHILE");
			lexparser.increaseProgramCounter();
			return w;
		}
		else return null;
	}
	
	/**
	 * {@inheritDoc}
	 * Compila tanto la condicion como el cuerpo.
	 */
	public void compile(Compiler compiler) throws ArrayException, NotFoundException {
		int pc1 = compiler.getCurrentNumberOfByteCodes();
		condition.compile(compiler);
		
		compiler.compile(whileBody);
		
		Goto gt = new Goto(pc1);
		compiler.addByteCode(gt);
		
		int jump = compiler.getCurrentNumberOfByteCodes();
		this.condition.setJump(jump);
	}
}
