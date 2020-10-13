package tp.pr1.mv;

/** Esta clase contiene los objetos que guardan la informacion de los comandos que introduce
 * el usuario por pantalla para poder modificar el programa.
 * @author Oscar Diaz Ribagorda y Mateo Garcia Perez.
 */
public class Command {
	/**
	 * Enumerado con el nombre del comando.
	 */
	private ENUM_COMMAND command;
	/**
	 * Objeto de la clase ByteCode con el codigo de la instruccion asociada al comando.
	 */
	private ByteCode instruction;
	/**
	 * Numero de instruccion por el cual se reemplaza en caso de que haya que reemplazar.
	 */
	private int replace;
	
	/** Esta funcion se encarga de distinguir el comando actual y ejecutarlo. Ademas devuelve fallo
	 * en caso de que la ejecucion del comando de fallo.
	 * 
	 * @param engine Objeto de la clase Engine
	 * @return Booleano informando si se ha ejecudado correctamente el comando.
	 */
	public boolean execute (Engine engine){
		System.out.print("Comienza la ejecucion de ");
		System.out.print(command.toString());
		if(instruction != null)
			System.out.print(" " + instruction.toString());
		System.out.println();
		boolean fallo = false;
		switch(this.command){
		
		case QUIT:
			engine.acabar();
			break;
		case HELP:
			engine.mostrarAyuda();
			break;
		case NEWINST:
			fallo = !engine.introducirInst(this.instruction);
			break;
		case RUN:
			fallo = engine.run();
			break;
		case RESET:
			engine.reset();
			break;
		case REPLACE:
			fallo = !engine.replace(this.replace);
			break;
		}
			
		return !fallo;
	}
	
	/** Establece el nombre del comando.
	 * 
	 * @param Comando el enumerado que va a dar nombre al comando.
	 */
	public void  setCommand(ENUM_COMMAND comando) {
		this.command = comando;
	}
	
	/** Establece el valor del parametro replace.
	 * 
	 * @param n El numero de instruccion que se quiere reemplazar.
	 */
	public void setReplace(int n) {
		this.replace = n;
	}
	
	/** Establece la instruccion (ByteCode) asociada al comando.
	 * 
	 * @param bcode El bytecode correspondiente al comando que se esta tratando.
	 */
	public void setByteCode( ByteCode bcode){
		this.instruction = bcode;
	}

}
