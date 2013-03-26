#pragma once
#include "config.h"
#include "icircuit.h"

DECLARE_CIRCUIT_CLASS(And2)
{
    setState(key("Q"), state(key("A")) && state(key("B")));
}

template<>
void declareIO<And2>(IConfig& config)
{
    config.declareInput("A");
    config.declareInput("B");
    config.declareOutput("Q");
}
