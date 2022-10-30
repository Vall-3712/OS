#include <stdio.h>
#include <stdlib.h>

int m,n; // original matrix dimensions

int det(int B[m][n]);

int main() {
    int determinant;
    register int row,column;

    printf("Enter matrix order\n");
    scanf("%d",&n);
    
    int A[n][n];

    printf("Enter matrix elements\n");

    for(row = 0; row < n; row++)
        for(column = 0; column < n; column++)
            scanf("%d",&A[row][column]);
            
    determinant = det(A);

    printf("determinant = %d \n",determinant);

    return 0;
}

int det(int B[n][n]) {
    int row_size = n;
    int column_size = n;

    if (row_size != column_size) {
        printf("DimensionError: Operation Not Permitted \n");
        exit(1);
    }

    else if (row_size == 1)
        return (B[0][0]);

    else if (row_size == 2)
        return (B[0][0]*B[1][1] - B[1][0]*B[0][1]);

    else {
        int minor[row_size-1][column_size-1];
        int row_minor, column_minor;
        int firstrow_columnindex;
        int sum = 0;

        register int row,column;

        // exclude first row and current column
        for(firstrow_columnindex = 0; firstrow_columnindex < row_size;
                firstrow_columnindex++) {

            row_minor = 0;

            for(row = 1; row < row_size; row++) {

                column_minor = 0;

                for(column = 0; column < column_size; column++) {
                    if (column == firstrow_columnindex)
                        continue;
                    else
                        minor[row_minor][column_minor] = B[row][column];

                    column_minor++;
                }

                row_minor++;
            }

            m = row_minor;
            n = column_minor;

            if (firstrow_columnindex % 2 == 0)
                sum += B[0][firstrow_columnindex] * det(minor);
            else
                sum -= B[0][firstrow_columnindex] * det(minor);

        }

        return sum;

    }
} 