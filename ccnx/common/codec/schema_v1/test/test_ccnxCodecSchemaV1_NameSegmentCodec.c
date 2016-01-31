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
#include "../ccnxCodecSchemaV1_NameSegmentCodec.c"
#include <parc/algol/parc_SafeMemory.h>
#include <LongBow/unit-test.h>

#include <ccnx/common/codec/schema_v1/ccnxCodecSchemaV1_NameCodec.h>

LONGBOW_TEST_RUNNER(ccnxTlvCodec_Name)
{
    LONGBOW_RUN_TEST_FIXTURE(Global);
}

// The Test Runner calls this function once before any Test Fixtures are run.
LONGBOW_TEST_RUNNER_SETUP(ccnxTlvCodec_Name)
{
    parcMemory_SetInterface(&PARCSafeMemoryAsPARCMemory);
    return LONGBOW_STATUS_SUCCEEDED;
}

// The Test Runner calls this function once after all the Test Fixtures are run.
LONGBOW_TEST_RUNNER_TEARDOWN(ccnxTlvCodec_Name)
{
    return LONGBOW_STATUS_SUCCEEDED;
}

LONGBOW_TEST_FIXTURE(Global)
{
    LONGBOW_RUN_TEST_CASE(Global, ccnxTlvCodecNameSegment_Decode);
    LONGBOW_RUN_TEST_CASE(Global, ccnxTlvCodecNameSegment_Decode_TLShort);
    LONGBOW_RUN_TEST_CASE(Global, ccnxTlvCodecNameSegment_Decode_VShort);
    LONGBOW_RUN_TEST_CASE(Global, ccnxTlvCodecNameSegment_Decode);
    LONGBOW_RUN_TEST_CASE(Global, ccnxTlvCodecNameSegment_Encode);
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

LONGBOW_TEST_CASE(Global, ccnxTlvCodecNameSegment_Decode)
{
    PARCBuffer *buffer = parcBuffer_WrapCString("brandywine");
    CCNxNameSegment *truth = ccnxNameSegment_CreateTypeValue(CCNxNameLabelType_NAME, buffer);
    parcBuffer_Release(&buffer);

    uint8_t decodeBytes[] = { 0x00, CCNxNameLabelType_NAME, 0x00, 0x0A, 'b', 'r', 'a', 'n', 'd', 'y', 'w', 'i', 'n', 'e' };
    PARCBuffer *decodeBuffer = parcBuffer_Wrap(decodeBytes, sizeof(decodeBytes), 0, sizeof(decodeBytes));
    CCNxCodecTlvDecoder *decoder = ccnxCodecTlvDecoder_Create(decodeBuffer);
    CCNxNameSegment *test = ccnxCodecSchemaV1NameSegmentCodec_Decode(decoder);

    assertTrue(ccnxNameSegment_Equals(truth, test), "Name segments do not match");

    ccnxNameSegment_Release(&test);
    ccnxCodecTlvDecoder_Destroy(&decoder);
    parcBuffer_Release(&decodeBuffer);
    ccnxNameSegment_Release(&truth);
}

/**
 * In this case, there are not enough bytes in the buffer to decode the T and L
 */
LONGBOW_TEST_CASE(Global, ccnxTlvCodecNameSegment_Decode_TLShort)
{
    uint8_t decodeBytes[] = { 0x00, CCNxNameLabelType_NAME, 0x00, 0x0A, 'b', 'r', 'a' };
    PARCBuffer *decodeBuffer = parcBuffer_Wrap(decodeBytes, sizeof(decodeBytes), 0, sizeof(decodeBytes));
    CCNxCodecTlvDecoder *decoder = ccnxCodecTlvDecoder_Create(decodeBuffer);
    CCNxNameSegment *test = ccnxCodecSchemaV1NameSegmentCodec_Decode(decoder);

    assertNull(test, "Name segments should have been null because there are not enough bytes in buffer");

    ccnxCodecTlvDecoder_Destroy(&decoder);
    parcBuffer_Release(&decodeBuffer);
}

/**
 * In this case, we decode the T and L, but there are not enough bytes for the V
 */
LONGBOW_TEST_CASE(Global, ccnxTlvCodecNameSegment_Decode_VShort)
{
    uint8_t decodeBytes[] = { 0x00, CCNxNameLabelType_NAME, 0x00 };
    PARCBuffer *decodeBuffer = parcBuffer_Wrap(decodeBytes, sizeof(decodeBytes), 0, sizeof(decodeBytes));
    CCNxCodecTlvDecoder *decoder = ccnxCodecTlvDecoder_Create(decodeBuffer);
    CCNxNameSegment *test = ccnxCodecSchemaV1NameSegmentCodec_Decode(decoder);

    assertNull(test, "Name segments should have been null because there are not enough bytes in buffer");

    ccnxCodecTlvDecoder_Destroy(&decoder);
    parcBuffer_Release(&decodeBuffer);
}


LONGBOW_TEST_CASE(Global, ccnxTlvCodecNameSegment_Encode)
{
    uint8_t truthBytes[] = { 0x00, CCNxNameLabelType_NAME, 0x00, 0x0A, 'b', 'r', 'a', 'n', 'd', 'y', 'w', 'i', 'n', 'e' };
    PARCBuffer *truth = parcBuffer_Wrap(truthBytes, sizeof(truthBytes), 0, sizeof(truthBytes));

    CCNxCodecTlvEncoder *encoder = ccnxCodecTlvEncoder_Create();
    ccnxCodecTlvEncoder_Initialize(encoder);

    PARCBuffer *buffer = parcBuffer_WrapCString("brandywine");
    CCNxNameSegment *segment = ccnxNameSegment_CreateTypeValue(CCNxNameLabelType_NAME, buffer);
    parcBuffer_Release(&buffer);

    ccnxCodecSchemaV1NameSegmentCodec_Encode(encoder, segment);

    ccnxCodecTlvEncoder_Finalize(encoder);
    PARCBuffer *test = ccnxCodecTlvEncoder_CreateBuffer(encoder);
    assertTrue(parcBuffer_Equals(truth, test), "Buffers do not match");

    parcBuffer_Release(&test);
    ccnxNameSegment_Release(&segment);
    ccnxCodecTlvEncoder_Destroy(&encoder);
    parcBuffer_Release(&truth);
}

int
main(int argc, char *argv[argc])
{
    LongBowRunner *testRunner = LONGBOW_TEST_RUNNER_CREATE(ccnxTlvCodec_Name);
    int exitStatus = longBowMain(argc, argv, testRunner, NULL);
    longBowTestRunner_Destroy(&testRunner);
    exit(exitStatus);
}
