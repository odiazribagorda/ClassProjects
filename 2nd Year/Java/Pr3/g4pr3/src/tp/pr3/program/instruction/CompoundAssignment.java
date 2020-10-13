package tp.pr3.program.instruction;

import tp.pr3.bytecode.arithmetics.Add;
import tp.pr3.bytecode.arithmetics.Div;
import tp.pr3.bytecode.arithmetics.Mul;
import tp.pr3.bytecode.arithmetics.Sub;
import tp.pr3.bytecode.instructions.Store;
import tp.pr3.exceptions.ArrayException;
import tp.pr3.exceptions.NotFoundException;
import tp.pr3.program.LexicalParser;
import tp.pr3.program.instruction.term.Term;
import tp.pr3.program.instruction.term.TermParser;
import tp.pr3.program.Compiler;

/**
 * Clase que contiene objetos del tipo CompoundAssignment, que son asignaciones con una operacion.
 * @author Oscar Diaz Ribagorda y Mateo Garcia Perez.
 *
 */
public class CompoundAssignment implements Instruction {
	private String var_name;
	private String operator;
	private Term term1;
	private Term term2;
	

	/**
	 * {@inheritDoc}
	 */
	public Instruction lexParse(String[] words, LexicalParser lexparser) {
		if(words.length == 5 && words[0].length()==1){
			char name = words[0].charAt(0);
			Term t1= TermParser.parse(words[2]);
			Term t2= TermParser.parse(words[4]);
			if('a'<=name && name <='z' && opIsValid(words[3]) && t1 != null && t2 != null) {
				CompoundAssignment ca= new CompoundAssignment();
				ca.var_name=words[0];
				ca.operator= words[3];
				ca.term1 = t1;
				ca.term2 = t2;
				lexparser.increaseProgramCounter();
				return ca;
			}
			else return null;
		}
		else return null;
		
	}
	
	/**
	 * {@inheritDoc}
	 */
	public void compile(Compiler compile) throws ArrayException, NotFoundException {
		term1.compile(compile);
		term2.compile(compile);
		switch(operator){
			case "+":
				compile.addByteCode(new Add());
				break;
			case "-":
				compile.addByteCode(new Sub());
				break;
			case "/":
				compile.addByteCode(new Div());
				break;
			case "*":
				compile.addByteCode(new Mul());
				break;
		}
		int i= compile.getVarAlt(var_name);
		Store s= new Store(i);
		compile.addByteCode(s);
	}
	
	/**
	 * Metodo que comprueba si el string se corresponde con alguna operacion permitida.
	 * @param s
	 * @return boolean que dice si es valida la operacion.
	 */
	private boolean opIsValid(String s){
		return s.equals("+") || s.equals("-") || s.equals("/") || s.equals("*");
	}
}
