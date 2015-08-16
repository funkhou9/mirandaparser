#ifndef MIRANDA
#define MIRANDA

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

/********************************************************************** 
 * Simple parser for Miranda output.
 *
 *	Tested with miranda output involving all known miRNA sequences
 *		downloaded from mirbase, with all 3'UTR sequences from the same
 *		organism.
 *
 * Goals:
 *  - Intended to tabulate results with chromosomal positions for each
 *		miRNA target prediction site. Nothing more for now.
 *  
 *  
 * Author: Scott Funkhouser <funkhou9@msu.edu>
 **********************************************************************/



class Scan {

	// A miranda scan (with a successful hit) has the following features
	//	...along with plenty of others that I'm not bothering to parse at the
	//	moment
	
	// Reference sequence name
	std::string sequence;

	// Reference sequence chromosome
	std::string chr;

	// Query miRNA name
	std::string mirna;

	// Reference position range, in chromosomal coordinates
	std::vector< std::string > chr_range;

	// Range that miRNA binds, a subset of chr_range
	std::vector< std:: string > bind_range;

	// Strand that reference UTR came from
	std::string strand;

	// Absolute chromosomal positions of mirna target site
	long pos1;
	long pos2;

public:
	// Constructed with 'header' line, beginning with "Read Sequence:"
	//	and hit line beginning with '>'<name of mirna>
	Scan(const std::string& header, const std::string& hit);

	// Determines absolute chromosomal position of mirna target site,
	//	pos1 and pos2, given chr_range and bind_range
	void adjust_pos();

	// Printing friendly
	friend std::ostream& operator<<(std::ostream& os, Scan& S);
};


// Globals used for parse_l()
char sep = ':';
char sep_range = '-';
char sep_equals = '=';

// Utility function to split a string into a vector
// Overloaded to include delimiter or not
std::vector< std::string > parse_l(const std::string& line);
std::vector< std::string > parse_l(const std::string& line,
                                   char sep);


#endif