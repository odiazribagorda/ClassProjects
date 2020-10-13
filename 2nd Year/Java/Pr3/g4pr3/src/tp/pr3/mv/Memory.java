package tp.pr3.mv;

/** Esta clase continene un vector de Integers que es la memoria sobre la que se almacenan datos
 * y todas las funciones necesarias para tratar con esta memoria.
 * 
 * @author Oscar Diaz Ribagorda y Mateo Garcia Perez.
 */

public class Memory {
	
	/**
	 * Vector que representa la memoria.
	 */
	private Integer[] memory;
	/**
	 * Indicador de si la memoria esta vacia.
	 */
	private boolean vacia;
	/**
	 * Constante con el tamaño inicial de la pila (tamaño final no acotado).
	 */
	private final int TAM_INI= 100;
	
	/** Construye un objeto de la clase Memory.
	 */
	public Memory() {
		memory = new Integer[TAM_INI];
		vacia = true;
	}
	
	/** Escribe un dato pasado como argumento en la posicion dada. En caso de que no quepa en el vector
	 * actual, este se redimensiona y despues se guarda en la posicion.
	 * 
	 * @param pos Posicion de memoria donde se va a escribir.
	 * @param value Valor que se va a guardar en la memoria.
	 */
	public void write(int pos, int value) {
		if(pos >= memory.length) redimensionar(pos);
		memory[pos] = value;
		vacia = false;
	}
	
	/** Devuelve el numero almacenado en la posicion dada.
	 * 
	 * @param pos Posicion de memoria de donde se quiere leer.
	 * @return	El valor guardado en la posicion dada o -1 si no hay nada en esa posicion de memoria.
	 */
	public int read(int pos) {
		if (pos > memory.length)redimensionar(pos); 
		if(memory[pos] == null){
			memory[pos] = 0;
			vacia = false;
			return 0;
		}
		else 
			return memory[pos];
	}
	
	/** Muestra por pantalla el estado de la memoria. Solo muestra las posiciones que han sido utilizadas.
	 */
	public String toString() {
		String s = new String();
		s = "Memoria:  ";
		if(vacia){
			s += "<vacia>";
		}
		else{
			for(int i =0; i < memory.length; ++i){
				if(memory[i] != null){
					s += "[" + i + "] :" + memory[i] + "   ";
				}
			}
		}
		s += "\n";
		
		return s;
	}
	
	/** Redimensiona el vector de memoria con tama�o el doble del numero que se le pase.
	 * Para hacerlo, se crea un nuevo vector de memoria con el nuevo tama�o y se copia el 
	 * antiguo en este nuevo.
	 * 
	 * @param pos Numero que servira como referencia para redimensionar (nueva dimension = 2 * pos).
	 */
	private void redimensionar(int pos){
		Integer[] aux = new Integer[pos *2];
		if(!vacia){
			for(int i =0; i < memory.length; ++i){
				aux[i] = memory[i];
			}
		}
		memory = aux;
	}
}
