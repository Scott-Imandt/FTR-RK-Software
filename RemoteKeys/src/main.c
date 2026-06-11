#include "globals.h"
#include "ini-parser.h"
#include "logging-system.h"
#include "comm-bt-usb.h"
#include "keyboard-emulation.h"

#include <windows.h>
#include <stdio.h>
#include <stdbool.h>

// Forward declarations for clean structure
bool start_worker_threads(struct GlobalContext* ctx, HANDLE* threads); // This Creates worker threads for logging and serial listenting
void handle_runtime_monitoring(struct GlobalContext* ctx); // this handles the keyboard commands for KeyCommand Execution

int main() {
    // ==========================================
    // PHASE 1: BOOTSTRAP & STACK ZEROING
    //          Initialize structs and amd set initial states 
    // ==========================================

    struct GlobalContext ctx;
    memset(&ctx, 0, sizeof(struct GlobalContext));

    ctx.currentState = STATE_INITIALIZING;

    //Initialize the Critical Sections before threads are created
    InitializeCriticalSection(&ctx.buffer.lock);

    // ==========================================
    // PHASE 2: CONFIGURATION & SUBSYSTEM INIT
    //          1. Load configuration from INI
    //          2. Initialize Logging
    //          3. Initialize COM PORT
    // ==========================================


    // ==========================================
    // PHASE 3: THREAD CREATION & MONITORING
    //          Create 2 Additional Threads for a total of three threads running
    //              1-Main Thread(Responsibility: monitors the que and executes the windows API commands for window selection and keyboard execution)
    //             *2-Serial Listener Thread(Repsonsiblilty is to continously poll the com port for data comming from the esp32)
    //             *3-Logging Thread(Responsibilty: When enabled by the INI it records data based on device status and execution and periodicly flushed the data to a log file)
    // ==========================================


    // ==========================================
    // PHASE 4: SHUTDOWN & DEEP CLEAN
    //          Signal Threads to shutdown and wait for closures
    //          Release hardware/file resource (log file, free heap, deletecritivcalsection)
    // ==========================================


    //Free Heap allocated items
    free(ctx.config.commands);
    
    //Destroy Win32 Sync mechanisms last
    DeleteCriticalSection(&ctx.buffer.lock);
}