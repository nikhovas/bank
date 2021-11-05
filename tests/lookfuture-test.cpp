#include <bank/DataSources/OperativeMemory/DataSource.h>
#include <gtest/gtest.h>


using namespace DatabaseObjects;


TEST(LookFutureTests, DebitSimple) {
    DebitAccount* object = new DebitAccount();

    date today = day_clock::local_day();

    object->opened_date = today - date_duration(5);
    object->interest_rate = 3.65;
    object->accumulated = 0;
    object->money = 1000;

    date future_moment = today + date_duration(5);
    int n_days = 10;

    auto future_object = object->lookFuture(future_moment, date_duration(n_days));

    ASSERT_EQ(future_object->money, 1050);
}

TEST(LookFutureTests, Debit) {
    DebitAccount* object = new DebitAccount();

    date today = day_clock::local_day();

    object->opened_date = today - date_duration(5);
    object->interest_rate = 3.65;
    object->accumulated = 0;
    object->money = 1000;

    date future_moment = today + date_duration(30);
    int n_days = 10;

    auto future_object = object->lookFuture(future_moment, date_duration(n_days));

    ASSERT_DOUBLE_EQ(future_object->money, 1270.5);
}

TEST(LookFutureTests, DebitWithAccumulated) {
    DebitAccount* object = new DebitAccount();
    date today = day_clock::local_day();
    object->opened_date = today - date_duration(5);
    object->interest_rate = 3.65;
    object->accumulated = 500;
    object->money = 1000;
    date future_moment = today + date_duration(30);
    int n_days = 10;

    auto future_object = object->lookFuture(future_moment, date_duration(n_days));

    ASSERT_DOUBLE_EQ(future_object->money, 1875.5);
}


TEST(LookFutureTests, DebitOneDayPeriod) {
    DebitAccount* object = new DebitAccount();
    date today = day_clock::local_day();
    object->opened_date = today - date_duration(5);
    object->interest_rate = 3.65;
    object->accumulated = 500;
    object->money = 1000;
    date future_moment = today + date_duration(2);
    int n_days = 1;


    auto future_object = object->lookFuture(future_moment, date_duration(n_days));

    ASSERT_DOUBLE_EQ(future_object->money, 1500 * pow(1 + 0.01, 2));
}

TEST(LookFutureTests, Deposit) {
    DepositAccount* object = new DepositAccount();
    date today = day_clock::local_day();
    object->opened_date = today;
    object->interest_rate = 3.65;
    object->accumulated = 0;
    object->money = 1000;
    object->end_date = object->opened_date + date_duration(30);
    date future_moment = today + date_duration(40);
    int n_days = 30;
    auto future_object = object->lookFuture(future_moment, date_duration(n_days));

    ASSERT_DOUBLE_EQ(future_object->money, 1300);
}