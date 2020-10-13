package tp.pr3.exceptions;

/**
 * Clase que genera excepciones cuando se producen problemas con el analisis lexico del
 * programa.
 * @author Oscar Diaz Ribagorda y Mateo Garcia Perez.
 *
 */
public class LexicalAnalysisException extends Exception{
	
	private String s;
	
	public LexicalAnalysisException(String s){
		super();
		this.s = s;
	}
	
	public String toString() {
		return "No se ha podido parsear el programa fuente. " + s;
	}

}
