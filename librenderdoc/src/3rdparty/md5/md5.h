// The MD5 functions that Windows exports from cryptdll.dll (import library
// cryptdll.lib), as RFC 1321's MD5Init, MD5Update, and MD5Final. The Windows
// SDK ships the import library but declares them in no header. The context
// keeps the running state A, B, C, D in buf, which the DXBC container hash
// reads directly.
//
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

typedef struct
{
  unsigned long i[2];
  unsigned long buf[4];
  unsigned char in[64];
  unsigned char digest[16];
} MD5_CTX;

void __stdcall MD5Init(MD5_CTX *context);
void __stdcall MD5Update(MD5_CTX *context, const unsigned char *input, unsigned int inputLen);
void __stdcall MD5Final(MD5_CTX *context);

#ifdef __cplusplus
}
#endif
