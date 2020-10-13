package es.ucm.fdi.tp.view.swing;

import java.awt.Color;

/**
 * Interfaz que se encarga de pintar elementos.
 * @author Oscar Diaz Ribagorda y Mateo Garcia Perez.
 *
 */
public interface PaintableTwoColor {
	
	/**
	 * Pinta el elemento 1 del color indicado.
	 * @param color
	 */
	public void paintElement1(Color color);
	/**
	 * Pinta el elemento 2 del color indicado.
	 * @param color
	 */
	public void paintElement2(Color color);
	/**
	 * @return El color del elemento 1;
	 */
	public Color colorElement1();
	/**
	 * @return El color del elemento 2;
	 */
	public Color colorElement2();

}
