package tp.pr3.bytecode.instructions;

import tp.pr3.bytecode.ByteCode;
import tp.pr3.mv.CPU;

/**
 * Esta clase implementa las funciones del objeto Halt de ByteCode.
 * @author Oscar Diaz Ribagorda y Mateo Garcia Perez.
 *
 */
public class Halt implements ByteCode{
	
	/**
	 * {@inheritDoc}
	 *
	 * Acaba el programa que se esta ejecutando.
	 */
	public void execute(CPU cpu){
		cpu.halt();
	}
	
	/**
	 * {@inheritDoc}
	 */
	public ByteCode parse(String[] s){
		if (s.length==1 && s[0].equalsIgnoreCase("HALT")){
			return new Halt();
			}
		else return null;
	}
	
	public String toString(){
		return "HALT";
	}
}
