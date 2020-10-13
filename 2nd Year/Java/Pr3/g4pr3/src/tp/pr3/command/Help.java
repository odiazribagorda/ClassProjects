package tp.pr3.command;

import tp.pr3.mv.Engine;

/**
 * Esta clase implementa las funciones del objeto Help de Command.
 * @author Oscar Diaz Ribagorda y Mateo Garcia Perez.
 *
 */
public class Help implements Command{
	/**
	 * Llama a mostrarAyuda de Engine que se encargara de mostrar la ayuda.
	 * @param engine Engine que llama al ComandParse para que se muestre la informacion de cada comando
	 */
	public void execute(Engine engine) {
		engine.mostrarAyuda();
		}
	
	/**
	 * Parsea un objeto de la clase Help.
	 * @param s Un array de string que lleva el comando a parsear
	 * @return el comando Help o null si no se corresponde
	 */
	public Command parse(String[] s) {
		if (s.length==1 && s[0].equalsIgnoreCase("HELP"))
			return new Help();
		else return null;
		}
	
	/**
	 * Da la ayuda correspondiente a este objeto en concreto.
	 * @return una string con la informacion de lo que hace help
	 */
	public String textHelp() {
		return "	HELP: Muestra esta ayuda" +
					System.getProperty("line.separator");
		}
	public String toString(){
		return "HELP";
	}
}
