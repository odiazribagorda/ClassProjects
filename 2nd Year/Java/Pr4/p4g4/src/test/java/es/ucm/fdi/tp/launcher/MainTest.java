package es.ucm.fdi.tp.launcher;

import static org.junit.Assert.*;

import org.junit.Test;
/**
 *Comprueba el correcto funcionamiento del Main
 * @author Oscar Diaz Ribagorda y Mateo Garcia Perez.
 *
 */
public class MainTest {
	/**
	 * Comprueba que se lanza excepcion si el juego no existe
	 */
	@Test
	public void juegoInvalido(){
		String [] args= {"tute", "", ""};
		try{
			Main.createInitialState(args[0]);
			fail("deberia dar error");
		}
		catch(IllegalArgumentException e){
		}
	}

}
