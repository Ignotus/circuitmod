#include <stdexcept>
#include <QtTest>
#include <circuits/and2.h>
#include <testmacro.h>
#include "and2circuittest.h"

void And2CircuitTest::logicTestCase()
{
    And2 circuit;
    const QList<QString>& input = circuit.inputs();
    const QList<QString>& output = circuit.outputs();
    
    QCOMPARE(input.size(), 2);
    QCOMPARE(output.size(), 1);
    
    const QString& firstPortName = input[0];
    const QString& secondPortName = input[1];
    const QString& outputPortName = output[0];
    
    QVERIFY_THROW(circuit.state("ABRACADABRA"), std::logic_error);
    
    const bool i[] = {true, true, false, false};
    const bool j[] = {true, false, true, false};
    for (int k = 0; k != sizeof(i) / sizeof(bool); ++k)
    {
        circuit.setSignal(firstPortName, i[k]);
        circuit.setSignal(secondPortName, j[k]);
        QCOMPARE(i[k] && j[k], circuit.state(outputPortName));
    }
}

QTEST_MAIN(And2CircuitTest)
