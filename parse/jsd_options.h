#ifndef JSD_OPTIONS_H_INCLUDED
#define JSD_OPTIONS_H_INCLUDED

namespace JSON
{
	enum class InvalidPropertyHandlingBehaviour : int
	{
		IGNORE,
		DEFAULT,
		TAG,
		THROW
	};

	struct ParsingOptions
    {
		InvalidPropertyHandlingBehaviour invBehaviour;

		ParsingOptions(InvalidPropertyHandlingBehaviour invBehaviour = InvalidPropertyHandlingBehaviour::THROW);
	};

	#define DEFAULT_PARSER_OPTIONS ParsingOptions{}
}

#endif