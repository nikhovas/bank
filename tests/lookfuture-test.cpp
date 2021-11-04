#include <bank/DataSources/OperativeMemory/DataSource.h>
#include <gtest/gtest.h>
//#include "helpers.h"


using namespace DatabaseObjects;


TEST(LookFutureTests, getPaymentsBound) {
    DebitAccount* object = new DebitAccount();
    date today = day_clock::local_day();
    object->opened_date = date(2021, 11, 1);
    auto res = object->getPaymentsBound(today, date(2021, 12, 3), date_duration(10));

    ASSERT_EQ(res.closest_payment, date(2021, 11, 11));
    ASSERT_EQ(res.latest_payment, date(2021, 12, 1));
}


TEST(LookFutureTests, getPaymentsBoundOpenedToday) {
    DebitAccount* object = new DebitAccount();
    date today = day_clock::local_day();
    object->opened_date = today;
    date future_moment = today + date_duration(30);
    auto res = object->getPaymentsBound(today, future_moment, date_duration(10));

    ASSERT_EQ(res.closest_payment, today);
}

TEST(LookFutureTests, getPaymentsBoundOneDayInterval) {
    DebitAccount* object = new DebitAccount();
    date today = day_clock::local_day();
    object->opened_date = today - date_duration(30);
    date future_moment = today + date_duration(30);
    int n_days = 1;
    auto res = object->getPaymentsBound(today, future_moment, date_duration(n_days));

    ASSERT_EQ(res.closest_payment, today);
    ASSERT_EQ(res.latest_payment, future_moment);
}

TEST(LookFutureTests, getPaymentsBoundTestDiff) {
    ASSERT_EQ(date(2021, 11, 16) - date(2021, 11, 10), date_duration(6));
    ASSERT_EQ(date(2021, 12, 01) - date(2021, 11, 10), date_duration(21));
}

TEST(LookFutureTests, DebitVerySimple) {
    DebitAccount* object = new DebitAccount();

    date today = day_clock::local_day();

    object->opened_date = today - date_duration(5);
    object->interest_rate = 3.65;
    object->accumulated = 0;
    object->money = 1000;

    date future_moment = today + date_duration(5);
    int n_days = 10;

    auto res = object->getPaymentsBound(today, future_moment, date_duration(n_days));

    ASSERT_EQ(res.closest_payment, today + date_duration(5));
    ASSERT_EQ(res.latest_payment, today + date_duration(5));

    auto future_object = object->lookFuture(future_moment, date_duration(n_days));

    ASSERT_EQ(future_object->money, 1050);
}

TEST(LookFutureTests, DebitSimple) {
    DebitAccount* object = new DebitAccount();

    date today = day_clock::local_day();

    object->opened_date = today - date_duration(5);
    object->interest_rate = 3.65;
    object->accumulated = 0;
    object->money = 1000;

    date future_moment = today + date_duration(30);
    int n_days = 10;

    auto res = object->getPaymentsBound(today, future_moment, date_duration(n_days));

    ASSERT_EQ(res.closest_payment, today + date_duration(5));
    ASSERT_EQ(res.latest_payment, today + date_duration(25));
    ASSERT_EQ(res.num_payments, 3);

    auto future_object = object->lookFuture(future_moment, date_duration(n_days));

    ASSERT_DOUBLE_EQ(future_object->money, 1270.5);
}

TEST(LookFutureTests, DebitSimpleWithAccumulated) {
    DebitAccount* object = new DebitAccount();
    date today = day_clock::local_day();
    object->opened_date = today - date_duration(5);
    object->interest_rate = 3.65;
    object->accumulated = 500;
    object->money = 1000;
    date future_moment = today + date_duration(30);
    int n_days = 10;
    auto res = object->getPaymentsBound(today, future_moment, date_duration(n_days));

    ASSERT_EQ(res.closest_payment, today + date_duration(5));
    ASSERT_EQ(res.latest_payment, today + date_duration(25));
    ASSERT_EQ(res.num_payments, 3);

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
    auto res = object->getPaymentsBound(today, future_moment, date_duration(n_days));

    ASSERT_EQ(res.closest_payment, today);
    ASSERT_EQ(res.latest_payment, future_moment);
    ASSERT_EQ(res.num_payments, 3);

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