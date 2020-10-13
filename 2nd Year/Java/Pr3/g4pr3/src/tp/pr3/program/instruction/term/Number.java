package tp.pr3.program.instruction.term;

import tp.pr3.bytecode.instructions.Push;
import tp.pr3.exceptions.ArrayException;
import tp.pr3.program.Compiler;
/**
 * Clase que implementa la interface Term
 * Representa los numeros del programa
 * @author Oscar Diaz Ribagorda y Mateo Garcia Perez.
 *
 */
public class Number implements Term {
	/**
	 * Numero que se utiliza en el programa
	 */
	private int num;
	/**
	 * Constructor de la clase Number
	 * @param n int con el numero que se va guardar en Number
	 */
	public Number(int n){
		num = n;
	}
	/**
	 * {@inheritDoc}
	 */
	public Term parse(String term)throws NumberFormatException{
		boolean isNum = true;
		int i = 0;
		while(isNum && i < term.length()) {
			if(term.charAt(i) < '0' || '9' < term.charAt(i)) {
				isNum = false;
			}
			++i;
		}
		if(isNum)
			return new Number(Integer.parseInt(term));
		else
			return null;
		
	}
	/**
	 * {@inheritDoc}
	 */
	public void compile(Compiler compiler) throws ArrayException {
		Push p= new Push(num);
		compiler.addByteCode(p);
	}

}
