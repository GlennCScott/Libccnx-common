/*
 * Copyright (c) 2014-2015, Xerox Corporation (Xerox)and Palo Alto Research Center (PARC)
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Patent rights are not granted under this agreement. Patent rights are
 *       available under FRAND terms.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL XEROX or PARC BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

// Include the file(s) containing the functions to be tested.
// This permits internal static functions to be visible to this Test Framework.
#include "../ccnxCodecSchemaV1_TlvDictionary.c"
#include <parc/algol/parc_SafeMemory.h>
#include <LongBow/unit-test.h>

LONGBOW_TEST_RUNNER(ccnxCodecSchemaV1_TlvDictionary)
{
    LONGBOW_RUN_TEST_FIXTURE(Global);
}

// The Test Runner calls this function once before any Test Fixtures are run.
LONGBOW_TEST_RUNNER_SETUP(ccnxCodecSchemaV1_TlvDictionary)
{
    parcMemory_SetInterface(&PARCSafeMemoryAsPARCMemory);
    return LONGBOW_STATUS_SUCCEEDED;
}

// The Test Runner calls this function once after all the Test Fixtures are run.
LONGBOW_TEST_RUNNER_TEARDOWN(ccnxCodecSchemaV1_TlvDictionary)
{
    return LONGBOW_STATUS_SUCCEEDED;
}

LONGBOW_TEST_FIXTURE(Global)
{
    LONGBOW_RUN_TEST_CASE(Global, ccnxCodecSchemaV1TlvDictionary_CreateInterest);
    LONGBOW_RUN_TEST_CASE(Global, ccnxCodecSchemaV1TlvDictionary_CreateInterestReturn);
    LONGBOW_RUN_TEST_CASE(Global, ccnxCodecSchemaV1TlvDictionary_CreateContentObject);
    LONGBOW_RUN_TEST_CASE(Global, ccnxCodecSchemaV1TlvDictionary_CreateControl);
}

LONGBOW_TEST_FIXTURE_SETUP(Global)
{
    return LONGBOW_STATUS_SUCCEEDED;
}

LONGBOW_TEST_FIXTURE_TEARDOWN(Global)
{
    if (parcSafeMemory_ReportAllocation(STDOUT_FILENO) != 0) {
        printf("('%s' leaks memory by %d (allocs - frees)) ", longBowTestCase_GetName(testCase), parcMemory_Outstanding());
        return LONGBOW_STATUS_MEMORYLEAK;
    }
    return LONGBOW_STATUS_SUCCEEDED;
}

LONGBOW_TEST_CASE(Global, ccnxCodecSchemaV1TlvDictionary_CreateInterest)
{
    CCNxTlvDictionary *test = ccnxCodecSchemaV1TlvDictionary_CreateInterest();
    assertNotNull(test, "Got null return from ccnxCodecSchemaV1TlvDictionary_CreateInterest");
    assertTrue(ccnxTlvDictionary_IsInterest(test), "Dictionary is not an interest");
    assertTrue(ccnxTlvDictionary_GetSchemaVersion(test) == CCNxTlvDictionary_SchemaVersion_V1,
               "Wrong schema version, expected %d got %d",
               CCNxTlvDictionary_SchemaVersion_V1,
               ccnxTlvDictionary_GetSchemaVersion(test));
    ccnxTlvDictionary_Release(&test);
}

LONGBOW_TEST_CASE(Global, ccnxCodecSchemaV1TlvDictionary_CreateInterestReturn)
{
    CCNxTlvDictionary *test = ccnxCodecSchemaV1TlvDictionary_CreateInterestReturn();
    assertNotNull(test, "Got null return from ccnxCodecSchemaV1TlvDictionary_CreateInterest");
    assertTrue(ccnxTlvDictionary_IsInterestReturn(test), "Dictionary is not an interest");
    assertTrue(ccnxTlvDictionary_GetSchemaVersion(test) == CCNxTlvDictionary_SchemaVersion_V1,
               "Wrong schema version, expected %d got %d",
               CCNxTlvDictionary_SchemaVersion_V1,
               ccnxTlvDictionary_GetSchemaVersion(test));
    ccnxTlvDictionary_Release(&test);
}

LONGBOW_TEST_CASE(Global, ccnxCodecSchemaV1TlvDictionary_CreateContentObject)
{
    CCNxTlvDictionary *test = ccnxCodecSchemaV1TlvDictionary_CreateContentObject();
    assertNotNull(test, "Got null return from ccnxCodecSchemaV1TlvDictionary_CreateContentObject");
    assertTrue(ccnxTlvDictionary_IsContentObject(test), "Dictionary is not a content object");
    assertTrue(ccnxTlvDictionary_GetSchemaVersion(test) == CCNxTlvDictionary_SchemaVersion_V1,
               "Wrong schema version, expected %d got %d",
               CCNxTlvDictionary_SchemaVersion_V1,
               ccnxTlvDictionary_GetSchemaVersion(test));
    ccnxTlvDictionary_Release(&test);
}

LONGBOW_TEST_CASE(Global, ccnxCodecSchemaV1TlvDictionary_CreateControl)
{
    CCNxTlvDictionary *test = ccnxCodecSchemaV1TlvDictionary_CreateControl();
    assertNotNull(test, "Got null return from ccnxCodecSchemaV1TlvDictionary_CreateControl");
    assertTrue(ccnxTlvDictionary_IsControl(test), "Dictionary is not a control");
    assertTrue(ccnxTlvDictionary_GetSchemaVersion(test) == CCNxTlvDictionary_SchemaVersion_V1,
               "Wrong schema version, expected %d got %d",
               CCNxTlvDictionary_SchemaVersion_V1,
               ccnxTlvDictionary_GetSchemaVersion(test));
    ccnxTlvDictionary_Release(&test);
}

int
main(int argc, char *argv[])
{
    LongBowRunner *testRunner = LONGBOW_TEST_RUNNER_CREATE(ccnxCodecSchemaV1_TlvDictionary);
    int exitStatus = longBowMain(argc, argv, testRunner, NULL);
    longBowTestRunner_Destroy(&testRunner);
    exit(exitStatus);
}
