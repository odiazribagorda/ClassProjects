package tp.pr3.program.instruction;

import tp.pr3.exceptions.LexicalAnalysisException;
import tp.pr3.program.LexicalParser;

/**
 * Clase utilizada para parsear strings a instrucciones, pasando por los parsers de las
 * instrucciones.
 * @author Oscar Diaz Ribagorda y Mateo Garcia Perez.
 *
 */
public class ParserInstruction {
	
	/**
	 * Vector constante con todas las diferentes instrucciones para poder recorrer todos
	 * los parsers de las mismas.
	 */
	private final static Instruction[] instructions = { new CompoundAssignment(),
			new IfThen(), new Return(), new SimpleAssignment(), new While(), new Write()
			};
	
	/**
	 * Metodo que parsea un string a una instruccion del tipo correspondiente.
	 * @param s
	 * @param lexical
	 * @return La instruccion parseada.
	 * @throws LexicalAnalysisException
	 */
	public static Instruction parse(String s, LexicalParser lexical) throws LexicalAnalysisException{
		Instruction inst = null;
		
		String[] words = s.split(" ");
		int i = 0;
		while(inst == null && i < instructions.length) {
			inst = instructions[i].lexParse(words, lexical);
			++i;
		}
		if(inst == null) throw new LexicalAnalysisException("Instruccion es incorrecta.");
		
		return inst;
	}
}
