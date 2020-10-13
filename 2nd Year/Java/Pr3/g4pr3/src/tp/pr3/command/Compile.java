package tp.pr3.command;

import tp.pr3.exceptions.ArrayException;
import tp.pr3.exceptions.LexicalAnalysisException;
import tp.pr3.exceptions.NotFoundException;
import tp.pr3.mv.Engine;

/**
 * Esta clase implementa las funciones del objeto Compile de Command.
 * @author Oscar Diaz Ribagorda y Mateo Garcia Perez.
 *
 */

public class Compile implements Command {

	/**
	 * Llama al compile del engine que contiene el programa fuente que se va a compilar
	 * @param engine Engine que contiene el programa a compilar
	 */
	public void execute(Engine engine) throws LexicalAnalysisException, ArrayException, NotFoundException {
		engine.compile();
	}
	/**
	 * Parsea un objeto de la clase Compile.
	 * @param s Un array de string que lleva el comando a parsear
	 * @return el comando Compile o null si no se corresponde
	 */
	public Command parse(String[] s) {
		if (s.length==1 && s[0].equalsIgnoreCase("COMPILE"))
			return new Compile();
		else return null;
	}

	/**
	 * Da la ayuda correspondiente a este objeto en concreto.
	 * @return una string con la informacion de lo que hace Compile
	 */
	public String textHelp() {
		return "	COMPILE: Genera un programa bytecode a partir de un programa fuente" +
				System.getProperty("line.separator");
	}
	/**
	 * Metodo que devuelve en una string el nombre del comando
	 * @return una string con el nombre del comando
	 * */
	public String toString(){
		return "COMPILE";
	}
}
