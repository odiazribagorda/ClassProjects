package es.ucm.fdi.tp.view.swing;

import java.awt.BorderLayout;
import java.awt.Color;
import java.util.Random;

import javax.swing.JPanel;

import es.ucm.fdi.tp.base.model.GameAction;
import es.ucm.fdi.tp.base.model.GameState;
import es.ucm.fdi.tp.extra.jboard.JBoard;

/**
 * Tablero del juego.
 * @author Oscar Diaz Ribagorda y Mateo Garcia Perez.
 */
public abstract class GameBoardUI<S extends GameState<S,A>,A extends GameAction<S,A>> extends JPanel implements PaintableTwoColor{
	
	/**
	 * 
	 */
	private static final long serialVersionUID = 4386851549676123874L;
	
	/**
	 * Atributo con el tablero pintado.
	 */
	protected JBoard boardComp;
	
	/**
	 * Color del primer jugador.
	 */
	
	private Color colPlayer1;
	/**
	 * Color del segundo jugador.
	 */
	private Color colPlayer2;
	

	
	/**
	 * Booleano que indica si se puede aplicar un movimiento.
	 */
	private boolean mover;
	
	/**
	 * Constructor de la clase.
	 */
	public GameBoardUI(){
		mover = false;
		colPlayer1= randomColor();
		colPlayer2 = randomColor();
	}

	/**
	 * Inicializa el tablero pintado.
	 * @param game
	 */
	protected void initGUI(int dim){
		
		this.setLayout(new BorderLayout());
		
		/**
		 * Implementa, principalmente el clickado de casilla.
		 */
		boardComp= new JBoard(){

			private static final long serialVersionUID = 1775809654123011806L;

			@Override
			protected void keyTyped(int keyCode) {}//No se necesita la tecla para nada

			@Override
			protected void mouseClicked(int row, int col, int clickCount, int mouseButton) {
		 		if(mover) {
		 		 mouseGameClicked(row,col,clickCount, mouseButton);
		 		}
				repaint();
			}

			@Override
			protected Shape getShape(int player) {
				return Shape.CIRCLE;
			}

			@Override
			protected Color getColor(int player) {
				return GameBoardUI.this.getColor(player);
			}

			@Override
			protected Integer getPosition(int row, int col) {
				return GameBoardUI.this.getPosition(row, col);
			}

			@Override
			protected Color getBackground(int row, int col) {
				return (row+col) % 2 == 0 ? Color.ORANGE : Color.BLACK;
			}

			@Override
			protected int getNumRows() {
				return dim;
			}

			@Override
			protected int getNumCols() {
				return dim;
			}
			
		};
		this.add(boardComp, BorderLayout.CENTER);
	}
	



	/**
	 * Devuelve el color correspondiente al jugador indicado.
	 * @param player
	 * @return
	 */
	protected Color getColor(int player) {
		return player == 0 ? colPlayer1 : colPlayer2;
	}
	
	/**
	 * Devuelve un color al azar.
	 * @return
	 */
	private Color randomColor(){
		Random rand = new Random();
		float r = rand.nextFloat();
		float g = rand.nextFloat();
		float b = rand.nextFloat();
		return new Color(r, g, b);
	}
	
	/**
	 * Cambia el color1 al color indicado.
	 * @param color
	 */
	public void paintElement1(Color color) {
		colPlayer1 = color;
		repaint();
	}
	
	/**
	 * Cambia el color2 al color indicado.
	 * @param color
	 */
	public void paintElement2(Color color) {
		colPlayer2 = color;
		repaint();
	}
	
	/**
	 * Actualiza el tablero con el nuevo juego.
	 */
	public void update(S state) {
		updateBoard(state);
	}
	
	/**
	 * Devuelve el color del jugador1
	 * @return Color del jugador 1.
	 */
	public Color colorElement1(){
		return colPlayer1;
	}
	
	/**
	 * Devuelve el color del jugador2
	 * @return Color del jugador 2.
	 */
	public Color colorElement2(){
		return colPlayer2;
	}
	
	/**
	 * Cambia el atributo mover.
	 * @param b Indica si se tiene que mover o no.
	 */
	public void setMover(boolean b){
		this.mover = b;
	}

	/**
	 * Se encarga de resolver el clicado de casilla.
	 */
	public abstract void mouseGameClicked(int row, int col, int clickCount, int mouseButton);
	/**
	 * Actualiza el tablero con el nuevo estado.
	 * @param state
	 */
	public abstract void updateBoard(S state);
	/**
	 * Devuelve el tipo de jugador en la casilla indicada.
	 */
	public abstract Integer getPosition(int row, int col);
}
