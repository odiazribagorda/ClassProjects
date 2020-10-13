package tp.pr3.exceptions;

/**
 * Clase que genera excepciones cuando se producen problemas con los arrays.
 * @author Oscar Diaz Ribagorda y Mateo Garcia Perez.
 *
 */
public class ArrayException extends Exception{
	
	public ArrayException(){
		super();
	}
	
	public String toString() {
		return "Posicion incorrecta en el array";
	}
}
