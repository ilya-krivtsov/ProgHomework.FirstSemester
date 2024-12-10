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

Database *createNewDatabase(void) {
    Database *db = createDatabase();
    ASSERT_NOT_NULL(db);
    return db;
}

void assertAddEntry(Database *database, const char *personName, const PhoneNumber phoneNumber) {
    PersonEntry entry = {
        .personName = strdup(personName),
        .phoneNumber = strdup(phoneNumber)
    };

    ASSERT_TRUE(addEntry(database, entry));
    ASSERT_STR(database->entries[database->entriesCount - 1].personName, personName);
    ASSERT_STR(database->entries[database->entriesCount - 1].phoneNumber, phoneNumber);
}

void assertAddNamesAndPhones(Database *db) {
    assertAddEntry(db, NAME_1, PHONE_1);
    assertAddEntry(db, NAME_2, PHONE_2);
}

void assertSave(Database *db) {
    FILE *file = fopen(SAVE_PATH, "w");
    ASSERT_NOT_NULL(file);

    ASSERT_TRUE(saveDatabase(file, db));
    ASSERT_EQUAL(fclose(file), 0);
}

Database *loadTestDatabase(void) {
    FILE *file = fopen(SAVE_PATH, "r");
    ASSERT_NOT_NULL(file);

    Database *db = loadDatabase(file);

    ASSERT_NOT_NULL(db);
    ASSERT_EQUAL(fclose(file), 0);
    return db;
}

CTEST(databaseTests, addEntriesTest) {
    Database *db = createNewDatabase();
    assertAddNamesAndPhones(db);
    disposeDatabase(db);
}

CTEST(databaseTests, saveDatabaseTest) {
    Database *db = createNewDatabase();

    assertAddNamesAndPhones(db);
    assertSave(db);

    disposeDatabase(db);
}

CTEST(databaseTests, loadDatabaseTest) {
    Database *db = createNewDatabase();

    assertAddNamesAndPhones(db);
    assertSave(db);

    Database *db2 = loadTestDatabase();

    ASSERT_EQUAL(db->entriesCount, db2->entriesCount);
    for (int i = 0; i < db->entriesCount; ++i) {
        PersonEntry entry = db->entries[i],
            entry2 = db2->entries[i];
        ASSERT_STR(entry.personName, entry2.personName);
        ASSERT_STR(entry.phoneNumber, entry2.phoneNumber);
    }

    disposeDatabase(db2);
    ASSERT_EQUAL(remove(SAVE_PATH), 0);

    disposeDatabase(db);
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
