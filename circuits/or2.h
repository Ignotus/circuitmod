#pragma once
#include "icircuit.h"

DECLARE_CIRCUIT_CLASS(Or2)
{
    setState(key("Q"), state(key("A")) || state(key("B")));
}

template<>
void declareIO<Or2>(IConfig& config)
{
    config.declareInput("A");
    config.declareInput("B");
    config.declareOutput("Q");
}

