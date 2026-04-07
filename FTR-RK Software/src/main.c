#include <stdio.h>
#include "globals.h"

int main() {
	
	//-----INITIALIZATION STEP-----
	
	//This Creates the Variable/Address space for the GLOBALCONTEXT and nested structs
	struct GlobalContext GLOBALCONTEXT;

	//This inializes the global struct to be all zero/null and allocates the memspace
	memset(&GLOBALCONTEXT, 0, sizeof(GLOBALCONTEXT));
	
	//Initializes the Thread safe lock by initializing its context
	InitializeCriticalSection(&GLOBALCONTEXT.buffer.lock);

	//Set the Global Context current state to STATE_INITIALIZING 
	GLOBALCONTEXT.currentState = STATE_INITIALIZING;

	//-----CONFICURATION STEP-----

	//Call Function from the XML PARSER / CREATOR

	





	// read if logging is true and create the indivudual thread if nessesary

	// change state to listening and create listnening thread

}