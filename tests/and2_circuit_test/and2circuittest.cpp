#include <stdexcept>
#include <QtTest>
#include <and2circuit.h>
#include <testmacro.h>
#include "and2circuittest.h"

void And2CircuitTest::logicTestCase()
{
    And2Circuit circuit;
    const QList<QString>& input = circuit.inputs();
    const QList<QString>& output = circuit.outputs();
    
    QCOMPARE(input.size(), 2);
    QCOMPARE(output.size(), 1);
    
    const QString& firstPortName = input[0];
    const QString& secondPortName = input[1];
    const QString& outputPortName = output[0];
    
    QVERIFY_THROW(circuit["ABRACADABRA"], std::logic_error);
    
    for (int i = 0; i < 2; ++i)
    {
        for (int j = 0; j < 2; ++j)
        {
            const bool ib = static_cast<bool>(i);
            const bool jb = static_cast<bool>(i);
            circuit[firstPortName] = ib;
            circuit[secondPortName] = jb;
            
            QCOMPARE(ib && jb, circuit.state(outputPortName));
        }
    }
}

void And2CircuitTest::signalTestCase()
{
    And2Circuit circuit;
    const QList<QString>& input = circuit.inputs();
    const QList<QString>& output = circuit.outputs();
    const QString& firstPortName = input[0];
    const QString& secondPortName = input[1];
    const QString& outputPortName = output[0];
    
    QSignalSpy spy(&circuit, SIGNAL(onOutputChanged(const QString&, bool)));
    
    circuit.setSignal(firstPortName, false);
    QCOMPARE(spy.count(), 1);
    
    circuit.setSignal(outputPortName, true);
    QCOMPARE(spy.count(), 1);
    
    circuit[secondPortName] = true;
    QCOMPARE(spy.count(), 2);
}

QTEST_MAIN(And2CircuitTest)
