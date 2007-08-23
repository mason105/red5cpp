#pragma	  once
#include "array.h"
using namespace goddk;
#include "goddk_lang.h"
#include "goddk_io.h"
#include "goddk_math.h"
#include "goddk_nio.h"
#include "goddk_util.h"

#include "LogMsg.h"

#define  final const static
#define  null  0
typedef  unsigned char boolean;

class Document:
	public String
{
public:
	virtual bool instanceof(const char* class_name)const throw()
	{
		if(strcmp("Document", class_name)== 0)
			return true;
		else
			return __super::instanceof(class_name);
	}

};
typedef CSmartPtr<Document> DocumentPtr;

typedef CSmartPtr<bytearray>	bytearrayPtr;
typedef CSmartPtr<jbytearray>	jbytearrayPtr;
typedef CSmartPtr<jchararray>	jchararrayPtr;
typedef CSmartPtr<jintarray>	jintarrayPtr;
typedef CSmartPtr<jlongarray>	jlongarrayPtr;
typedef CSmartPtr<jdoublearray>	jdoublearrayPtr;
typedef array<TimerTask>		  TimerTaskarray;
typedef CSmartPtr<TimerTaskarray> TimerTaskarrayPtr;

typedef Map<Integer, Object> IntegerAndObject_Map;
typedef CSmartPtr<IntegerAndObject_Map> IntegerAndObject_MapPtr;
typedef Map<String, Integer> StringAndInteger_Map;
typedef CSmartPtr<StringAndInteger_Map> StringAndInteger_MapPtr;
typedef Map<String, Object> StringAndObject_Map;
typedef CSmartPtr<StringAndObject_Map> StringAndObject_MapPtr;
typedef Map<String, String> StringAndString_Map;
typedef CSmartPtr<StringAndString_Map> StringAndString_MapPtr;
typedef Map<Object, Object> ObjectAndObject_Map;
typedef CSmartPtr<ObjectAndObject_Map> ObjectAndObject_MapPtr;
typedef Map<Integer , Boolean> IntegerAndBoolean_Map;
typedef CSmartPtr<IntegerAndBoolean_Map> IntegerAndBoolean_MapPtr;
typedef Map<Integer, Integer> IntegerAndInteger_Map;
typedef CSmartPtr<IntegerAndInteger_Map> IntegerAndInteger_MapPtr;
typedef Map<Long, Long> LongAndLong_Map;
typedef CSmartPtr<LongAndLong_Map> LongAndLong_MapPtr;

typedef Iterator<String>	String_Iterator;
typedef CSmartPtr<String_Iterator> String_IteratorPtr;

typedef Set<String>	String_Set;
typedef CSmartPtr<String_Set> String_SetPtr;
typedef Set<Object>	Object_Set;
typedef CSmartPtr<Object_Set> Object_SetPtr;
typedef Hashtable<Integer, Object> IntegerAndObject_Hashtable;
typedef CSmartPtr<IntegerAndObject_Hashtable> IntegerAndObject_HashtablePtr;
typedef Hashtable<Object, Integer> ObjectAndInteger_Hashtable;
typedef CSmartPtr<ObjectAndInteger_Hashtable> ObjectAndInteger_HashtablePtr;
typedef Hashtable<String, Object> StringAndObject_Hashtable;
typedef CSmartPtr<StringAndObject_Hashtable> StringAndObject_HashtablePtr;
typedef Hashtable<Object, Object> ObjectAndObject_Hashtable;
typedef CSmartPtr<ObjectAndObject_Hashtable> ObjectAndObject_HashtablePtr;
typedef Hashtable<String, Integer> StringAndInteger_Hashtable;
typedef CSmartPtr<StringAndInteger_Hashtable> StringAndInteger_HashtablePtr;
typedef Hashtable<Long, Long> LongAndLong_Hashtable;
typedef CSmartPtr<LongAndLong_Hashtable> LongAndLong_HashtablePtr;
typedef Hashtable<Long, Integer> LongAndInteger_Hashtable;
typedef CSmartPtr<LongAndInteger_Hashtable> LongAndInteger_HashtablePtr;

typedef List<Object> Object_List;
typedef CSmartPtr<Object_List> Object_ListPtr;
typedef List<String> String_List;
typedef CSmartPtr<String_List> String_ListPtr;
typedef List<Long> Long_List;
typedef CSmartPtr<Long_List> Long_ListPtr;
typedef List<Integer> Integer_List;
typedef CSmartPtr<Integer_List> Integer_ListPtr;
typedef ArrayList<Object> Object_ArrayList;
typedef CSmartPtr<Object_ArrayList> Object_ArrayListPtr;
typedef ArrayList<String> String_ArrayList;
typedef CSmartPtr<String_ArrayList> String_ArrayListPtr;
typedef List<Runnable> Runnable_List;
typedef CSmartPtr<Runnable_List> Runnable_ListPtr;

ByteBufferPtr inline ByteBuffer_allocate(size_t capacity, boolean direct = true)
{
	ByteBufferPtr result;
	result.Attach(ByteBuffer::allocate(capacity));
	return result;
}
ByteBufferPtr inline ByteBuffer_allocate(const byte* data, size_t capacity, boolean direct = true)
{
	ByteBufferPtr result;
	result.Attach(ByteBuffer::allocate(data, capacity));
	return result;
}
ByteBufferPtr inline ByteBuffer_wrap(bytearrayPtr v)
{
	ByteBufferPtr result;
	result.Attach(ByteBuffer::wrap(v.RawData()));
	return result;
}
IntegerPtr inline Integer_valueOf(jint v)
{
	IntegerPtr result;
	result.Attach(Integer::valueOf(v));
	return result;
}
DoublePtr inline Double_valueOf(jdouble v)
{
	DoublePtr result;
	result.Attach(Double::valueOf(v));
	return result;
}
LongPtr inline Long_valueOf(jlong v)
{
	LongPtr result;
	result.Attach(Long::valueOf(v));
	return result;
}
BooleanPtr inline Boolean_valueOf(byte v)
{
	BooleanPtr result;
	result.Attach(new Boolean(v));
	return result;
}
StringPtr inline String_valueOf(char* v)
{
	StringPtr result;
	result.Attach(new String(v));
	return result;
}
StringPtr inline String_valueOf(String v)
{
	StringPtr result;
	result.Attach(new String(v));
	return result;
}
StringPtr inline String_valueOf(int v)
{
	StringPtr result;
	result.Attach(new String(String::valueOf(v)));
	return result;
}
void inline Free_ArrayString(array<String*>& v)
{
	for(int i = 0; i < v.size(); i ++)
		v[i]->removeRef();
}
