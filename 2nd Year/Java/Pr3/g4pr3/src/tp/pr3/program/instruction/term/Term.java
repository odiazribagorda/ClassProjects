package tp.pr3.program.instruction.term;

import tp.pr3.exceptions.ArrayException;
import tp.pr3.exceptions.NotFoundException;
import tp.pr3.program.Compiler;
/**
 * Interface que representa a los posibles terminos del programa, tanto numeros como variables
 * @author Oscar Diaz Ribagorda y Mateo Garcia Perez
 *
 */
public interface Term {
	/**
	 * Dada una string se comprueba si se corresponde con el Term 
	 * @param term String que guarda el dato a parsear
	 * @return un term parseado con la informacion correspondiente o null si no se corresponde
	 */
	Term parse(String term);
	/**
	 * Metodo que genera y introduce en el ByteCodeProgam del compiler el bytecode asociado al Term
	 * @param compiler Objeto de la clase Compiler donde se introduce el bytecode asociado ademas de buscar la variable necesarias
	 * @throws NotFoundException Error si no se ha encontrado una variable en la lista del compiler
	 * @throws ArrayException Erro por acceso a una posicion del array no disponible
	 */
	void compile(Compiler compiler) throws NotFoundException, ArrayException;
}
