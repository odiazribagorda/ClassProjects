package tp.pr3.command;

import tp.pr3.exceptions.ExecutionError;
import tp.pr3.mv.Engine;

/**
 * Esta clase implementa las funciones del objeto Run de Command.
 * @author Oscar Diaz Ribagorda y Mateo Garcia Perez.
 *
 */
public class Run implements Command{
	/**
	 * Llama a el run de engine que se encarga de ejecutar el programa.
	 * @param engine Engine que contiene el programa que se va a ejecutar
	 */
	public void execute(Engine engine) throws ExecutionError {
		try {
			engine.run();
		} catch (ExecutionError e) {
			throw e;
		}
		}
	/**
	 * Parsea un objeto de la clase Run.
	 * @param s Un array de string que lleva el comando a parsear
	 * @return el comando Run o null si no se corresponde
	 */
	public Command parse(String[] s) {
		if (s.length==1 && s[0].equalsIgnoreCase("RUN"))
			return new Run();
		else return null;
		}
	/**
	 * Da la ayuda correspondiente a este objeto en concreto.
	 * @return una string con la informacion de lo que hace quit
	 */
	public String textHelp() {
		return "	RUN: Ejecuta el programa" +
					System.getProperty("line.separator");
		}
	/**
	 * Metodo que devuelve el nombre del comando
	 * @return una string con el nombre del comando
	 * */
	public String toString(){
		return "RUN";
	}
}
