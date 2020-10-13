package es.ucm.fdi.tp.was;

import java.awt.Point;

import javax.swing.SwingUtilities;

import es.ucm.fdi.tp.base.model.GameAction;
import es.ucm.fdi.tp.base.model.GameState;
import es.ucm.fdi.tp.mvc.GameTable;
import es.ucm.fdi.tp.view.swing.GameBoardUI;
import es.ucm.fdi.tp.view.swing.MessageUI;

/**
 * Esta clase implementa un tablero para el juego del Wolf And Sheep y se
 * encarga de que todos sus metodos funcionen bien.
 * 
 * @author Oscar Diaz Ribagorda y Mateo Garcia Perez.
 *
 */
public class WolfAndSheepBoard<S extends GameState<S, A>, A extends GameAction<S, A>> extends GameBoardUI<S, A> {

	/**
	 * Fila que ha sido clicada.
	 */
	private int rowClicked;

	/**
	 * Columna que ha sido clicada.
	 */
	private int colClicked;

	/**
	 * Indica si el tablero ha sido clicado o no.
	 */
	boolean clicked;

	/**
	 * Tablero del juego
	 */
	private GameTable<S, A> game;

	/**
	 * Panel de mensajes.
	 */
	private MessageUI msg;

	/**
	 * Una matriz con la distribucion del tablero.
	 */
	private Integer[][] board;

	/**
	 * Constructor de la clase.
	 * 
	 * @param game
	 * @param msg
	 */
	public WolfAndSheepBoard(GameTable<S, A> game, MessageUI msg) {
		this.game = game;
		this.msg = msg;
		initWasGUI();
	}

	@Override
	/**
	 * Implementa las medidas y acciones que ha de tomar cuando se clica en una
	 * casilla del juego.
	 * 
	 * @param row
	 *            Fila clicada.
	 * @param col
	 *            Columna clicada.
	 * @param clickCount
	 *            Numero de clicks
	 * @param mouseButton
	 *            Numero del boton del raton.
	 */
	public void mouseGameClicked(int row, int col, int clickCount, int mouseButton) {
		if (!clicked) {
			// Preguntamos si es null para luego poder comparar con un entero.
			if (board[row][col] != null)
				if (board[row][col] == game.getState().getTurn()) {
					clicked = true;
					rowClicked = row;
					colClicked = col;
					msg.addLine("Selected (" + row + " , " + col + "). Click destination or\n"
							+ "other cell to cancel selection");
					boardComp.setHighlighted(new Point(col, row));
				}
		}
		// Para que puedas elegir una ficha diferente.
		else if (board[row][col] != null && board[row][col] == game.getState().getTurn()) {
			boardComp.clearHightlighted();
			rowClicked = row;
			colClicked = col;
			msg.addLine(
					"Selected (" + row + " , " + col + "). Click destination or\n" + "other cell to cancel selection");
			boardComp.setHighlighted(new Point(col, row));
		} else {
			boardComp.clearHightlighted();
			@SuppressWarnings("unchecked")
			WolfAndSheepAction actualAction = new WolfAndSheepAction(game.getState().getTurn(), new Casilla(rowClicked, colClicked),
					new Casilla(row, col));
			WolfAndSheepState actualState = (WolfAndSheepState) game.getState();
			if (actualState.isValid(actualAction)) {
				SwingUtilities.invokeLater(new Runnable() {
					public void run() {
						game.execute((A) actualAction);
					}
				});
			} else
				msg.addLine("Selection canceled.");
			clicked = false;
		}

	}

	/**
	 * Inicializa un juego tipo GUI de Wolf And Sheep.
	 */
	private void initWasGUI() {
		initGUI(8);
		updateBoard(game.getState());
	}

	@Override
	/**
	 * Actualiza el tablero con el nuevo estado.
	 * 
	 * @param state
	 *            Nuevo estado.
	 */
	public void updateBoard(S state) {
		board = new Integer[8][8];
		
		WolfAndSheepState actualState= (WolfAndSheepState) state;
		for (int i = 0; i < 8; ++i) {
			for (int j = 0; j < 8; ++j) {
				if (actualState.at(i, j) == 1)
					board[i][j] = 1;
				else if (actualState.at(i, j) == 0)
					board[i][j] = 0;
				else
					board[i][j] = null;
			}
		}
	}

	@Override
	/**
	 * Devuelve el tipo de jugador que hay en la posicion indicada.
	 * 
	 * @param row
	 *            Fila indicada.
	 * @param col
	 *            Columna indicada.
	 * @return
	 */
	public Integer getPosition(int row, int col) {
		return board[row][col];
	}

}
