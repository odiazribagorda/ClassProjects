package tp.pr3.program;

import tp.pr3.exceptions.ArrayException;

/**
 * Clase con objetos SourceProgram que son vectores de strings con la informacion del programa
 * a ejecutar.
 * @author Oscar Diaz Ribagorda y Mateo Garcia Perez.
 *
 */
public class SourceProgram {
	/**
	 * Atributo con las diferentes instrucciones en forma de string.
	 */
	private String[] sProgram;
	/**
	 * Atributo con el numero de instrucciones del programa fuente.
	 */
	private int numInst;
	/**
	 * Constante con el numero maximo de instrucciones que puede tener el programa
	 * fuente.
	 */
	private final int MAX_INST = 100;
	
	/**
	 * Constructor de la clase SourceProgram.
	 */
	public SourceProgram(){
		sProgram = new String[MAX_INST];
		numInst = 0;
	}
	
	/**
	 * Metodo que introduce una nueva instruccion en forma de string en el programa fuente.
	 * @param s
	 * @throws ArrayException
	 */
	public void introducir(String s) throws ArrayException {
		if (numInst < MAX_INST) {
			sProgram[numInst] = s;
			++numInst;
		}
		else throw new ArrayException();
	}
	
	/**
	 * Metodo que devuelve la instruccion en forma de string en la posicion indicada del
	 * programa fuente.
	 * @param i
	 * @return El string en la posicion i.
	 */
	public String getInst(int i) {
		if(i < numInst)
			return sProgram[i];
		else return null;
	}
	
	/**
	 * Metodo que devuelve el numero de instrucciones almacenadas en el programa fuente.
	 * @return El numero de instrucciones.
	 */
	public int getNumInst(){
		return numInst;
	}
	
	/**
	 * Metodo tString de la clase SourceProgram que muestra el programa fuente almacenado.
	 */
	public String toString() {
		String s = new String();
		if(numInst > 0) {
			s = "Programa fuente almacenado:\n";
			for(int i = 0; i < numInst; ++i)
				s += i + ": " + sProgram[i] + "\n";
		}
		
		return s;
	}
}
