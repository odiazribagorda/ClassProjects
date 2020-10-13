package tp.pr1.mv;


/** Esta clase se encarga unicamente de pasar un string con la informacion del ByteCode
 * a un objeto de la clase ByteCode para que se pueda a�adir al programa como tal.
 * @author Oscar Diaz Ribagorda y Mateo Garcia Perez.
 */
public class ByteCodeParser {
	
	/** La funcion divide por el espacio para distinguir el ByteCode del parametro que va con el.
	 * Luego se va comparando con los ByteCodes posibles para guardarlo.
	 * @return Bytecode con todos sus datos.
	 */
	public static ByteCode parse(String s) {
		ByteCode b = new ByteCode();
		String[] subcadenas = s.split(" ");
		subcadenas[0] = subcadenas[0].toLowerCase();
		
		if(subcadenas[0].equals("push")){
			b.setName(ENUM_BYTECODE.PUSH);
			if(subcadenas.length == 1) b = null;
			else b.setParam(Integer.parseInt(subcadenas[1]));
			
		} else if(subcadenas[0].equals("load")) {
			b.setName(ENUM_BYTECODE.LOAD);
			if(subcadenas.length == 1) b = null;
			else b.setParam(Integer.parseInt(subcadenas[1]));
			
		} else if(subcadenas[0].equals("store")) {
			b.setName(ENUM_BYTECODE.STORE);
			if(subcadenas.length == 1) b = null;
			else b.setParam(Integer.parseInt(subcadenas[1]));
			
		} else if(subcadenas[0].equals("add"))
			b.setName(ENUM_BYTECODE.ADD);
		
		else if(subcadenas[0].equals("sub"))
			b.setName(ENUM_BYTECODE.SUB);
		
		else if(subcadenas[0].equals("mul"))
			b.setName(ENUM_BYTECODE.MUL);
		
		else if(subcadenas[0].equals("div"))
			b.setName(ENUM_BYTECODE.DIV);
		
		else if(subcadenas[0].equals("out"))
			b.setName(ENUM_BYTECODE.OUT);
		
		else if(subcadenas[0].equals("halt"))
			b.setName(ENUM_BYTECODE.HALT);
		else b = null;
		return b;
	}
}
