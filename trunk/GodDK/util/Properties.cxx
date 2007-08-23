

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include "util/Properties.h"
using goddk::util::Properties;
#include "util/Date.h"
using goddk::util::Date;
#include "io/DataInputStream.h"
using goddk::io::DataInputStream;
#include "io/PrintStream.h"
using goddk::io::PrintStream;

using namespace goddk::util;

Properties::Names::Names(Hashtable<Object,Object>& h) : _list(h.size())
{
	Iterator<class Map<Object,Object>::Entry>* it = h.entrySet().iterator();

	_pos = 0;
	while (it->hasNext())
	{
		const String* name = dynamic_cast<String*>(it->next()->getKey());
		if (name)
			_list[_pos++] = new String(*name);
		else
			_list[_pos++] = 0;
	}
	_pos = 0;
}

Properties::Names::~Names()
{
	for (int i = 0; i < _list.size(); i++)
		delete _list[i];
}

bool Properties::Names::hasMoreElements() throw ()
{
	return _pos < _list.size();
}

const String* Properties::Names::nextElement() throw (NoSuchElementExceptionPtr)
{
	if (_pos >= _list.size())
		THROWEXCEPTIONPTR(NoSuchElementException)

	return _list[_pos++];
}

Properties::Properties()
{
	defaults = 0;
}

Properties::Properties(const Properties& copy)
{
	defaults = copy.defaults;

	putAll(copy);
}

Properties::Properties(const Properties* defaults) : defaults(defaults)
{
}

void Properties::enumerate(Hashtable<Object,Object>& h) const
{
	if (defaults)
		defaults->enumerate(h);

	Iterator<class Map<Object,Object>::Entry>* it = entrySet().iterator();
	assert(it != 0);
	while (it->hasNext())
	{
		class Map<Object,Object>::Entry* p = it->next();

		const String* key = dynamic_cast<const String*>(p->getKey());
		if (key)
		{
			const String* value = dynamic_cast<const String*>(p->getValue());
			if (value)
			{
				String* newKey = new String(*key);
				String* newValue = new String(*value);
				Object* oldValue = h.put(newKey, newValue);
				if (oldValue)
				{
					delete newKey;
					delete oldValue;
				}
			}
		}
	}
	delete it;
}

const String* Properties::getProperty(const String& key) const throw ()
{
	const String* result = dynamic_cast<const String*>(Hashtable<Object,Object>::get(&key));
	if (!result && defaults)
		return defaults->getProperty(key);
	else
		return result;
}

const String* Properties::getProperty(const String& key, const String& defaultValue) const throw ()
{
	const String* result = getProperty(key);
	if (result)
		return result;
	else
		return &defaultValue;
}

Object* Properties::setProperty(const String& key, const String& value)
{
	String* tmp = new String(key);

	Object* result = put(tmp, new String(value));
	if (result) // Hashtable already contained key tmp; we can free it
		delete tmp;

	return result;
}

Enumeration<const String>* Properties::propertyNames() const
{
	Hashtable<Object,Object> h;

	enumerate(h);

	return new Names(h);
}

void Properties::load(InputStream& in) throw (IOExceptionPtr)
{
	String line;

	DataInputStream dis(in);

	try
	{
		synchronized (this)
		{
			while (dis.available())
			{
				line = dis.readLine();

				if (line.indexOf((UChar) 0x23) != 0)
				{
					// more advanced parsing can come later
					// see if we can find an '=' somewhere inside the string
					int32_t eqidx = line.indexOf((UChar) 0x3D);
					if (eqidx >= 0)
					{
						// we can split the line into two parts
						Object* tmp = put(new String(line.substring(0, eqidx)), new String(line.substring(eqidx+1)));
						if (tmp)
							delete tmp;
					}
				}
				// else it's a comment line which we discard
			}
		}
	}
	catch (IOException&)
	{
		throw;
	}
}

void Properties::store(OutputStream& out, const String& header) throw (IOExceptionPtr)
{
	/*!\todo first enumerate (recursively) into a new Hashtable, then get all the keys from it
	 */

	Date now;

	/*!\todo use an OutputWriter instead of a PrintStream
	 */
	PrintStream ps(out);

	ps.println("# " + header);
	//ps.println("# " + now.toString());
	
	synchronized (this)
	{
		Iterator<class Map<Object,Object>::Entry>* it = entrySet().iterator();
		assert (it != 0);
		while (it->hasNext())
		{
			class Map<Object,Object>::Entry* p = it->next();

			const String* key = dynamic_cast<const String*>(p->getKey());
			if (key)
			{
				const String* value = dynamic_cast<const String*>(p->getValue());
				if (value)
				{
					ps.print(*key);
					ps.print((jchar) 0x3D);
					ps.println(*value);
				}
			}
		}
	}
}
