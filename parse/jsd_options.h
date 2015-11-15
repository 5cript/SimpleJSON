#ifndef JSD_OPTIONS_H_INCLUDED
#define JSD_OPTIONS_H_INCLUDED

namespace JSON
{
    enum class InvalidPropertyHandlingBehaviour : int
	{
		IGNORE_ALL_ERROR,
		DEFAULT,
		TAG,
		THROW
	};

	enum class InvalidPathHandlingBehaviour : int
	{
		IGNORE_ALL_ERROR,
		DEFAULT,
		TAG,
		THROW
	};

	struct ParsingOptions
    {
		InvalidPropertyHandlingBehaviour invalidPropertyHandler;
		InvalidPathHandlingBehaviour invalidPathHandler;


		ParsingOptions(InvalidPropertyHandlingBehaviour invalidPropertyHandler = InvalidPropertyHandlingBehaviour::THROW,
                       InvalidPathHandlingBehaviour invalidPathHandler = InvalidPathHandlingBehaviour::TAG);
	};

	#define DEFAULT_PARSER_OPTIONS ParsingOptions{}
}

#endif
