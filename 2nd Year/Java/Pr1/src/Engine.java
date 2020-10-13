package tp.pr1.mv;

import java.util.Scanner;

/** Esta clase contiene un vector de ByteCodes que representa el programa que vamos almacenando.
 * Ademas implementa las funciones referidas a la ejecucion de cada comando por separado que van
 * cambiando el estado del vector programa.
 * @author Oscar Diaz Ribagorda y Mateo Garcia Perez.
 */
public class Engine {
	/**
	 * Objeto de la clase ByteCodeProgram que representa el programa almacenado.
	 */
	private ByteCodeProgram program;
	/**
	 * Indicador que informa si el usuario quiere salir.
	 */
	private boolean end;
	private static Scanner entrada = new Scanner(System.in);
	
	/** Construye un objeto de la clase Engine.
	 */
	public Engine(){
		program = new ByteCodeProgram();
		end = false;
	}
	
	/** Funcion que lleva el funcionamiento del programa, va leyendo por pantalla, convirtiendo en comandos
	 * y ejecutando estos comandos hasta que el comando sea el de salir en cuyo caso acaba el programa.
	 * Al final de cada ejecucion muestra el programa actualizado.
	 */
	public void start(){
		Command comando = new Command();
		while (!end){ 
			System.out.print("> ");
			String instruc = entrada.nextLine();
			comando = CommandParser.parse(instruc);
			if(comando == null)
				System.out.println("Error: Comando incorrecto");
			else if(!comando.execute(this)){
				System.out.println("Error: Ejecucion incorrecta del comando");
			}
			
			program.mostrarPrograma();
		}
		System.out.println("Fin de la ejecucion....");
	}
	
	/** Cambia el valor de end a verdadero para acabar el programa.
	 */
	public void acabar(){
		this.end = true;
	}
	
	/** Muestra por pantalla ayuda sobre los comandos que se pueden ejecutar.
	 */
	public void mostrarAyuda() {
		System.out.println("	HELP: Muestra esta ayuda");
		System.out.println("	QUIT: Cierra la aplicacion");
		System.out.println("	RUN: Ejecuta el programa");
		System.out.println("	NEWINST BYTECODE: Introduce una nueva instruccion al programa");
		System.out.println("	RESET: Vacia el programa actual");
		System.out.println("	REPLACE N: Reemplaza la instruccion N por la solicitada al usuario");
	}
	
	/** Inserta una nueva instruccion al final del programa, en caso de que no pueda devuelve falso.
	 * 
	 * @param instr El ByteCode que se va a introducir.
	 * @return	Booleano indicando si se ha podido introducir el ByteCode.
	 */
	public boolean introducirInst(ByteCode instr){
		if(instr == null || !program.insertarByteCode(instr)) return false;
		else return true;
		
	}
	
	/** Resetea el vector del programa (crea uno nuevo).
	 */
	public void reset(){
		program = new ByteCodeProgram();
	}
	
	/** Esta funcion crea un objeto de CPU que va a ir cambiando segun las ejecuciones de los ByteCodes
	 * almacenados en el vector de programa. Se ejecutara hasta que haya un fallo o se acaben las instrucciones.
	 * 
	 * @return Booleano indicando si la instruccion ha tenido fallo.
	 */
	public boolean run(){
		boolean fallo = false;
		
		CPU cpu = new CPU();
		
		int i = 0;
		while (!fallo && !cpu.getEnd() && i < program.getNumInst()) {
			if(cpu.execute(program.devolverByteCode(i))) {
				System.out.println("El estado de la maquina tras la ejecucion de la instruccion "
								+ program.devolverByteCode(i).toString() + " es:");
				cpu.mostrarEstado();
				System.out.println();
			}
			else fallo = true;
			++i;
		}
		
		return fallo;
	}
	
	/** Reemplaza una instruccion almacenada en el programa por otra que introducen por consola.
	 * 
	 * @param n Posicion de la instruccion que se va a reemplazar.
	 * @return Booleano indicando si se ha podido reemplazar la instruccion.
	 */
	public boolean replace(int n){
		if(n >= program.getNumInst())return false;
		System.out.print("Nueva instruccion: ");
		String instruc = entrada.nextLine();
		ByteCode instruction = new ByteCode();
		instruction = ByteCodeParser.parse(instruc);
		if(instruction == null || !program.colocarByteCode(instruction, n )) return false;
		else return true;
	}
}
