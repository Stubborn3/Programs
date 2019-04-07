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

void Matrix_inReducedEchelon(float **matrix, int r, int c){
	float num;
	int i = r-1;
	while(i > 0){
		if(matrix[i][i] == 0 ){
			i--;
			continue;
		}
		if(matrix[i][i] == 1){
			int j = i-1;
			while(j >= 0){
				num = matrix[j][i];
				for(int k = 0; k < c; k++){
					matrix[j][k] = matrix[j][k] - (num*matrix[i][k]);
				}
				j--;
			}
	 	}
	i--;
	}
}

bool ZeroRowCondtion(float **matrix, int r, int c){
	cout << "First" << endl;
	int count;
	int i = 0;
	while(i < r){
		count = 0;
		for(int j = 0; j < c; j++){
			if(matrix[i][j] == 0 && i != r-1){
				count++;
			}
		}
		if(count == c){ 
			return false;
		}
		i++;
	}
	return true;
}
bool EchelonFormCondition(float **matrix, int r, int c){
	cout << "second" << endl;
	int i = 0;
	while(i < c-1){
		if(matrix[i][i] != 0){
			int j = i+1;
			while(j < r){
				if(matrix[j][i] != 0){
					return false;
				}
			j++;
			}	
		}
	i++;
	}
	return true;
}
bool PivotElementCondition(float **matrix, int r, int c){
	cout << "third" << endl;
	for(int i = 0; i < r; i++){
		for(int j = 0; j < c; j++){
			if(matrix[i][j] != 1 && matrix[i][j] != 0 && matrix[i][j+1] == 1  && i == j){
				return false;
			}
			else if(matrix[i][j] != 1 && i == j && matrix[i][j] != 0){
				return false;
			}
		}
	}
	return true;
}

bool ReducedEchelonFormCondition(float **matrix, int r, int c){
	cout << "forth" << endl;
	int i = 0;
	while(i < c){
		int j = 0;
		while(j < r){
			if(matrix[j][i] == 0 && i != j){
				j++;
				continue;
			}
			else if(matrix[j][i] != 0 && i != j && i < c){
				return false;
			}
		j++;
		}
	i++;	
	}
	return true;
	
}
void is_reducedEche_form(float **matrix, int row, int col) {
	if(ZeroRowCondtion(matrix, row, col) == true){
		if(EchelonFormCondition(matrix, row, col) == true){
			if(PivotElementCondition(matrix, row, col)  == true){
				if(ReducedEchelonFormCondition(matrix, row, col)  == true){
					cout << "It is Already Reduced Echelon Form" << endl;
					return;
				}
			}
		}
	}
	if(ZeroRowCondtion(matrix, row, col) == false || EchelonFormCondition(matrix, row, col) == false || PivotElementCondition(matrix, row, col) == false){
		Matrix_inEchelon(matrix, row, col);
		Matrix_inReducedEchelon(matrix, row, col);
		return;
	}
	if(ReducedEchelonFormCondition(matrix, row, col) == false){
		Matrix_inReducedEchelon(matrix, row, col);
		return;		
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
		
		out << row << endl;
		out << col << endl;
		is_reducedEche_form(matrix, row, col);
		for (int k = 0; k < row; k++){
			for (int j = 0; j < col; j++){
				out << matrix[k][j] << "  ";
			}
			out << endl;
		}
		free_memory(matrix, row); // to free the memory allocated

	}

}
