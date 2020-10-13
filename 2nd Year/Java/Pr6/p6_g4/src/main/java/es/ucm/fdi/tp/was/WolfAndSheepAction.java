package es.ucm.fdi.tp.was;

import es.ucm.fdi.tp.base.model.GameAction;

/**
 * Una accion del Wolf and Sheep.
 * Se indica quien va a hacer el movimiento y cual es este
 * @author Oscar Diaz Ribagorda y Mateo Garcia Perez.
 *
 */
public class WolfAndSheepAction implements GameAction<WolfAndSheepState, WolfAndSheepAction> {

	private static final long serialVersionUID = -7393105354486248741L;
	/**
	 * Jugador que va a realizar la accion 0 si lobo, 1 si ovejas
	 */
	private int player;
	/**
	 * Donde esta la ficha que se va a mover
	 */
	private Casilla cIni;
	/**
	 * A donde se va a mover la ficha
	 */
	private Casilla cFin;
    /**
     * Crea una nueva accion
     * @param player que realiza la accion
     * @param c1 casilla de origen
     * @param c2 casilla de destino
     */
    public WolfAndSheepAction(int player, Casilla c1, Casilla c2) {
        this.player = player;
        this.cIni = c1;
        this.cFin = c2;
    }
    /**
     * {@inheritDoc}
     */
    public int getPlayerNumber() {
        return player;
    }
    /**
     * Aplica la accion.
     * Cambia la ficha de lugar, actualiza el estado y comprueba si hay ganador
     * @param state de Wolf and Sheeps sobre el cual se aplican los cambios
     */
    public WolfAndSheepState applyTo(WolfAndSheepState state) {
        if (player != state.getTurn()) {
            throw new IllegalArgumentException("Not the turn of this player");
        }

        
        // make move
        int[][] board = state.getBoard();
        if(cFin != null && cIni != null) {
	        board[cFin.getRow()][cFin.getCol()] = player;
	        board[cIni.getRow()][cIni.getCol()] = -1;
        }

        // update state
        WolfAndSheepState next;
        if (WolfAndSheepState.isWinner(board, state.getTurn())) {
            next = new WolfAndSheepState(state, board, true, state.getTurn());
        } else {
            next = new WolfAndSheepState(state, board, false, -1);
        }
        return next;
    }
    /**
     * Crea una string con la accion.
     * Se indica donde esta la ficha que se va a mover y a donde se mueve.
     * Hay un movimiento "comodin" que solo pueden realizar las ovejas que es el de pasar,
     * se indica con una casilla nula
     */
    public String toString() {
    	String s;
    	if(player == 0) s = "WOLF";
    	else s = "SHEEP";
    	if (cIni == null || cFin == null) return "pass";
    	else return "move " + s + " from (" + cIni.getRow() + ", " + cIni.getCol() +
        		") to (" + cFin.getRow() + ", " + cFin.getCol() + ")";
    }
    
    /**
     * Metodo equals implementado para que puedan funcionar algunos metodos de
     * librerias externas.
     * @param action
     * @return
     */
    public boolean equals(WolfAndSheepAction action) {
    	return player == action.player
    			&& cIni.equals(action.cIni)
    			&& cFin.equals(action.cFin);
    }

}
