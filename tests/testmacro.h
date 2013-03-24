#pragma once
#define QVERIFY_THROW(expression, ExpectedExceptionType) \
    do \
    { \
        bool caught_ = false; \
        try { expression; } \
        catch (ExpectedExceptionType const&) { caught_ = true; } \
        catch (...) {} \
        if (!QTest::qVerify(caught_, #expression ", " #ExpectedExceptionType, "", __FILE__, __LINE__))\
            return; \
    } while (0)
    