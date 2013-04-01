#include "not.h"

DECLARE_CIRCUIT_CLASS_IMPL(Not)
{
    setState(key("Q"), !state(key("A")));
}

template<>
void declareIO<Not>(IConfig& config)
{
    config.declareInput("A");
    config.declareOutput("Q");
}