// A library for parsing miranda output
#include "miranda.h"


int main(int argc, char* argv[])
{
	std::string line;
	std::string read_seq;
	std::string hit;
	int l;
	bool flag = false;

	std::ifstream mir(argv[1]);
	while (getline(mir, line)) {
		
		// If "Read Sequence:" found, check if ">"
		//	is found 15 lines after - signifying a true hit.
		if (line.find("Read Sequence:") == 0) {
			
			// Store line set flag to 'start counting'
			//	and reset count
			l = 0;
			flag = true;
			read_seq = line;			
		}

		l++;

		// flag prevents it from just grabbing the
		//	15th line from the top
		if (flag & (l == 15)) {
			if(line.find(">") == 0) {
				
				// If hit found, store and use to
				//	initialize Scan object
				hit = line;
				
				Scan Seq(read_seq, hit);
				Seq.adjust_pos();
				std::cout << Seq << std::endl;

				flag = false;
			}
		}
	}		
	return 0;
}