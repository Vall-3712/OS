#include<pthread.h>
#include<iostream>
#include<ctime> 
#include<vector>
#include<fstream>
#include<chrono>
#include<math.h>

using namespace std;
pthread_mutex_t mutex;
int flag = 0;

struct arg_to_thread {
	int* matrix;
	int partition;
	int num_of_thread;
	int count_threads;
	int n;
};

void* thread_func(void *args)
{	
    int minimum = 1e9;
	arg_to_thread* arguments = (arg_to_thread*) args;
	int num_of_thread = arguments->num_of_thread;
	int partition = arguments->partition;
	flag = 1;
	int count_threads = arguments->count_threads;
	int n = arguments->n;
	int* matrix = arguments->matrix;
   int res;

		if (num_of_thread != count_threads - 1) {
			for (int j = num_of_thread * partition; j < num_of_thread * partition + partition; ++j) {
            res = det(matrix, n);
			}	
		} else {
			for (int j = n - 1; j > n - partition - 1; --j) {	
            res = det(matrix, n);
                    
			}	

		}


	
	return 0;
}

int det( int matrix[10][10], int n) {
   int determinant = 0;
   int minor[10][10];
   if (n == 2)
   return ((matrix[0][0] * matrix[1][1]) - (matrix[1][0] * matrix[0][1]));
   else {
      for (int x = 0; x < n; x++) {
         int subi = 0;
         for (int i = 1; i < n; i++) {
            int subj = 0;
            for (int j = 0; j < n; j++) {
               if (j == x)
               continue;
               minor[subi][subj] = matrix[i][j];
               subj++;
            }
            subi++;
         }
         determinant = determinant + (pow(-1, x) * matrix[0][x] * det( minor, n - 1 ));
      }
   }
   return determinant;
}


int main(int argc, char const *argv[]){
	
   ifstream file("./src/big_massives.txt");
	int count_threads;
	cout<<"Введите количество потоков: ";
	cin>>count_threads;
	cout<<endl;
	int n;
   int i, j;
   //int matrix[10][10];
   cout << "Введите порядок матрицы:\n";
   cin >> n;
   vector<vector<int>>matrix(n);
   cout << "Введите элементы матрицы:\n";
   for (i = 0; i < n; i++)
   for (j = 0; j < n; j++)
   cin >> matrix[i][j];


   pthread_t threads[count_threads];

	pthread_mutex_init(&mutex, NULL);
	int partition = n / count_threads;
	struct arg_to_thread arg;
	arg.partition = partition;
	//arg.matrix = matrix.data();
	arg.count_threads = count_threads;
	arg.n = n;
/*chrono::steady_clock::time_point begin = chrono::steady_clock::now();
	for (int i = 0; i < count_threads; i++) {
		arg.num_of_thread = i;
		if (i == count_threads - 1) {
			partition += size_array % count_threads;
			arg.partition = partition;
		}
		int status = pthread_create(&threads[i], NULL, thread_func, (void*)&arg);
		while(flag != 1) {
			//ожидание пока функции передадутся аргументы
		}
		flag = 0;
		if (status != 0) {
			cout<<"Create thread error"<<endl;
		}
	}

	for (int i = 0; i < count_threads; ++i) {
		pthread_join(threads[i], NULL);
	}
    chrono::steady_clock::time_point end = chrono::steady_clock::now();

	pthread_mutex_destroy(&mutex);
    int minimum2 = 1e9;
    for (int i = 0; i < count_threads; ++i) {
        if (result[i] < 1e9) {
            minimum2 = result[i];
        }
    }
	cout<<"Минимальное значение: "<<minimum2<<endl;
    cout<<chrono::duration_cast<chrono::microseconds>(end-begin).count();
	return 0;

}*/

   cout<<"Det of the matrix is:\n"<< det(matrix, n) << "\n ";
   return 0;
}