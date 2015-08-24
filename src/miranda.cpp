#include "miranda.h"


// GLOBALS
// Utility function to split a string into a vector
// Overloaded to include delimiter or not
std::vector< std::string > parse_l(const std::string& line)
{
  std::istringstream iss(line);
  std::string attr;
  std::vector< std::string > attr_set;

  // Deposit tokens into vector
  while (iss) {
    iss >> attr;
    attr_set.push_back(attr);
  }
  return attr_set;
}

std::vector< std::string > parse_l(const std::string& line,
                                   char&& sep)
{
  std::istringstream iss(line);
  std::string attr;
  std::vector< std::string > attr_set;

  // Deposit tokens into a vector, remove sep
  while (getline(iss, attr, sep)) {
    attr_set.push_back(attr);
  }
  return attr_set;
}


// Scan METHODS
Scan::Scan(const std::string& header,
		       const std::string& hit)
{
	std::vector< std::string > line;
	std::vector< std::string > tmp;
	std::vector< std::string > tmp2;
	std::vector< std::string > tmp3;

	// 'header line' contains reference sequence and strand info. Needed for
	//	chr_range and strand
	line = parse_l(header);
	tmp = parse_l(line[2], ':');
	tmp2 = parse_l(tmp[1], '-');
	tmp3 = parse_l(tmp[0], '=');

	this->chr_range = tmp2;
	this->chr = tmp3[1];

	tmp = parse_l(line[5], '=');
	this->strand = tmp[1];

	// hit contains the remainder of the information
	line = parse_l(hit);

	// Remove leading '>' character
	this->mirna = line[0].erase(0, 1);

	this->sequence = line[1];
	this->bind_range.push_back(line[6]);
	this->bind_range.push_back(line[7]);
}

void Scan::adjust_pos()
{
	if (strand == "-") {
	  this->pos1 = std::stol(chr_range[1]) - (std::stol(bind_range[1]) - 1);
	  this->pos2 = std::stol(chr_range[1]) - (std::stol(bind_range[0]) - 1);
	} else {
	  this->pos1 = std::stol(chr_range[0]) + (std::stol(bind_range[0]) - 1);
	  this->pos2 = std::stol(chr_range[0]) + (std::stol(bind_range[1]) - 1);
	}
}

// Friendly cout
std::ostream& operator<<(std::ostream& os, Scan& S)
{
	os << S.mirna << '\t' << S.sequence << '\t' << S.chr << '\t' << '\t' <<
		S.pos1 << '\t' << S.pos2 << '\t' << S.strand;
	return os;
}
