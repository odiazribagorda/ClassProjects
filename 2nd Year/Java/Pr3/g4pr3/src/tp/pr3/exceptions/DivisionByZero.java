package tp.pr3.exceptions;

/**
 * Clase que genera excepciones cuando se intenta dividir entre 0.
 * @author Oscar Diaz Ribagorda y Mateo Garcia Perez.
 *
 */
public class DivisionByZero extends Exception{
	
	public DivisionByZero(){
		super();
	}
	
	public String toString() {
		return "No se permite dividir entre 0";
	}

}
