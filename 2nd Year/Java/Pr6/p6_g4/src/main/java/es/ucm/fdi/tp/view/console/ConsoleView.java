package es.ucm.fdi.tp.view.console;


import es.ucm.fdi.tp.base.model.GameAction;
import es.ucm.fdi.tp.base.model.GameState;
import es.ucm.fdi.tp.mvc.GameEvent;
import es.ucm.fdi.tp.mvc.GameObservable;
import es.ucm.fdi.tp.mvc.GameObserver;

/**
 * Vista del modo consola.
 * @author Oscar Diaz Ribagorda y Mateo Garcia Perez.
 */
public class ConsoleView<S extends GameState<S,A>, A extends GameAction<S,A>> implements GameObserver<S,A> {
	
	
	
	/**
	 * Añade la vista a la lista de observadores.
	 * @param gameTable al cual se añade la vista como observador
	 */
	public ConsoleView(GameObservable<S,A> gameTable){
		gameTable.addObserver(this);
	}

	/**
	 * Recibe un evento y los va administrando.
	 * El evento info no se tiene en cuenta ya que lo primero que hace este metodo es
	 * mostrar la informacion del evento
	 * @param e evento a administrar
	 */
	public void notifyEvent(GameEvent<S, A> e) {
		System.out.println(e);
		switch(e.getType()){
		case Start:
			this.start(e);
			break;
		case Stop:
			this.stop(e);
			break;
		case Change:
			this.change(e);
			break;
		case Error:
			this.error(e);
			break;
		default:
			break;
		}
	}
	
	/**
	 * Muestra por pantalla el estado inicial.
	 * @param e evento que guarda el estado a mostrar
	 */
	private void start(GameEvent<S, A> e){
		System.out.println(e.getState());
	}
	
	/**
	 * Avisa al jugador de que el juego ha acabado.
	 * Aqui solo se entra si el juego ha acabado, ya que es la unica manera de que parar el juego
	 * Si es el jugador el que escoge parar entonces ConsolePlayer ya se encarga de cerrar el programa
	 * @param e evento a mostrar
	 */
	private void stop(GameEvent<S, A> e){
		String endText = "The game ended: ";
		int winner = e.getState().getWinner();
		if (winner == -1) {
			endText += "draw!";
		} else {
			endText += "player " + (winner + 1) + " won!";
		}
		System.out.println(endText);
	}
	
	/**
	 * Muestra el estado tras el cambio
	 * @param e evento a mostrar
	 */
	private void change(GameEvent<S, A> e){
		System.out.println("After action:\n" + e.getState());
	}
	
	/**
	 * Muestra el mensaje de error
	 * @param e evento a mostrar
	 */
	private void error(GameEvent<S, A> e){
		System.out.println(e.getError());
	}
	
}
