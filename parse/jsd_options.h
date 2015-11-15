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

	const auto DefaultParserOptions = ParsingOptions{};
	const auto IngoreErrorsParserOptions = ParsingOptions{InvalidPropertyHandlingBehaviour::IGNORE_ALL_ERROR, InvalidPathHandlingBehaviour::IGNORE_ALL_ERROR};
	const auto IgnoreMissingParserOptions = ParsingOptions{InvalidPropertyHandlingBehaviour::THROW, InvalidPathHandlingBehaviour::IGNORE_ALL_ERROR};
	const auto TagMissingParserOptions = ParsingOptions{InvalidPropertyHandlingBehaviour::THROW, InvalidPathHandlingBehaviour::TAG};

	#define DEFAULT_PARSER_OPTIONS DefaultParserOptions
}

#endif
