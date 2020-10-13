package tp.pr3.command;

import tp.pr3.exceptions.ArrayException;
import tp.pr3.exceptions.BadFormatByteCode;
import tp.pr3.mv.Engine;

/**
 * Esta clase implementa las funciones del objeto Replace de Command.
 * @author Oscar Diaz Ribagorda y Mateo Garcia Perez.
 *
 */
public class Replace implements Command{
	/**
	 * Numero de la instruccion a sustituir
	 * */
	private int num;
	
	public Replace(int n){
		num=n;
	}

	/**
	 * Llama a replace de engine que se encarga de reemplazar la instruccion indicada por
	 * otra nueva.
	 * @param engine Engine que contiene el programa a modificar
	 * @throws BadFormatByteCode 
	 * @throws ArrayException 
	 */
	public void execute(Engine engine) throws ArrayException, BadFormatByteCode {
		engine.replace(num);
		}
	
	/**
	 * Parsea un objeto de la clase Replace.
	 * @param s Un array de string que lleva el comando a parsear
	 * @return el comando Replace o null si no se corresponde
	 */
	public Command parse(String[] s) {
		if (s.length==2 && s[0].equalsIgnoreCase("REPLACEBC")){
			return new Replace(Integer.parseInt(s[1]));
			}
		else return null;
		}
	
	/**
	 * Da la ayuda correspondiente a este objeto en concreto.
	 * @return una string con la informacion de lo que hace Replace
	 */
	public String textHelp() {
		return "	REPLACEBC N: Reemplaza la instruccion n por la solicitada al usuario" +
					System.getProperty("line.separator");
		
		}
	/**
	 * Metodo que dado un numero se encarga de igualar num a ese numero;
	 * @param n int al que se iguala num
	 * */
	private void setNum(int n) {
		num = n;
	}
	/**
	 * Metodo que devuelve en una string el nombre del comando
	 * @return una string con el nombre del comando
	 * */
	public String toString(){
		return "REPLACEBC " + num;
	}
}
