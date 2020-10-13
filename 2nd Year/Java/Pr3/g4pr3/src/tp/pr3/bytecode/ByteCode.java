package tp.pr3.bytecode;


import tp.pr3.exceptions.ExecutionError;
import tp.pr3.mv.CPU;

/**
 * Se trata de una clase abstracta de la cual heredaran todos los objetos tipo ByteCode.
 * @author Oscar Diaz Ribagorda y Mateo Garcia Perez.
 */
 public interface ByteCode {
	/**
	 * Ejecuta el ByteCode
	 * @param cpu CPU donde se ejecuta el ByteCode
	 * @throws ExecutionError error si falla la ejecucion
	 */
	abstract public void execute(CPU cpu) throws ExecutionError;
	/**
	 * Parsea una string en un Bytecode
	 * @param s Array de Strings con la informacion a parsear
	 * @return El ByteCode con la información o null si no se corresponde con ninguno
	 */
	abstract public ByteCode parse(String[] s);
	
	abstract public String toString();

}
