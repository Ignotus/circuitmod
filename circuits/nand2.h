#pragma once
#include "icircuit.h"

DECLARE_CONFIG(NAnd2Circuit)
{
    m_inputs[key("A")] = false;
    m_inputs[key("B")] = false;
    m_outputs[key("Q")] = true;
}

DECLARE_CIRCUIT_CLASS(NAnd2Circuit)
{
    setState(KEY(NAnd2Circuit, "Q"), !(state(KEY(NAnd2Circuit, "A")) && state(KEY(NAnd2Circuit, "B"))));
}