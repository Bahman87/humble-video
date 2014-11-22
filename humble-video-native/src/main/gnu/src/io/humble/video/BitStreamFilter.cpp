/*******************************************************************************
 * Copyright (c) 2014, Andrew "Art" Clarke.  All rights reserved.
 *
 * This file is part of Humble-Video.
 *
 * Humble-Video is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Humble-Video is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with Humble-Video.  If not, see <http://www.gnu.org/licenses/>.
 *******************************************************************************/
/*
 * BitStreamFilter.cpp
 *
 *  Created on: Sep 28, 2014
 *      Author: aclarke
 */

#include <io/humble/ferry/Logger.h>
#include <io/humble/ferry/HumbleException.h>
#include <io/humble/video/Global.h>

#include "BitStreamFilter.h"

using namespace io::humble::ferry;

VS_LOG_SETUP(VS_CPP_PACKAGE.BitStreamFilter);

namespace io { namespace humble { namespace video {

  BitStreamFilterType*
  BitStreamFilterType::make(AVBitStreamFilter* f)
  {
    if (!f)
      throw HumbleInvalidArgument("no filter passed in");
    BitStreamFilterType* r = new BitStreamFilterType(f);
    r->acquire();
    return r;
  }

  int32_t
  BitStreamFilterType::getNumBitStreamFilterTypes() {
    Global::init();

    AVBitStreamFilter* f = 0;
    int32_t i = 0;
    while ((f = av_bitstream_filter_next(f)) != 0) {
      ++i;
    }
    return i;
  }

  BitStreamFilterType*
  BitStreamFilterType::getBitStreamFilterType(int32_t index) {
    Global::init();

    AVBitStreamFilter* f = 0;
    int32_t i = 0;
    while ((f = av_bitstream_filter_next(f)) != 0) {
      if (i == index) {
        VS_LOG_TRACE("Found filter \"%s\" at position %d",
                     f->name,
                     i);
        // this is the one we want
        break;
      }
      ++i;
    }
    return f ? make(f) : 0;
  }

  BitStreamFilterType*
  BitStreamFilterType::getBitStreamFilterType(const char* name) {
    Global::init();

    AVBitStreamFilter* f = 0;
    int32_t i = 0;
    while ((f = av_bitstream_filter_next(f)) != 0) {
      if (strcmp(name, f->name)==0) {
        VS_LOG_TRACE("Found filter \"%s\" at position %d",
                     f->name,
                     i);
        // this is the one we want
        break;
      }
      ++i;
    }
    return f ? make(f) : 0;
  }


  BitStreamFilter::~BitStreamFilter ()
  {
    if (mCtx)
      av_bitstream_filter_close(mCtx);
    mCtx = 0;
  }
  BitStreamFilter::BitStreamFilter (AVBitStreamFilterContext* ctx,
                                    BitStreamFilterType *type)
  {
    mCtx = ctx;
    if (type) {
      mType.reset(type, true);
    } else {
      mType = BitStreamFilterType::make(mCtx->filter);
    }
  }

  BitStreamFilter*
  BitStreamFilter::make(const char* filtername) {
    Global::init();

    if (!filtername || !*filtername)
      throw HumbleInvalidArgument("no filtername passed in");
    AVBitStreamFilterContext* b = av_bitstream_filter_init(filtername);
    if (!b)
      throw HumbleBadAlloc();
    return make(b, 0);
  }

  BitStreamFilter*
  BitStreamFilter::make(BitStreamFilterType *type) {
    if (!type)
      throw HumbleInvalidArgument("no filter type");
    AVBitStreamFilterContext* b = av_bitstream_filter_init(type->getName());
    if (!b)
      throw HumbleBadAlloc();
    return make(b, type);
  }

  BitStreamFilter*
  BitStreamFilter::make(AVBitStreamFilterContext*c,
                        BitStreamFilterType* t)
  {
    Global::init();
    if (!c)
      throw HumbleInvalidArgument("no filter context");

    BitStreamFilter* r = new BitStreamFilter(c, t);
    if (!r)
      throw HumbleBadAlloc();
    r->acquire();
    return r;
  }

  int32_t
  BitStreamFilter::filter(Buffer* output,
                          Buffer* input,
                          int32_t inputSize,
                          const char* args,
                          bool isKey)
  {
    (void) output;
    (void) input;
    (void) inputSize;
    (void) args;
    (void) isKey;
    throw HumbleRuntimeError("unimplemented method");
    return -1;
  }

} /* namespace video */
} /* namespace humble */
} /* namespace io */
