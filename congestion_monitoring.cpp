#include <iostream>
using namespace std;

// maxSize of the table will be 43 because there are total 42 edges in our graph
// and we choose 43 because its a prime number(to reduce collisions)

struct hashNode{
    hashNode *next;
    int vehicleCount;
    string start;
    string end;

    hashNode(string start = "", string end = "", int vehicleCount = 0, hashNode *next = NULL){
        this -> next = next;
        this -> vehicleCount = vehicleCount;
        this -> start = start;
        this -> end = end;
    }
};

class HashTable{
    private:
        hashNode **table;
        int tableSize;
    
    public:
        HashTable(int tableSize = 0, hashNode **table = nullptr){
            this -> tableSize = tableSize;
            this -> table = new hashNode*[tableSize];

            for(int i = 0; i < tableSize; i++){
                table[i] = NULL;
            }
        }

        int hash(string start, string end){ //Hashing Function
            string temp = start + "->" + end; // This ensures that every road section has a unique representation
            int hashValue = 0;
            for(int i = 0; temp[i] != '\0'; i++){
                hashValue += temp[i]; //ASCII value will be used to generate hashValue
            }
            return hashValue % tableSize;
        }

        void insertToHash(string start, string end, int vehicleCount){
            int index = hash(start, end);
            
            hashNode *present = table[index];
            if(present == NULL){
                hashNode *newNode = new hashNode(start, end, vehicleCount);
                table[index] = newNode;
            }
            
            else{
                while(present != NULL){
                    if(present -> start == start && present -> end == end){
                        present -> vehicleCount += 1;
                        return;
                    }
                    present = present -> next;
                }
                hashNode *newNode = new hashNode(start, end, vehicleCount);
                present -> next = newNode;
            }
        }


};



// void readcsv(){

// }

int main(){

}








