package es.ucm.fdi.tp.view.swing;

import java.awt.BorderLayout;
import java.awt.Color;

import javax.swing.BorderFactory;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTextArea;
import javax.swing.border.Border;
import javax.swing.border.TitledBorder;
/**
 * Cuadro de dialogo con la informacion del juego
 *@author Oscar Diaz Ribagorda y Mateo Garcia Perez.
 *
 */
public class MessageUI extends JPanel{

	/**
	 * Donde se escribe la informacion del juego
	 */
	private JTextArea log = new JTextArea();
	
	/**
	 * Constructora de la clase.
	 * Crea el scroll pane para ver mover el texto, hace que no se pueda editar,
	 * y le pone un borde
	 */
	public MessageUI() {
		setLayout(new BorderLayout());
		log.setWrapStyleWord(true);
		log.setLineWrap(false);
		JScrollPane jsp = new JScrollPane(log, 
				JScrollPane.VERTICAL_SCROLLBAR_ALWAYS,
				JScrollPane.HORIZONTAL_SCROLLBAR_AS_NEEDED);
		this.log.setEditable(false);
		add(jsp);
		Border b= BorderFactory.createLineBorder(Color.BLACK);
		jsp.setBorder(BorderFactory.createTitledBorder(b,"Status Messages",
				TitledBorder.RIGHT,TitledBorder.TOP));
		
	}
	
	/**
	 * Limpia el cuadro de texto
	 */
	public void clear() {
		log.setText("");
	}
	
	/**
	 * Añade una linea con información referida al juego
	 * @param s informacion a añadir
	 */
	public void addLine(String s) {
		log.append(s + '\n');
	}
}
