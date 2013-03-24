#include <QtTest>
#include <circuits/nand2.h>
#include <circuits/nor2.h>
#include <circuits/or2.h>
#include "circuittest.h"

#define TEST_ELEMENT(CLASS_NAME, FUNCTION) \
    CLASS_NAME circuit;\
    const bool i[] = {true, true, false, false};\
    const bool j[] = {true, false, true, false};\
    \
    const QList<QString>& output = circuit.outputs();\
    const QList<QString>& input = circuit.inputs();\
    const QString& firstPortName = input[0];\
    const QString& secondPortName = input[1];\
    const QString& outputPortName = output[0];\
    \
    for (int k = 0; k != sizeof(i) / sizeof(bool); ++k)\
    {\
        circuit.setSignal(firstPortName, i[k]);\
        circuit.setSignal(secondPortName, j[k]);\
        QCOMPARE(FUNCTION, circuit.state(outputPortName));\
    }

void CircuitTest::nand2Test()
{
    TEST_ELEMENT(NAnd2Circuit, !(i[k] && j[k]));
}

void CircuitTest::nor2Test()
{
    TEST_ELEMENT(NOr2Circuit, !(i[k] || j[k]));
}

void CircuitTest::or2Test()
{
    TEST_ELEMENT(Or2Circuit, i[k] || j[k]);
}

QTEST_MAIN(CircuitTest)