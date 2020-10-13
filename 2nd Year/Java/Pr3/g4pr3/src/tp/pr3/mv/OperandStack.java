package tp.pr3.mv;

import tp.pr3.exceptions.StackException;

/** Esta clase contiene un vector de enteros que representa la pila y contiene todas
 * las funciones necesarias para tratar con la pila.
 * 
 * @author Oscar Diaz Ribagorda y Mateo Garcia Perez.
 */
public class OperandStack {
	/**
	 * Vector de que representa la pila.
	 */
	private int[] stack;
	/**
	 * TamaÃ±o de la pila.
	 */
	private int tam;
	/**
	 * Indicador de si la pila esta vacia.
	 */
	private boolean vacia;
	/**
	 * Constante con el tamaÃ±o maximo de la pila
	 */
	private final int MAX_STACK = 100;
	
	
	/** Construye un objeto de la clase OperandStack.
	 */
	public OperandStack() {
		stack = new int[MAX_STACK];
		tam = 0;
		vacia = true;
	}
	
	/** Introduce un nuevo elemento a la pila por el final. En caso de que no se pueda devuelve falso.
	 * 
	 * @param num Numero que se introducira al final de la pila.
	 * @return booleano indicando si se ha podido introducir correctamente el numero.
	 */
	public void push(int num) throws StackException {
		if(tam >= MAX_STACK) throw new StackException();
		else{
			stack[tam] = num;
			++tam;
			vacia = false;
		}
	}
	
	/** Devuelve el ultimo elemento de la pila y lo elimina de esta.
	 * 
	 * @return El valor del numero en la ultima posicion de la pila.
	 */
	public int pop() {
		int num = stack[tam - 1];
		--tam;
		if(tam == 0) vacia = true;
		return num;
	}
	
	/** Muestra por pantalla el estado de la pila.
	 */
	public String toString() {
		String s = new String();
		s = "Pila:";
		
		if(!vacia) {
			for(int i = 0; i < tam; ++i) {
				s += " " + stack[i];
			}
		}
		else s += " <vacia>";
		s += "\n";
		
		return s;
	}
	
	/** Devuelve el valor de vacia.
	 * 
	 * @return El valor de vacia.
	 */
	public boolean getVacia(){
		return vacia;
	}
	
	/**
	 * Devuelve el tamaño de la pila.
	 * @return El tamaño de la pila.
	 */
	public int getTam() {
		return tam;
	}
	
}
