#define CTEST_MAIN
#define CTEST_SEGFAULT
#include "../../ctest/ctest.h"

#include "database.h"
#include "personEntry.h"

int main(int argc, const char *argv[]) {
    return ctest_main(argc, argv);
}

#define NAME_1 "Test Name"
#define PHONE_1 "+12345678900"

#define NAME_2 "Test Name 2"
#define PHONE_2 "+98765432100"

#define SAVE_PATH "test_tmp_db"

CTEST_DATA(databaseTests) {
    Database *database;
};

CTEST_SETUP(databaseTests) {
    data->database = createDatabase();
    ASSERT_NOT_NULL(data->database);
}

CTEST_TEARDOWN(databaseTests) {
    disposeDatabase(data->database);
}

CTEST2(databaseTests, addEntryTest) {
    PersonEntry entry = {
        .personName = strdup(NAME_1),
        .phoneNumber = strdup(PHONE_1)
    };

    ASSERT_TRUE(addEntry(data->database, entry));
    ASSERT_STR(data->database->entries[data->database->entriesCount - 1].personName, NAME_1);
    ASSERT_STR(data->database->entries[data->database->entriesCount - 1].phoneNumber, PHONE_1);
}

CTEST2(databaseTests, addEntryTest2) {
    PersonEntry entry = {
        .personName = strdup(NAME_2),
        .phoneNumber = strdup(PHONE_2)
    };

    ASSERT_TRUE(addEntry(data->database, entry));
    ASSERT_STR(data->database->entries[data->database->entriesCount - 1].personName, NAME_2);
    ASSERT_STR(data->database->entries[data->database->entriesCount - 1].phoneNumber, PHONE_2);
}

CTEST2(databaseTests, saveDatabaseTest) {
    FILE *file = fopen(SAVE_PATH, "w");
    ASSERT_NOT_NULL(file);

    ASSERT_TRUE(saveDatabase(file, data->database));
    ASSERT_EQUAL(fclose(file), 0);
}

CTEST2(databaseTests, loadDatabaseTest) {
    FILE *file = fopen(SAVE_PATH, "r");
    ASSERT_NOT_NULL(file);

    Database *database2 = loadDatabase(file);

    ASSERT_NOT_NULL(database2);
    ASSERT_EQUAL(fclose(file), 0);

    ASSERT_EQUAL(data->database->entriesCount, database2->entriesCount);
    for (int i = 0; i < data->database->entriesCount; ++i) {
        PersonEntry entry = data->database->entries[i],
            entry2 = database2->entries[i];
        ASSERT_STR(entry.personName, entry2.personName);
        ASSERT_STR(entry.phoneNumber, entry2.phoneNumber);
    }

    disposeDatabase(database2);
    ASSERT_EQUAL(remove(SAVE_PATH), 0);
}

CTEST(phoneParsingTest, incorrectPhoneTest) {
    PhoneNumber phoneNumber;
    ASSERT_FALSE(tryParsePhoneNumber("0--0", &phoneNumber));
}

CTEST(phoneParsingTest, incorrectPhoneTest2) {
    PhoneNumber phoneNumber;
    ASSERT_FALSE(tryParsePhoneNumber("+1 ((12))-14", &phoneNumber));
}

CTEST(phoneParsingTest, incorrectPhoneTest3) {
    PhoneNumber phoneNumber;
    ASSERT_FALSE(tryParsePhoneNumber("834-14-", &phoneNumber));
}

CTEST(phoneParsingTest, correctPhoneTest) {
    PhoneNumber phoneNumber;
    ASSERT_TRUE(tryParsePhoneNumber("135-67-54", &phoneNumber));
}

CTEST(phoneParsingTest, correctPhoneTest2) {
    PhoneNumber phoneNumber;
    ASSERT_TRUE(tryParsePhoneNumber("(135) 67 54", &phoneNumber));
}

CTEST(phoneParsingTest, correctPhoneTest3) {
    PhoneNumber phoneNumber;
    ASSERT_TRUE(tryParsePhoneNumber("+5 (432) 234 67-54", &phoneNumber));
}
