package es.ucm.fdi.tp.mvc;

import static org.junit.Assert.*;

import org.junit.Test;

import es.ucm.fdi.tp.base.model.GameAction;
import es.ucm.fdi.tp.base.model.GameError;
import es.ucm.fdi.tp.base.model.GameState;

/**
 *Comprueba el correcto funcionamiento de GameTable
 * @author Oscar Diaz Ribagorda y Mateo Garcia Perez.
 *
 */

public class GameTableTest<S extends GameState<S, A>, A extends GameAction<S, A>> {

	
	/**
	 * Comprueba que no se puede parar un juego parado
	 */
	@Test
	public void pararParado() {
		GameTable<S,A> game= new GameTable<S,A>(null);
		try{
			game.stop();
			fail("deberia dar error");
		}
		catch(GameError e){
		}
	}
	
	/**
	 * Comprueba que no se puede ejecutar un juego si el estado es null
	 */
	@Test
	public void ejecutarNoIniciado(){
		GameTable<S,A> game= new GameTable<S,A>(null);
		try{
			game.execute(null);
			fail("deberia dar error");
		}
		catch(GameError e){
		}
	}
}
