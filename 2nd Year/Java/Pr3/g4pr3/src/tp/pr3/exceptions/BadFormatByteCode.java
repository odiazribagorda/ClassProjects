package tp.pr3.exceptions;

/**
 * Clase que genera excepciones cuando se producen problemas con el formato de los bytecodes.
 * @author Oscar Diaz Ribagorda y Mateo Garcia Perez.
 *
 */
public class BadFormatByteCode extends Exception{
	
	public BadFormatByteCode(){
		super();
	}
	
	public String toString() {
		return "Sintaxis incorrecta del bytecode";
	}
}
