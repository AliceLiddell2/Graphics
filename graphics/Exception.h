
#pragma once

#include "graphics/Common.h"

namespace MyGL
{
	class Exception 
	{
	protected:
		string src;
		string functionName;
		int line;
		string message;

	public:
		Exception(const string& message)
		{
			this->message = message;
			line = -1;
		}

		Exception(const string& message, int line, const string& functionName, const string& source)
		{
			this->message = message;
			this->line = line;
			this->functionName = functionName;
			this->src = source; 
		}

		inline bool HasCodeInfo() const { return line != -1; } 

		inline string ToString() const 
		{
			char line_s[256];
			sprintf(line_s, "%d", line);
			//
			return message + "\n" + line_s + " @ " + src + "\n[" + functionName + "]"; 
		}
	};

#	define ThrowException(msg) (throw ::MyGL::Exception(msg,__LINE__,string(__FUNCTION__),string(__FILE__)))
	// one can put ; after the macro 

} // namespace MyGL

