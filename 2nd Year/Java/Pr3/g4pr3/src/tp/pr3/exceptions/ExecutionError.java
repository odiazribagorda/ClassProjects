package tp.pr3.exceptions;

/**
 * Clase que genera excepciones cuando se producen problemas en la ejecucion del programa.
 * @author Oscar Diaz Ribagorda y Mateo Garcia Perez.
 *
 */
public class ExecutionError extends Exception{
	private String s;
	
	public ExecutionError(String s){
		super();
		this.s = s;
	}
	
	public String toString() {
		return "Se ha producido un error durante la ejecucion del programa. " + s;
	}

}
