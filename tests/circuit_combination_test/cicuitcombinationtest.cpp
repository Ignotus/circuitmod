#include <QtTest>
#include <circuits/and2.h>
#include <circuits/not.h>
#include "cicuitcombinationtest.h"

void CicuitCombinationTest::combinationTest()
{
    And2 circuit1;
    Not circuit2;
    
    QCOMPARE(circuit1.inputs().size(), 2);
    QCOMPARE(circuit1.outputs().size(), 1);
    
    QCOMPARE(circuit2.inputs().size(), 1);
    QCOMPARE(circuit2.outputs().size(), 1);
    
    CircuitSlot slot(&circuit2, "A2");
    circuit1.subscribe("Q1", slot);
    
    const bool sigA[] = {true, true, false, false};
    const bool sigB[] = {true, false, true, false};
    for (int i = 0; i < 4; ++i)
    {
        QCOMPARE(circuit1.setSignal("A1", sigA[i]), true);
        QCOMPARE(circuit1.setSignal("B1", sigB[i]), true);
        
        QCOMPARE(circuit2.state("A2"), sigA[i] && sigB[i]);
        QCOMPARE(circuit2.state("Q2"), !(sigA[i] && sigB[i]));
    }
    
    circuit1.unsubscribe(slot);
    QCOMPARE(circuit1.setSignal("A1", true), true);
    QCOMPARE(circuit1.setSignal("B1", true), true);
    
    QVERIFY(circuit1.state("Q1") != circuit2.state("A2"));
}

QTEST_MAIN(CicuitCombinationTest)