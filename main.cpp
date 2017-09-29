#include <iostream>
#include <random>
#include <cmath>

using namespace std;

int main(){

	random_device rd;
	uniform_real_distribution<> dist(0, 1);
	double x = 0;
	double y = 0;
	int c = 0;
	double count = 1000000;
	
	double inside = 0;

	while(c < count){
		x = dist(rd);
		y = dist(rd);

		if((x*x + y*y) <= 1){
			inside++;
		}
		c++;
	}

	cout << inside/count << endl;
	cout << 3.14/4 << endl;

	return 0;
}
