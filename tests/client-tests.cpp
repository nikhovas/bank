#include <gtest/gtest.h>
#include <bank/exceptions.h>
#include <bank/DataSources/OperativeMemory/DataSource.h>
#include "helpers.h"


TEST(ClientTests, SimpleUserTest) {
    dsi::ITypeDataSource* storage = (new OperativeMemory::DataSource())->getClientStorage();
    Client* object = generateUser(storage, "1234", "F");
    ASSERT_EQ(object->object_id, 0);

    Client* object2 = dynamic_cast<Client*>(storage->getObject(0));
    ASSERT_EQ(object->passport, object2->passport);

    storage->deleteObject(object);

    ASSERT_THROW(storage->getObject(0), ObjectDoesNotExists);
}



TEST(ClientTests, TwoUsersDifferentIdsTest) {
    dsi::ITypeDataSource* storage = (new OperativeMemory::DataSource())->getClientStorage();
    Client* object = generateUser(storage, "1234", "F");
    ASSERT_EQ(object->object_id, 0);
    ASSERT_EQ(object->passport, "1234");

    Client* object2 = generateUser(storage, "1235", "F");
    ASSERT_EQ(object2->object_id, 1);
    ASSERT_EQ(object2->passport, "1235");
}