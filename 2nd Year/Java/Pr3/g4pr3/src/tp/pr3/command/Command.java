package tp.pr3.command;


import java.io.IOException;

import tp.pr3.exceptions.ArrayException;
import tp.pr3.exceptions.BadFormatByteCode;
import tp.pr3.exceptions.ExecutionError;
import tp.pr3.exceptions.LexicalAnalysisException;
import tp.pr3.exceptions.NotFoundException;
import tp.pr3.mv.Engine;

/** Interfaz que engloba a todos los comandos y la cual implementan los diferentes comandos
 * @author Oscar Diaz Ribagorda y Mateo Garcia Perez.
 */
public interface Command {
	
	 abstract public void execute (Engine engine) 
			 throws ExecutionError, ArrayException, BadFormatByteCode, 
			 LexicalAnalysisException, IOException, NotFoundException;
	 
	 abstract public Command parse(String [] s);
	 
	 abstract public String textHelp();

}
