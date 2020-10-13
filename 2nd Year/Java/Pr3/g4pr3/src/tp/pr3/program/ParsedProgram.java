package tp.pr3.program;

import tp.pr3.exceptions.ArrayException;
import tp.pr3.program.instruction.Instruction;

/**
 * Clase con objetos ParsedProgram que es un vector de instrucciones parseadas y
 * las funciones necesarias para tratar estos vectores.
 * @author Oscar Diaz Ribagorda y Mateo Garcia Perez.
 *
 */
public class ParsedProgram {
	/**
	 * Atributo con el vector de instrucciones donde se almacenara el programa
	 * parseado.
	 */
	private Instruction[] sProgram;
	/**
	 * Atributo con el numero de instrucciones que tiene el programa.
	 */
	private int numInst;
	/**
	 * Constante que indica el numero maximo de instrucciones que puede tener el programa.
	 */
	private final int MAX_INST=100;
	

	/**
	 * Constructor de la clase ParsedProgram.
	 */
	public ParsedProgram() {
		sProgram = new Instruction[MAX_INST];
		numInst= 0;
	}
	
	/**
	 * Metodo que introduce en el vector de instrucciones una nueva instruccion.
	 * @param inst
	 * @throws ArrayException
	 */
	public void introducir(Instruction inst) throws ArrayException {
		if(numInst < MAX_INST){
			sProgram[numInst] = inst;
			++numInst;
		}
		else throw new ArrayException();
	}
	
	/**
	 * Metodo que devuelve el numero de instrucciones actual del programa.
	 * @return Un entero con el numero de instrucciones del vector;
	 */
	public int getNumeroInst(){
		return numInst;
	}
	
	/**
	 * Metodo que devuelve la instruccion en una posicion especificada.
	 * @param i
	 * @return La instruccion correspondiente a la posicion i.
	 * @throws ArrayException
	 */
	public Instruction getInstruction(int i) throws ArrayException{
		if(i >= numInst) throw new ArrayException();
		else return sProgram[i];
	}
}
