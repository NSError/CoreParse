//
//  Parser.h
//  CoreParse
//
//  Created by Tom Davie on 04/03/2011.
//  Copyright 2011 In The Beginning... All rights reserved.
//

#import <Foundation/Foundation.h>

#import "CPGrammar.h"
#import "CPSyntaxTree.h"

#import "CPTokenStream.h"

@class CPParser;

/**
 * The delegate of a CPParser must adopt the CPParserDelegate protocol.  This allows you to replace the produced syntax trees with data structures of your choice.
 * 
 * Significant processing can be performed in a parser delegate.  For example, a parser for numeric expressions could replace each syntax tree with an NSNumber representing
 * the resultant value of evaluating the expression.  This would allow you to parse, and compute the result of the expression in one pass.
 */
@protocol CPParserDelegate <NSObject>

/**
 * Should return an object to replace a produced syntax tree with.
 * 
 * You should not return `nil` from this method.
 * 
 * @warning Note that it is not guarenteed that this method will be called in the same order as the structures appear in your input stream.
 * 
 * @param parser     The parser which produced the syntax tree.
 * @param syntaxTree The syntax tree the parser has produced.
 * @return An object value to replace the syntax tree with.
 */
- (id)parser:(CPParser *)parser didProduceSyntaxTree:(CPSyntaxTree *)syntaxTree;

@end

/**
 * The CPParser class allows you to parse token streams.
 *
 * Parsers are built by constructing a grammar, and then using it to create a parser.  The parser delegate may be used to monitor and replace output from the parser.
 *
 * @warning Note that CPParser is an abstract superclass.  Use one of its subclasses to construct your parser.
 */
@interface CPParser : NSObject

///---------------------------------------------------------------------------------------
/// @name Creating and Initialising a Parser
///---------------------------------------------------------------------------------------

/**
 * Creates a parser for a certain grammar.
 *
 * @param grammar The grammar on which to base the parser.
 * @return Returns a parser that parses the input grammar, or nil if no such parser could be created.
 */
+ (id)parserWithGrammar:(CPGrammar *)grammar;

/**
 * Initialises a parser for a certain grammar.
 *
 * @param grammar The grammar on which to base the parser.
 * @return Returns a parser that parses the input grammar, or nil if no such parser could be created.
 */
- (id)initWithGrammar:(CPGrammar *)grammar;

///---------------------------------------------------------------------------------------
/// @name Managing the Delegate 
///---------------------------------------------------------------------------------------

/**
 * The parser's delegate.
 */
@property (readwrite,assign) id<CPParserDelegate> delegate;

///---------------------------------------------------------------------------------------
/// @name Finding out about the parsed Grammar 
///---------------------------------------------------------------------------------------

/**
 * The parser's grammar.
 */
@property (readonly,retain) CPGrammar *grammar;

///---------------------------------------------------------------------------------------
/// @name Parsing a Token Stream.
///---------------------------------------------------------------------------------------

/**
 * Parses an input token stream.
 * 
 * Currently if errors are generated, `nil` is returned and the error Logged using NSLog.  This behaviour may change in the future to return the error in a more usable form.
 *
 * @param tokenStream The token stream to parse.
 * @return Returns the parsed syntax tree for the whole stream or `nil` if the token stream could not be parsed.
 */
- (id)parse:(CPTokenStream *)tokenStream;

@end