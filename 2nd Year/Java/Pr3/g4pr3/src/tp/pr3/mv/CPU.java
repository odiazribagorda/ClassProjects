package tp.pr3.mv;

import tp.pr3.bytecode.ByteCode;
import tp.pr3.bytecode.ByteCodeProgram;
import tp.pr3.exceptions.ExecutionError;
import tp.pr3.exceptions.StackException;

/** Los objetos de esta clase tienen una memoria, una pila y un booleano para acabar.
 * La CPU sera la que instruccion a instruccion se vaya ejecutando realizando los cambios necesarios
 * en memoria y pila.
 * @author Oscar Diaz Ribagorda y Mateo Garcia Perez.
 */

public class CPU {
	/**
	 * Objeto de la clase Memory que representa la memoria de la CPU.
	 */
	private Memory mem;
	/**
	 * Objeto de la clase OperandStack que representa la pila de la CPU.
	 */
	private OperandStack stack;
	/**
	 * Indicador de si la CPU tiene que acabar su ejecucion.
	 */
	private boolean end;
	
	/**
	 * Un entero que indica en que instruccion del programa se esta.
	 */
	private int programCounter;
	
	/**
	 * Un objeto de la clase ByteCodeProgram que indica el programa a ejecutar.
	 */
	private ByteCodeProgram bcProgram;
	
	/** Construye un objeto de la clase CPU.
	 * 
	 */
	public CPU(ByteCodeProgram program) {
		mem = new Memory();
		stack = new OperandStack();
		bcProgram = program;
		programCounter = 0;
		end = false;
	}
	
	/** Se encarga de la ejecucion del programa.
	 * 
	 * @return Booleano que indica si el programa se ha podido ejecutar.
	 */
	public void run() throws ExecutionError{
		try {
			while(!end && programCounter >=0 && programCounter < bcProgram.getNumInst()){
				// Siempre que se entra en el bucle la posicion va a ser valida.
				ByteCode aux = bcProgram.devolverByteCode(programCounter);
				++programCounter;
				aux.execute(this);
			}
		}
		catch(ExecutionError e) {
			System.out.println("Excepcion en la ejecucion del ByteCode: " + programCounter);
			throw e;
		}
	}
	
	/**
	 * @return El booleano end
	 */
	public boolean getEnd() {
		return end;
	}
	
	/** Muestra por pantalla el estado de la CPU.
	 * 
	 */
	public String toString() {
		String s = new String();
		s = "Estado de la CPU:\n" + mem + stack;
		return s;
	}
	
	/**
	 * Mete al final de la pila en numero indicado.
	 * @param n El entero a almacenar
	 * @return Si se ha podido almacenar da cierto.
	 */
	public void push (int n) throws StackException {
		stack.push(n);
	}
	
	/**
	 * Carga en la pila el valor que hay en la posicion indicada de la memoria.
	 * @param n Posicion de memoria
	 * @return Si se ha podido ejecutar devuelve cierto.
	 */
	public void load (int n) throws StackException{
		stack.push(mem.read(n));
	}
	
	/**
	 * Guarda el ultimo valor de la pila en la posicion de memoria indicada.
	 * @param n Posicion donde se guardara el valor de la pila
	 * @return Si se ha podido almacenar da cierto.
	 */
	public void store (int n) throws StackException {
		if(!stack.getVacia()){
			int aux= stack.pop();
			mem.write(n, aux);
		}
		else throw new StackException();
	}
	
	/**
	 * Muestra por pantalla el ultimo valor de la pila.
	 * @return Si se ha podido ejecutar devuelve cierto.
	 */
	public void  out() throws StackException {
		if(!stack.getVacia()){
			System.out.println("El numero a mostrar es: " + stack.pop());
		}
		else throw new StackException();
	}
	
	/**
	 * Acaba el programa que se esta ejecutando
	 * @return Si se ha podido ejecutar devuelve cierto.
	 */
	public void halt(){
		end= true;
	}
	
	/**
	 * Va a la instruccion de programa indicada.
	 * @param n Instruccion a la que saltara el programa.
	 * @return Si se ha podido ejecutar devuelve cierto.
	 */
	public void irA(int n){
		programCounter= n; 
		/*
		Se iguala el contador del programa a n aunque a la hora de ejecutarse la instruccion en esa posición,
		el programa para si el contador es menor que 0 o mayor o igual al numero de byte codes del programa
		*/
		
	}
	/**
	 * Comprueba que la pila tiene dos o mas elementos.
	 * @return Si tiene dos o mas elemento devuelve cierto.
	 */
	public void comprobarPila() throws StackException{
		if(stack.getTam() < 2) throw new StackException();
	}
	/**
	 * Saca el ultimo valor de la pila.
	 * @return Si se ha podido ejecutar devuelve cierto.
	 */
	public int pop(){
		return stack.pop();
	}
}
