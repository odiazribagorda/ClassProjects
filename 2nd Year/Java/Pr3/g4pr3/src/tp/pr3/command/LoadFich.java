package tp.pr3.command;

import java.io.IOException;

import tp.pr3.exceptions.ArrayException;
import tp.pr3.mv.Engine;

/**
 * Esta clase implementa las funciones del objeto LoadFich de Command.
 * @author Oscar Diaz Ribagorda y Mateo Garcia Perez.
 *
 */

public class LoadFich implements Command {
	/**
	 * String que guarda el nombre del fichero que se va a abrir
	 * */
	private String fich;
	
	public LoadFich(String s){
		fich= s;
	}
	/**
	 * Llama al leerFich del engine que se encarga de cargar el programa fuente del texto de fich
	 * @param engine Engine en el que se guarda el programa fuente
	 * @throws IOException 
	 * @throws ArrayException 
	 */
	public void execute(Engine engine) throws IOException, ArrayException {
		engine.leerFich(fich); 
	}
	/**
	 * Parsea un objeto de la clase LoadFich.
	 * @param s Un array de string que lleva el comando a parsear
	 * @return el comando LoadFich o null si no se corresponde
	 */
	public Command parse(String[] s) {
		if (s.length==2 && s[0].equalsIgnoreCase("LOAD")){
			return new LoadFich(s[1]);
			}
		else return null;
	}
	/**
	 * Da la ayuda correspondiente a este objeto en concreto.
	 * @return una string con la informacion de lo que hace Load 
	 */
	public String textHelp() {
		return "	LOAD FICH: Carga el programa fuente almacenado en el fichero de nombre FICH" +
				System.getProperty("line.separator");
	}
	/**
	 * Metodo que devuelve en una string el nombre del comando
	 * @return una string con el nombre del comando
	 * */
	public String toString(){
		return "LOAD " + fich;
	}
	/**
	 * Metodo que dado una string se encarga de igualar fich a esa string;
	 * @param aux string a la  que se iguala fich
	 * */
	private void setFich(String aux){
		fich = aux;
	}
}
