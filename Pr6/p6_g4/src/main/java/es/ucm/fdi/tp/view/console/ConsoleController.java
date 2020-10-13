package es.ucm.fdi.tp.view.console;

import java.util.List;

import es.ucm.fdi.tp.base.model.GameAction;
import es.ucm.fdi.tp.base.model.GamePlayer;
import es.ucm.fdi.tp.base.model.GameState;
import es.ucm.fdi.tp.mvc.GameTable;
/**
 * Controlador del juego en consola.
 * @author Oscar Diaz Ribagorda y Mateo Garcia Perez.
 */
public class ConsoleController<S extends GameState<S,A>, A extends GameAction<S,A>> implements Runnable {

	/**
	 * Modelo del mvc
	 */
	private GameTable<S,A> modelo;
	/**
	 * Lista de jugadores 
	 */
	List<GamePlayer> jugadores;
	
	/**
	 * Inicializa el controlador
	 * @param players del juego
	 * @param game modelo
	 */
	public ConsoleController(List<GamePlayer> players, GameTable<S,A> game){
		this.modelo= game;
		this.jugadores= players;
	}
	
	
	/**
	 * Ejecuta el juego
	 * Primero añade los jugadores al juego, luego inicializa el juego y despues va 
	 * ejecutando acciones hasta que se acaba entonces para el juego
	 */
	public void run(){
		int playerCount = 0;
		for (GamePlayer p : jugadores) {
			p.join(playerCount++); // welcome each player, and assign
									// playerNumber
		}
		
		//Se empieza el juego
		modelo.start();
		
		S currentState = modelo.getState();

		while (!currentState.isFinished()) {
			// request move
			A action = jugadores.get(currentState.getTurn()).requestAction(currentState);
			// apply move
			modelo.execute(action);
			currentState = modelo.getState();
			if (currentState.isFinished())
				modelo.stop();
		}
	}
}
