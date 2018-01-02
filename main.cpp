#include <iostream>
#include <random>
#include <chrono>
#include <thread>
#include <future>

void random_number_generator(std::promise<double> accumulate_promise){

	std::random_device rd;
	std::mt19937_64 gen(rd());
	std::uniform_real_distribution<> dist(0, 1);
	int count = 100'000'000;
	double x = 0;
	double y = 0;
	double inside = 0;
	
	for(unsigned int i = 0; i < count/2; i++){
		x = dist(gen);
		y = dist(gen);

		if((x*x + y*y) <= 1){
			inside += 1;
		}
	}

//	std::cout << "inside = " << inside << std::endl;
	accumulate_promise.set_value(inside);
}

int main(){
	unsigned int n = std::thread::hardware_concurrency();
	std::cout << n << " concurrent threads are supported." << std::endl;

	double pi = 3.141592653589793;

	double inside = 0;

	std::promise<double> ap1, ap2;
	std::future<double> af1 = ap1.get_future();
	std::future<double> af2 = ap2.get_future();
	
	std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();

	std::thread t1(random_number_generator, std::move(ap1));
	std::thread t2(random_number_generator, std::move(ap2));

	af1.wait();
	af2.wait();
	inside = af1.get() + af2.get();
	std::cout << "Inside = " << inside << std::endl;
	std::cout << "Calculated value: " << inside/100'000'000 << std::endl;
	t1.join();
	t2.join();

	std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

	std::cout << "Real value: " << pi/4 << std::endl;
	std::cout << "Computing took: " 
		<< std::chrono::duration_cast<std::chrono::seconds>(end - start).count() 
		<< " s" << std::endl;

	return 0;
}
