package tp.pr3.bytecode;

import tp.pr3.bytecode.arithmetics.Add;
import tp.pr3.bytecode.arithmetics.Div;
import tp.pr3.bytecode.arithmetics.Mul;
import tp.pr3.bytecode.arithmetics.Sub;
import tp.pr3.bytecode.conditional_jumps.Ifeq;
import tp.pr3.bytecode.conditional_jumps.Ifle;
import tp.pr3.bytecode.conditional_jumps.Ifleq;
import tp.pr3.bytecode.conditional_jumps.Ifneq;
import tp.pr3.bytecode.instructions.Goto;
import tp.pr3.bytecode.instructions.Halt;
import tp.pr3.bytecode.instructions.Load;
import tp.pr3.bytecode.instructions.Out;
import tp.pr3.bytecode.instructions.Push;
import tp.pr3.bytecode.instructions.Store;

/** Esta clase se encarga unicamente de pasar un string con la informacion del ByteCode
 * a un objeto de la clase ByteCode para que se pueda a�adir al programa como tal.
 * @author Oscar Diaz Ribagorda y Mateo Garcia Perez.
 */
public class ByteCodeParser {
	
	/**
	 * Es un vector constante con los diferentes tipos de Bytecode para que recorriendolo
	 * se pueda decidir que tipo de ByteCode ha sido introducido.
	 */
	private final static ByteCode[] bytecodes = {
		new Push(0), new Load(0), new Store(0), new Out(),
		new Halt(), new Goto(0), new Add(), new Sub(), new Div(),
		new Mul(), new Ifeq(0), new Ifle(0), new Ifleq(0), new Ifneq(0)
	};
	
	/** La funcion divide por el espacio para distinguir el ByteCode del parametro que va con el.
	 * Luego se va comparando con los ByteCodes posibles para guardarlo.
	 * @return Bytecode con todos sus datos.
	 */
	public static ByteCode parse(String s) {
		ByteCode bc = null;
		String[] subcadenas = s.split(" ");
		int i = 0;
		while (bc == null && i < bytecodes.length) {
			bc = bytecodes[i].parse(subcadenas);
			++i;
		}
		return bc;
	
	}
}
