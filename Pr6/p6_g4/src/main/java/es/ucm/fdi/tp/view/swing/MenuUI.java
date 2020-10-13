package es.ucm.fdi.tp.view.swing;

import java.awt.GridLayout;
import java.io.IOException;

import javax.imageio.ImageIO;
import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JComboBox;
import javax.swing.JPanel;

/**
 * Menu que permite administrar el juego.
 * @author Oscar Diaz Ribagorda y Mateo Garcia Perez.
 */
public class MenuUI extends JPanel {
	
	/**
	 * 
	 */
	private static final long serialVersionUID = 8009227913737514435L;
	
	/**
	 * Lista con los tipos de jugador y que permite elegir caul se quiere(empieza por defecto en manual)
	 */
	private JComboBox<PlayerMode> list;
	
	/**
	 * Boton de jugada aleatoria.
	 */
	private JButton randButton;
	
	/**
	 * Boton de jugada inteligente.
	 */
	private JButton smartButton;
	
	/**
	 * Boton de salida
	 */
	private JButton exitButton;
	
	/**
	 * Boton de reinicio de partida.
	 */
	private JButton restartButton;

	/**
	 * Interfaz para los listeners de los botones
	 * @author Oscar Diaz Ribagorda y Mateo Garcia Perez.
	 *
	 */
	public interface ListenerB {
		public void randomMove();
		public void smartMove();
		public void exit();
		public void restart();
		public void move();
	}
	
	/**
	 * Enumerado que representa el tipo de jugador para saber cual se esta usando en cada momento
	 * @authorOscar Oscar Diaz Ribagorda y Mateo Garcia Perez.
	 *
	 */
	public enum PlayerMode {
		Manual,
		Smart,
		Random
	}
	
	/**
	 * Constructora del menu.
	 * Crea los botones y la combobox;
	 * @param listenerButton
	 */
	public MenuUI(ListenerB listenerButton) {
		
		
		this.randButton = createButton("Random", "dice");
		this.randButton.addActionListener((e)->listenerButton.randomMove());
		
		this.smartButton = createButton("Smart", "nerd");
		this.smartButton.addActionListener((e)->listenerButton.smartMove());
		
		this.restartButton= createButton("Reset", "restart");
		this.restartButton.addActionListener((e)->listenerButton.restart());
		
		this.exitButton= createButton("Exit", "exit");
		this.exitButton.addActionListener((e)->listenerButton.exit());
		
		add(randButton);
		add(smartButton);
		add(restartButton);
		add(exitButton);
		
		list = new JComboBox<>(PlayerMode.values());
		list.setSelectedIndex(0);
		this.list.addActionListener((e)->listenerButton.move());
		
		add(list);
	}

	/**
	 * Crea los botones.
	 * @param text nombre del boton
	 * @param icon imagen que lo representa
	 * @param listener de cada boton
	 * @return el boton ya creado
	 */
	private JButton createButton(String text, String icon) {
		try {
			JButton b = new JButton(text);
			b.setIcon(new ImageIcon(ImageIO.read(
					getClass().getResource("/" + icon + ".png"))));
			return b;			
		} catch (IOException ioe) {
			System.err.println("Error loading icon: " + ioe);
		}
		return null;
	}

	/**
	 * Sirve para seleccionar que tipo de jugador se quiere (Manual, Inteligente o aletorio)
	 * @return enumerado con el tipo del jugador
	 */
	public PlayerMode getSelectedMode() {
		return (PlayerMode) list.getSelectedItem();
	}
	
	/**
	 * Cambia el modo seleccionado en el comboBox.
	 * @param mode Modo al que ha de cambiar.
	 */
	public void setSelectedMode(PlayerMode mode) {
		list.setSelectedItem(mode);
	}
	
	/**
	 * Controla si los botones de movimiento estan habilitados o no.
	 * @param boolean que indica si habilitar o no.
	 */
	public void enable(boolean b){
		randButton.setEnabled(b);
		smartButton.setEnabled(b);
		list.setEnabled(b);
	}
}
