package tp.pr3.bytecode.arithmetics;

import tp.pr3.bytecode.ByteCode;
import tp.pr3.exceptions.DivisionByZero;
import tp.pr3.exceptions.StackException;
import tp.pr3.mv.CPU;

/**
 * Esta clase implementa las funciones del objeto DIV de Arithmetics.
 * @author Oscar Diaz Ribagorda y Mateo Garcia Perez.
 *
 */
public class Div extends Arithmetics {
	
	/**
	 * {@inheritDoc}
	 */
	public ByteCode parseAux(String s){
		if (s.equalsIgnoreCase("DIV")){
			return new Div();
		}
		else return null;
	}
	
	/**
	 * {@inheritDoc}
	 *
	 * Divide dos numeros, asegurandose que el divisor no es 0.
	 */
	public void execute(int n1, int n2, CPU cpu) throws DivisionByZero, StackException {
		if(n1 == 0) throw new DivisionByZero();
		else   {
			try {
				cpu.push(n2 / n1);
			} catch (StackException e) {
				throw e;
			}
		}
	}
	
	/**
	 * Devuelve el nombre de un objeto de la clase Div.
	 */
	public String toString() {
		return "DIV";
	}


}
