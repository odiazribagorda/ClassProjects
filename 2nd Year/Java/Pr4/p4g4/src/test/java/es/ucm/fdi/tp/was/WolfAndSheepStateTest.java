package es.ucm.fdi.tp.was;

import static org.junit.Assert.*;

import java.util.List;

import org.junit.Test;
/**
 *Comprueba el correcto funcionamiento del WolfAndSheepState
 * @author Oscar Diaz Ribagorda y Mateo Garcia Perez.
 *
 */

public class WolfAndSheepStateTest {
	/**
	 * Comprueba que cuando las ovejas arrinconan al lobo ganan
	 */
	@Test
	public void testVictoriaOvejas() {
		int[][] board = new int[8][];
		for (int i=0; i<8; i++) {
            board[i] = new int[8];
            for (int j=0; j<8; j++) board[i][j] = -1;
        }
		//Se coloca un lobo  y las ovejas rodeandolo
		board[3][3] = 0;
		board[2][2] = 1;
		board[2][4] = 1;
		board[4][2] = 1;
		board[4][4] = 1;
		//Se comprueba si la ovejas han ganado
		assertEquals(true,WolfAndSheepState.isWinner(board,1));
	}
	/**
	 * Comprueba que el lobo gana si esta en la fila 0
	 */
	@Test
	public void testVictoriaLobo() {
		int[][] board = new int[8][];
		for (int i=0; i<8; i++) {
            board[i] = new int[8];
            for (int j=0; j<8; j++) board[i][j] = -1;
        }
		//Se coloca un lobo en la fila 0 
		board[0][3] = 0;
		//Se comprueba si el lobo ha ganado
		assertEquals(true,WolfAndSheepState.isWinner(board,0));
	}
	/**
	 * Comprueba que el lobo solo tiene un movimiento valido al principio y despues tiene 4
	 */
	@Test
	public void testMovValidosLobo() {
		//Se crea el estado inicial
		WolfAndSheepState wasState= new WolfAndSheepState(8);
		//Se comprueba que el lobo tiene solo un movimiento valido
		List<WolfAndSheepAction> valid1 = wasState.validActions(0);
		assertEquals(1,valid1.size());
		//Se aplica la accion
		WolfAndSheepState next= valid1.get(0).applyTo(wasState);
		//Se comprueba que hay 4 acciones disponibles
		List<WolfAndSheepAction> valid2 = next.validActions(0);
		assertEquals(4,valid2.size());
	}
	/**
	 * Comprueba que las ovejas tienen 7 movimentos validos al principio y 1 oveja 
	 * tiene un unico movimieto si esta en el lateral
	 */
	@Test
	public void testMovValidosOveja() {
		//Se crea el estado inicial
		WolfAndSheepState wasState= new WolfAndSheepState(8);
		//Se avanza un turno
		WolfAndSheepState wasState2= new WolfAndSheepState(wasState,wasState.getBoard(),false, -1);
		//Se comprueba que las ovejas tienen 7 movimientos validos (1 la de la esquina y 2 las otras 3)
		List<WolfAndSheepAction> valid1 = wasState2.validActions(1);
		assertEquals(7,valid1.size());
		//Se aplica la accion 0 (que pone a la oveja de la izquierda en un lateral)
		WolfAndSheepState next= valid1.get(0).applyTo(wasState2);
		//Se comprueba que hay 6 acciones disponibles ya que desde un lateral una oveja solo puede hacer un movimiento (1+2+2+1)
		List<WolfAndSheepAction> valid2 = next.validActions(1);
		assertEquals(6,valid2.size());
	}
}
