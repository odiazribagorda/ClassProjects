package tp.pr1.mv;

/** Esta clase se encarga de convertir de string que te pasan por consola a un
 * objeto de la clase Command con su correspondiente nombre y ByteCode y, en caso
 * de que sea replace, su parametro para replace.
 * @author Oscar Diaz Ribagorda y Mateo Garcia Perez.
 */

public class CommandParser {
	
	/** Se divide la cadena por el espacio para distinguir entre el nombre del comando
	 * el ByteCode que viene asociado a el y en caso necesario el parametro replace.
	 * Se guarda en un objeto de comando.
	 * 
	 * @param line Un String que contenga la informacion del comando.
	 * @return El comando con su informacion o null en caso de error.
	 */
	public static Command parse(String line){
		Command comando = new Command();
		String[] subcadenas = line.split(" ");
		subcadenas[0] = subcadenas[0].toLowerCase();
		
		if(subcadenas[0].equals("help"))
			comando.setCommand(ENUM_COMMAND.HELP);
		
		else if(subcadenas[0].equals("quit"))
			comando.setCommand(ENUM_COMMAND.QUIT);
		
		else if(subcadenas[0].equals("newinst")) {
			comando.setCommand(ENUM_COMMAND.NEWINST);
			
			// Si la longitud de subacenas es 1 es que solo se recibe una palabra y porlo tanto faltan argumentos
			if (subcadenas.length ==1) comando = null;
			else {
				// Si es 3 es porque tiene un ByteCode con parametro asi que se juntan.
				if(subcadenas.length > 2) {
					subcadenas[1] = subcadenas[1] + " " + subcadenas[2];
				}
				ByteCode bcode= new ByteCode();
				bcode = ByteCodeParser.parse(subcadenas[1]);
				comando.setByteCode(bcode);
			}
		}
		
		else if(subcadenas[0].equals("run"))
			comando.setCommand(ENUM_COMMAND.RUN);
		
		else if(subcadenas[0].equals("reset"))
			comando.setCommand(ENUM_COMMAND.RESET);
		
		else if(subcadenas[0].equals("replace")) {
			comando.setCommand(ENUM_COMMAND.REPLACE);
			if(subcadenas.length == 1) comando = null;
			else {
				int n = Integer.parseInt(subcadenas[1]);
				comando.setReplace(n);
			}
		}
		
		else return null;
		
		return comando;
	}

}
