package tp.pr1.mv;

/** Esta es la clase principal que solo se encarga de crear una engine y comenzar su ejecucion.
 * 
 * @author Oscar Diaz Ribagorda y Mateo Garcia Perez.
 *
 */
public class Main {

	/**
	 * Funcion que inicia la Engine que lleva el programa.
	 * 
	 * @param args
	 */
	public static void main(String[] args) {
		Engine engine = new Engine();
		engine.start();
	}

}
