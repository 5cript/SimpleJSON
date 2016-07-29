#pragma once

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
        bool strings_are_binary;

		ParsingOptions(InvalidPropertyHandlingBehaviour invalidPropertyHandler = InvalidPropertyHandlingBehaviour::THROW,
                       InvalidPathHandlingBehaviour invalidPathHandler = InvalidPathHandlingBehaviour::THROW,
                       bool strings_are_binary = false);
	};

	const auto DefaultParserOptions = ParsingOptions{};
	const auto IngoreErrorsParserOptions = ParsingOptions{InvalidPropertyHandlingBehaviour::IGNORE_ALL_ERROR, InvalidPathHandlingBehaviour::IGNORE_ALL_ERROR};
	const auto IgnoreMissingParserOptions = ParsingOptions{InvalidPropertyHandlingBehaviour::THROW, InvalidPathHandlingBehaviour::IGNORE_ALL_ERROR};
	const auto TagMissingParserOptions = ParsingOptions{InvalidPropertyHandlingBehaviour::THROW, InvalidPathHandlingBehaviour::TAG};

	#define DEFAULT_PARSER_OPTIONS DefaultParserOptions
}
