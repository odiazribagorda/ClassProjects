package tp.pr3.program;

import tp.pr3.bytecode.ByteCode;
import tp.pr3.bytecode.ByteCodeProgram;
import tp.pr3.exceptions.ArrayException;
import tp.pr3.exceptions.NotFoundException;
import tp.pr3.program.instruction.Instruction;

/**
 * Clase que realiza y controla la correcta compilacion de un programa escrito por instrucciones
 * para generar un programa de bytecodes que se pueda ejecutar.
 * @author Oscar Diaz Ribagorda y Mateo Garcia Perez.
 *
 */
public class Compiler {
	/**
	 * Atributo que guarda el programa de bytecodes ya compilado.
	 */
	private ByteCodeProgram bytecode;
	/**
	 * Atributo que almacena todas las variables utilizadas en el programa.
	 */
	private String[] varTable;
	/**
	 * Atributo con el numero de variables utilizadas.
	 */
	private int numVars;
	/**
	 * Constante con el valor maximo de variables permitidas.
	 */
	private final int NUM_VAR= 200;
	
	/**
	 * Constructor de la clase Compiler.
	 * @param bcp
	 */
	public Compiler(ByteCodeProgram bcp){
		bytecode= bcp;
		varTable= new String[NUM_VAR];
		numVars=0;
		
	}
	
	/**
	 * Metodo principal de la clase Compiler que compila a un programa de bytecodes un programa
	 * fuente parseado a instruciones.
	 * @param pProgram
	 * @throws ArrayException
	 * @throws NotFoundException
	 */
	public void compile(ParsedProgram pProgram) throws ArrayException, NotFoundException {
		int i = 0;
		while (i < pProgram.getNumeroInst()) {
			Instruction instr = pProgram.getInstruction(i);
			instr.compile(this);
			i++;
		}
	}
	
	/**
	 * Metodo que introduce en el programa de bytecodes un nuevo bytecode.
	 * @param b
	 * @throws ArrayException
	 */
	public void addByteCode(ByteCode b) throws ArrayException{
		bytecode.insertarByteCode(b);
	}
	
	/**
	 * Metodo que devuelve la posicion en la tabla de variables de la variable solicitada,
	 * si no existe se crea una nueva variable con ese numero.
	 * @param var
	 * @return La posicion de la variable solicitada.
	 */
	public int getVarAlt(String var){
		int i = 0;
		while(i < numVars && !var.equals(varTable[i]))
			++i;
		if(i == numVars) {
			varTable[numVars] = var;
			++numVars;
			return numVars - 1;
		}
		else return i;
	}
	
	/**
	 * Metodo que devuelve la posicion de la variable solicitada, si no la encuentra da error.
	 * @param var
	 * @return La posicion de la variable solicitada.
	 * @throws NotFoundException
	 */
	public int getVarOnly(String var) throws NotFoundException{
		int i = 0;
		while(i < numVars && !var.equals(varTable[i]))
			++i;
		if(i == numVars)
			throw new NotFoundException();
		else return i;
	}

	/**
	 * Metodo que devuelve el numero actual de bytecodes almacenados en el programa.
	 * @return Un entero con el numero de bytecodes almacenados en el programa.
	 */
	public int getCurrentNumberOfByteCodes() {
		return bytecode.getNumInst();
	}
}

