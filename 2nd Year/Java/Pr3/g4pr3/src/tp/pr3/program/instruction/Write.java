package tp.pr3.program.instruction;

import tp.pr3.bytecode.instructions.Load;
import tp.pr3.bytecode.instructions.Out;
import tp.pr3.exceptions.ArrayException;
import tp.pr3.exceptions.NotFoundException;
import tp.pr3.program.LexicalParser;
import tp.pr3.program.Compiler;

/**
 * Clase que contiene objetos del tipo Write, que escribe por pantalla el valor correspondiente a
 * el numero o variable especificado.
 * @author Oscar Diaz Ribagorda y Mateo Garcia Perez.
 *
 */
public class Write implements Instruction{
	
	/**
	 * Atributo variable con el nombre de la variable a escribir.
	 */
	private String var_name;

	/**
	 * {@inheritDoc}
	 */
	public Instruction lexParse(String[] words, LexicalParser lexparser) {
		if(words.length == 2 && words[1].length()==1){
			char name= words[1].charAt(0);
			if(words[0].equalsIgnoreCase("write") &&('a' <= name && name <= 'z')){
				Write w = new Write();
				w.var_name= words[1];
				lexparser.increaseProgramCounter();
				return w;
			}
		}
		return null;
	}
	
	/**
	 * {@inheritDoc}
	 */
	public void compile(Compiler compile) throws NotFoundException, ArrayException {
		int i = compile.getVarOnly(var_name);
		Load l= new Load(i);
		compile.addByteCode(l);
		compile.addByteCode(new Out());
	}
}
