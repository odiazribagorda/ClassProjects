package tp.pr3.mv;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.Scanner;

import tp.pr3.bytecode.ByteCode;
import tp.pr3.bytecode.ByteCodeParser;
import tp.pr3.bytecode.ByteCodeProgram;
import tp.pr3.command.Command;
import tp.pr3.command.CommandParser;
import tp.pr3.exceptions.ArrayException;
import tp.pr3.exceptions.BadFormatByteCode;
import tp.pr3.exceptions.ExecutionError;
import tp.pr3.exceptions.LexicalAnalysisException;
import tp.pr3.exceptions.NotFoundException;
import tp.pr3.program.LexicalParser;
import tp.pr3.program.ParsedProgram;
import tp.pr3.program.SourceProgram;

import tp.pr3.program.Compiler;

/** Esta clase contiene un vector de ByteCodes que representa el programa que vamos almacenando.
 * Ademas implementa las funciones referidas a la ejecucion de cada comando por separado que van
 * cambiando el estado del vector programa.
 * @author Oscar Diaz Ribagorda y Mateo Garcia Perez.
 */
public class Engine {
	/**
	 * Objeto de la clase ByteCodeProgram que representa el programa almacenado.
	 */
	private ByteCodeProgram bytecodeProgram;
	/**
	 * Objeto de la clase ParsedProgram que guarda el programa parseado, es decir un array de instrucciones
	 */
	private ParsedProgram parsedProgram;
	/**
	 * Objeto de la clase SourceProgram que tiene un array de strings con los datos del archivo cargado
	 */
	private SourceProgram sProgram;
	/**
	 * Indicador que informa si el usuario quiere salir.
	 */
	private boolean end;
	/**
	 * Objeto de la clase Scanner para poder leer las lineas de entrada del usuario
	 */
	private static Scanner entrada = new Scanner(System.in);
	
	/** Construye un objeto de la clase Engine.
	 */
	public Engine(){
		bytecodeProgram = new ByteCodeProgram();
		parsedProgram= new ParsedProgram();
		sProgram = new SourceProgram();
		end = false;
	}
	
	/** Funcion que lleva el funcionamiento del programa, va leyendo por pantalla, convirtiendo en comandos
	 * y ejecutando estos comandos hasta que el comando sea el de salir en cuyo caso acaba el programa.
	 * Al final de cada ejecucion muestra el programa actualizado.
	 */
	public void start(){
		Command comando = null;
		while (!end){ 
			System.out.print("> ");
			String instruc = entrada.nextLine();
			comando = CommandParser.parse(instruc);
			if(comando == null)
				System.out.println("Error: Comando incorrecto");
			else {
				System.out.print("Comienza la ejecucion de ");
				System.out.println(comando);
				
				try {
					comando.execute(this);
				} catch (ExecutionError e) {
					System.out.println(e);
				} catch (ArrayException e) {
					System.out.println(e);
				} catch (BadFormatByteCode e) {
					System.out.println(e);
				} catch (LexicalAnalysisException e) {
					System.out.println(e);
				} catch (IOException e) {
					System.out.println(e);
				} catch (NotFoundException e) {
					System.out.println(e);
				}
			}
			System.out.println(sProgram);
			System.out.println(bytecodeProgram);
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
		CommandParser.showHelp();
	}
	
	/** Esta funcion crea un objeto de CPU que va a ir cambiando segun las ejecuciones de los ByteCodes
	 * almacenados en el vector de programa. Se ejecutara hasta que haya un fallo o se acaben las instrucciones.
	 * @throws ExecutionError se si se produce un error durante la ejecucion
	 */
	public void run() throws ExecutionError{
		//Hacer run en un programa sin compilar mostrara la cpu sin cambio alguno
		CPU cpu = new CPU(bytecodeProgram);
		cpu.run();
		System.out.println(cpu);
		
		
	}
	
	/** Reemplaza una instruccion almacenada en el programa por otra que introducen por consola.
	 * 
	 * @param n Posicion de la instruccion que se va a reemplazar.
	 * @throws ArrayException error si no se ha podido acceder al array para campiar la instruccion en n (esta fuera de rango)
	 * @throws BadFormatByteCode error si la string introducida no se corresponde con ningun bytecode
	 */
	public void replace(int n) throws ArrayException, BadFormatByteCode{
		if(n >= bytecodeProgram.getNumInst()) throw new ArrayException();
		
		else{
			System.out.print("Nueva instruccion: ");
			String instruc = entrada.nextLine();
			ByteCode instruction = null;
			instruction = ByteCodeParser.parse(instruc);
			if(instruction == null) new BadFormatByteCode();
			bytecodeProgram.colocarByteCode(instruction, n );
			
		}

	}
	/**
	 * Se ejecuta la instruccion compile la cual consta de dos partes el analisis léxico 
	 * y la generacion del bytecode
	 * @throws LexicalAnalysisException si se ha producido algun error durante el analisis lexico
	 * @throws ArrayException si se ha producido algun error en el acceso a arrays
	 * @throws NotFoundException si no se ha encontrado un elemento necesario en un array determinado
	 */
	public void compile() throws LexicalAnalysisException, ArrayException, NotFoundException {
		this.lexicalAnalysis();
		this.generateBytecode();
	}
	/**
	 * Metodo que dado un fichero con un programa lo abre y lo carga en el programa fuente
	 * @param fich String con el nombre del fichero donde esta el programa
	 * @throws FileNotFoundException error si no se ha encontrado el fichero con el nombre dado
	 */
	public void leerFich(String fich) throws FileNotFoundException , ArrayException {
		Scanner entradaFich = new Scanner(new BufferedReader(new FileReader(fich)));
		
		bytecodeProgram = new ByteCodeProgram();
		parsedProgram= new ParsedProgram();
		sProgram = new SourceProgram();
		
		String s = new String();
		while(entradaFich.hasNextLine()) {
			s = entradaFich.nextLine();
			sProgram.introducir(s.trim());
		}
		entradaFich.close();
		
	}
	/**
	 * Metodo que ejecuta el analisis lexico generando el ParsedProgram asociado al
	 * SourceProgram que se tiene guardado en el Engine
	 * @throws LexicalAnalysisException error si se ha producido algun fallo durante el parseo de instrucciones
	 */
	private void lexicalAnalysis() throws LexicalAnalysisException{
		LexicalParser lexparse = new LexicalParser(sProgram);
		parsedProgram = new ParsedProgram();
		lexparse.lexicalParser(parsedProgram, "END");
	}
	/**
	 * Método que genera el ByteCode asociado al ParseProgram guardado en el engine
	 * @throws ArrayException error al acceder a un elemento de un array
	 * @throws NotFoundException error si no se ha encontrado un elemento determinado en un array donde deberia estar
	 */
	private void generateBytecode() throws ArrayException, NotFoundException {
		bytecodeProgram = new ByteCodeProgram();
		Compiler compile= new Compiler(bytecodeProgram);
		compile.compile(parsedProgram);
	}
}
