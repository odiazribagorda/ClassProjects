package es.ucm.fdi.tp.was;

/**
 * Representa una casilla del tablero.
 * @author Oscar Diaz Ribagorda y Mateo Garcia Perez.
 *
 */
public class Casilla {
	/**
	 * Fila de la casilla
	 */
	private int row;
	/**
	 * Columna de la casilla
	 */
	private int col;
	/**
	 * Crea una casilla
	 * @param r valor que indica la fila
	 * @param c valor que indica la columna
	 */
	public Casilla(int r, int c) {
		row = r;
		col = c;
	}
	/**
	 * 
	 * @return la fila de una casilla
	 */
	public int getRow() {
		return row;
	}
	/**
	 * 
	 * @return la columna de una casilla
	 */
	public int getCol() {
		return col;
	}
	/**
	 * 
	 * @param c casilla a comparar
	 * @return true si se apunta a la misma fila y columna false si no
	 */
	public boolean equals(Casilla c) {
		return c.row == row && c.col == col;
	}
}
