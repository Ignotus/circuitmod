#pragma once
#include "icircuit.h"



DECLARE_CONFIG
{
    m_inputs[key("A")] = false;
    m_outputs[key("Q")] = true;
}

DECLARE_CIRCUIT_CLASS(NotCircuit)
{
    setState(KEY(NotCircuit, "Q"), !state(KEY(NotCircuit, "A")));
}