#include <iostream>

#include "command.h"
#include "observer.h"
#include "chainOfResp.h"

int main()
{    
    StartCommandLogger();
    StartObserverLogger();
    StartChainOfResponsobilityLogger();
}