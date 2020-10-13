package tp.pr3.bytecode;

import tp.pr3.exceptions.ArrayException;

/** Esta clase contine un vector de ByteCodes que va a ser el programa que luego habra que ejecutar
 * y todas las funciones para poder modificar este vector.
 * @author Oscar Diaz Ribagorda y Mateo Garcia Perez.
 */
public class ByteCodeProgram {
	/**
	 * Vector de ByteCodes que representa el programa que se va almacenando.
	 */
	private ByteCode[] program;
	/**
	 * Numero de instrucciones del programa almacenado.
	 */
	private int numInst;
	
	private final int MAX_INST = 100;
	
	/** Construye un objeto de la clase ByteCodeProgram().
	 */
	public ByteCodeProgram() {
		program = new ByteCode[MAX_INST];
		numInst = 0;
	}
	
	/** Inserta un nuevo ByteCode al final del programa.
	 * 
	 * @param bcode El bytecode que se va a insertar
	 * @throws ArrayException Error por acceso a Arrays
	 */
	public void insertarByteCode(ByteCode bcode) throws ArrayException {
		if (numInst >= program.length)
			throw new ArrayException();
		else {
			program[numInst] = bcode;
			++numInst;
		}
	}
	
	/** Inserta un nuevo ByteCode en una posicion dada (que ya esta llena).
	 * 
	 * @param bcode El bytecode que se va a insertar
	 * @param n La posicion donde se va a insertar
	 * @throws ArrayException Error por acceso a Arrays
	 */
	public void colocarByteCode(ByteCode bcode, int n)throws ArrayException {
		if (n >= numInst)
			throw new ArrayException();
		else {
			program[n] = bcode;
		}
	}
	
	/** Dada una posicion devuelve el bytecode que hay en esa posicion.
	 * 
	 * @param n Posicion de la que se quiere saber el bytecode
	 * @return El bytecode en la posicion dada (null si no hay nada en la posicion dada)
	 */
	public ByteCode devolverByteCode(int n) {
		ByteCode bc = null;
		if (n < numInst)
			bc = program[n];
		return bc;
	}
	
	/** Muestra por pantalla el programa (vector de ByteCode).
	 * 
	 */
	public String toString() {
		String s = new String();
		if(numInst > 0) {
			s = "Programa bytecode almacenado:\n";
			for(int i = 0; i < numInst; ++i)
				s += i + ": " + program[i] + "\n";
		}
		
		return s;
	}
	
	/**
	 * @return El numero de instrucciones del programa actual
	 */
	public int getNumInst() {
		return numInst;
	}

}
