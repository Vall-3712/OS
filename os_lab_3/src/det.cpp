#include<iostream>
#include<math.h>
#include<vector>
using namespace std;

int det(int n, vector<vector<int>> matrix) {
   int determinant = 0;
vector<vector<int>> minor(n, vector <int> (n) );
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
         determinant = determinant + (pow(-1, x) * matrix[0][x] * det(n - 1,  minor));
      }
   }
   return determinant;
}
int main() {
   int n, i, j;
   cout << "Введите порядок матрицы:\n";
   cin >> n;
   vector<vector<int>> matrix(n, vector <int> (n) );
   cout << "Введите элементы матрицы:\n";
   for (i = 0; i < n; i++)
   for (j = 0; j < n; j++)
   cin >> matrix[i][j];
   cout<<"Определитель матрицы:\n"<< det(n, matrix) << "\n ";
   return 0;
}