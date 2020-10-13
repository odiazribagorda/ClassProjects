package tp.pr3.exceptions;

/**
 * Clase que genera excepciones cuando se producen problemas con variables no inicializadas.
 * @author Oscar Diaz Ribagorda y Mateo Garcia Perez.
 *
 */
public class NotFoundException extends Exception {
	
	public NotFoundException(){
		super();
	}
	
	public String toString() {
		return "No se ha encontrado el elemento";
	}
}
