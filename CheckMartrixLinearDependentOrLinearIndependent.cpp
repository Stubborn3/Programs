#include<iostream>
#include<fstream>
using namespace std;

void Matrix_InterChange(float **matrix, int i,int r, int c){
	if(matrix[i+1][i] != 0 && matrix[i][i] == 0 && i != c-1){
		for(int k = 0; k < c; k++){
			float temp;
			temp = matrix[i][k];
			matrix[i][k] = matrix[i+1][k];
			matrix[i+1][k] = temp;
		}
			return;
	}
	if(matrix[i-1][i] != 0 && matrix[i][i] == 0 && matrix[i][i-1] != 0 && i == c-1){ 
		for(int k = 0; k < c; k++){
			float temp;
			temp = matrix[i][k];
			matrix[i][k] = matrix[i-1][k];
			matrix[i-1][k] = temp;
		}
		return;
	}
	if(matrix[i][i] == 0 && matrix[i+1][i] != 0 && r > c){
		for(int k = 0; k < c; k++){
			float temp;
			temp = matrix[i][k];
			matrix[i][k] = matrix[i+1][k];
			matrix[i+1][k] = temp;
		}
		return;
		
	}	
	if(matrix[i+1][i] == 0 && matrix[i][i] == 0 && matrix[i+1][i+1] != 0 && i != c-1 ){ 
		for(int k = 0; k < c; k++){
			float temp;
			temp = matrix[i][k];
			matrix[i][k] = matrix[i+1][k];
			matrix[i+1][k] = temp;
		}
		return;
	}
}

bool zeroColumn(float **matrix, int r, int c){
	int count;
	for(int i = 0; i < c; i++){
		count = 0;
		for(int j = 0; j < r; j++){
			if(matrix[j][i] == 0){
				count++;
			}
		}
		if(count == r){
			return true;
		}
	}
	return false;
}

void Matrix_inEchelon(float **matrix, int r, int c){
	float num;
	int i = 0;
	while(i < r){
		if(matrix[i][i] == 0 && i < r-1){
			Matrix_InterChange(matrix, i, r, c);
		}
		if(matrix[i][i] != 1 && matrix[i][i] != 0){
			float number =  matrix[i][i];
			int l = 0;
			while(l < c){
				if(matrix[i][l] != 0){
					matrix[i][l] = matrix[i][l] / number;
				}
			l++;	
			}
		}
		if(matrix[i][i] == 1 && matrix[i][i] != 0){
			int j = i+1;
			while(j < r){
				num = matrix[j][i];
				for(int k = 0; k < c; k++){
					matrix[j][k] = matrix[j][k] - (num*matrix[i][k]);
				}
				j++;
			}
	 	}
	i++;
	}
}


bool LinearDependentOrIndependent(float **matrix, int row, int col) {
	int rank = 0;
	int noOfVariables;
	if (zeroColumn(matrix, row, col) == true){
		return false;
	}
	if(zeroColumn(matrix, row, col) == false){
		Matrix_inEchelon(matrix, row, col);
		for(int i = 0; i < row; i++){
			for(int j = 0; j < row; j++){
				if(matrix[i][j] != 0 && i == j){
					rank++;
				}	
			}
		}
		noOfVariables = col;
		if(rank == noOfVariables){
			return true;
		}
		else{
			return false;
		}	
	}
}

void alloca_memory(float **matrix, int row, int col) {
	for (int i = 0; i < row; i++)
		matrix[i] = new float[col];
}

void free_memory(float **matrix, int row) {
	for (int i = 0; i > row; i++)
		delete[] matrix[i];
	delete[] matrix;
}

int main() {

	int row = 0, col = 0, tmatrix = 0;
	float **matrix;
	ifstream in("in.txt");
	ofstream out("out.txt"); // will automatically created if not present

	if (!in.is_open()) {
		cout << "Error in opening file" << endl;
		return 0;
	}

	in >> tmatrix;

	for (int i = 0; i < tmatrix; i++) {
		in >> row >> col;
		matrix = new float*[row];
		alloca_memory(matrix, row, col);

		for (int k = 0; k < row; k++) 
			for (int j = 0; j < col; j++)
				in >> matrix[k][j];
		
		out << i+1 << endl;
		
		if(LinearDependentOrIndependent(matrix, row, col) == true){
			out << "Linear Independent(Trivial Solution) \n"; 
		}
		else{
			out << "Linear Dependent(Non Trivial Solution) \n"; 
		}	
		free_memory(matrix, row); // to free the memory allocated

	}

}
