#include <iostream>
using namespace std;
struct node{
	long long info;
	node *next;
	long long shift;
};
class multiplication{
	private:
		node *ptr, *temp, *head, *head1, *result_head;
		long long count, i, total_number;
	public:
		multiplication(){
			ptr = temp = head1 = head = result_head = NULL;
			count = i = 0;
		}
		~multiplication(){
			delete ptr, temp, head1,result_head, head;
		}
		void insert_LinkList(long long num){      // digits store in link List 
			long long mod_num = 0;
			count = 0;
			while (num != 0){
				mod_num = num % 10;
				temp = new node;
				temp->info = mod_num;
				temp->next = ptr;
				ptr = temp;
				ptr->shift = count;
				count++;
				num /= 10;
			}
			if(count % 2 != 0){
				temp = new node;
				temp->info = 0;
				temp->next = ptr;
				ptr = temp;
				ptr->shift = count;
			}
			if(head == NULL){
				head = ptr;
				ptr = NULL;
				return;
			}
			head1 = ptr;
		}
		void multiply(){
			for(temp = head; temp != NULL; temp = temp->next){
				for(ptr = head1; ptr != NULL; ptr = ptr->next){
					divideAndConquer();
				}
			}
		}
		void divideAndConquer(){
			long long total_Shift, num;
			count = total_number = num = 0;
			while(count != ptr->info){
				if(ptr->info > 0){
					total_number +=  temp->info;
					count++;
				}
				else{
					total_number -=  temp->info;
					count--;
				}
			}
			i++; 
			total_Shift = temp->shift + ptr->shift; 
			cout << i << ") " << temp->info  << " Multiply " << ptr->info <<  " Shift " << total_Shift;
			shifting(total_Shift);
			cout << " Result " << total_number << endl;
			node *ptr1, *temp1; 		// result store in link list
			ptr1 = new node;
			ptr1->info = total_number;
			if(result_head == NULL){
				result_head = ptr1;
			}
			else{
				temp1->next = ptr1;
			}
			ptr1->next = NULL;
			temp1 = ptr1;
		}
		void shifting(long long shift){ // shifting
			long long number;
			for(int m = 1; m <= shift; m++){
				number = 0;
				for(int n = 1; n <= 10; n++){
					number += total_number;
				}
				total_number = number;
			}
		}
		void print_result(){
			count = 0;
			for(temp = result_head; temp != NULL; temp = temp->next){
				count += temp->info;
			}
			cout << "Total Sum of Result: " << count << endl;
		}
}; 
int main(){
	multiplication mul;
	long long number;
	cout << "Enter the 1st Num: ";
	cin >> number;
	mul.insert_LinkList(number);
	cout << "Enter the 2nd Num: ";
	cin >> number;
	mul.insert_LinkList(number);
	mul.multiply();
	mul.print_result();
}
