package tp.pr3.program.instruction;

import tp.pr3.exceptions.ArrayException;
import tp.pr3.exceptions.LexicalAnalysisException;
import tp.pr3.exceptions.NotFoundException;
import tp.pr3.program.LexicalParser;
import tp.pr3.program.Compiler;

/**
 * Clase interfaz que lleva la estructura y funciones comunes a todas la instrucciones.
 * @author Oscar Diaz Ribagorda y Mateo Garcia Perez.
 *
 */
public interface Instruction {
	/**
	 * Metodo que parsea un vector con strings a una instruccion,
	 * comprobando que los atributos son correctos.
	 * 
	 * @param words
	 * @param lexparser
	 * @return Una instruccion con los valores del String pasado.
	 * @throws LexicalAnalysisException
	 */
	Instruction lexParse(String[] words, LexicalParser lexparser) throws LexicalAnalysisException;
	
	/**
	 * Metodo que compila una instruccion del programa parseado y la convierte en
	 * bytecodes que son introducidos en el programa de bytecodes.
	 * 
	 * @param compiler
	 * @throws ArrayException
	 * @throws NotFoundException
	 */
	void compile(Compiler compiler) throws ArrayException, NotFoundException;
}
