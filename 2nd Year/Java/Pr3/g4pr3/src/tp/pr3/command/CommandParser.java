package tp.pr3.command;


/** Esta clase se encarga de convertir de string que te pasan por consola a un
 * objeto de la clase Command.
 * @author Oscar Diaz Ribagorda y Mateo Garcia Perez.
 */

public class CommandParser {
	
	/**
	 * Un vector constante con los diferentes comandos posibles para poder recorrerlo
	 * y asi parsear el comando necesario.
	 */
	private final static Command[] commands = {
			new Help(), new Quit(), new Compile(),
			new Replace(0), new Run(), new LoadFich("")};
	
	/** Se divide la cadena por el espacio para distinguir entre los diferentes datos
	 * que se piden.
	 * 
	 * @param line Un String que contenga la informacion del comando.
	 * @return El objeto comando con su informacion o null en caso de error.
	 */
	public static Command parse(String line){
		Command comando = null;
		String[] subcadenas = line.split(" ");
		int i = 0;
		while (comando == null && i < commands.length) {
			comando = commands[i].parse(subcadenas);
			++i;
		}
		return comando;
	}
	
	/**
	 * Esta funcion se encarga de mostrar la ayuda de todos los comandos ya que es en 
	 * esta clase donde esta el vector constante con la informacion de todos ellos.
	 */
	public static void showHelp() {
		for(int i = 0; i < commands.length; ++i) {
			System.out.print(commands[i].textHelp());
		}
		System.out.println("");
	}

}
