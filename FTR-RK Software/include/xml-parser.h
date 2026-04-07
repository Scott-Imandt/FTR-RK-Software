// This is the header file for the xml-parser.c

// This will be the header file for handling the reading of the xml File for setting configurations for the software application

#pragma once

#include "globals.h"
#include <stdbool.h>

typedef enum xmlState {
	XML_STATE_UNKNWON = 0,
	XML_STATE_SUCESS =-1, // Transition state to reach State_listening
	XML_STATE_FILE_NOT_FOUND=-2, // Call create_default_config
	XML_STATE_MEMORY_ERROR=-3,// Log "Out of Memory" and close program
	XML_STATE_SYNTEX_ERROR=-4 // Log "invalid XML and exit"
};


/*
*Checks if the config.xml file exists int he local directory and if it is valid[port number in range, triggerid in range, etc]
*Returns TRUE if found, false otherwise
*/
bool config_exists(const char* filename);

/*
*Creates a template XML file with default values
*Returns true if successful, false otherwise
*/
int create_default_config(const char* filename);

/*
* Opens the file
*		return error state if not possible
* Counts the key entries
*		return error stae if not possible
* Malloc memory for the app config keyCommands array
*		return error state if not possible
* populates the GlobalCONTEXT with the date read from the XML file
* 
*/
int load_config(struct GlobalContext* GLOBALCONTEXT, const char* filename);

/*
*Deep Cleans the Allocated memory for the XML keyboardCommands
* MUST BE CALLED DURING THE SHUTDOWN STATE
* Check if ctx->config.commands is NULL.
* Call free(ctx->config.commands).
* Set ctx->config.commands = NULL;.
* Set ctx->config.commandCount = 0;.
*/
void free_config(struct GlobalContext* GLOBALCONTEXT);