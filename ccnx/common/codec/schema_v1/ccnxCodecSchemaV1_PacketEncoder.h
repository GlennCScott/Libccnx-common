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
/**
 * @file ccnxCodecSchemaV1_PacketEncoder.h
 * @brief Encoder for the version 1 TLV Packet
 *
 * Example:
 * @code
 * {
 * }
 * @endcode
 *
 * @author Marc Mosko, Palo Alto Research Center (Xerox PARC)
 * @copyright 2014-2015, Xerox Corporation (Xerox)and Palo Alto Research Center (PARC).  All rights reserved.
 */

#ifndef CCNxCodecSchemaV1_PacketEncoder_h
#define CCNxCodecSchemaV1_PacketEncoder_h

#include <parc/algol/parc_Buffer.h>
#include <parc/security/parc_Signer.h>

#include <ccnx/common/internal/ccnx_TlvDictionary.h>
#include <ccnx/common/codec/ccnxCodec_TlvEncoder.h>
#include <ccnx/common/codec/ccnxCodec_EncodingBuffer.h>
#include <ccnx/common/codec/ccnxCodec_NetworkBuffer.h>

/**
 * Encode the packetDictionary to wire format
 *
 * Will only use the PacketType from FixedHeader in the dictionary, if provided.  The packet Version is fixed at "1",
 * the PayloadLength and HeaderLength are calculated.  If the FixedHeaderDictionary is not provided, the
 * PacketType is inferred from the type of CCNx message.
 *
 * The signer is not stored beyond the call to DictionaryEncode.
 * If the dictionary already has a ValidationAlg and ValidationPayload, those are used, not the Signer.
 * Otherwise, if the signer is not null, it is used to sign the wire format.
 *
 * @param [in] packetDictionary The dictionary representation of the packet to encode
 * @param [in] signer If not NULL will be used to sign the wire format
 *
 * @retval non-null An IoVec that can be written to the network
 * @retval null an error
 *
 * Example:
 * @code
 * <#example#>
 * @endcode
 */
CCNxCodecNetworkBufferIoVec *ccnxCodecSchemaV1PacketEncoder_DictionaryEncode(CCNxTlvDictionary *packetDictionary, PARCSigner *signer);

/**
 * Encode a packetDictionary to wire format.
 *
 * Will only use the PacketType from FixedHeader in the dictionary, if provided.  The packet Version is fixed at "1",
 * the PayloadLength and HeaderLength are calculated.  If the FixedHeaderDictionary is not provided, the
 * PacketType is inferred from the type of CCNx message.
 *
 * You must use ccnxCodecTlvEncoder_SetSigner(signer) if you require a signature or MAC on the packet.
 *
 * @param [in] packetEncoder A TLV packet will be appended to the encoder
 * @param [in] packetDictionary The dictionary representation of the packet to encode
 *
 * @retval non-negative The total bytes appended to the encode buffer
 * @retval -1 An error
 *
 * Example:
 * @code
 * <#example#>
 * @endcode
 */
ssize_t ccnxCodecSchemaV1PacketEncoder_Encode(CCNxCodecTlvEncoder *packetEncoder, CCNxTlvDictionary *packetDictionary);

#endif // CCNxCodecSchemaV1_PacketEncoder_h
