
#include "generationhandler.h"
#include "viewhandler.h"
#include <QtTest>
#include <chrono>
#include <thread>
#include <unordered_set>

// add necessary includes here
using namespace time_line;
class test_generation : public QObject {
  Q_OBJECT

public:
  test_generation() = default;
  ~test_generation() = default;

private slots:
  void test_bkmrk_generation();
  void test_generation_of_draw_objs();
};

void test_generation::test_generation_of_draw_objs() {
  ViewHandler view_handler;
  GenerationHandler gen_handler;
  connect(&gen_handler, &GenerationHandler::visibleObjsGenerated, &view_handler,
          &ViewHandler::drawVisibleObjects);

  gen_handler.setNumOfBkmrs(0);
  gen_handler.startGeneration();
  QCOMPARE_EQ(view_handler.get_visible_widgets().size(), 0ul);

  size_t const num_of_tries = 500;

  for (size_t i = 1; i < num_of_tries; i *= 2) {
    gen_handler.setNumOfBkmrs(i);
    gen_handler.startGeneration();
    std::this_thread::sleep_for(std::chrono::seconds(2));
    auto vis_objs = view_handler.get_visible_widgets();
    QCOMPARE_LE(vis_objs.size(), i);

    if (i > 30) {
      // must have at least one group
      QCOMPARE_LT(vis_objs.size(), i);
    }
  }
}

void test_generation::test_bkmrk_generation() {
  GenerationHandler gen_handler;
  gen_handler.setNumOfBkmrs(0);
  connect(&gen_handler, &GenerationHandler::visibleObjsGenerated,
          [this](const VisibleObjs &res) { QCOMPARE_EQ(res.size(), 0ul); });
  gen_handler.startGeneration();
  gen_handler.disconnect();

  size_t const num_of_tries = 500;
  for (size_t i = 1; i < num_of_tries; i *= 2) {
    gen_handler.setNumOfBkmrs(i);
    connect(&gen_handler, &GenerationHandler::visibleObjsGenerated,
            [this, i](const VisibleObjs &res) {
              QCOMPARE_EQ(res.size(), i);
              std::unordered_set<int> result_bkmrks;
              for (auto &v : res) {
                for (auto &idx : v.bkmrks_idxs) {
                  result_bkmrks.insert(idx);
                }
                QVERIFY(!v.bkmrks_idxs.empty());

                // size of bkmrk no more than 3 hour
                QCOMPARE_LT(v.start_millisec - v.end_millisec,
                            3 * 60 * 60 * 60);
              }

              // there are no reapeted bkmrk idx
              QCOMPARE_EQ(result_bkmrks.size(), i);
            });
    gen_handler.startGeneration();
    std::this_thread::sleep_for(std::chrono::seconds(3));
    gen_handler.disconnect();
  }
}

// QTEST_APPLESS_MAIN(test_generation)
int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  TESTLIB_SELFCOVERAGE_START(test_generation)
  QT_PREPEND_NAMESPACE(QTest::Internal::callInitMain)<test_generation>();
  test_generation tc;
  QTEST_SET_MAIN_SOURCE_PATH
  return QTest::qExec(&tc, argc, argv);
}

#include "tst_test_generation.moc"
