package es.ucm.fdi.tp.view.swing;

import java.awt.BorderLayout;
import java.awt.Dimension;
import java.awt.GridLayout;

import javax.swing.JFrame;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.SwingUtilities;

import es.ucm.fdi.tp.base.model.GameAction;
import es.ucm.fdi.tp.base.model.GameError;
import es.ucm.fdi.tp.base.model.GameState;
import es.ucm.fdi.tp.base.player.ConcurrentAiPlayer;
import es.ucm.fdi.tp.base.player.RandomPlayer;
import es.ucm.fdi.tp.base.player.SmartPlayer;
import es.ucm.fdi.tp.mvc.GameEvent;
import es.ucm.fdi.tp.mvc.GameObserver;
import es.ucm.fdi.tp.mvc.GameTable;
import es.ucm.fdi.tp.peones.PeonesBoard;
import es.ucm.fdi.tp.ttt.TttBoard;
import es.ucm.fdi.tp.view.swing.MenuUI.ListenerB;
import es.ucm.fdi.tp.view.swing.MenuUI.PlayerMode;
import es.ucm.fdi.tp.was.WolfAndSheepBoard;

/**
 * Ventana principal del juego, tiene todos los diferentes componentes.
 * 
 * @author Oscar Diaz Ribagorda y Mateo Garcia Perez.
 */
public class WindowUI<S extends GameState<S, A>, A extends GameAction<S, A>> extends JFrame
		implements GameObserver<S, A> {

	/**
	 * Entero que indica el numero de jugador que esta jugando.
	 */
	private int playerID;

	/**
	 * Atributo con el tipo de jugador que esta jugando.
	 */
	private PlayerMode mode;
	/**
	 * Atributo con toda la informacion sobre el juego.
	 */
	private GameTable<S, A> game;

	/**
	 * Atributo que tiene los botones y el comboBox para poder ejecutar
	 * acciones.
	 */
	private MenuUI menu;

	/**
	 * Menu inteligente que se encarga de controlar las jugadas inteligentes.
	 */
	private SmartMenuUI smartMenu;
	/**
	 * Atributo con un panel donde mostrar los mensajes de informacion.
	 */
	private MessageUI messages;
	/**
	 * Atributo con el tablero pintado.
	 */
	private GameBoardUI<S, A> board;
	/**
	 * Atributo que se encarga de la seleccion de los colores.
	 */
	private ColorTableUI colorTable;

	/**
	 * Booleano que indica si el juego esta parado.
	 */
	private boolean stop;

	/**
	 * Jugador inteligente que se encargara de ejecutar las acciones
	 * inteligentes
	 */
	ConcurrentAiPlayer smartPlayer;

	/**
	 * Hilo que lleva el procesamiento de jugadas inteligentes.
	 */
	private Thread smartThread;

	private static final long serialVersionUID = 3249217233766777837L;

	/**
	 * Constructor de la clase, que crea una nueva ventana con todos sus
	 * atributos.
	 * 
	 * @param playerId
	 * @param game
	 * @param gameCtrl
	 */
	public WindowUI(int playerId, GameTable<S, A> game) {
		super(game.getState().getGameDescription() + " (view for player " + playerId + ")");
		this.playerID = playerId;
		this.game = game;
		this.stop = false;
		mode = PlayerMode.Manual;
		smartPlayer = new ConcurrentAiPlayer("smart");
		smartPlayer.join(playerID);
		game.addObserver(this);
		initGui();
	}

	/**
	 * Inicializa los diferentes componentes de la ventana principal.
	 */
	public void initGui() {
		this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

		JPanel mainPanel = new JPanel(new BorderLayout(10, 10));

		// Se implementa la interfaz ListenerB, con lo que tiene que hacer en
		// caso de recibir una llamada.
		menu = new MenuUI(new ListenerB() {

			public void randomMove() {
				makeRandomMove();
			}

			public void smartMove() {
				makeSmartMove();
			}

			public void exit() {
				int seleccion = JOptionPane.showOptionDialog(mainPanel, "Are you sure?", "Exit",
						JOptionPane.OK_CANCEL_OPTION, JOptionPane.QUESTION_MESSAGE, null, null, null);
				if (JOptionPane.OK_OPTION == seleccion)
					System.exit(0);
			}

			public void restart() {
				int seleccion = JOptionPane.showOptionDialog(mainPanel, "Are you sure?", "Reset",
						JOptionPane.OK_CANCEL_OPTION, JOptionPane.QUESTION_MESSAGE, null, null, null);
				if (JOptionPane.OK_OPTION == seleccion)
					game.start();
			}
			// Y otro mas.

			public void move() {
				if (menu.getSelectedMode() == null) {
					return;
				}
				if (playerID == game.getState().getTurn()) {
					switch (menu.getSelectedMode()) {
					case Smart:
						makeSmartMove();
						return;
					case Random:
						makeRandomMove();
						return;
					default:
						break;
					}
				}
			}

		});
		smartMenu = new SmartMenuUI(smartPlayer, new Parable() {
			public void parar() {
				if (smartThread != null && smartThread.isAlive())
					smartThread.interrupt();
			}
		});

		JPanel menuPanel = new JPanel();
		menuPanel.setLayout(new BorderLayout());
		menuPanel.add(menu, BorderLayout.LINE_START);
		menuPanel.add(smartMenu, BorderLayout.LINE_END);
		mainPanel.add(menuPanel, BorderLayout.PAGE_START);

		JPanel rightPanel = new JPanel(new GridLayout(2, 1, 10, 10));
		this.messages = new MessageUI();
		rightPanel.add(messages);

		switch (game.getState().getGameDescription()) {
		case "Tic-Tac-Toe":
			board = new TttBoard<S, A>(game, messages);
			break;
		case "Wolf And Sheep":
			board = new WolfAndSheepBoard<S, A>(game, messages);
			break;
		case "Peones":
			board = new PeonesBoard<S,A>(game, messages);
		}
		mainPanel.add(board, BorderLayout.CENTER);

		this.colorTable = new ColorTableUI(board);
		rightPanel.add(colorTable);

		mainPanel.add(rightPanel, BorderLayout.LINE_END);

		add(mainPanel);

		this.setMinimumSize(new Dimension(950, 600));
		this.setVisible(true);
	}

	/**
	 * Trata los diferentes posibles eventos que se pueden producir tras el
	 * transcurso de la partida.
	 */
	@Override
	public void notifyEvent(GameEvent<S, A> e) {
		switch (e.getType()) {
		case Start:
			messages.clear();
			messages.addLine(e.toString());
			stop = false;
			if (playerID == game.getState().getTurn()) {
				this.enable(true);
				messages.addLine("It´s your turn. Click a cell");
			} else {
				this.enable(false);
				messages.addLine("It´s player " + game.getState().getTurn() + " turn.");
			}
			board.update(game.getState());
			repaint();

			break;
		case Stop:// Se mira si alguien ha ganado al acabar
			String endText = "The game ended: ";
			int winner = game.getState().getWinner();
			if (winner == -1) {
				endText += "draw!";
			} else {
				endText += "player " + (winner) + " won!";
			}
			messages.addLine(endText);
			this.enable(false);
			mode = PlayerMode.Manual;
			menu.setSelectedMode(mode);
			this.stop = true;
			this.board.update(game.getState());
			this.board.repaint();
			break;
		case Change:
			if (!stop) {
				messages.addLine(e.toString());

				if (playerID == game.getState().getTurn()) {
					this.enable(true);
					messages.addLine("It´s your turn. Click a cell. ");
				} else {
					this.enable(false);
					messages.addLine("It´s player " + game.getState().getTurn() + " turn.");
				}

				// Se mira que modo se ha escogido en el comboBox y se cambia el
				// atributo.
				mode = menu.getSelectedMode();

				if (mode.equals(PlayerMode.Random) && playerID == game.getState().getTurn()) {
					makeRandomMove();
				} else if (mode.equals(PlayerMode.Smart) && playerID == game.getState().getTurn()) {
					makeSmartMove();
				}
				board.update(game.getState());
				board.repaint();
				if (game.getState().isFinished())
					game.stop();
			}
			break;
		case Error:
			messages.addLine(e.toString());
			break;
		case Info:
			messages.addLine(e.toString());
		default:
			break;
		}
	}

	/**
	 * Hace que no sea posible modificar los botones ni el tablero.
	 * 
	 * @param booleano
	 *            que indica si se debe habilitar o no.
	 */
	public void enable(boolean b) {
		this.board.setMover(b);
		this.menu.setEnabled(b);
	}

	/**
	 * Se encarga de pedir la ejecucion de un movimiento aleatorio.
	 */
	private void makeRandomMove() {
		RandomPlayer randPlayer = new RandomPlayer("random");
		randPlayer.join(playerID);
		try {
			SwingUtilities.invokeLater(() -> {
				if (!game.getState().isFinished())
					game.execute(randPlayer.requestAction(game.getState()));
			});
		} catch (GameError error) {
			messages.addLine(error.toString());
			mode = PlayerMode.Manual;
			menu.setSelectedMode(mode);
		}
	}

	/**
	 * Se encarga de pedir la ejecucion de un movimiento inteligente. Para ello
	 * crea un nuevo hilo que se encarga de pedir las acciones disponibles, tras
	 * eso se pinta. Si no se pudo realizar la jugada o se interrumpio al hilo,
	 * se informa de ello.
	 */
	private void makeSmartMove() {

		smartThread = new Thread() {
			public void run() {
				long time_start, time_end;
				time_start = System.currentTimeMillis();
				final A actualAction;
				if (!game.getState().isFinished())
					actualAction = smartPlayer.requestAction(game.getState());
				else
					actualAction = null;
				time_end = System.currentTimeMillis();
				try {
					SwingUtilities.invokeLater(() -> {
						if (actualAction != null) {
							game.execute(actualAction);
							messages.addLine(getSmartLine(smartPlayer.getEvaluationCount(), (time_end - time_start),
									smartPlayer.getValue()));
						} else {
							messages.addLine("Smart action interrupted.");
							enable(true);
							menu.setSelectedMode(PlayerMode.Manual); // Para poder hacer el movimiento en caso parada.
						}
						smartMenu.activate(false);
					});
				} catch (GameError error) {
					messages.addLine(error.toString());
					menu.setSelectedMode(PlayerMode.Manual);
				}
			}
		};
		smartMenu.activate(true);
		enable(false);
		smartThread.start();
	}

	/**
	 * Devuelve el mensaje de la ejecucion de la jugada inteligente.
	 * 
	 * @param numNodos
	 *            numero total de nodos analizado.
	 * @param time
	 *            que tardo en la ejecucion.
	 * @param value
	 *            de la jugada escogida.
	 * @return El mensaje.
	 */
	private String getSmartLine(int numNodos, long time, double value) {
		return (numNodos + " nodes in " + time + " ms (" + (numNodos / time) + " n/ms) value= " + value);
	}
}
