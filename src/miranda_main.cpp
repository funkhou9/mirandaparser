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
		
		// If "Read Sequence:" check if "Scores for this hit"
		//	is found after - signifying a true hit.
		if (line.find("Read Sequence:") == 0) {
			l = 0;
			flag = true;
			read_seq = line;			
		}

		l++;

		if (flag & (l == 15)) {
			if(line.find(">") == 0) {
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