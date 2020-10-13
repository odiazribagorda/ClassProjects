package es.ucm.fdi.tp.peones;

import es.ucm.fdi.tp.base.model.GameAction;
import es.ucm.fdi.tp.was.Casilla;
import es.ucm.fdi.tp.was.WolfAndSheepState;

public class PeonesAction implements GameAction<PeonesState, PeonesAction> {
	/**
	 * 
	 */
	private static final long serialVersionUID = -636186052353848925L;
	
	Casilla cIni;
	Casilla cFin;
	private int playerNumber;
	
	public PeonesAction(int playerNumber, Casilla cFin, Casilla cIni) {
		this.cIni = cIni;
		this.cFin = cFin;
		this.playerNumber = playerNumber;
	}

	@Override
	public int getPlayerNumber() {
		return playerNumber;
	}

	@Override
	public PeonesState applyTo(PeonesState state) {
		if (playerNumber != state.getTurn()) {
            throw new IllegalArgumentException("Not the turn of this player");
        }

        // make move
        int[][] board = state.getBoard();
        if(cFin != null && cIni != null) {
	        board[cFin.getRow()][cFin.getCol()] = playerNumber;
	        board[cIni.getRow()][cIni.getCol()] = -1;
        }

        // update state
        PeonesState next;
        if (PeonesState.isWinner(board, state.getTurn())) {
            next = new PeonesState(state, board, true, state.getTurn());
        } else {
            next = new PeonesState(state, board, false, -1);
        }
        return next;
	}
	
	public boolean equals(PeonesAction a) {
		return a instanceof PeonesAction && cFin.equals(a.cFin)
		&& cIni.equals(a.cIni)
		&& playerNumber == a.playerNumber;
	}

}
