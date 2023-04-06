
#include <QtTest>

// add necessary includes here

class test_generation : public QObject
{
    Q_OBJECT

public:
    test_generation();
    ~test_generation();

private slots:
    void test_case1();

};

test_generation::test_generation()
{

}

test_generation::~test_generation()
{

}

void test_generation::test_case1()
{
//    QLineEdit lineEdit;

//    QTest::keyClicks(&lineEdit, "hello world");

//    QCOMPARE(lineEdit.text(), QString("hello world"));
}

QTEST_APPLESS_MAIN(test_generation)

#include "tst_test_generation.moc"
