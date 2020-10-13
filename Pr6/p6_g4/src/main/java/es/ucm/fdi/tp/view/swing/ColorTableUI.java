package es.ucm.fdi.tp.view.swing;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Component;
import java.awt.FlowLayout;
import java.util.HashMap;
import java.util.Map;

import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTable;
import javax.swing.SwingUtilities;
import javax.swing.table.TableCellRenderer;

import es.ucm.fdi.tp.extra.jcolor.ColorChooser;

/**
 * Recuadro de seleccion de colores.
 * @author Oscar Diaz Ribagorda y Mateo Garcia Perez.
 *
 */
public class ColorTableUI extends JPanel {
	
	/**
	 * 
	 */
	private static final long serialVersionUID = 1794195613977583639L;
	/**
	 * Nombres de las columnas de la tabla
	 */
	private final String[] cols = {"Player", "Color"};
	/**
	 * Datos de la tabla
	 */
	private final Object[][] data = {{0, ""}, {1, ""}};
	
	/**
	 * Color del jugador 1
	 */
	private Color color1;
	/**
	 * Color del jugador 2
	 */
	private Color color2;
	
	/**
	 * Mapa que asocia a un entero un color
	 */
	private Map<Integer, Color> colors; // Line -> Color
	
	/**
	 * Ventana de dialogo para escoger un color
	 */
	private ColorChooser colorChooser;
	
	/**
	 * Atributo que se encargara del pintado.
	 */
	private PaintableTwoColor paintable;

	/**
	 * Contructora de la clase.
	 * Llama al metodo que la inicializa
	 */
	public ColorTableUI(PaintableTwoColor paintable) {
		this.paintable = paintable;
		initGUI();
	}

	/**
	 * Inicializa la clase.
	 * Viene del ejemplo
	 */
	private void initGUI() {

		setLayout(new BorderLayout());
		colors = new HashMap<>();
		colorChooser = new ColorChooser(new JFrame(), "Choose Line Color", Color.BLACK);

		// names table
		JTable table = new JTable(data, cols) {
			private static final long serialVersionUID = 1L;

			// THIS IS HOW WE CHANGE THE COLOR OF EACH ROW
			@Override
			public Component prepareRenderer(TableCellRenderer renderer, int row, int col) {
				Component comp = super.prepareRenderer(renderer, row, col);

				// the color of row 'row' is taken from the colors table, if
				// 'null' setBackground will use the parent component color.
				if (col == 1)
					comp.setBackground(colors.get(row));
				else
					comp.setBackground(Color.WHITE);
				comp.setForeground(Color.BLACK);
				return comp;
			}
		};

		table.setToolTipText("Click on a row to change the color of a player");
		table.addMouseListener(new java.awt.event.MouseAdapter() {
			@Override
			public void mouseClicked(java.awt.event.MouseEvent evt) {
				int row = table.rowAtPoint(evt.getPoint());
				int col = table.columnAtPoint(evt.getPoint());
				if (row >= 0 && col >= 0) {
					changeColor(row);
				}
			}

		});

		this.add(new JScrollPane(table), BorderLayout.CENTER);
		JPanel ctrlPabel = new JPanel(new FlowLayout(FlowLayout.LEFT));
		this.add(ctrlPabel, BorderLayout.PAGE_START);

		this.add(new JLabel("Click to change color."), BorderLayout.PAGE_END);
		
		colors.put(0, paintable.colorElement1());
		colors.put(1, paintable.colorElement2());
		this.setOpaque(true);
		this.setSize(800, 500);
		this.setVisible(true);
	}

	/**
	 * Metodo para cambiar el color de una fila de la tabla
	 * @param row a cambiar
	 */
	private void changeColor(int row) {
		colorChooser.setSelectedColorDialog(colors.get(row));
		colorChooser.openDialog();
		if (colorChooser.getColor() != null) {
			if(row == 0) {
				color1 = colorChooser.getColor();
				colors.put(row, color1);
				paintable.paintElement1(color1);
			}
			else if(row == 1) {
				color2 = colorChooser.getColor();
				colors.put(row, color2);
				paintable.paintElement2(color2);
			}
		}

	}
	/**
	 * @return el color del primer jugador
	 */
	public Color getColor1() {
		return color1;
	}
	/**
	 * @return el color del segundo jugador
	 */
	public Color getColor2() {
		return color2;
	}
	
}