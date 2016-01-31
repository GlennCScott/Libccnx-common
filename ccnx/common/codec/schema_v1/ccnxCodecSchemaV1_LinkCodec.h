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
 * @file ccnxCodecSchemaV1_LinkCodec.h
 * @brief A Link is a well-known value, not a TLV field
 *
 * A Link may be the "value" of a TLV element, such as the KeyName.  It can also occur
 * in the payload of a ContentObject whose PayloadType is Link.
 *
 * @author Marc Mosko, Palo Alto Research Center (Xerox PARC)
 * @copyright 2013-2015, Xerox Corporation (Xerox)and Palo Alto Research Center (PARC).  All rights reserved.
 */

#ifndef __CCNx_Common__ccnxCodecSchemaV1_LinkCodec__
#define __CCNx_Common__ccnxCodecSchemaV1_LinkCodec__

#include <ccnx/common/ccnx_Link.h>
#include <ccnx/common/codec/ccnxCodec_TlvEncoder.h>
#include <ccnx/common/codec/ccnxCodec_TlvDecoder.h>

/**
 * Encodes the link, but without a "TL" container
 *
 * Will append the Link in it's well-known TLV format, but without any
 * "TL" container.
 *
 * If the link does not have a name, will return -1 with the error TLV_MISSING_MANDATORY.
 *
 * @param [in] encoder The link will be appended to the encoder
 * @param [in] link The link to append
 *
 * @retval non-negative The number of bytes appended to the encoder
 * @retval negative An error, look at the CCNxCodecError of the encoder
 *
 * Example:
 * @code
 * <#example#>
 * @endcode
 */
ssize_t ccnxCodecSchemaV1LinkCodec_Encode(CCNxCodecTlvEncoder *encoder, const CCNxLink *link);

/**
 * The decoder points to the first byte of the "value" of something that is a Link
 *
 * For a KeyName, decoder should be pointed to the "value" of the KeyName.  for a ContentObject
 * of type Link, it should be the first byte of the Payload.
 *
 * A link is the tuple {Name, [KeyId], [Hash]}, where KeyId is the keyIdRestriction and
 * Hash is the ContentObjectHash restriction to use in an Interest for Name.
 * No additional fields are allowed in the Link.
 *
 * @param [in] decoder The Tlv Decoder pointing to the start of the Name value
 * @param [in] length the length of the Link value
 *
 * @return non-null A parsed name
 * @return null An error, check the decoder's error message
 *
 * Example:
 * @code
 * <#example#>
 * @endcode
 */
CCNxLink *ccnxCodecSchemaV1LinkCodec_DecodeValue(CCNxCodecTlvDecoder *decoder, uint16_t length);

#endif /* defined(__CCNx_Common__ccnxCodecSchemaV1_LinkCodec__) */