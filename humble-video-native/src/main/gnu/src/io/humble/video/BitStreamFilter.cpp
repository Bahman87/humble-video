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

#include "BitStreamFilter.h"

namespace io { namespace humble { namespace video {

  BitStreamFilter::~BitStreamFilter ()
  {
    if (mCtx)
      av_bitstream_filter_close(mCtx);
    mCtx = 0;
  }
  BitStreamFilter::BitStreamFilter (BitStreamFilterType *type, Coder* coder)
  {
    (void) type;
    (void) coder;
    mCtx = 0;
  }

} /* namespace video */
} /* namespace humble */
} /* namespace io */
