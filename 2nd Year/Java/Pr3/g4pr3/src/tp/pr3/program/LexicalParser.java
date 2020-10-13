package tp.pr3.program;

import tp.pr3.exceptions.ArrayException;
import tp.pr3.exceptions.LexicalAnalysisException;
import tp.pr3.program.instruction.Instruction;
import tp.pr3.program.instruction.ParserInstruction;

/**
 * Clase que se encarga de parsear un programa fuente escrito en strings a instrucciones, comprobando
 * que estas instrucciones son correctas.
 * @author Oscar Diaz Ribagorda y Mateo Garcia Perez.
 *
 */
public class LexicalParser {
	/**
	 * Atributo con el programa fuente que se ha de parsear.
	 */
	private SourceProgram sProgram;
	/**
	 * Atributo con el indicador de la posicion del programa por la que va.
	 */
	private int programCounter;
	
	/**
	 * Constructor de la clase LexicalParser.
	 * @param source
	 */
	public LexicalParser(SourceProgram source){
		sProgram=source;
		programCounter=0;
	}
	
	/**
	 * Metodo principal de la clase LexicalParser que se encarga de parsear el programa fuente
	 * a un programa parseado hasta una palabra que indicara el final.
	 * @param pProgram
	 * @param stopKey
	 * @throws LexicalAnalysisException
	 */
	public void lexicalParser(ParsedProgram pProgram, String stopKey)throws LexicalAnalysisException{
		try{
			boolean salir = false;
			while(this.programCounter< sProgram.getNumInst() && !salir){
				String instr = sProgram.getInst(this.programCounter);
				if(instr.equalsIgnoreCase(stopKey)){
					salir = true;
				}
				else{
					Instruction instruction= ParserInstruction.parse(instr, this);
					pProgram.introducir(instruction);
				}
			}
		}catch(ArrayException e) {
			throw new LexicalAnalysisException(e.toString());
		}
		
	}
	
	/**
	 * Metodo que se encargar de avanzar una posicion al indicador de posicion del programa.
	 */
	public void increaseProgramCounter() {
		++programCounter;
	}

}
