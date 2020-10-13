package es.ucm.fdi.tp.mvc;

import java.util.ArrayList;

import es.ucm.fdi.tp.base.model.GameAction;
import es.ucm.fdi.tp.base.model.GameError;
import es.ucm.fdi.tp.base.model.GameState;

/**
 * Motor de juego.
 * Guarda el estado, y avisa a los observadores de cualquier cambio.
 * @author Oscar Diaz Ribagorda y Mateo Garcia Perez.
 */
public class GameTable<S extends GameState<S, A>, A extends GameAction<S, A>> implements GameObservable<S, A> {
	
	/**
	 * Guarda el estado inicial del juego al cual se vuelve si se
	 * reinicia el juego.
	 */
    private S initialState;
    /**
     * Guarda el estado actual del juego
     */
    private S state;
    /**
     * Lista con los observadores del modelo
     */
    private ArrayList<GameObserver<S, A>> observadores;
    /**
     * Indica si el juego está parado o no
     */
    boolean stop;

    /**
     * Inicializa el motor de juego
     * @param initState Estado inicial del juego
     */
    public GameTable(S initState) {
        initialState= initState;
        state= initState;
        observadores= new ArrayList<GameObserver<S,A>>();
        stop= true;
    }
    
    /**
     * Empieza el juego.
     * Copia el estado inicial al estado actual (por si se está reiniciando el juego)
     * y notifica a los observadores que se está iniciando el juego.
     */
    public void start() {
        state= initialState;
        stop= false;
        GameEvent<S,A> event= new GameEvent<S, A>(GameEvent.EventType.Start,null , initialState, null, "Starting game");
        this.notifyEvent(event);
    }
    
    /**
     * Para el juego.
     * Cambia el stop a verdadero.
     * No se puede parar un juego ya parado
     * @throws GameError si el juego ya está parado
     */
    public void stop() throws GameError {
       if(stop){
    	   GameError error= new GameError("Game already stopped");
    	   GameEvent<S,A> event= new GameEvent<S,A>(GameEvent.EventType.Error, null, state,error,"Stop Error");
    	   this.notifyEvent(event);
    	   throw error;
       }
       else{
    	   stop=true;
    	   GameEvent<S,A> event= new GameEvent<S,A>(GameEvent.EventType.Stop, null, state,null,"Game stopped");
    	   this.notifyEvent(event);
       }
    }
    
    /**
     * Ejecuta la accion dada en el estado actual..
     * No se puede ejecutar si el juego está ya parado o no iniciado
     * @throws GameError si el juego está parado, no iniciado o se produce un  error en l
     */
    public void execute(A action) throws GameError {
    	
    	if( state== null ||this.stop){
    		 GameError error;
    		if(state==null)
    			error= new GameError("Game not started");
    		else 
    			error= new GameError("Game stopped");
    		GameEvent<S,A> event= new GameEvent<S,A>(GameEvent.EventType.Error, null, state,error,"Error");
      	   	this.notifyEvent(event);
      	   	throw error;
    	 }
        try{
        	state= action.applyTo(state);
        	GameEvent<S,A> event= new GameEvent<S,A>(GameEvent.EventType.Change, action, state,null,"Action Executed");
     	   	this.notifyEvent(event);
        }
        catch(Exception e){
        	GameError error= new GameError("Executing error", e);
        	GameEvent<S,A> event= new GameEvent<S,A>(GameEvent.EventType.Error, null, state,error,"Error");
      	   	this.notifyEvent(event);
      	   	throw error;
        }    
    }
    /**
     * 
     * @return estado actual del juego
     */
    public S getState() {
		return state;
   
    }
    /**
     * Añade un observador a la lista
     */
    public void addObserver(GameObserver<S, A> o) {
        this.observadores.add(o);
    }
    /**
     * Elimina un observador de la lista
     */
    public void removeObserver(GameObserver<S, A> o) {
        this.observadores.remove(o);
    }
    
    /**
     * Notifica un evento a todos los observadores
     * @param event a notificar
     */
    private void notifyEvent(GameEvent<S,A> event){
    	 for(GameObserver<S, A> o : observadores)
         	o.notifyEvent(event);
    }
}
