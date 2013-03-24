#pragma once
#include "icircuit.h"

DECLARE_CONFIG(NOr2Circuit)
{
    m_inputs[key("A")] = false;
    m_inputs[key("B")] = false;
    m_outputs[key("Q")] = true;
}

DECLARE_CIRCUIT_CLASS(NOr2Circuit)
{
    setState(KEY(NOr2Circuit, "Q"), !(state(KEY(NOr2Circuit, "A")) || state(KEY(NOr2Circuit, "B"))));
}