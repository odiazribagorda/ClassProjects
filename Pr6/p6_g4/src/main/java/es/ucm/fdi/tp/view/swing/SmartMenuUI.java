package es.ucm.fdi.tp.view.swing;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.IOException;

import javax.imageio.ImageIO;
import javax.swing.BorderFactory;
import javax.swing.Icon;
import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JSeparator;
import javax.swing.JSpinner;
import javax.swing.SpinnerNumberModel;
import javax.swing.SwingConstants;
import javax.swing.border.Border;
import javax.swing.border.TitledBorder;
import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;

import es.ucm.fdi.tp.base.player.ConcurrentAiPlayer;

/** Muestra el menu encargado de la ejecucion de las jugadas inteligentes, permite elegir el numero de hilos,
 * y el tiempo de procesamiento de jugadas.
 *
 * @author Oscar Diaz Ribagorda y Mateo Garcia Perez.
 *
 */
public class SmartMenuUI extends JPanel {
	
	/**
	 * Atributo con el jugador inteligente que aplicara las jugadas.
	 */
	private ConcurrentAiPlayer smartPlayer;
	/**
	 * Etiqueta con el dibujo de un cerebro que indica si el hilo esta procesandose o no.
	 */
	private JLabel brain;
	/**
	 * Componente para seleccionar el numero de hilos.
	 */
	private JSpinner numHilos;
	/**
	 * Componenete para seleccionar el numero maximo de milisegundos.
	 */
	private JSpinner numMiliseg;
	/**
	 * Boton para interrumpir lo que indique el parar.
	 */
	private JButton stopButton;
	/**
	 * Atributo que indica lo que se ha de parar.
	 */
	private Parable parar;
	

	/**
	 * Constructor de la clase.
	 * @param smartPlayer el jugador inteligente que ejecutara las jugadas
	 * @param parar el atributo que para la ejecucion.
	 */
	public SmartMenuUI(ConcurrentAiPlayer smartPlayer, Parable parar){
		this.smartPlayer=smartPlayer;
		this.parar=parar;
		initGui();
	}
	/**
	 * Inicializa un menu inteligente.
	 */
	public void initGui(){
		brain= new JLabel(createImageIcon("brain"));
		brain.setBackground(Color.YELLOW);
		brain.setOpaque(false);
		
		numHilos= new JSpinner(new SpinnerNumberModel(1,1,Runtime.getRuntime
				().availableProcessors(),1));
		numHilos.addChangeListener((a) -> {
				smartPlayer.setMaxThreads((int) numHilos.getValue());
		});
		
		
		this.add(brain);
		this.add(numHilos);
		this.add(new JLabel("threads"));
		this.add(new JLabel("       "));
		this.add(new JLabel(createImageIcon("timer")));
		numMiliseg= new JSpinner(new SpinnerNumberModel(1000,500,5000,500));
		
		numMiliseg.addChangeListener((a) -> {
				smartPlayer.setTimeout((int)numMiliseg.getValue());
		});
		
		this.add(numMiliseg);
		this.add(new JLabel("ms."));
		
		stopButton= new JButton();
		stopButton.setIcon(createImageIcon("stop"));
		stopButton.setEnabled(false);
		stopButton.addActionListener((a) -> {
			parar.parar();
		});
		this.add(stopButton);
		
		Border b= BorderFactory.createLineBorder(Color.BLACK);
		this.setBorder(BorderFactory.createTitledBorder(b,"Smart Moves",
				TitledBorder.LEFT,TitledBorder.TOP));
	}
	
	/**
	 * Crea una imagen a partir del nombre del icono.
	 * @param name del icono
	 * @return imagen o null en caso de error
	 */
	private ImageIcon createImageIcon(String name){
		try {
			return new ImageIcon(ImageIO.read(
					getClass().getResource("/" + name + ".png")));			
		} catch (IOException ioe) {
			System.err.println("Error loading icon: " + ioe);
		}
		return null;
	}
	
	/**
	 * Segun el booleano, activa o desactiva el menu inteligente para poder utilizarlo o no.
	 * Activar: pintar de amarillo el cerebro, habilitar el boton de stop y deshabilitar los spinners.
	 * Desactivar: quita la capa de amarillo del cerebro, deshabilita el boton de stop y habilita los spinners.
	 * @param b indica si se debe activar o desactivar (true: activar, false: desactivar)
	 */
	public void activate(boolean b){
		brain.setOpaque(b);
		brain.repaint();
		numHilos.setEnabled(!b);
		numMiliseg.setEnabled(!b);
		stopButton.setEnabled(b);
	}
}
