#include "nand2.h"

DECLARE_CIRCUIT_CLASS_IMPL(NAnd2)
{
    setState(key("Q"), !(state(key("A")) && state(key("B"))));
}

template<>
void declareIO<NAnd2>(IConfig& config)
{
    config.declareInput("A");
    config.declareInput("B");
    config.declareOutput("Q");
}