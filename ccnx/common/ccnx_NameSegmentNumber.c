/*
 * Copyright (c) 2013-2015, Xerox Corporation (Xerox)and Palo Alto Research Center (PARC)
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
/**
 * @author Glenn Scott, Palo Alto Research Center (Xerox PARC)
 * @copyright 2013-2015, Xerox Corporation (Xerox)and Palo Alto Research Center (PARC).  All rights reserved.
 */
#include <config.h>
#include <LongBow/runtime.h>

#include <ccnx/common/ccnx_NameSegmentNumber.h>
#include <ccnx/common/ccnx_NameSegment.h>

#include <parc/algol/parc_Buffer.h>
#include <parc/algol/parc_BufferComposer.h>

bool
ccnxNameSegmentNumber_IsValid(const CCNxNameSegment *nameSegment)
{
    bool result = false;

    size_t remaining = parcBuffer_Remaining(ccnxNameSegment_GetValue(nameSegment));
    if (remaining > 0 && remaining < 8) {
        result = true;
    }

    return result;
}

void
ccnxNameSegmentNumber_AssertValid(const CCNxNameSegment *nameSegment)
{
    assertTrue(ccnxNameSegmentNumber_IsValid(nameSegment), "Encountered an invalid CCNxNameSegment");
}

CCNxNameSegment *
ccnxNameSegmentNumber_Create(CCNxNameLabelType type, uint64_t value)
{
    PARCBufferComposer *composer = parcBufferComposer_Create();

    bool mustContinue = false;
    for (int byte = 7; byte >= 0; byte--) {
        uint8_t b = (value >> (byte * 8)) & 0xFF;
        if (b != 0 || byte == 0 || mustContinue) {
            parcBufferComposer_PutUint8(composer, b);
            mustContinue = true;
        }
    }
    PARCBuffer *buffer = parcBuffer_Flip(parcBufferComposer_GetBuffer(composer));
    CCNxNameSegment *segment = ccnxNameSegment_CreateTypeValue(type, buffer);
    parcBufferComposer_Release(&composer);

    return segment;
}

uint64_t
ccnxNameSegmentNumber_Value(const CCNxNameSegment *nameSegment)
{
    const PARCBuffer *buffer = ccnxNameSegment_GetValue(nameSegment);

    uint64_t result = 0;

    for (size_t i = 0; i < parcBuffer_Remaining(buffer); i++) {
        result = (result << 8) | parcBuffer_GetAtIndex(buffer, i);
    }
    return result;
}