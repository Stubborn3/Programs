#include <iostream>
using namespace std;

class MedianAlgorithm{
	private:
		int *array1, *array2, *FinalArray, *ptr, *temp, *current;
		int size1, size2, size;
		bool flag_ptr, flag_temp;
	public:
		MedianAlgorithm(){
			size1 = size2 = size = 0;
			flag_ptr = flag_temp = false;
			ptr = current = temp = array1 = array2 = FinalArray = NULL;
			array1 = new int[100];
			array2 = new int[100];
			FinalArray = new int[200];
		}
		
		void Input_List(){
			cout << "Enter the size of List 1: ";
			cin >> size1;
			cout << "Enter the Values" << endl;
			ptr = array1;
			for(int i = 1; i <= size1; i++){
				cin >> *ptr;
				ptr++;
			}
			cout << "Enter the size of List 2: ";
			cin >> size2;
			cout << "Enter the Values" << endl;
			temp = array2;
			for(int i = 1; i <= size2; i++){
				cin >> *temp;
				temp++;
			}
		}
		
		void Median(){
			size = size1 + size2;
			ptr = array1;
			temp = array2;
			current = FinalArray;
			for(int i = 1; i <= size; i++){
				if(*ptr <= *temp && ptr != array1 + size1){
					*current = *ptr;
					ptr++;
				}
				else if(*ptr >= *temp && temp != array2 + size2){
					*current = *temp;
					temp++;
			 	}
			 	else{
			 		if(ptr != array1 + size){
			 			*current = *temp;
						temp++;
					}
					else{
						*current = *ptr;
						ptr++;
					}	
				}
				current++;
			}
			
			if(size % 2 == 0){
				ptr = FinalArray + size/2-1;
				temp = FinalArray + size/2;
				cout << *ptr << " " << *temp << endl;
			}
			else{
				temp = FinalArray + size/2;
				cout << *temp << endl;
			}
			
		}
		
		
};






int main(){
	MedianAlgorithm obj;
	obj.Input_List();
	obj.Median();
}
