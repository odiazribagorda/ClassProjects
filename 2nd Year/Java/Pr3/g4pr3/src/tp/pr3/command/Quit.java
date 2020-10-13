package tp.pr3.command;

import tp.pr3.mv.Engine;

/**
 * Esta clase implementa las funciones del objeto Quit de Command.
 * @author Oscar Diaz Ribagorda y Mateo Garcia Perez.
 *
 */
public class Quit implements Command{
	/**
	 * Llama a acabar de engine que se encarga de terminar el programa.
	 * @param engine Objeto Engine cuya ejecucion se va a terminar
	 */
	public void execute(Engine engine) {
		engine.acabar();
		}
	
	/**
	 * Parsea un objeto de la clase Quit.
	 * @param s Un array de string que lleva el comando a parsear
	 * @return el comando Quit o null si no se corresponde
	 */
	public Command parse(String[] s) {
		if (s.length==1 && s[0].equalsIgnoreCase("QUIT"))
			return new Quit();
		else return null;
		}
	
	/**
	 * Da la ayuda correspondiente a este objeto en concreto.
	 * @return una string con la informacion de lo que hace quit
	 */
	public String textHelp() {
		return "	QUIT: Cierra la aplicacion" +
					System.getProperty("line.separator");
		}
	/**
	 * @return una string con el nombre del comando
	 * */
	public String toString(){
		return "QUIT";
	}
}
