
#include <QtTest>
#include "generationhandler.h"
#include <unordered_set>

// add necessary includes here
using namespace time_line;
class test_generation : public QObject
{
    Q_OBJECT

public:
    test_generation();
    ~test_generation();

private slots:
    void test_bkmrk_generation();
private:
    GenerationHandler gen_handler;

};

test_generation::test_generation()
{

}

test_generation::~test_generation()
{

}

void test_generation::test_bkmrk_generation() {
    QApplication::setActiveWindow(&gen_handler);
    gen_handler.setNumOfBkmrs(0);
    gen_handler.startGeneration();
    connect(&gen_handler, &GenerationHandler::visibleObjsGenerated,
                [=](const VisibleObjs & res){
                    QCOMPARE_EQ(res.size(),0l);
                });

    size_t const num_of_tries = 99;
    for (size_t i = 0; i < num_of_tries; i ++) {
        gen_handler.setNumOfBkmrs(i);
        connect(&gen_handler, &GenerationHandler::visibleObjsGenerated,
                [i](const VisibleObjs & res){
                    QCOMPARE_EQ(res.size(),i);
                    std::unordered_set<int> result_bkmrks;
                    bool has_at_least_one_group = false;
                    for(auto& v : res) {
                        for(auto& idx : v.bkmrks_idxs) {
                            result_bkmrks.insert(idx);
                        }
                        QVERIFY(!v.bkmrks_idxs.empty());

                        //size of bkmrk no more than 3 hour
                        QCOMPARE_LT(v.start_millisec - v.end_millisec, 3 * 60 * 60 * 60);

                        if (!has_at_least_one_group && v.bkmrks_idxs.size() > 1) {
                            has_at_least_one_group = true;
                        }
                    }

                    //generated different expected num of bkmrks
                    QCOMPARE_EQ(result_bkmrks.size(),i);
                    if (i > 30){
                        QVERIFY(has_at_least_one_group);
                    }
                });
        gen_handler.startGeneration();
    }
}


//QTEST_APPLESS_MAIN(test_generation)
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TESTLIB_SELFCOVERAGE_START(test_generation)
    QT_PREPEND_NAMESPACE(QTest::Internal::callInitMain)<test_generation>();
    test_generation tc;
    QTEST_SET_MAIN_SOURCE_PATH
    return QTest::qExec(&tc, argc, argv);
}

#include "tst_test_generation.moc"
