/*
 * Copyright (c) 2004 Beeyond Software Holding BV
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

/*!\file UnsupportedOperationException.h
 * \ingroup CXX_LANG_m
 */

#ifndef _CLASS_GOD_LANG_UNSUPPORTEDOPERATIONEXCEPTION_H
#define _CLASS_GOD_LANG_UNSUPPORTEDOPERATIONEXCEPTION_H

#ifdef __cplusplus

#include "lang/RuntimeException.h"
using goddk::lang::RuntimeException;

namespace goddk {
	namespace lang {
		/* \ingroup CXX_LANG_m
		 */
		class UnsupportedOperationException : public RuntimeException
		{
		public:
			inline UnsupportedOperationException()
			{
			}
			inline UnsupportedOperationException(const char* message) : RuntimeException(message)
			{
			}
			inline UnsupportedOperationException(const String* message) : RuntimeException(message)
			{
			}
			inline ~UnsupportedOperationException()
			{
			}
		};
		typedef CSmartPtr<UnsupportedOperationException> UnsupportedOperationExceptionPtr;
	}
}

#endif

#endif
