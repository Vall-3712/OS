#include<pthread.h>
#include<iostream>
#include<ctime>
#include<vector>
#include<fstream>
#include<chrono>
#include <stdio.h>
#include <stdlib.h>
#include<math.h>

using namespace std;

int flag = 0;

typedef struct arguments {
   int num_of_thread;
   int total;
   int size;
   vector<int> *minors;
   vector<vector<int>> *matrix;
} arg;

int det(int n, vector<vector<int>> * matrix) {
   int determinant = 0;
   vector<vector<int>> minor(n, vector<int> (n) );
   if (n == 1) {
      return (*matrix)[0][0];
   }
   if (n == 2)
      return (((*matrix)[0][0] * (*matrix)[1][1]) - ((*matrix)[1][0] * (*matrix)[0][1]));
   else {
      for (int x = 0; x < n; x++) {
         int subi = 0;
         for (int i = 1; i < n; i++) {
            int subj = 0;
            for (int j = 0; j < n; j++) {
            if (j == x)
            continue;
            minor[subi][subj] = (*matrix)[i][j];
            subj++;
            }
         subi++;
      }
      determinant = determinant + (pow(-1, x) * (*matrix)[0][x] * det(n - 1, &minor));
      
      }
   }
return determinant;
}

int count_minor(int n, int x, vector<vector<int>> * matrix) {
   vector<vector<int>> minor(n - 1, vector<int> (n - 1));
   for (int i = 1; i < n; ++i) {
      for (int j = 0; j < x; ++j) {
      minor[i - 1][j] = (*matrix)[i][j];
      }
      for (int j = x + 1; j < n; ++j) {
      minor[i - 1][j - 1] = (*matrix)[i][j];
      }
   }
   return det(n - 1, &minor);
}

void *thread_function(void *arguments) {
   arg args = * (arg *)arguments;
   int num_of_thread = args.num_of_thread;
   int total = args.total;
   flag = 1;
   vector<int> *minors = args.minors;
   vector<vector<int>> *matrix = args.matrix;
   int size = args.size;

   for (int i = num_of_thread; i < size; i += total) {
      int result = count_minor(size, i, matrix);
      (*minors)[i] = result;
   }
}

int main(int argc, const char **argv) {
int n, i, j;
int count_threads;
count_threads = atoi(argv[1]);
cout << "Введите порядок матрицы:\n";
cin >> n;
vector<vector<int>> matrix(n, vector <int> (n) );
cout << "Введите элементы матрицы:\n";
for (i = 0; i < n; i++)
for (j = 0; j < n; j++)
cin >> matrix[i][j];

chrono::steady_clock::time_point begin = chrono::steady_clock::now();
vector<int> minors(n, 0);
pthread_t threads[count_threads];
for (int i = 0; i < count_threads; ++i) {
   arg args = {i, count_threads, n, &minors, &matrix};
   pthread_create(&threads[i], NULL, thread_function, &args);
   while (flag == 0) {
   }
   flag = 0;
}  
for (int i = 0; i < count_threads; ++i) {
   pthread_join(threads[i], NULL);
}
int result = 0;
for (int i = 0; i < n; ++i) {
   if (i % 2 == 0)
   result += minors[i] * matrix[0][i];
   else
   result -= minors[i] * matrix[0][i];
}

chrono::steady_clock::time_point end = chrono::steady_clock::now();

cout<<"Определитель матрицы:\n"<< result << "\n ";

cout<<"Время: " << chrono::duration_cast<chrono::microseconds>(end-begin).count();
cout<<"\n";
return 0;
}
