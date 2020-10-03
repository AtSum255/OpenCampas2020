#include<iostream>
#include<chrono>
#include<random>
#include<algorithm>

std::chrono::system_clock::time_point start, end;

double alpha(int N, int K, int A[]){
	int res = 0;
	start = std::chrono::system_clock::now();
	
	//実際の処理
	for(int i = 0; i < N; ++i){
		if(A[i] >= K)++res;
	}
	//ここまで

	end = std::chrono::system_clock::now();
	return std::chrono::duration_cast<std::chrono::nanoseconds>(end-start).count(); 
}


double beta(int N, int K, int A[]){
	int res = 0;
	start = std::chrono::system_clock::now();
	
	//実際の処理
	for(int i = 0; i < N; ++i){
		if(A[i] >= K){
			res = N - i;
			break;
		}
	}
	//ここまで

	end = std::chrono::system_clock::now();
	return std::chrono::duration_cast<std::chrono::nanoseconds>(end-start).count(); 
}


double gamma(int N, int K, int A[]){
	int res = 0;
	start = std::chrono::system_clock::now();

	//実際の処理
	int* pos = std::lower_bound(A, A+N, K);
	res = N - (int)(pos-A) + 1;
	//ここまで

	end = std::chrono::system_clock::now();
	return std::chrono::duration_cast<std::chrono::nanoseconds>(end-start).count(); 
}


int main(){
	int trial;
	int array_len;
	double sum_times_alpha = 0.0;
	double sum_times_beta = 0.0;
	double sum_times_gamma = 0.0;
	int nk;
	int narray[1001000];
	std::random_device seed_gen;
	std::mt19937 engine(seed_gen());

	scanf("%d %d", &trial, &array_len);
	for(int i = 0; i < trial; ++i){
		for(int j = 0; j < array_len; ++j){
			narray[j] = engine() % 10001;
		}
		std::sort(narray, narray + array_len);
		nk = engine() % 10001;
		sum_times_alpha += alpha(array_len, nk, narray);
		sum_times_beta += beta(array_len, nk, narray);
		sum_times_gamma += gamma(array_len, nk, narray);
	}

	printf("algorithm_alpha -> [%f nsec]\n", sum_times_alpha/trial);
	printf("algorithm_beta -> [%f nsec]\n", sum_times_beta/trial);
	printf("algorithm_gamma -> [%f nsec]\n", sum_times_gamma/trial);
	return 0;
}
