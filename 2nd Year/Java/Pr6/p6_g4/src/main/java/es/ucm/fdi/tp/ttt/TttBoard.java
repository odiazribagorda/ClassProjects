package es.ucm.fdi.tp.ttt;

import javax.swing.SwingUtilities;

import es.ucm.fdi.tp.base.model.GameAction;
import es.ucm.fdi.tp.base.model.GameState;
import es.ucm.fdi.tp.mvc.GameTable;
import es.ucm.fdi.tp.view.swing.GameBoardUI;
import es.ucm.fdi.tp.view.swing.MessageUI;

public class TttBoard<S extends GameState<S, A>, A extends GameAction<S, A>> extends GameBoardUI<S, A> {

	/**
	 * El tablero del juego.
	 */
	private GameTable<S, A> game;
	/**
	 * El cuadro de mensajes del juego.
	 */
	private MessageUI msg;
	/**
	 * Matriz que indica el tipo de jugador que hay en cada casilla.
	 */
	private Integer[][] board;

	/**
	 * Constructor de la clase.
	 */
	public TttBoard(GameTable<S, A> game, MessageUI msg) {
		super();
		this.game = game;
		this.msg = msg;
		initTttGUI();
	}

	/**
	 * {@inheritDoc}
	 */
	public void mouseGameClicked(int row, int col, int clickCount, int mouseButton) {
		TttAction actualAction = new TttAction(game.getState().getTurn(), row, col);
		msg.addLine("Selected (" + row + " , " + col + ")");
		TttState actualState = (TttState) game.getState();
		if (actualState.isValid(actualAction)) {
			SwingUtilities.invokeLater(new Runnable() {
				public void run() {
					game.execute((A) actualAction);
				}
			});
		} else
			msg.addLine("Invalid selection, please select another position");

	}

	/**
	 * Inicializa un juego en GUI de Ttt.
	 */
	private void initTttGUI() {
		initGUI(3);
		updateBoard(game.getState());
	}

	@Override
	/**
	 * {@inheritDoc}
	 */
	public void updateBoard(S state) {
		board = new Integer[3][3];
		TttState actualState = (TttState) state;
		for (int i = 0; i < 3; ++i) {
			for (int j = 0; j < 3; ++j) {
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
	 * {@inheritDoc}
	 */
	public Integer getPosition(int row, int col) {
		return board[row][col];
	}

}
