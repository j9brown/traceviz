// Copyright 2016 The Fuchsia Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#pragma once

#include <stdint.h>
#include <assert.h>

#ifdef __cplusplus
extern "C" {
#endif

// clang-format off

// KTRACE TAG 0xGGGEEEXZ
//
// 12 group flags
// 12 event id bits
//  4 spare bits
//  4 bit size (in uint8_t units)

#define KTRACE_TAG(evt,grp,siz)   ((((grp)&0xFFF)<<20)|(((evt)&0xFFF)<<8)|(((siz)>>3)&0x0F))

#define KTRACE_TAG_32B(e,g)       KTRACE_TAG(e,g,32)
#define KTRACE_TAG_NAME(e,g)      KTRACE_TAG(e,g,48)

#define KTRACE_LEN(tag)           (((tag)&0xF)<<3)
#define KTRACE_GROUP(tag)         (((tag)>>20)&0xFFF)
#define KTRACE_EVENT(tag)         (((tag)>>8)&0xFFF)

#define KTRACE_HDRSIZE            (16)
#define KTRACE_RECSIZE            (32)
#define KTRACE_NAMESIZE           (24)
#define KTRACE_NAMEOFF            (8)

#define KTRACE_VERSION            (0x00020000)

// Filter Groups
#define KTRACE_GRP_ALL            0xFFF
#define KTRACE_GRP_META           0x001
#define KTRACE_GRP_LIFECYCLE      0x002
#define KTRACE_GRP_SCHEDULER      0x004
#define KTRACE_GRP_TASKS          0x008
#define KTRACE_GRP_IPC            0x010

#define KTRACE_GRP_TO_MASK(grp)   ((grp) << 20)

typedef struct ktrace_header {
    uint32_t tag;
    uint32_t tid;
    uint64_t ts;
} ktrace_header_t;

typedef struct ktrace_rec_32b {
    uint32_t tag;
    uint32_t tid;
    uint64_t ts;
    uint32_t a;
    uint32_t b;
    uint32_t c;
    uint32_t d;
} ktrace_rec_32b_t;

typedef struct ktrace_rec_name {
    uint32_t tag;
    uint32_t tid;
    uint64_t ts;
    uint32_t id;
    uint32_t arg;
    char name[1];
} ktrace_rec_name_t;

// Actions for ktrace control
#define KTRACE_ACTION_START    1 // options = grpmask, 0 = all
#define KTRACE_ACTION_STOP     2 // options ignored
#define KTRACE_ACTION_REWIND   3 // options ignored

#ifdef __cplusplus
};
#endif
