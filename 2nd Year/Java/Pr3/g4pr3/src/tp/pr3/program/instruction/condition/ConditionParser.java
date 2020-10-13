package tp.pr3.program.instruction.condition;

import tp.pr3.program.LexicalParser;
/**
 * Clase que se encarga de parsear las condiciones
 * @author Oscar Diaz Ribagorda y Mateo Garcia Perez.
 *
 */
public class ConditionParser {
	/**
	 * Array de Conditions con las posibles condiciones 
	 */
	private final static Condition[] conditions = {new Equal(), new Less(), 
												new LessEq(), new NotEqual()};
	/**
	 * Método que se encarga de recorrer los parses de cada contdition para ver con cual se corresponde
	* @param s1 String con el primer termino de la comparacion
	 * @param s2 simbolo de la comparacion
	 * @param s3 String con el segundo termino de la comparacion
	 * @param parser LexicalParse que parsea el programa, se necesita aqui para poder aumentar su contador al acabar
	 * @return Condition ya parseada o null si no se corresponde con ninguna
	 */
	public static Condition parse(String s1, String s2, String s3, LexicalParser parser) {
		Condition cond= null;
		
		int i = 0;
		while (cond == null && i < conditions.length) {
			cond = conditions[i].parse(s1, s2, s3, parser);
			++i;
		}
		return cond;
	}
}
