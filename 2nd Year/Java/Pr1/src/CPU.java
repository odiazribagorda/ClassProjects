package tp.pr1.mv;

/** Los objetos de esta clase tienen una memoria, una pila y un booleano para acabar.
 * La CPU sera la que instruccion a instruccion se vaya ejecutando realizando los cambios necesarios
 * en memoria y pila.
 * @author Oscar Diaz Ribagorda y Mateo Garcia Perez.
 */

public class CPU {
	/**
	 * Objeto de la clase Memory que representa la memoria de la CPU.
	 */
	private Memory mem;
	/**
	 * Objeto de la clase OperandStack que representa la pila de la CPU.
	 */
	private OperandStack stack;
	/**
	 * Indicador de si la CPU tiene que acabar su ejecucion.
	 */
	private boolean end;
	
	/** Construye un objeto de la clase CPU.
	 * 
	 */
	public CPU() {
		mem = new Memory();
		stack = new OperandStack();
		end = false;
	}
	
	/** Se encarga de la ejecucion de los ByteCodes almacenados en el programa. Tiene que identificar de que
	 * ByteCode se trata y realizar la ejecuci�n adecuada de la instruccion.
	 * 
	 * @param instruc ByteCode que se va a ejecutar en la CPU.
	 * @return Booleano que indica si la instruccion se ha podido ejecutar.
	 */
	public boolean execute(ByteCode instruc){
		boolean nofallo=true;
		switch(instruc.getName()){
		case PUSH:
			nofallo= stack.push(instruc.getParam());
			break;
			
		case LOAD:
			//El -1 es el que simboliza el error
			int aux = mem.read(instruc.getParam());
			if(aux != -1)
				nofallo = stack.push(aux);
			else
				nofallo= false;	
			break;
			
		case STORE:
			if(stack.getVacia())nofallo= false;
			else{
				mem.write(instruc.getParam(), stack.pop());
			}
			break;
			
		case ADD:
			if(stack.getVacia())nofallo = false;
			else{
				int aux1= stack.pop();
				if(stack.getVacia())nofallo = false;
				else{
					int aux2= stack.pop();
					nofallo=stack.push(aux2+aux1);
				}
			}
			break;
			
		case SUB:
			if(stack.getVacia())nofallo = false;
			else{
				int aux1= stack.pop();
				if(stack.getVacia())nofallo = false;
				else{
					int aux2= stack.pop();
					nofallo=stack.push(aux2-aux1);
				}
			}
			break;
			
		case MUL:
			if(stack.getVacia())nofallo = false;
			else{
				int aux1= stack.pop();
				if(stack.getVacia())nofallo = false;
				else{
					int aux2= stack.pop();
					nofallo=stack.push(aux2*aux1);
				}
			}
			break;
			
		case DIV:
			if(stack.getVacia())nofallo = false;
			else{
				int aux1= stack.pop();
				if(stack.getVacia() || aux1 == 0)nofallo = false;
				else{
					int aux2= stack.pop();
					nofallo=stack.push(aux2/aux1);
				}
			}
			break;
			
		case OUT:
			if(stack.getVacia()) nofallo= false;
			else{
				System.out.println("El numero a mostrar es: " +  stack.pop());
			}
			
			break;
			
		case HALT:
			end = true;
			break;
		}
		return nofallo;
	}
	
	/**
	 * @return El booleano end
	 */
	public boolean getEnd() {
		return end;
	}
	
	/** Muestra por pantalla el estado de la CPU.
	 * 
	 */
	public void mostrarEstado() {
		System.out.println("Estado de la CPU:");
		mem.mostrar();
		stack.mostrar();
	}

}
