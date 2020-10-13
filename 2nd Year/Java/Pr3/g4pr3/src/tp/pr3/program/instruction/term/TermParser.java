package tp.pr3.program.instruction.term;
/**
 * Clase que se encarga de parsear los objetos que implementan la interface 
 * llamando a los parse de cada uno de ellos
 * @author Oscar Diaz Ribagorda y Mateo Garcia Perez.
 *
 */
public class TermParser {
	/**
	 * Array de Terms con los posibles Terms para poder parsearlos al recorrerlo
	 */
	private final static Term[] terms = {new Variable(""), new Number(0)};
	/**
	 * Método que se encarga de llamar a los parses los Terms y comprobar asi si pertenecen a estos
	 * @param s String con la informacion a parsear
	 * @return Un term con la informacion dada o null si no se corresponde con ninguno
	 */
	public static Term parse(String s) {
		Term t = terms[0].parse(s);
		if (t == null)
			t = terms[1].parse(s);
		
		return t;
	}
}
