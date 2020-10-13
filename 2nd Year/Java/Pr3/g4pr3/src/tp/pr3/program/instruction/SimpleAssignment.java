package tp.pr3.program.instruction;

import tp.pr3.bytecode.instructions.Store;
import tp.pr3.exceptions.ArrayException;
import tp.pr3.exceptions.NotFoundException;
import tp.pr3.program.LexicalParser;
import tp.pr3.program.instruction.term.Term;
import tp.pr3.program.instruction.term.TermParser;
import tp.pr3.program.Compiler;

/**
 * Clase que contiene objetos del tipo SimpleAssignment, que son asignaciones simples de un
 * numero o una variable a una variable.
 * @author Oscar Diaz Ribagorda y Mateo Garcia Perez.
 *
 */
public class SimpleAssignment implements Instruction {
	private String var_name;
	private Term rhs;
	
	/**
	 * {@inheritDoc}
	 */
	public Instruction lexParse(String[] words, LexicalParser lexparser) {
		if(words.length== 3 && words[0].length()==1){
			char name= words[0].charAt(0);
			Term t= TermParser.parse(words[2]);
			if('a'<=name && name <='z' && t != null){
				SimpleAssignment sa= new SimpleAssignment();
				sa.var_name=words[0];
				sa.rhs=t;
				lexparser.increaseProgramCounter();
				return sa;
			}
			else return null;
		}
		else return null;
	}

	/**
	 * {@inheritDoc}
	 */
	public void compile(Compiler compile) throws ArrayException, NotFoundException {
		rhs.compile(compile);
		int i= compile.getVarAlt(var_name);
		Store s= new Store(i);
		compile.addByteCode(s);
	}

}
