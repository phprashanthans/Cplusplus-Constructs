/*---------------------------------------------------------------------------------
How to create a simple watchdog for your application, so it will terminate if it gets 
blocked for more than a specified number of seconds ?
One simple approach is to set up a timer before a long task and disable it afterwards
If the delay is exceeded, the application will receive a SIGALRM signal and
terminate abnormally.
----------------------------------------------------------------------------------*/
#include <iostream>
#include <csignal>
#include <unistd.h>

// Watchdog timeout in seconds
constexpr unsigned int WATCHDOG_TIMEOUT = 5;

int main() {
    for(int i=1; i<=10; i++) {
        // Set the watchdog timer at the beginning of the loop
        alarm(WATCHDOG_TIMEOUT);
        std::cout << "Iteration " << i << ": Watchdog timer set for " << 
            WATCHDOG_TIMEOUT << " seconds.\n";
        
        // Simulate some work that might take varying time
        std::cout << "Working...\n";
        sleep(2);  // Simulate work that takes 2 second (within the watchdog limit)

        // Disable the watchdog timer at the end of loop
        alarm(0);
        std::cout << "Iteration " << i << " Watchdog timer cleared.\n\n";
    }
    std::cout << "All iterations completed successfully.\n";
}

/************************************************************************
Iteration 1: Watchdog timer set for 5 seconds.
Working...
Iteration 1 Watchdog timer cleared.

Iteration 2: Watchdog timer set for 5 seconds.
Working...
Iteration 2 Watchdog timer cleared.

Iteration 3: Watchdog timer set for 5 seconds.
Working...
Iteration 3 Watchdog timer cleared.

Iteration 4: Watchdog timer set for 5 seconds.
Working...
Iteration 4 Watchdog timer cleared.

Iteration 5: Watchdog timer set for 5 seconds.
Working...
Iteration 5 Watchdog timer cleared.

Iteration 6: Watchdog timer set for 5 seconds.
Working...
Iteration 6 Watchdog timer cleared.

Iteration 7: Watchdog timer set for 5 seconds.
Working...
Iteration 7 Watchdog timer cleared.

Iteration 8: Watchdog timer set for 5 seconds.
Working...
Iteration 8 Watchdog timer cleared.

Iteration 9: Watchdog timer set for 5 seconds.
Working...
Iteration 9 Watchdog timer cleared.

Iteration 10: Watchdog timer set for 5 seconds.
Working...
Iteration 10 Watchdog timer cleared.

All iterations completed successfully.
************************************************************************/
