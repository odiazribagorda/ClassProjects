package es.ucm.fdi.tp.peones;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

import es.ucm.fdi.tp.base.model.GameState;
import es.ucm.fdi.tp.was.Casilla;

public class PeonesState extends GameState<PeonesState, PeonesAction> {
	/**
	 * 
	 */
	private static final long serialVersionUID = 821795275801853509L;
	private final int turn;
	/**
	 * Indica si la partida a acabado o no
	 */
    private final boolean finished;
    /**
     * Representa el tablero con -1 para las casillas vacias, 0 para la que contiene al lobo
     * y 1 para las que contienen una oveja
     */
    private final int[][] board;
    /**
     * Indica quien ha ganado 0 si lobo, 1 si oveja y -1 si todavía no ha ganado nadie
     */
    private final int winner;
    /**
     * Guarda todas las aciiones que puede realizar el jugador que tiene el turno
     */
    private ArrayList<PeonesAction> valid;
    
    private final int BLANCA = 0;
    private final int NEGRA = 1;
    private final int EMPTY = -1;
    private final int DIM = 4;

	public PeonesState() {
		super(2);
		board = new int[DIM][];
        for (int i=0; i<DIM; i++) {
            board[i] = new int[DIM];
            for (int j=0; j<DIM; j++) board[i][j] = EMPTY;
        }
        for(int i=0; i < DIM;i++){
        	board[0][i] = BLANCA;
        	board[DIM - 1][i] = NEGRA;
        }
        List<Integer> num = new ArrayList<Integer>();
        num.add(0); num.add(1); Collections.shuffle(num);
        this.turn = num.get(0);
        this.winner = -1;
        this.finished = false;
        this.valid= null;
	}
	
	public PeonesState(PeonesState prev, int[][] board, boolean finished, int winner) {
		super(2);
        this.board = board;
        if(!bloqueado((prev.turn + 1) % 2)) this.turn = (prev.turn + 1) % 2;
        else this.turn = prev.turn;
        this.finished = finished;
        this.winner = winner;
        this.valid = null;
	}
	
	private boolean bloqueado(int numPlayer) {
		return validActions(numPlayer).size() == 0;
	}
	

	public boolean isValid(PeonesAction action) {
        if (isFinished()) {
            return false;
        }
        else {
        	List<PeonesAction> list = validActions(turn);
        	for(int i = 0; i < list.size(); ++i) {
        		if(list.get(i).equals(action)) return true;
        	}
        	return false;
        }
        
    }
	
	@Override
	public int getTurn() {
		return turn;
	}

	@Override
	public List<PeonesAction> validActions(int playerNumber) {
		if(valid == null) {
			valid = new ArrayList<PeonesAction>();
		if(finished) return valid;
			
		for(int i = 0; i < DIM; ++i)
			for(int j = 0; j < DIM; ++j) {
				if(board[i][j] == playerNumber) {
					if(playerNumber == BLANCA) {
						añadirJugadas(valid, BLANCA, i, j);
					} else if (playerNumber == NEGRA) {
						añadirJugadas(valid,NEGRA,i,j);
					}
				}
			}
		}
		return valid;
	}
	
	private void añadirJugadas(List<PeonesAction> valid, int jugador, int i, int j) {
		int dir;
		if (jugador == BLANCA) dir = 1;
		else dir = -1;
		
		if(i + dir >= 0 && i+dir < DIM) {
			if(board[i+dir][j] == EMPTY)
				valid.add(new PeonesAction(jugador, new Casilla(i+dir, j), new Casilla(i, j)));
			if(j+1 < DIM && board[i+dir][j+1] == contrario(jugador))
				valid.add(new PeonesAction(jugador, new Casilla(i+dir, j+1), new Casilla(i, j)));
			if(j-1 >= 0 && board[i+dir][j-1] == contrario(jugador))
				valid.add(new PeonesAction(jugador, new Casilla(i+dir, j-1), new Casilla(i, j)));
		}

	}
	
	private int contrario(int j) {
		if(j == BLANCA) return NEGRA;
		else return BLANCA;
	}
	
	public static boolean isWinner(int board[][], int playerNumber) {
		for(int i = 0; i < board.length; ++i) {
			if(playerNumber == 0 && board[board.length - 1][i] == 0) return true;
			else if(playerNumber == 1 && board[0][i] == 1) return true;
		}
		return false;
	}
	
    public int at(int row, int col) {
        return board[row][col];
    }
	
	@Override
	public boolean isFinished() {
		return finished;
	}

	@Override
	public int getWinner() {
		return winner;
	}

	public int[][] getBoard() {
		int[][] copy = new int[board.length][];
        for (int i=0; i<board.length; i++) copy[i] = board[i].clone();
        return copy;
	}
	
	public String getGameDescription() {
    	return "Peones";
    }
	
	public int getDim() {
		return DIM;
	}
}
