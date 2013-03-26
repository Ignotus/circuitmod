#pragma once
#include "icircuit.h"

DECLARE_CIRCUIT_CLASS(Not)
{
    setState(key("Q"), !state(key("A")));
}

template<>
void declareIO<Not>(IConfig& config)
{
    config.declareInput("A");
    config.declareOutput("Q");
}
