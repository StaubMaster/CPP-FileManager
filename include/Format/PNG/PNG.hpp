
#ifndef  PNG_HPP
# define PNG_HPP

# include "FileContext.hpp"
# include "Format/Image.hpp"

class PNG
{
	public:
		static Image * Load(const FileContext & file, bool debug = false);

		class PNG_Exception_Signature : public std::exception { public: const char * what() const throw(); };
};

#endif
