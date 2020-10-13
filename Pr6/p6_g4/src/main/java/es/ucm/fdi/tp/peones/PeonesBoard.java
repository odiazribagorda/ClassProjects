package es.ucm.fdi.tp.peones;

import java.awt.Point;

import javax.swing.SwingUtilities;

import es.ucm.fdi.tp.base.model.GameAction;
import es.ucm.fdi.tp.base.model.GameState;
import es.ucm.fdi.tp.mvc.GameTable;
import es.ucm.fdi.tp.view.swing.GameBoardUI;
import es.ucm.fdi.tp.view.swing.MessageUI;
import es.ucm.fdi.tp.was.Casilla;
import es.ucm.fdi.tp.was.WolfAndSheepAction;
import es.ucm.fdi.tp.was.WolfAndSheepState;

public class PeonesBoard<S extends GameState<S, A>, A extends GameAction<S, A>> extends GameBoardUI<S, A> {
	
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
	public PeonesBoard(GameTable<S, A> game, MessageUI msg) {
		this.game = game;
		this.msg = msg;
		initPeonesGUI();
	}
	
	private void initPeonesGUI() {
		initGUI(((PeonesState) game.getState()).getDim());
		updateBoard(game.getState());
	}

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
			PeonesAction actualAction = new PeonesAction(game.getState().getTurn(), new Casilla(row, col),
					new Casilla(rowClicked, colClicked));
			PeonesState actualState = (PeonesState) game.getState();
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

	@Override
	public void updateBoard(S state) {		
		PeonesState actualState= (PeonesState) state;
		board = new Integer[actualState.getDim()][actualState.getDim()];

		for (int i = 0; i < actualState.getDim(); ++i) {
			for (int j = 0; j < actualState.getDim(); ++j) {
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
	public Integer getPosition(int row, int col) {
		return board[row][col];
	}

}
