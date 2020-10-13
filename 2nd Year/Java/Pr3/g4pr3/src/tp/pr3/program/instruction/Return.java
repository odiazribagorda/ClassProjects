package tp.pr3.program.instruction;

import tp.pr3.bytecode.instructions.Halt;
import tp.pr3.exceptions.ArrayException;
import tp.pr3.program.LexicalParser;
import tp.pr3.program.Compiler;

/**
 * Clase que contiene objetos del tipo Return, que se encarga de parar el programa cuando
 * se llega a esta instruccion.
 * @author Oscar Diaz Ribagorda y Mateo Garcia Perez.
 *
 */
public class Return implements Instruction{
	
	/**
	 * {@inheritDoc}
	 */
	public Instruction lexParse(String[] words, LexicalParser lexparser) {
		if (words[0].equalsIgnoreCase("return")){
			lexparser.increaseProgramCounter();
			return new Return();
		}
		else return null;
	}
	
	/**
	 * {@inheritDoc}
	 */
	public void compile(Compiler compile) throws ArrayException{
		compile.addByteCode(new Halt());
	}
}
