package tp.pr1.mv;

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
	 * @return Falso si no se puede introducir o verdadero si se puede.
	 */
	public boolean insertarByteCode(ByteCode bcode) {
		if (numInst >= program.length)
			return false;
		else {
			program[numInst] = bcode;
			++numInst;
			return true;
		}
	}
	
	/** Inserta un nuevo ByteCode en una posicion dada (que ya esta llena).
	 * 
	 * @param bcode El bytecode que se va a insertar
	 * @param n La posicion donde se va a insertar
	 * @return Falso si no se puede insertar, verdadero en caso contrario.
	 */
	public boolean colocarByteCode(ByteCode bcode, int n) {
		if (n >= numInst)
			return false;
		else {
			program[n] = bcode;
			return true;
		}
	}
	
	/** Dada una posicion devuelve el bytecode que hay en esa posicion.
	 * 
	 * @param n Posicion de la que se quiere saber el bytecode
	 * @return El bytecode en la posicion dada (null si no hay nada en la posicion dada)
	 */
	public ByteCode devolverByteCode(int n) {
		ByteCode bc = new ByteCode();
		if (n >= numInst)
			bc = null;
		else
			bc = program[n];
		return bc;
	}
	
	/** Muestra por pantalla el programa (vector de ByteCode).
	 * 
	 */
	public void mostrarPrograma() {
		
		if(numInst > 0) {
			System.out.println("Programa almacenado:");
			for(int i = 0; i < numInst; ++i)
				System.out.println(i + ": " + program[i].toString());
		}
	}
	
	/**
	 * @return El numero de instrucciones del programa actual
	 */
	public int getNumInst() {
		return numInst;
	}

}
