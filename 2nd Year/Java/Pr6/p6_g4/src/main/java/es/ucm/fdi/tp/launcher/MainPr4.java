package es.ucm.fdi.tp.launcher;

import es.ucm.fdi.tp.base.console.ConsolePlayer;
import es.ucm.fdi.tp.base.model.GameAction;
import es.ucm.fdi.tp.base.model.GamePlayer;
import es.ucm.fdi.tp.base.model.GameState;
import es.ucm.fdi.tp.base.player.RandomPlayer;
import es.ucm.fdi.tp.base.player.SmartPlayer;
import es.ucm.fdi.tp.ttt.TttState;
import es.ucm.fdi.tp.was.WolfAndSheepState;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.List;
import java.util.Scanner;

/**
 * Main del juego desde donde se escoge el juego a ejecutar y los jugadores
 * @author Oscar Diaz Ribagorda y Mateo Garcia Perez.
 */
public class MainPr4{
	/**
	 * Array con nombres de ejemplos para los jugador
	 */
	private static String[] gente ={ "Eustaquio" , "Furtancio", "Meliodas", "Caliope", "Zurbano", "Dio", "Briseida" , "Eratostenes" };

	/**
	 * Coge n nombres aleatorios del array.
	 * @param n numero de nombres a coger
	 * @return una lista con los nobres escogidos
	 */
	private static List <String> nombresNoReps(int n){
		ArrayList<String> elegidos =  new ArrayList<>(Arrays.asList(gente));
		Collections.shuffle(elegidos);
		while(elegidos.size() > n) elegidos .remove(elegidos.size()-1);
		return elegidos;
	}
	
	/**
	 * Metodo que dirige el juego.
	 * Va alternado los turnos, mostrando los tableros y las acciones disponibles, etc.
	 * @param initialState incial del juego que se va a jugar
	 * @param players que van a participar en juego
	 * @return quien ha ganado
	 */
	public static <S extends GameState<S, A>, A extends GameAction<S, A>> int playGame(GameState<S, A> initialState,
			List<GamePlayer> players) {
		int playerCount = 0;
		for (GamePlayer p : players) {
			p.join(playerCount++); // welcome each player, and assign
									// playerNumber
		}
		@SuppressWarnings("unchecked")
		S currentState = (S) initialState;

		while (!currentState.isFinished()) {
			// request move
			A action = players.get(currentState.getTurn()).requestAction(currentState);
			// apply move
			currentState = action.applyTo(currentState);
			System.out.println("After action:\n" + currentState);

			if (currentState.isFinished()) {
				// game over
				String endText = "The game ended: ";
				int winner = currentState.getWinner();
				if (winner == -1) {
					endText += "draw!";
				} else {
					endText += "player " + (winner + 1) + " (" + players.get(winner).getName() + ") won!";
				}
				System.out.println(endText);
			}
		}
		return currentState.getWinner();
	}


	/**
	 * Main method.
	 * 
	 * @param args con la forma Juego, Jugador1, Jugador2 (si no se cumple da error)
	 */
	public static void main(String... args){
		if(args.length == 3){
			try{
				//Se crea el estado inicial del juego
				GameState<?, ?> game = createInitialState(args[0]);
				//Se crea una lista de jugadores y se le escoge el nombre
				List<GamePlayer> players = new ArrayList<GamePlayer>();
				List<String> elegidos = nombresNoReps(2);
				players.add(createPlayer(args[0],args[1], elegidos.get(0)));
				players.add(createPlayer(args[0],args[2], elegidos.get(1)));
				//Se desarrolla el juego
				playGame(game, players);
			}
			catch(IllegalArgumentException e){
				System.out.println(e);
			}
		}
		else System.out.println("Error: Too many arguments");
	}
	/**
	 * Se crea el estado inicial del juego.
	 * Tres en raya si se introduce TTT y Wolf and Sheep si se introduce WAS
	 * @param gameName del que se crea el estado
	 * @return el estado incial del juego
	 * @throws IllegalArgumentException si la primera palabra del args no se corresponde con ningun juego
	 */
	public static GameState<?,?> createInitialState(String gameName) {
		gameName.toLowerCase();
		if (gameName.equals("ttt")) return new TttState(3);
		else if (gameName.equals("was")) return new WolfAndSheepState();
		else throw new IllegalArgumentException("Error: This is game is unknown.");
	}
	/**
	 * Crea un jugador
	 * @param gameName nombre del juego
	 * @param playerType tipode de jugador(consola, aleatorio o listo)
	 * @param playerName del jugador
	 * @return jugador creado
	 * @throws IllegalArgumentException si no se corresponde con ningun tipo de jugador
	 */
	public static GamePlayer createPlayer (String gameName, String playerType, String playerName) {
		playerType.toLowerCase();
		if (playerType.equals("rand")) return new RandomPlayer(playerName);
		else if (playerType.equals("smart")) return new SmartPlayer(playerName,15);
		else if(playerType.equals("console")){
			Scanner in = new Scanner(System.in);
			return new ConsolePlayer(playerName, in);
		}
		else throw new IllegalArgumentException("Error: Player " + playerType + " undefined.");
	}
}
