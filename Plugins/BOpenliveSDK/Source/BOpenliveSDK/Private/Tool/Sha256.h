// Copyright 2022 Tangcl, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#define SHA256_BLOCK_SIZE  ( 512 / 8)
#define SHA256_DIGEST_SIZE (256 / 8)

namespace ogayImpl
{
	/*
	* FIPS 180-2 SHA-224/256/384/512 implementation
	* Last update: 02/02/2007
	* Issue date:  04/30/2005
	*
	* Copyright (C) 2005, 2007 Olivier Gay <olivier.gay@a3.epfl.ch>
	* All rights reserved.
	*
	* Redistribution and use in source and binary forms, with or without
	* modification, are permitted provided that the following conditions
	* are met:
	* 1. Redistributions of source code must retain the above copyright
	*    notice, this list of conditions and the following disclaimer.
	* 2. Redistributions in binary form must reproduce the above copyright
	*    notice, this list of conditions and the following disclaimer in the
	*    documentation and/or other materials provided with the distribution.
	* 3. Neither the name of the project nor the names of its contributors
	*    may be used to endorse or promote products derived from this software
	*    without specific prior written permission.
	*
	* THIS SOFTWARE IS PROVIDED BY THE PROJECT AND CONTRIBUTORS ``AS IS'' AND
	* ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
	* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
	* ARE DISCLAIMED.  IN NO EVENT SHALL THE PROJECT OR CONTRIBUTORS BE LIABLE
	* FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
	* DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
	* OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
	* HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
	* LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
	* OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
	* SUCH DAMAGE.
	*/

	typedef struct {
		unsigned int tot_len;
		unsigned int len;
		unsigned char block[2 * SHA256_BLOCK_SIZE];
		uint32 h[8];
	} sha256_ctx;

	typedef struct {
		sha256_ctx ctx_inside;
		sha256_ctx ctx_outside;

		/* for hmac_reinit */
		sha256_ctx ctx_inside_reinit;
		sha256_ctx ctx_outside_reinit;

		unsigned char block_ipad[SHA256_BLOCK_SIZE];
		unsigned char block_opad[SHA256_BLOCK_SIZE];
	} hmac_sha256_ctx;
}

class SHA256Key
{
	friend class SHA256;
	friend class HMAC_SHA256;
	uint8 m_KeyBytes[SHA256_DIGEST_SIZE];
public:
	bool operator==(const SHA256Key& rOther) const;
	bool operator!=(const SHA256Key& rOther) const;
	void operator=(const SHA256Key& rOther);
	SHA256Key() {}
	SHA256Key(const SHA256Key& rOther)
	{
		*this = rOther;
	}
	FString ToHexString();
	void FromStringKey(const FString&);
};

class SHA256
{
	ogayImpl::sha256_ctx m_Context;
public:
	void Init();
	void Update(const unsigned char* message, unsigned int len);
	void Update(const FString& rStr);
	void Final(unsigned char* digest, int digestsize);
	SHA256Key Final();
	SHA256()
	{
		Init();
	}

	static SHA256Key Hash(const FString& rStr)
	{
		SHA256 tmp;
		tmp.Update(rStr);
		return tmp.Final();
	}

	static SHA256Key Hash(const unsigned char* message, unsigned int len)
	{
		SHA256 tmp;
		tmp.Update(message, len);
		return tmp.Final();
	}
};

class HMAC_SHA256
{
	ogayImpl::hmac_sha256_ctx m_Context;
public:

	HMAC_SHA256() {}
	HMAC_SHA256(const unsigned char* key, unsigned int key_size) { Init(key, key_size); }
	HMAC_SHA256(const FString& key) { Init(key); }
	void Init(const unsigned char* key, unsigned int key_size);
	void Init(const FString& key);
	void Init(const SHA256Key& key);
	void Update(const unsigned char* message, unsigned int message_len);
	void Update(const FString& rMsg);
	void ReInit();
	void Final(unsigned char* mac, unsigned int mac_size);
	SHA256Key Final();
	static void Hash(const unsigned char* key, unsigned int key_size,
		const unsigned char* message, unsigned int message_len,
		unsigned char* mac, unsigned mac_size);
	static SHA256Key Hash(const FString& rKey, const FString& rMsg);
	static SHA256Key Hash(const SHA256Key& rKey, const FString& rMsg);
};