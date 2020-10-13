package tp.pr3.program.instruction.term;

import tp.pr3.bytecode.instructions.Load;
import tp.pr3.exceptions.ArrayException;
import tp.pr3.exceptions.NotFoundException;
import tp.pr3.program.Compiler;
/**
 * Clase que implenta la interface Term
 * Representa las posibles variables del programa
 * @author Oscar Diaz Ribagorda y Mateo Garcia Perez.
 *
 */
public class Variable implements Term {
	/**
	 * String con el nombre de la variable
	 */
	private String nombre;
	/**
	 * Constructor de Variable
	 * @param s String que guarda el nombre que se le va a dar a la variable
	 */
	public Variable(String s){
		nombre = s;
	}

	/**
	 * {@inheritDoc}
	 */
	public Term parse(String term) {
		if(term.length() != 1) return null;
		else{
			char name = term.charAt(0);
			if('a' <= name && name <= 'z' ) return new Variable(term);
			else return null;
		}
	}

	/**
	 * {@inheritDoc}
	 */
	public void compile(Compiler compiler) throws NotFoundException, ArrayException {
		int i = compiler.getVarOnly(nombre);
		Load l = new Load(i);
		compiler.addByteCode(l);
	}

}
