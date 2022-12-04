/**************************************************************************/
/*                                                                        */
/*   Experiment 1                                                         */
/*                                                                        */
/*   To compile: g++ experiment.cpp timer.cpp -std=c++0x                 */
/*   Alter this main to help answer your first experiment question        */
/*                                                                        */
/**************************************************************************/

#include "table.h"
#include "timer.h"
#include <string>
#include <iostream>
#include <cstdlib>

const int maxRecords=2000000;

void createData(std::string keys[],int data[],int max);
int main(int argc, char* argv[]){

    //this makes it easier to supply values on command line without recompiling
    //alternatively you can also just hard code the values and perhaps even loop 
    //through the values to create a csv
	if(argc != 3){
		std::cout << "usage: a.out numrecords capacity" << std::endl;
		return 0;
	}

    std::string* keys = new std::string[maxRecords];        //list of test cases. 
    int* data=new int[maxRecords];
    createData(keys,data,maxRecords);

    int numrecords=atoi(argv[1]);
    size_t cap=atoi(argv[2]);


    std::cout << "number of records: " << numrecords << std::endl;
    std::cout << "capacity: " << cap << std::endl;

    LPTable<int> table1(cap, 0.4);
	LPTable<int> table2(cap, 0.6);
	LPTable<int> table3(cap, 0.8);
    ChainingTable<int> table4(cap, 0.5);
	ChainingTable<int> table5(cap, 1.4);
	ChainingTable<int> table6(cap, 1.8);


    //create a timer
    Timer T, T2, T3, T4, T5, T6;
 

    for(int i=0;i<numrecords;i++){
		table1.insert(keys[i],data[i]);
		table2.insert(keys[i],data[i]);
		table3.insert(keys[i],data[i]);
    	table4.insert(keys[i],data[i]);
		table5.insert(keys[i],data[i]);
		table6.insert(keys[i],data[i]);
    }
	int val;
	T.start();   
	for(int i=0;i<numrecords;i++){
    	table1.find("asdsafasfasfasfasfasfasfasfasfsaffasfsaffsaasf", val);
    }
	T.stop();
	T2.start();   
	for(int i=0;i<numrecords;i++){
    	table2.find("asdsafasfasfasfasfasfasfasfasfsaffasfsaffsaasf", val);
    }
	T2.stop();
	T3.start();
	for(int i=0;i<numrecords;i++){
    	table3.find("asdsafasfasfasfasfasfasfasfasfsaffasfsaffsaasf", val);
    }
	T3.stop();
	T4.start();
	for(int i=0;i<numrecords;i++){
    	table4.find("asdsafasfasfasfasfasfasfasfasfsaffasfsaffsaasf", val);
    }
	T4.stop();
	T5.start();
	for(int i=0;i<numrecords;i++){
    	table5.find("asdsafasfasfasfasfasfasfasfasfsaffasfsaffsaasf", val);
    }
	T5.stop();
	T6.start();
	for(int i=0;i<numrecords;i++){
    	table6.find("asdsafasfasfasfasfasfasfasfasfsaffasfsaffsaasf", val);
    }
	T6.stop();
    //currtime reads the time on the stop watch
    std::cout << "LP Table 1 Time: " << T.currtime() << std::endl;
	std::cout << "LP Table 2 Time: " << T2.currtime() << std::endl;
	std::cout << "LP Table 3 Time: " << T3.currtime() << std::endl;
    std::cout << "Chaining Table Time: " << T4.currtime() << std::endl;
	std::cout << "Chaining Table Time: " << T5.currtime() << std::endl;
	std::cout << "Chaining Table Time: " << T6.currtime() << std::endl;
}




void createData(std::string keys[],int data[],int max){
	FILE* fp=fopen("dictionary.txt","r");
	int i=0;
	std::string front="A_";
	char curr[50];
	while(fscanf(fp,"%s\n",curr)==1){
		keys[i]=curr;
		data[i]=rand()%100;
		i++;                      
	}
	int numWords=i;
	int j=0;
	while(i<max){
		keys[i]=front+keys[j];
		data[i]=rand()%100;
		i++;
		j++;
		if(j==numWords){
			front[0]+=1;
			j=0;
		}
	}
}

