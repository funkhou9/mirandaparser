#include "miranda.h"


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
	tmp = parse_l(line.at(2), sep);
	tmp2 = parse_l(tmp.at(1), sep_range);
	tmp3 = parse_l(tmp.at(0), sep_equals);

	this->chr_range = tmp2;
	this->chr = tmp3.at(1);

	tmp = parse_l(line.at(5), sep_equals);
	this->strand = tmp.at(1);

	// hit contains the remainder of the information
	line = parse_l(hit);

	// Remove leading '>' character
	this->mirna = line.at(0).erase(0, 1);

	this->sequence = line.at(1);
	this->bind_range.push_back(line.at(6));
	this->bind_range.push_back(line.at(7));
}

void Scan::adjust_pos()
{
	if (strand == "-") {
	  this->pos1 = std::stol(chr_range[1]) - (std::stol(bind_range[1])-1);
	  this->pos2 = std::stol(chr_range[1]) - (std::stol(bind_range[0])-1);
	} else {
	  this->pos1 = std::stol(chr_range[0]) + (std::stol(bind_range[0])-1);
	  this->pos2 = std::stol(chr_range[0]) + (std::stol(bind_range[1])-1);
	}
}



// GLOBALS
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
                                   const char sep)
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

std::ostream& operator<<(std::ostream& os, Scan& S)
{
	os << S.mirna << '\t' << S.sequence << '\t' << S.chr << '\t' << '\t' <<
		S.pos1 << '\t' << S.pos2 << '\t' << S.strand;
	return os;
}

















