/*
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 */

/*
 * Original code taken from mcuboot project at:
 * https://github.com/JuulLabs-OSS/mcuboot
 * Git SHA of the original version: 3c469bc698a9767859ed73cd0201c44161204d5c
 * Modifications are Copyright (c) 2019 Arm Limited.
 */

#include <bootutil/sign_key.h>

 /*Added by AR, TODO: identify if this is the best place for it, duplicated in flash_map*/
#define MCUBOOT_IMAGE_NUMBER (1)
#define MCUBOOT_SIGN_RSA
#define MCUBOOT_SIGN_RSA_LEN (2048)

#if !defined(MCUBOOT_HW_KEY)
#if defined(MCUBOOT_SIGN_RSA)
#if MCUBOOT_SIGN_RSA_LEN == 2048
#define HAVE_KEYS
/* Autogenerated by imgtool.py, do not edit. */
/* Autogenerated by imgtool.py, do not edit. */
const unsigned char rsa_pub_key[] = {
    0x30, 0x82, 0x01, 0x0a, 0x02, 0x82, 0x01, 0x01,
    0x00, 0xd0, 0xc4, 0x33, 0x53, 0xf3, 0x5c, 0xc1,
    0xeb, 0xc5, 0x0d, 0x41, 0xd3, 0xdc, 0x32, 0x04,
    0xf9, 0x37, 0x49, 0xe6, 0x85, 0x7b, 0x43, 0x89,
    0x18, 0x0c, 0xdd, 0x63, 0x12, 0xb4, 0x29, 0x95,
    0xb4, 0xbc, 0xdf, 0x83, 0x0c, 0x6d, 0xb4, 0xbe,
    0x02, 0xe0, 0xf1, 0xba, 0xbf, 0x47, 0x39, 0x4a,
    0xaf, 0x1b, 0xf6, 0xec, 0x24, 0x8c, 0x0b, 0x75,
    0x72, 0x5f, 0xf6, 0x5e, 0x00, 0xf4, 0xba, 0x3b,
    0xd1, 0x83, 0x99, 0x9b, 0xf8, 0xab, 0xa8, 0x28,
    0x0e, 0x18, 0xec, 0xa5, 0xe8, 0x52, 0x1f, 0x1c,
    0xf0, 0x96, 0x35, 0x70, 0x45, 0xee, 0xc8, 0xa1,
    0x96, 0xad, 0x20, 0x9a, 0x13, 0x3e, 0x5b, 0xa2,
    0xdc, 0x5c, 0x45, 0xac, 0x35, 0xb7, 0xcd, 0x6e,
    0x69, 0x1d, 0x9e, 0xab, 0x12, 0xba, 0xaf, 0xdd,
    0x6f, 0x78, 0x49, 0x57, 0xd6, 0x0f, 0x38, 0x8b,
    0x1e, 0xa7, 0x85, 0xb6, 0x52, 0x36, 0x77, 0xc8,
    0x71, 0x49, 0xf3, 0xb6, 0xac, 0x71, 0x5d, 0x98,
    0x1c, 0x5c, 0x42, 0x97, 0x77, 0x9e, 0x0a, 0xa1,
    0x5a, 0x6d, 0x4f, 0x71, 0xe9, 0xfc, 0x0e, 0x8f,
    0x94, 0xb5, 0x2f, 0x60, 0x6e, 0x6c, 0xa5, 0x64,
    0x9c, 0xdd, 0x86, 0xfe, 0x21, 0x55, 0x8e, 0x27,
    0x9e, 0xde, 0x18, 0xd5, 0x11, 0x9a, 0xd6, 0x4d,
    0x12, 0x5f, 0x6e, 0x14, 0x21, 0x20, 0x2c, 0x33,
    0x75, 0x88, 0xb2, 0x38, 0x3a, 0x9f, 0x80, 0xb6,
    0x97, 0xfa, 0xe7, 0x91, 0xb4, 0x5e, 0xaf, 0x5e,
    0x97, 0x28, 0x70, 0x5e, 0x5e, 0x60, 0x01, 0xf4,
    0x1d, 0xc2, 0x6f, 0xf3, 0xa8, 0x76, 0xdc, 0xa3,
    0x50, 0x67, 0x84, 0x6d, 0x95, 0xdd, 0x36, 0xb1,
    0x7c, 0x73, 0xe3, 0x50, 0xaf, 0xfc, 0x01, 0x70,
    0x69, 0x9a, 0x67, 0xd9, 0xac, 0x5c, 0xcf, 0x85,
    0x1d, 0xf3, 0x06, 0xd1, 0x92, 0x90, 0x9a, 0xda,
    0xaf, 0x2c, 0x9b, 0xc8, 0xec, 0x9a, 0x79, 0x29,
    0xf1, 0x02, 0x03, 0x01, 0x00, 0x01,
};
const unsigned int rsa_pub_key_len = 270;
#if (MCUBOOT_IMAGE_NUMBER ==2)
const unsigned char rsa_pub_key_1[] = {
    0x30, 0x82, 0x01, 0x0a, 0x02, 0x82, 0x01, 0x01,
    0x00, 0xac, 0xd2, 0x74, 0x93, 0x3e, 0x5f, 0xe7,
    0xaf, 0xf2, 0xc8, 0x6c, 0xe8, 0x58, 0x51, 0x63,
    0x77, 0x0e, 0x52, 0xfe, 0x58, 0xd5, 0xbb, 0xa5,
    0xe3, 0x9c, 0x8a, 0xcd, 0x14, 0x0a, 0x89, 0xc6,
    0x15, 0xae, 0x49, 0x04, 0x9f, 0x5f, 0x3d, 0x2b,
    0x89, 0x12, 0x1f, 0x3e, 0x7f, 0x05, 0xfc, 0x0b,
    0x99, 0x26, 0x63, 0x5e, 0x96, 0xef, 0x33, 0xbc,
    0x8c, 0x27, 0x68, 0x4d, 0x46, 0x8d, 0x66, 0x33,
    0x99, 0x3b, 0x38, 0x11, 0x1b, 0xe3, 0xac, 0x18,
    0x07, 0x95, 0x48, 0x87, 0xb2, 0xab, 0x4f, 0x2d,
    0x0e, 0x12, 0x51, 0x1b, 0x7f, 0x33, 0xba, 0x78,
    0xb1, 0xd5, 0xfa, 0x7f, 0xbf, 0x71, 0x4b, 0xe4,
    0x5f, 0x67, 0x57, 0x67, 0xd5, 0xab, 0xbb, 0x64,
    0x06, 0x17, 0x3d, 0x81, 0xeb, 0xd8, 0xc1, 0xf9,
    0x7a, 0x57, 0xd3, 0x29, 0x5c, 0x10, 0xff, 0xa7,
    0xd3, 0x3a, 0x58, 0x3f, 0x25, 0x8a, 0xc5, 0x84,
    0x7b, 0x97, 0x27, 0xa5, 0xe4, 0x90, 0xe7, 0xdf,
    0x1c, 0x33, 0xe6, 0x7c, 0xaf, 0x68, 0x77, 0x5e,
    0x1f, 0x09, 0x6e, 0xdd, 0x92, 0x60, 0x4e, 0xac,
    0x73, 0x84, 0xb0, 0xf7, 0xb6, 0x02, 0xc2, 0xce,
    0x9f, 0xaf, 0xad, 0xb2, 0xb1, 0x57, 0xcc, 0xf9,
    0x06, 0x1d, 0x6a, 0x25, 0x2f, 0x72, 0x2a, 0x7d,
    0xfe, 0x0d, 0xed, 0xb8, 0xc2, 0x95, 0x88, 0x41,
    0xf2, 0x45, 0xa8, 0x6e, 0x6a, 0x85, 0xee, 0xae,
    0xfa, 0x8a, 0x79, 0xfa, 0xfe, 0x7e, 0x40, 0x49,
    0x43, 0xec, 0x2c, 0x8e, 0x8e, 0x82, 0x7e, 0xe2,
    0xf8, 0x0f, 0xf2, 0xe9, 0x7d, 0xa3, 0x7f, 0xac,
    0x23, 0xbd, 0x0a, 0x42, 0xea, 0x18, 0xfb, 0x72,
    0xa0, 0x9a, 0x24, 0x01, 0xc8, 0x27, 0x8c, 0x56,
    0x24, 0x93, 0x82, 0xdf, 0x23, 0x19, 0x96, 0x73,
    0xf2, 0x11, 0xc3, 0x05, 0xe6, 0xa5, 0xb8, 0x0b,
    0xe0, 0x73, 0xce, 0x07, 0x9b, 0x57, 0xe6, 0x8e,
    0xfb, 0x02, 0x03, 0x01, 0x00, 0x01,
};
const unsigned int rsa_pub_key_len_1 = 270;
#endif
#elif MCUBOOT_SIGN_RSA_LEN == 3072
#define HAVE_KEYS
const unsigned char rsa_pub_key[] = {
    0x30, 0x82, 0x01, 0x8a, 0x02, 0x82, 0x01, 0x81,
    0x00, 0x9c, 0xba, 0xc2, 0x5a, 0xbf, 0xcc, 0xc5,
    0x4f, 0x20, 0x0c, 0x4f, 0x6f, 0x6c, 0x51, 0x4f,
    0x5c, 0x0a, 0xab, 0x80, 0xb8, 0x6b, 0x10, 0xc4,
    0x9b, 0x2b, 0xc4, 0x52, 0x32, 0x09, 0x4b, 0x3b,
    0x27, 0x94, 0x6a, 0x1d, 0xd5, 0x4c, 0xa8, 0x5c,
    0xa0, 0xc0, 0x76, 0x95, 0x7b, 0x26, 0x04, 0xb1,
    0x13, 0x7e, 0x78, 0x27, 0xd6, 0x0c, 0xb4, 0xe8,
    0xb0, 0x2d, 0x92, 0x52, 0x8a, 0xfb, 0x69, 0xff,
    0x42, 0x10, 0xaa, 0x56, 0x0c, 0x83, 0xc8, 0x65,
    0x6e, 0xba, 0x0d, 0x5f, 0x8e, 0xf7, 0x2b, 0x29,
    0x92, 0xfc, 0x42, 0x2d, 0x2d, 0xf9, 0x80, 0xf5,
    0x85, 0x21, 0x87, 0xea, 0xac, 0x40, 0xa8, 0xcb,
    0xd0, 0xa8, 0x3b, 0xe2, 0xd2, 0xec, 0xf0, 0x14,
    0x48, 0x0e, 0xcf, 0x2b, 0x8a, 0x4b, 0xa4, 0xcd,
    0xa1, 0x05, 0x5b, 0x17, 0x66, 0x1d, 0xde, 0x6e,
    0x44, 0xfe, 0x46, 0xa3, 0x0d, 0xd0, 0x69, 0xbf,
    0x8c, 0xad, 0xa9, 0x16, 0x68, 0x51, 0xeb, 0x79,
    0x91, 0x20, 0xe6, 0x81, 0x03, 0x07, 0x89, 0x40,
    0x55, 0x4b, 0xeb, 0xcf, 0x67, 0xf8, 0x31, 0xc7,
    0x1c, 0x54, 0x4e, 0x52, 0x0b, 0x60, 0xe8, 0xa2,
    0x50, 0x07, 0xd1, 0xcf, 0xce, 0x12, 0x26, 0xcd,
    0x8e, 0x82, 0x8d, 0x4e, 0x64, 0xa9, 0xf7, 0xc7,
    0x21, 0x99, 0x25, 0x07, 0xdd, 0xc5, 0xd5, 0x5f,
    0xf4, 0x63, 0xfa, 0xcc, 0x2b, 0xda, 0x06, 0x5c,
    0x59, 0x67, 0xb0, 0x06, 0x35, 0xe9, 0xaa, 0x92,
    0x45, 0x35, 0xe5, 0xa0, 0x03, 0xff, 0x1c, 0x02,
    0xb5, 0xc7, 0x4e, 0x94, 0x4b, 0x6e, 0xad, 0x73,
    0x9d, 0xce, 0x6f, 0x09, 0xb3, 0xb1, 0x8f, 0x60,
    0x6c, 0xa2, 0xfa, 0xcd, 0x77, 0x0f, 0xcc, 0x27,
    0xe6, 0x36, 0x58, 0xb3, 0x52, 0xf7, 0x8f, 0xbe,
    0x49, 0x98, 0xb7, 0xe9, 0x60, 0xfd, 0x97, 0x57,
    0xcd, 0xea, 0xd3, 0x0b, 0xdf, 0xa2, 0x42, 0xf7,
    0x44, 0xd3, 0x87, 0xde, 0xe0, 0x10, 0x03, 0x94,
    0xda, 0xfc, 0xbc, 0xdd, 0xbe, 0x93, 0xb3, 0x4a,
    0x2b, 0x58, 0xdc, 0x96, 0x12, 0xf2, 0x6f, 0x23,
    0xba, 0x3b, 0x37, 0xfe, 0xfc, 0x18, 0x1f, 0x75,
    0x7d, 0x54, 0x01, 0x0e, 0xbe, 0x3d, 0x18, 0x13,
    0xb3, 0x28, 0xb9, 0x34, 0x2c, 0xd5, 0xfb, 0xc5,
    0x33, 0xbd, 0x87, 0xbd, 0x3b, 0xe4, 0x1d, 0xd7,
    0x02, 0x3d, 0x1c, 0x72, 0x65, 0x72, 0x43, 0x43,
    0x36, 0xa8, 0xfa, 0xe6, 0x73, 0x2d, 0xa4, 0x61,
    0xe8, 0x02, 0x9c, 0x3a, 0x56, 0x4d, 0x1c, 0xd1,
    0x76, 0x9c, 0x8c, 0xaa, 0x5f, 0x1b, 0xeb, 0x1c,
    0x4a, 0xf5, 0xb9, 0xb8, 0x6f, 0x41, 0x4b, 0x27,
    0x87, 0xde, 0xf6, 0x94, 0x1f, 0xdd, 0xe6, 0xf1,
    0xa9, 0xc2, 0x02, 0xc2, 0x4f, 0xa3, 0xfc, 0xa4,
    0x03, 0x5a, 0xd9, 0x6f, 0x78, 0xfd, 0x84, 0xf0,
    0xe5, 0xfd, 0x3d, 0xa5, 0x4d, 0x1b, 0xad, 0x5b,
    0x4b, 0x02, 0x03, 0x01, 0x00, 0x01,
};
const unsigned int rsa_pub_key_len = 398;
#if (MCUBOOT_IMAGE_NUMBER == 2)
const unsigned char rsa_pub_key_1[] = {
    0x30, 0x82, 0x01, 0x8a, 0x02, 0x82, 0x01, 0x81,
    0x00, 0xbf, 0xb7, 0xb0, 0x9f, 0xe8, 0xc8, 0xd1,
    0xfe, 0x16, 0x1d, 0x53, 0x87, 0x97, 0x79, 0x1c,
    0x15, 0xc7, 0x99, 0x16, 0x6c, 0xca, 0xb8, 0x2d,
    0xca, 0xc2, 0x0d, 0x62, 0xf9, 0xeb, 0x8f, 0xe9,
    0x3a, 0x18, 0x43, 0x47, 0xd7, 0xbb, 0xd5, 0x62,
    0xbc, 0xe3, 0x33, 0x63, 0xa7, 0xa3, 0xa8, 0x5c,
    0xf3, 0x23, 0x78, 0xfd, 0x2d, 0x07, 0x21, 0x1f,
    0xb9, 0x54, 0x70, 0x28, 0xa9, 0x08, 0xda, 0x50,
    0x7e, 0x9e, 0x8e, 0xcc, 0x68, 0x4e, 0x7f, 0x48,
    0x0d, 0xea, 0x27, 0xe8, 0xc6, 0xef, 0xad, 0x5f,
    0x9d, 0x46, 0x4a, 0xbc, 0x69, 0x9a, 0x30, 0x5f,
    0x3b, 0xc1, 0x52, 0x92, 0xf8, 0xbc, 0x75, 0xd4,
    0x3c, 0x27, 0x70, 0x40, 0x00, 0xa6, 0x2e, 0x28,
    0x7f, 0x59, 0xe5, 0x60, 0x43, 0x11, 0xdc, 0x31,
    0x09, 0x7d, 0xcf, 0x2f, 0x41, 0x3f, 0xb6, 0x52,
    0x1a, 0xa3, 0x49, 0x16, 0xf2, 0xb5, 0xb3, 0x9c,
    0x3c, 0xfb, 0x5e, 0x2c, 0x1f, 0x22, 0x86, 0xbd,
    0xae, 0xbe, 0x36, 0x52, 0xbd, 0xc4, 0xf0, 0x58,
    0x69, 0x36, 0xa7, 0x80, 0x3e, 0x81, 0xb3, 0x54,
    0x98, 0xe4, 0x5d, 0x95, 0xed, 0x21, 0xf0, 0xba,
    0xae, 0x21, 0xfb, 0xc4, 0x19, 0x87, 0x55, 0xd1,
    0x2b, 0x4f, 0x00, 0xd8, 0x41, 0x58, 0xcb, 0xdb,
    0xa9, 0x9a, 0x53, 0xe9, 0x6c, 0x67, 0xcb, 0x7c,
    0x5d, 0xf6, 0x91, 0x06, 0x75, 0x52, 0xf2, 0xc0,
    0x7e, 0xb1, 0x6b, 0x5d, 0x30, 0x40, 0x40, 0x2f,
    0xd8, 0x1e, 0x95, 0x3c, 0x05, 0x97, 0x7f, 0xf0,
    0x04, 0xf0, 0x4e, 0x2c, 0xd5, 0x39, 0x0e, 0x94,
    0x3d, 0x7c, 0x03, 0x08, 0x1d, 0x09, 0x08, 0xf2,
    0x8d, 0x44, 0x0d, 0xcf, 0xb3, 0x96, 0x3d, 0x5a,
    0x76, 0xe8, 0xf6, 0xee, 0x93, 0x64, 0xe8, 0x57,
    0xd1, 0xe2, 0xf5, 0x0b, 0x18, 0x69, 0x6f, 0xe9,
    0xe1, 0x3d, 0xf8, 0x89, 0x49, 0x28, 0xe6, 0xaf,
    0xb8, 0xa8, 0xc6, 0x42, 0x55, 0x2d, 0xc1, 0xdb,
    0x8c, 0x5d, 0xb2, 0x6d, 0x7f, 0xfe, 0x26, 0xea,
    0x75, 0xd9, 0xfd, 0x1f, 0xdc, 0x22, 0x3b, 0xa4,
    0x1b, 0xa7, 0xad, 0xeb, 0x71, 0xdf, 0xbd, 0xb4,
    0x37, 0xd1, 0xeb, 0xbe, 0x08, 0x10, 0x1c, 0x78,
    0x84, 0x1c, 0x9a, 0x75, 0xc4, 0xad, 0xe5, 0xef,
    0x73, 0x17, 0xac, 0x69, 0x78, 0xbc, 0xd6, 0x37,
    0x8c, 0x0c, 0x14, 0x21, 0x06, 0x47, 0xbd, 0xf8,
    0x0a, 0xac, 0x19, 0x09, 0x9d, 0x0d, 0x1d, 0x72,
    0xe1, 0x3e, 0x1a, 0x74, 0xea, 0x86, 0xd9, 0x5c,
    0x4a, 0xcd, 0xcc, 0xc6, 0x94, 0xa7, 0xfe, 0xda,
    0x0b, 0x87, 0x11, 0xbb, 0x6b, 0xf0, 0x3a, 0xe3,
    0x4f, 0x82, 0x4f, 0xb1, 0xe4, 0xa4, 0xcd, 0xbc,
    0x70, 0x3c, 0x9d, 0x9c, 0x49, 0xf9, 0xcf, 0x28,
    0x6d, 0xb8, 0xda, 0x6f, 0x7d, 0x38, 0x57, 0x55,
    0x43, 0x2a, 0x73, 0x8d, 0xb6, 0x18, 0xfd, 0x70,
    0xa7, 0x02, 0x03, 0x01, 0x00, 0x01,
};
const unsigned int rsa_pub_key_len_1 = 398;
#endif
#endif
#else
#error "No public key available for given signing algorithm."
#endif

#if defined(HAVE_KEYS)
const struct bootutil_key bootutil_keys[] = {
    {
        .key = rsa_pub_key,
        .len = &rsa_pub_key_len,
    },
#if (MCUBOOT_IMAGE_NUMBER == 2)
    {
        .key = rsa_pub_key_1,
        .len = &rsa_pub_key_len_1,
    },
#endif
};
const int bootutil_key_cnt = MCUBOOT_IMAGE_NUMBER;
#endif /* HAVE_KEYS */
#else  /* MCUBOOT_HW_KEY */
unsigned int pub_key_len;
struct bootutil_key bootutil_keys[1] = {
    {
        .key = 0,
        .len = &pub_key_len,
    },
};
const int bootutil_key_cnt = 1;
#endif
