#pragma once
#include "icircuit.h"

DECLARE_CONFIG(Or2Circuit)
{
    m_inputs[key("A")] = false;
    m_inputs[key("B")] = false;
    m_outputs[key("Q")] = false;
}

DECLARE_CIRCUIT_CLASS(Or2Circuit)
{
    setState(KEY(Or2Circuit, "Q"), state(KEY(Or2Circuit, "A")) || state(KEY(Or2Circuit, "B")));
}