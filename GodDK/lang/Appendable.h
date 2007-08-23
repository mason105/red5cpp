

#ifndef _INTERFACE_GOD_LANG_APPENDABLE_H
#define _INTERFACE_GOD_LANG_APPENDABLE_H

#ifdef __cplusplus

#include "lang/CharSequence.h"
using namespace goddk::lang;

namespace goddk {
	namespace lang {
		class  Appendable
		{
		public:
			virtual ~Appendable() {}

			virtual Appendable& append(jchar c) = 0;
			virtual Appendable& append(const CharSequence& cseq) = 0;
		};
	}
}

#endif

#endif
