package tp.pr1.mv;

/**
 * Esta clase contiene los objetos y funciones que corresponden al codigo de instruccion
 * que se va a añadir al ByteCode program.
 * @author Oscar Diaz Ribagorda y Mateo Garcia Perez.
 */
public class ByteCode {
	/**
	 * Enumerado con el nombre del ByteCode.
	 */
	private ENUM_BYTECODE name;
	/**
	 * Parametro con el valor correspondiente para la correcta ejecucion del ByteCode.
	 */
	private int param;
	
	/**Cambia el nombre del objeto al nombre que le pasan como parametro.
	 * 
	 * @param code Enumerado con el nombre del bytecode.
	 */
	public void setName(ENUM_BYTECODE code){
		this.name = code;
	}
	
	/** Cambia el parametro del ByteCode por el que le pasan.
	 * 
	 * @param n Entero con el parametro correspondiente al bytecode.
	 */
	public void setParam(int n){
		this.param = n;
	}
	
	/** Convierte un ByteCode a String para luego poder mostrarlo por pantalla.
	 * 
	 * @return Un String con la informacion del bytecode.
	 */
	public String toString() {
		String s = new String();
		s = name.toString();
		if(name.equals(ENUM_BYTECODE.PUSH) || name.equals(ENUM_BYTECODE.LOAD) || name.equals(ENUM_BYTECODE.STORE))
			s += " " + param;
		return s;
	}
	
	/**
	 * @return El nombre del ByteCode.
	 */
	public ENUM_BYTECODE getName(){
		return name;
	}
	
	/**
	 * @return El parametro del ByteCode.
	 */
	public int getParam(){
		return param;
	}

}
