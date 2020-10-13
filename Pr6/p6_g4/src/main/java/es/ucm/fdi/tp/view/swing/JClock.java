package es.ucm.fdi.tp.view.swing;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Dimension;

import javax.swing.BorderFactory;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.JTextField;
import javax.swing.SwingUtilities;
import javax.swing.border.Border;
import javax.swing.border.TitledBorder;

public class JClock extends JPanel{
	
	private JButton play;
	private JButton stop;
	private JButton restart;
	private JTextField text;
	private int cont;
	private Thread t;
	
	public JClock() {
		JPanel menuPanel = new JPanel();
		menuPanel.setLayout(new BorderLayout());
		
		t = new Thread(() -> {
			try {
				while(true) {
					Thread.sleep(1000);
					SwingUtilities.invokeLater(()->actualizar(cont + 1));
				}
			} catch (InterruptedException e1) {}
		});
		play = new JButton("play");
		stop = new JButton("stop");
		restart = new JButton("restart");
		
		menuPanel.add(play, BorderLayout.LINE_START);
		menuPanel.add(stop, BorderLayout.CENTER);
		menuPanel.add(restart, BorderLayout.LINE_END);
		
		
		play.addActionListener((e) -> {
			t.start();
		});
		stop.addActionListener((e) -> {
			t.interrupt();
			t = new Thread(() -> {
				try {
					while(true) {
						Thread.sleep(1000);
						SwingUtilities.invokeLater(()->actualizar(cont + 1));
					}
				} catch (InterruptedException e1) {}
			});
		});
		restart.addActionListener((e) -> {
			actualizar(0);
		});
		cont = 0;
		text = new JTextField(cont);
		text.setEditable(false);
		text.setPreferredSize(new Dimension(100,20));
		
		add(menuPanel, BorderLayout.PAGE_START);
		add(text, BorderLayout.PAGE_END);
		
		
		Border b= BorderFactory.createLineBorder(Color.BLACK);
		this.setBorder(BorderFactory.createTitledBorder(b,"Clock",
				TitledBorder.LEFT,TitledBorder.TOP));
	}
	
	private void actualizar(int cont) {
		this.cont = cont;
		text.setText(""+this.cont);
		repaint();
	}
	
	

	public static void main(String[] args) {
		JFrame ventana = new JFrame("clock");
		ventana.add(new JClock());
		ventana.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		ventana.setSize(new Dimension(200, 200));
		ventana.setVisible(true);
		ventana.pack();
	}
	


}
