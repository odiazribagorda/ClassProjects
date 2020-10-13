package tp.pr3.exceptions;

/**
 * Clase que genera excepciones cuando no se encuentra el fichero a abrir.
 * @author Oscar Diaz Ribagorda y Mateo Garcia Perez.
 *
 */
public class FileNotFoundException extends Exception {
	
	public FileNotFoundException() {
		super();
	}
	
	public String toString() {
		return "No se encontro el archivo solicitado.";
	}
}
