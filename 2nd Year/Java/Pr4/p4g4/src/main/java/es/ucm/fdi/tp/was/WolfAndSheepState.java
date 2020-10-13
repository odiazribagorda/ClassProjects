package es.ucm.fdi.tp.was;

import java.util.ArrayList;
import java.util.List;

import es.ucm.fdi.tp.base.model.GameState;

/**
 * Un estado del juego Wolf and Sheep.
 * En el se representa el estado del juego en un momento determinado y se puede
 * acceder a la información que contiene como por ejemplo, a que casillas puede ir el jugador
 * @author Oscar Diaz Ribagorda y Mateo Garcia Perez.
 *
 */
public class WolfAndSheepState extends GameState<WolfAndSheepState, WolfAndSheepAction> {

	private static final long serialVersionUID = 1171285932949282245L;
	/**
	 * Representa  quien esta jugando (0 para lobo y 1 para ovejas)
	 */
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
    private ArrayList<WolfAndSheepAction> valid;
    /**
     * Indica la dimension del tablero (si no es 8 no se puede crear el juego)
     */
    private final int dim;
    /**
     * Numero para representar cuando no se refiere al lobo ni a las ovejas
     */
    final static int EMPTY = -1;
    /**
     * Numero para representar cuando se refiere al lobo
     */
    final static int LOBO = 0;
    /**
     * Numero para representar cuando se refiere a las ovejas
     */
    final static int OVEJA = 1;
    
    /**
     * Crea el estado base del juego.
     * Se crea el tablero con la dimension dada (de momento solo se admite dimension 8),
     * se ponen todas las casillas vacias y se colocan las ovejas y el lobo en su sitio determinado,
     * el primer turno es del lobo (jugador 0) 
     * 
     * @param dim Dimension del tablero a crear, solo se admite un 8
     */
    public WolfAndSheepState(int dim) {    	
        super(2);
        if (dim != 8) {
            throw new IllegalArgumentException("Expected dim to be 8");
        }

        this.dim = dim;
        board = new int[dim][];
        for (int i=0; i<dim; i++) {
            board[i] = new int[dim];
            for (int j=0; j<dim; j++) board[i][j] = EMPTY;
        }
        board[dim-1][0]= LOBO;
        for(int i=1; i < dim;i+=2){
        	board[0][i] = OVEJA;
        }
        this.turn = 0;
        this.winner = -1;
        this.finished = false;
        this.valid= null;
    }
    /**
     * Crea un nuevo estado a partir del anterior.
     * A partir del estado en el turno anterior se crea otro con los cambios apropiados
     * para el siguiente turno 
     * @param prev Estado anterior del que se copia la dimension y se comprueba el turno para avanzarlo
     * @param board Guarda la colocacion de las fichas
     * @param finished Indica si el juego ha acabado
     * @param winner Indica si hay ganador y quien es
     */
    public WolfAndSheepState(WolfAndSheepState prev, int[][] board, boolean finished, int winner) {
    	super(2);
    	this.dim = prev.dim;
        this.board = board;
        this.turn = (prev.turn + 1) % 2;
        this.finished = finished;
        this.winner = winner;
        this.valid = null;
    }    
    /**
     * Comprueba si una accion es valida.
     * Para ello comprueba que se encuentra en la lista de acciones validas del jugador
     * @param action que se quiere comprobar
     * @return Si es valida true, si no false
     */
    public boolean isValid(WolfAndSheepAction action) {
        if (isFinished()) {
            return false;
        }
        return valid.contains(action);
    }
    /**
     * Crea una lista con las acciones validas del jugador del turno.
     * Se recorre el tablero hasta que se encuentran las ficahs del jugador (lobo o ovejas)
     * se mira las acciones validas del jugador. Si la lista de acciones validas ya tiene acciones guardadas,
     * no se compurban más. En el caso de las ovejas se tiene el movimiento comodin con casillas nulas, 
     * que representa la accion de pasar el turno
     */
    public List<WolfAndSheepAction> validActions(int playerNumber) {
    	if (valid == null) {
	        valid = new ArrayList<>();
	        if (finished) {
	            return valid;
	        }
	     for(int i =0; i < dim; ++i){
	    	 for(int j =0 ;  j < dim; ++j){
	    		 if (board[i][j] == playerNumber){
	    			 if (i + 1 < dim && j - 1 >= 0 && board[i + 1][j - 1] == EMPTY){// Movimiento abajo izquierda 
			    			valid.add(new WolfAndSheepAction(playerNumber, new Casilla(i, j), new Casilla(i + 1, j - 1)));
			    		}
	    			 if (i + 1 < dim && j + 1 < dim && board[i + 1][j + 1] == EMPTY) {// Movimiento abajo derecha
			    			valid.add(new WolfAndSheepAction(playerNumber, new Casilla(i, j), new Casilla(i + 1, j + 1)));
			    		}
	    			 if(playerNumber== LOBO){
	    				 if (i - 1 >= 0 && j - 1 >= 0 && board[i - 1][j - 1] == EMPTY) {// Movimiento arriba izquierda
								valid.add(new WolfAndSheepAction(LOBO, new Casilla(i, j), new Casilla(i - 1, j - 1)));
							}
	    				 if (i - 1 >= 0 && j + 1 < dim && board[i - 1][j + 1] == EMPTY) {// Movimiento arriba derecha
								valid.add(new WolfAndSheepAction(LOBO, new Casilla(i, j), new Casilla(i - 1, j + 1)));
							}
	    			 	}
	    		 	}
	    	 	}
	     	}
	     /*
	      * Esta seria la accion comodin para permitir a las ovejas 
	      * pasar el turno si no tienen ningun movimiento valido
	      */
	     if(playerNumber == OVEJA && valid.size() == 0) {
		    	valid.add(new WolfAndSheepAction(OVEJA, null, null));
		    	}
    	}
        return valid;
    }

    /**
     * Se comprueba si el jugador ha ganado.
     * Como un jugador no puede ganar en el truno del contrario se comprueba solo si se 
     * cumple la condicion de victoria del jugador correspondiente al playerNumber
     * Lobo gana si esta en la fila 0, ovejas si el lobo no tiene movimientos.
     * @param board donde se comprueban si las fichas cumplen la condicion de victoria
     * @param playerNumber del jugador que se tiene que comprobar
     * @return true si ha ganado, false si no
     */
    public static boolean isWinner(int[][] board, int playerNumber) {
        boolean enc = false;
        // Lobo gana si esta en la fila 0, ovejas si el lobo no tiene movimientos.
        int i = 0;
        while(i < board.length && !enc) {
        	int j = 0;
        	while(j < board[i].length && !enc) {
        		if(board[i][j] == LOBO) {
        			enc = true;
        			if(playerNumber == LOBO) {
        				return i == 0;
        			}
        			else if (playerNumber == OVEJA) {
        				boolean block = true;
        				if (block && i - 1 > 0 && j - 1 > 0 && board[i - 1][j - 1] == EMPTY) block = false;
        				else if (block && i - 1 > 0 && j + 1 < board[i - 1].length && board[i - 1][j + 1] == EMPTY) block = false;
        				else if (block && i + 1 < board.length && j - 1 > 0 && board[i + 1][j - 1] == EMPTY) block = false;
        				else if (block && i + 1 < board.length && j + 1 < board[i + 1].length && board[i + 1][j + 1] == EMPTY) block = false;
        				return block;
        			}
        		}
        		++j;
        	}
        	++i;
        }
        return false; // Nunca se llega a este punto porque siempre se encuentra al lobo.
    }    
    /**
     * Devuelve lo que hay en una fila y columna determinadadas.
     * @param row a comprobar
     * @param col a comprobar
     * @return -1 si vacia, 0 si lobo, 1 si oveja
     */
    public int at(int row, int col) {
        return board[row][col];
    }
    /**
     * Indica de quien es el turno
     */
    public int getTurn() {
        return turn;
    }
    /**
     * Indica si el juego ha acabado.
     */
    public boolean isFinished() {
        return finished;
    }
    /**
     * Devuelve la informacion del ganador
     */
    public int getWinner() {
        return winner;
    }

    /**
     * @return a copy of the board
     */
    public int[][] getBoard() {
        int[][] copy = new int[board.length][];
        for (int i=0; i<board.length; i++) copy[i] = board[i].clone();
        return copy;
    }
    /**
     * Dibujo del tablero, la O representa al lobo y las X a las ovejas
     */
    public String toString() {
        StringBuilder sb = new StringBuilder();
        for (int i=0; i<board.length; i++) {
            sb.append("|");
            for (int j=0; j<board.length; j++) {
                sb.append(board[i][j] == EMPTY ? "   |" : board[i][j] == 0 ? " O |" : " X |");
            }
            sb.append("\n");
        }
        return sb.toString();
    }
}
