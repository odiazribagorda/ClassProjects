package tp.pr3.exceptions;

/**
 * Clase que genera excepciones cuando se producen problemas con los accesos a la pila.
 * @author Oscar Diaz Ribagorda y Mateo Garcia Perez.
 *
 */
public class StackException extends Exception {
	
	public StackException(){
		super();
	}
	
	public String toString() {
		return "Error en el manejo de la pila";
	}

}
