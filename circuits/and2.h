#pragma once
#include "icircuit.h"

DECLARE_CONFIG(And2Circuit)
{
    m_inputs[key("A")] = false;
    m_inputs[key("B")] = false;
    m_outputs[key("Q")] = false;
}

DECLARE_CIRCUIT_CLASS(And2Circuit)
{
    setState(KEY(And2Circuit, "Q"), state(KEY(And2Circuit, "A")) && state(KEY(And2Circuit, "B")));
}