package es.ucm.fdi.tp.launcher;

import es.ucm.fdi.tp.base.console.ConsolePlayer;
import es.ucm.fdi.tp.base.model.GameAction;
import es.ucm.fdi.tp.base.model.GamePlayer;
import es.ucm.fdi.tp.base.model.GameState;
import es.ucm.fdi.tp.base.player.RandomPlayer;
import es.ucm.fdi.tp.base.player.SmartPlayer;
import es.ucm.fdi.tp.mvc.GameTable;
import es.ucm.fdi.tp.peones.PeonesState;
import es.ucm.fdi.tp.ttt.TttState;
import es.ucm.fdi.tp.view.console.ConsoleController;
import es.ucm.fdi.tp.view.console.ConsoleView;
import es.ucm.fdi.tp.view.swing.WindowUI;
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
public class Main {
	
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
	 * Crea el modelo del juego a partir del nombre de este.
	 * @param gType nombre del juego
	 * @return GameTable con toda la información del juego
	 */
	@SuppressWarnings("unchecked")
	private static GameTable<?,?> createGame(String gType){
		gType.toLowerCase();
		if (gType.equals("ttt")){
			return new GameTable(new TttState(3));
		}
		else if (gType.equals("was")) {
			return new GameTable(new WolfAndSheepState());
		}
		else if(gType.equals("peones")) {
			return new GameTable(new PeonesState());
		}
		else return null;
	}
	
	/**
	 * Administra el juego de consola.
	 * @param gType tipo de juego
	 * @param game motor del juego
	 * @param playerModes modos de los jugadores (rand, smart o manual)
	 */
	private static <S extends GameState<S,A>, A extends GameAction<S,A>>
			void startConsoleMode(String gType, GameTable<S,A> game, String playerModes[]){
		//Se crea una lista de jugadores y se le escoge el nombre
		List<GamePlayer> players = new ArrayList<GamePlayer>();
		List<String> elegidos = nombresNoReps(playerModes.length);
		try{
			for(int i =0;i < playerModes.length ;++i){
				players.add(createPlayer(gType,playerModes[i], elegidos.get(i)));
			}
		}	
		catch(IllegalArgumentException e){
			System.err.println(e);
		}
		new ConsoleView<S,A>(game);
		new ConsoleController<S,A>(players,game).run();
	}
	
	/**
	 * Administra el juego en Swing
	 * @param gType tipo de juego
	 * @param game motor del juego
	 */
	private static <S extends GameState<S,A>, A extends GameAction<S,A>>
		void startGUIMode(String gType,GameTable<S,A> game){
		new WindowUI<S,A>(0, game);
		new WindowUI<S,A>(1, game);
		game.start();
	}
	
	/**
	 * Indica como debe ser la entrada de los argumentos, para la correcta
	 * seleccion de juego.
	 */
	private static void usage(){
		System.err.println("Arguments must be: game mode player1 player2");
		System.err.println("game can be was or ttt");
		System.err.println("mode can be gui (for graphical interface) or console");
		System.err.println("player can be manual, random or smart (in gui mode all players are manual)");
	}
	
	
	/**
	 * Metodo main
	 * 
	 * @param args con la forma Juego, Modo, Jugador1, Jugador2 (si no se cumple da error)
	 */
	public static void main(String[] args){
		if(args.length < 2){
			usage();
			System.exit(1);
		}
		
		GameTable<?,?> game = createGame(args[0]);
		
		
		if(game == null){
			System.err.println("Invalid game");
			System.exit(1);
		}
				
		String[] playerModes = Arrays.copyOfRange(args, 2, args.length);
				
		if(game.getState().getPlayerCount() != playerModes.length && args[1].equalsIgnoreCase("console")){
			System.err.println("Invalid number of players");
			System.exit(1);
		}
		
		switch(args[1].toLowerCase()){
		case "console":
			startConsoleMode(args[0],game,playerModes);
			break;
		case "gui":
			startGUIMode(args[0], game);
			break;
		default:
			usage();
			System.exit(1);
		}
	}
	
	/**
	 * Se crea el estado inicial del juego.
	 * Tres en raya si se introduce TTT y Wolf and Sheep si se introduce WAS
	 * @param gameName del que se crea el estado
	 * @return el estado incial del juego
	 * @throws IllegalArgumentException si la primera palabra del args no se corresponde con ningun juego
	 */
	public static GamePlayer createPlayer (String gameName, String playerType, String playerName) {
		playerType = playerType.toLowerCase();
		if (playerType.equals("rand")) return new RandomPlayer(playerName);
		else if (playerType.equals("smart")) return new SmartPlayer(playerName,15);
		else if(playerType.equals("manual")){
			Scanner in = new Scanner(System.in);
			return new ConsolePlayer(playerName, in);
		}
		else throw new IllegalArgumentException("Error: Player " + playerType + " undefined.");
	}
}
