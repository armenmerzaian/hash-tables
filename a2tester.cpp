/**************************************************************************/
/*                                                                        */
/*   A2 tester file                                                       */
/*                                                                        */
/*   To compile: g++ a2tester.cpp timer.cpp -std=c++0x                    */
/*   You will also need:                                                  */
/*      * timer.h/timer.cpp                                               */
/*      * dictionary.txt                                                  */ 
/*                                                                        */
/*                                                                        */
/*   Reminder that if you are working in VS, you need to change the       */
/*   #define PLATFORM line in timer.h                                     */
/*                                                                        */
/*                                                                        */
/**************************************************************************/

#include "table.h"
#include "timer.h"
#include <string>
#include <iostream>
#include <cstdlib>
struct Items{
    std::string word_;
    int count_;
    std::string toString() const{ 
        std::string s="{";
        s+= word_;
        s+= ",";
        s+= std::to_string(count_);
        s+= "}";
        return s;
    }
};
std::ostream& operator<<(std::ostream& os, const Items rec);
bool operator==(const Items& a,const Items& b);
bool operator!=(const Items& a,const Items& b);
bool operator<(const Items& a, const Items& b);
std::ostream& operator<<(std::ostream& os, const Items rec){
    os << rec.word_;
    return os;
}
bool operator==(const Items& a,const Items& b){
    bool rc=false;
    if(a.word_==b.word_ && a.count_==b.count_){
        rc=true;
    }
    return rc;
}
bool operator!=(const Items& a,const Items& b){
    return !(a==b);
}
bool operator<(const Items& a, const Items& b){
    bool rc=false;
    if(a.word_ < b.word_){
        rc=true;
    }
    return rc;
}

bool test1(std::string key[], int data[], int max, std::string& error);	
bool test2(std::string key[], int data[], int max, std::string& error);	
bool test3(std::string key[], int data[], int max, std::string& error);	
bool test4(std::string key[], int data[], int max, std::string& error);	
bool test5(std::string key[], int data[], int max, std::string& error);	
bool test6(std::string key[], int data[], int max, std::string& error);	
bool test7(std::string key[], int data[], int max, std::string& error);	
bool test8(std::string key[], int data[], int max, std::string& error);	
bool test9(std::string key[], int data[], int max, std::string& error);	
bool test10(std::string key[], int data[], int max, std::string& error);	
bool test11(std::string key[], int data[], int max, std::string& error);	
bool test12(std::string key[], int data[], int max, std::string& error);	
bool test13(std::string key[], int data[], int max, std::string& error);	
bool test14(std::string key[], int data[], int max, std::string& error);	
bool test15(std::string key[], int data[], int max, std::string& error);	
bool test16(std::string key[], int data[], int max, std::string& error);	
bool test17(std::string key[], int data[], int max, std::string& error);	
bool test18(std::string key[], int data[], int max, std::string& error);	
bool test19(std::string key[], int data[], int max, std::string& error);	
bool test20(std::string key[], int data[], int max, std::string& error);	
bool test21(std::string key[], int data[], int max, std::string& error);	
bool test22(std::string key[], int data[], int max, std::string& error);	

const int numTests=22;
const int maxRecords=2000000;

typedef bool (*TestPtr)(std::string [], int [], int , std::string& );
void createData(std::string keys[],int data[],int max);
int main(void){
	TestPtr runTest[numTests]={test1, test2, test3, test4, test5, 
		                       test6, test7, test8, test9, test10,
		                   	   test11, test12, test13, test14, test15, 
		                       test16, test17, test18, test19, test20,
		                   	   test21,test22};
	std::string msg;
	bool result=true;
	int numPassed=0;

    std::string* keys = new std::string[maxRecords];        //list of test cases. 
    int* data=new int[maxRecords];

    Timer t;
    double times[numTests];
    createData(keys,data,maxRecords);
	for(int i=0;result && i<numTests;i++){
		t.reset();
		t.start();
		result = runTest[i](keys,data,maxRecords,msg);
		t.stop();
		times[i]=t.currtime();
		if(!result){
			std::cout << msg << std::endl;
		}
		else{
			numPassed++;
			std::cout << "Test " << i+1 << " passed!" << std::endl;
		}
	}
	if(numPassed == numTests){
		std::cout << std::endl;
		std::cout << "  Test Number  |    Time     " << std::endl;
		std::cout << "---------------|-------------" << std::endl;

		for(int i=0;i<numTests;i++){
			std::cout << "   Test ";
			std::cout.width(2);
			std::cout << i+1;
			std::cout << "     |  " << times[i] << std::endl;
		}
		std::cout << std::endl;
		std::cout << "Congratulations! You have passed testing for A2 part 3" << std::endl;
		return 0;
	}
	else{
		std::cout << std::endl;
		std::cout << "Looks like you still have some work left to do" << std::endl;
		return 1;
	}
}
/* test1: Initialization, numRecords(),  isEmpty()
*/
bool test1(std::string keys[], int data[], int max, std::string& error){
	ChainingTable<int> table1(1000);
	ChainingTable<int> table2(10000);
	ChainingTable<int> table3(20000);
	bool isGood=true;
	if(table1.numRecords()!=0 || table2.numRecords()!=0 || table3.numRecords() != 0){
		isGood=false;
		error="Error 1a: numRecords() should return 0 when table is empty";
	}
	else if(!table1.isEmpty() || !table2.isEmpty() || !table3.isEmpty()){
		isGood=false;
		error="Error 1b: isEmpty() should return true when table is empty";
	}
	else if(table1.capacity()!=1000){
		isGood=false;
		error="Error 1c: capacity() should return ";
		error+= std::to_string(1000);
		error+=" records, your capacity() returned: ";
		error+=std::to_string(table1.capacity());				
	}
	else if(table2.capacity()!=10000){
		isGood=false;
		error="Error 1d: capacity() should return ";
		error+= std::to_string(10000);
		error+=" records, your capacity() returned: ";
		error+=std::to_string(table2.capacity());				

	}
	else if(table3.capacity()!=20000){
		isGood=false;
		error="Error 1e: capacity() should return ";
		error+= std::to_string(20000);
		error+=" records, your capacity() returned: ";
		error+=std::to_string(table3.capacity());				
	}
	else if(table1.loadFactor()!=0){
		isGood=false;
		error="Error 1c: loadFactor() should return ";
		error+= std::to_string(0);
		error+=" records, your loadFactor() returned: ";
		error+=std::to_string(table1.loadFactor());				
	}
	else if(table2.loadFactor()!=0){
		isGood=false;
		error="Error 1d: capacity() should return ";
		error+= std::to_string(0);
		error+=" records, your loadFactor() returned: ";
		error+=std::to_string(table2.loadFactor());				

	}
	else if(table3.loadFactor()!=0){
		isGood=false;
		error="Error 1e: capacity() should return ";
		error+= std::to_string(0);
		error+=" records, your loadFactor() returned: ";
		error+=std::to_string(table3.loadFactor());				
	}

	return isGood;
}

/*test2: use insert() with new records.  capacity should not change in these cases*/
bool test2(std::string keys[], int data[], int max, std::string& error){
	ChainingTable<int> table1(1000);
	ChainingTable<int> table2(10000);
	ChainingTable<int> table3(20000);

	bool isGood=true;
	int i=0;
	int count=0;
	bool rc;
	while(isGood && count<1000){
		rc=table1.insert(keys[i],data[i]);
		if(table1.isEmpty()){
			isGood=false;
			error="Error 2a: table is not empty, isEmpty() should return false, your isEmpty() returns true";
		}
		if(isGood && !rc){
			isGood=false;
			error="Error 2b: insert() returned false.  it should have returned true";
		}
		if(isGood && table1.numRecords()!=count+1){
			isGood=false;
			error="Error 2c: table should have ";
			error+= std::to_string(count+1);
			error+=" records, your numRecords() returned: ";
			error+=std::to_string(table1.numRecords());				
		}
		if(isGood && table1.capacity()!= 1000){
			isGood=false;
			error="Error 2d: table capacity should be 1000";
		}
		i++;
		count++;
	}


	count=0;
	while(isGood && count<10000){
		rc=table2.insert(keys[i],data[i]);

		if(table2.isEmpty()){
			isGood=false;
			error="Error 2e: table is not empty, isEmpty() should return false, your isEmpty() returns true";
		}
		if(isGood && !rc){
			isGood=false;
			error="Error 2f: insert() returned false.  it should have returned true";
		}
		if(isGood && table2.numRecords()!=count+1){
			isGood=false;
			error="Error 2g: table should have ";
			error+= std::to_string(count+1);
			error+=" records, your numRecords() returned: ";
			error+=std::to_string(table2.numRecords());				
		}		
		if(isGood && table2.capacity()!= 10000){
			isGood=false;
			error="Error 2h: table capacity should be 10000";
		}
	
		i++;
		count++;
	}


	count=0;
	while(isGood && count<20000){
		rc=table3.insert(keys[i],data[i]);
		if(table3.isEmpty()){
			isGood=false;
			error="Error 2i: table is not empty, isEmpty() should return false, your isEmpty() returns true";
		}
		if(isGood && !rc){
			isGood=false;
			error="Error 2j: insert() returned false.  it should have returned true";
		}
		if(isGood && table3.numRecords()!=count+1){
			isGood=false;
			error="Error 2k: table should have ";
			error+= std::to_string(count+1);
			error+=" records, your numRecords() returned: ";
			error+=std::to_string(table3.numRecords());				
		}		
		if(isGood && table3.capacity()!= 20000){
			isGood=false;
			error="Error 2l: table capacity should be 20000";
		}

		i++;
		count++;
	}


	//try to add the same records again.  This should not be allowed.
	i=0;
	count = table1.numRecords();
	while(isGood && i<1000){
		rc=table1.insert(keys[i],data[i]+10);
		if(isGood && rc){
			isGood=false;
			error="Error 2m: insert() returned true.  it should have returned false";
		}
		if(isGood && table1.numRecords()!=count){
			isGood=false;
			error="Error 2n: table should have ";
			error+= std::to_string(count);
			error+=" records, your numRecords() returned: ";
			error+=std::to_string(table1.numRecords());				
		}
		if(isGood && table1.capacity()!= 1000){
			isGood=false;
			error="Error 2o: table capacity should be 1000";
		}
		i++;
	}
	if(table1.loadFactor()!=1.0){
		isGood=false;
		error="Error 2p: loadFactor() should return ";
		error+= std::to_string(1.0);
		error+=" records, your loadFactor() returned: ";
		error+=std::to_string(table1.loadFactor());				
	}
	else if(table2.loadFactor()!=1.0){
		isGood=false;
		error="Error 2p: loadFactor() should return ";
		error+= std::to_string(1.0);
		error+=" records, your loadFactor() returned: ";
		error+=std::to_string(table2.loadFactor());				
	}
	else if(table3.loadFactor()!=1.0){
		isGood=false;
		error="Error 2p: loadFactor() should return ";
		error+= std::to_string(1.0);
		error+=" records, your loadFactor() returned: ";
		error+=std::to_string(table3.loadFactor());				

	}

	return isGood;

}

/*test3: testing find() and insert()
*/
bool test3(std::string keys[], int data[], int max, std::string& error){
	ChainingTable<int> table1(1000);
	ChainingTable<int> table2(10000);
	ChainingTable<int> table3(20000);
	bool isGood=true;
	int i=0;
	int count=0;
	while(count<1000){
		table1.insert(keys[i],data[i]);
		i++;
		count++;
	}
	count=0;
	while(count<10000){
		table2.insert(keys[i],data[i]);
		i++;
		count++;
	}
	count=0;
	while(count<20000){
		table3.insert(keys[i],data[i]);
		i++;
		count++;
	}

	i=0;
	count=0;
	while(isGood && count<1000){
		int value;
		isGood=table1.find(keys[i],value);
		if(!isGood){
			error="Error 3a: find returned false for a record that should exist in the table";
		}
		else{
			if(value!=data[i]){
				isGood=false;				
				error="Error 3b: value associated with key: ";
				error+=keys[i];
				error+= " should be: ";
				error+=std::to_string(data[i]);
				error+="\nyour find passed back: ";
				error+=std::to_string(value);
			}
		}
		i++;
		count++;
	}
	count=0;
	while(isGood && count<10000){
		int value;
		isGood=table2.find(keys[i],value);
		if(!isGood){
			error="Error 3c: find returned false for a record that should exist in the table";
		}
		else{
			if(value!=data[i]){
				isGood=false;								
				error="Error 3d: value associated with key: ";
				error+=keys[i];
				error+= " should be: ";
				error+=std::to_string(data[i]);
				error+="\nyour find passed back: ";
				error+=std::to_string(value);
			}
		}
		i++;
		count++;
	}
	count=0;
	while(isGood && count<20000){
		int value;
		isGood=table3.find(keys[i],value);
		if(!isGood){
			error="Error 3e: find returned false for a record that should exist in the table";
		}
		else{
			if(value!=data[i]){
				isGood=false;				
				error="Error 3f: value associated with key: ";
				error+=keys[i];
				error+= " should be: ";
				error+=std::to_string(data[i]);
				error+="\nyour find passed back: ";
				error+=std::to_string(value);
			}
		}
		i++;
		count++;
	}
	count=0;
	bool rc;
	while(isGood && count<1000){
		int value;
		rc=table1.find(keys[i],value);
		if(rc){
			error="Error 3g: find returned true for a record that does not exist in the table";
			isGood=false;
		}
		i++;
		count++;
	}
	count=0;
	while(isGood && count<10000){
		int value;
		rc=table2.find(keys[i],value);
		if(rc){
			error="Error 3h: find returned true for a record that does not exist in the table";
			isGood=false;
		}
		i++;
		count++;
	}
	count=0;
	while(isGood && count<20000){
		int value;
		rc=table3.find(keys[i],value);
		if(rc){
			error="Error 3i: find returned true for a record that does not exist in the table";
			isGood=false;
		}
		i++;
		count++;
	}
	i=0;
	while(count<1000){
		table1.insert(keys[i],data[i] + 10);
		i++;
		count++;
	}
	i=0;
	while(isGood && i<1000){
		int value;
		isGood=table1.find(keys[i],value);
		if(!isGood){
			error="Error 3j: find returned false for a record that should exist in the table";
		}
		else{
			if(value!=data[i]){
				isGood=false;				
				error="Error 3k: value associated with key: ";
				error+=keys[i];
				error+= " should be: ";
				error+=std::to_string(data[i]);
				error+="\nyour find passed back: ";
				error+=std::to_string(value);
			}
		}
		i++;
	}

	return isGood;
}

/*test 4: modify records, ensure numRecords() is returning the correct value.
  number of slots should not incrase during this process
*/
bool test4(std::string keys[], int data[], int max, std::string& error){

	ChainingTable<int> table1(1000);
	ChainingTable<int> table2(10000);
	ChainingTable<int> table3(20000);
	bool isGood=true;
	int i=0;
	int count=0;
	bool rc;

	while(isGood && count<650){
		rc = table1.modify(keys[i],data[i]);
		if(rc){
			isGood=false;
			error="Error 4a: modify() returned true.  it should have returned false as record does not yet exist";
		}
		i++;
		count++;
	}
	count=0;
	while(isGood && count<10000){
		rc=table2.modify(keys[i],data[i]);
		if(rc){
			isGood=false;
			error="Error 4b: modify() returned true.  it should have returned false as record does not yet exist";
		}
		i++;
		count++;
	}
	count=0;
	while(isGood && count<20000){
		rc=table3.modify(keys[i],data[i]);
		if(rc){
			isGood=false;
			error="Error 4c: modify() returned true.  it should have returned false as record does not yet exist";
		}
		i++;
		count++;
	}

	if(isGood && table1.numRecords() != 0 || table2.numRecords() != 0 || table3.numRecords()!=0 ){
			isGood=false;
			error="Error 4d: numRecords() should return 0 as tables should be empty";		
	}
	if(isGood && table1.capacity() != 1000 || table2.capacity() != 10000 || table3.capacity()!=20000 ){
			isGood=false;
			error="Error 4e: capacity() should not have changed as records were not added";		
	}

	i = 0;
	count = 0;
	while(isGood && count<650){
		table1.insert(keys[i],data[i]);
		i++;
		count++;
	}
	count=0;
	while(isGood && count<10000){
		table2.insert(keys[i],data[i]);
		i++;
		count++;
	}
	count=0;
	while(isGood && count<20000){
		table3.insert(keys[i],data[i]);
		i++;
		count++;
	}

	i=0;
	count=0;
	while(isGood && count<650){
		if(count%2){
			rc=table1.modify(keys[i],data[i]+1);
			if(!rc){
				isGood=false;
				error="Error 4a: modify() returned false.  it should have returned true";
			}
		}
		if(isGood && table1.numRecords()!=650){
			isGood=false;
			error="Error 4b: table should have ";
			error+= std::to_string(650);
			error+=" records, your numRecords() returned: ";
			error+=std::to_string(table1.numRecords());				
		}

		if(isGood && table1.capacity()!= 1000){
			isGood=false;
			error="Error 4c: table capacity should be 1000";
		}
		i++;
		count++;
	}
	count=0;
	while(isGood && count<10000){
		if(count%2){
			rc=table2.modify(keys[i],data[i]+2);
			if(!rc){
				isGood=false;
				error="Error 4d: modify() returned false.  it should have returned true";
			}
		}
		if(isGood && table2.numRecords()!=10000){
			isGood=false;
			error="Error 4e: table should have ";
			error+= std::to_string(10000);
			error+=" records, your numRecords() returned: ";
			error+=std::to_string(table2.numRecords());				
		}		
		if(isGood && table2.capacity()!= 10000){
			isGood=false;
			error="Error 4f: table capacity should be 10000";
		}
		i++;
		count++;
	}
	count=0;
	while(isGood && count<20000){
		if(count%2){
			rc=table3.modify(keys[i],data[i]+3);
			if(!rc){
				isGood=false;
				error="Error 4g: modify() returned false.  it should have returned true";
			}
		}
		if(isGood && table3.numRecords()!=20000){
			isGood=false;
			error="Error 4h: table should have ";
			error+= std::to_string(20000);
			error+=" records, your numRecords() returned: ";
			error+=std::to_string(table3.numRecords());				
		}		
		if(isGood && table3.capacity()!= 20000){
			isGood=false;
			error="Error 4i: table capacity should be 20000";
		}
		i++;
		count++;
	}
	return isGood;
}
/*test 5: Modify records and test find, ensure that find returns true 
for all records and that the values are updated
*/

bool test5(std::string keys[], int data[], int max, std::string& error){

	ChainingTable<int> table1(1000);
	ChainingTable<int> table2(10000);
	ChainingTable<int> table3(20000);
	bool isGood=true;
	int i=0;
	int count=0;
	while(count<650){
		table1.insert(keys[i],data[i]);
		i++;
		count++;
	}
	count=0;
	while(count<10000){
		table2.insert(keys[i],data[i]);
		i++;
		count++;
	}
	count=0;
	while(count<20000){
		table3.insert(keys[i],data[i]);
		i++;
		count++;
	}

	i=0;
	count=0;
	while(count<650){
		if(count%2){
			table1.modify(keys[i],data[i]+1);
		}
		i++;
		count++;
	}
	count=0;
	while(count<10000){
		if(count%2){
			table2.modify(keys[i],data[i]+2);
		}
		i++;
		count++;
	}
	count=0;
	while(count<20000){
		if(count%2){
			table3.modify(keys[i],data[i]+3);
		}
		i++;
		count++;
	}


	i=0;
	count=0;
	int value;
	int correct;

	while(isGood && count<650){
		isGood=table1.find(keys[i],value);
		if(!isGood){
			error="Error 5a: find returned false for a record that should exist in the table";
		}
		else{
			correct=data[i]+(count%2);
			if(value!=correct){
				isGood=false;				
				error="Error 5b: value associated with key: ";
				error+=keys[i];
				error+= " should be: ";
				error+=std::to_string(correct);
				error+="\nyour find passed back: ";
				error+=std::to_string(value);
			}
		}
		i++;
		count++;
	}
	count=0;
	while(isGood && count<10000){
		isGood=table2.find(keys[i],value);
		if(!isGood){
			error="Error 5c: find returned false for a record that should exist in the table";
		}
		else{
			correct=data[i]+(count%2)*2;

			if(value!=correct){

				isGood=false;								
				error="Error 5d: value associated with key: ";
				error+=keys[i];
				error+= " should be: ";
				error+=std::to_string(correct);
				error+="\nyour find passed back: ";
				error+=std::to_string(value);
			}
		}
		i++;
		count++;
	}
	count=0;
	while(isGood && count<20000){
		int value;
		isGood=table3.find(keys[i],value);
		if(!isGood){
			error="Error 5e: find returned false for a record that should exist in the table";
		}
		else{
			correct=data[i]+(count%2)*3;
			if(value!=correct){
				isGood=false;				
				error="Error 5f: value associated with key: ";
				error+=keys[i];
				error+= " should be: ";
				error+=std::to_string(correct);
				error+="\nyour find passed back: ";
				error+=std::to_string(value);
			}
		}
		i++;
		count++;
	}
	return isGood;

}
/*Test 6: Test that table grows appropriately()*/
bool test6(std::string keys[], int data[], int max, std::string& error){
	ChainingTable<int> table1(10);
	bool isGood=true;
	int i=0;
	int count=0;
	int currCapacity = 10;
	while(isGood && count<1281){
		table1.insert(keys[i],data[i]);
		i++;
		if(count == currCapacity-1 && table1.capacity() != currCapacity){
			isGood=false;
			error="Error 6a: capacity was modified before it should have been modified";
		}
		if(count == currCapacity){
			currCapacity*=2;
			if( table1.capacity() != currCapacity){
				isGood=false;
				error="Error 6b: capacity has not changed even though load factor is at limit";
			}
		}
		count++;
	}
	i=0;
	int result;
	while(isGood && i <1281){
		if(!table1.find(keys[i],result)){
				isGood=false;
				error="Error 6c: after growing the table, a record that should have been found was not";			
		}		
		else if (result != data[i]){
				isGood=false;
				error="Error 6d: after growing the table, the data associated with a key is not correct";			
		}
		i++;		
	}
	i=0;
	while(isGood && i<1281){
		table1.modify(keys[i],data[i]+10);
		i++;
		if(table1.capacity() != currCapacity){
			isGood=false;
			error="Error 6e: capacity should not change when modifying table";
		}
	}
	i=0;
	while(isGood && i <1281){
		if(!table1.find(keys[i],result)){
				isGood=false;
				error="Error 6f: after growing the table, a modified record that should have been found was not";			
		}		
		else if (result != data[i]+10){
				isGood=false;
				error="Error 6g: after growing the table, the data associated with a modified record not correct";			
		}
		i++;	
	}
	return isGood;
}

/*Test 7: Test remove()*/
bool test7(std::string keys[], int data[], int max, std::string& error){
	ChainingTable<int> table(500000);
	bool isGood=true;

	for(int i=0;i<350000;i++){
		table.insert(keys[i],data[i]);
	}
	for(int i=0;isGood && i<350000;i+=2){
		isGood=table.remove(keys[i]);
		if(!isGood){
			error="Error 7a: remove() should have returned true, function returned falsed";
		}
		if(table.capacity() != 500000){
			error="Error 7b: capacity() should return 500000, it returned: ";
			error+=std::to_string(table.capacity());
		}
	}
	bool rc;
	for(int i=0;isGood && i<350000;i+=2){
		rc=table.remove(keys[i]);
		if(rc){
			error="Error 7c: remove() should have returned false, function returned true";
			isGood=false;
		}
		if(table.capacity() != 500000){
			error="Error 7d: capacity() should return 500000, it returned: ";
			error+=std::to_string(table.capacity());
		}
	}

	int value;
	int result;
	for(int i=0;isGood && i<350000;i++){
		result=table.find(keys[i],value);
		if(i%2){
			if(!result){
				isGood=false;
				error="Error 7e: finding key (";
				error+=keys[i];
				error+=") that was not removed but find() is returning false";
			}
			else{
				if(value != data[i]){
					isGood=false;
					error="Error 7f: value passed back from find is not correct after a remove operation";
				}
			}
		}
		else {
			if(result){
				isGood=false;
				error="Error 7g: key (";
				error+=keys[i];
				error+=") was removed but find() is returning true";			
			}
		}
	}
	return isGood;
}




/*Test 8: Test Copy Constructor, ensure that copy is same as original*/
bool test8(std::string keys[], int data[], int max, std::string& error){
	ChainingTable<int> table1(1000);
	ChainingTable<int> table2(10000);
	ChainingTable<int> table3(20000);
	bool isGood=true;
	int i=0;
	int count=0;
	while(count<650){
		table1.insert(keys[i],data[i]);
		i++;
		count++;
	}
	count=0;
	while(count<10000){
		table2.insert(keys[i],data[i]);
		i++;
		count++;
	}
	count=0;
	while(count<20000){
		table3.insert(keys[i],data[i]);
		i++;
		count++;
	}

	ChainingTable<int> table1copy=table1;
	ChainingTable<int> table2copy=table2;
	ChainingTable<int> table3copy=table3;

	if(isGood && table1copy.numRecords() != table1.numRecords()){
		error="Error 8a: number of records was not correct.\n Correct number of records: ";
		error+=std::to_string(table1.numRecords());
		error+="\nYour function returns: ";
		error+=std::to_string(table1copy.numRecords());
		isGood=false;
	}
	if(isGood && table2copy.numRecords() != table2.numRecords()){
		error="Error 8b: number of records was not correct.\n Correct number of records: ";
		error+=std::to_string(table2.numRecords());
		error+="\nYour function returns: ";
		error+=std::to_string(table2copy.numRecords());
		isGood=false;

	}
	if(isGood && table3copy.numRecords() != table3.numRecords() ){
		error="Error 8c: number of records was not correct.\n Correct number of records: ";
		error+=std::to_string(table3.numRecords());
		error+="\nYour function returns: ";
		error+=std::to_string(table3copy.numRecords());
		isGood=false;
	}

	if(isGood && table1copy.capacity() != table1.capacity()){
		error="Error 8d: copy's capacity was not correct.\n Correct capacity: ";
		error+=std::to_string(table1.capacity());
		error+="\nYour function returns: ";
		error+=std::to_string(table1copy.capacity());
		isGood=false;
	}
	if(isGood && table2copy.capacity() != table2.capacity()){
		error="Error 8e: copy's capacity was not correct.\n Correct capacity: ";
		error+=std::to_string(table2.capacity());
		error+="\nYour function returns: ";
		error+=std::to_string(table2copy.capacity());
		isGood=false;

	}
	if(isGood && table3copy.capacity() != table3.capacity()){
		error="Error 8f: copy's capacity was not correct.\n Correct capacity: ";
		error+=std::to_string(table3.capacity());
		error+="\nYour function returns: ";
		error+=std::to_string(table3copy.capacity());
		isGood=false;
	}


    //alter original record's data
	while(count<650){
		table1.insert(keys[i],data[i]+1);
		i++;
		count++;
	}
	count=0;
	while(count<10000){
		table2.insert(keys[i],data[i]+1);
		i++;
		count++;
	}
	count=0;
	while(count<20000){
		table3.insert(keys[i],data[i]+1);
		i++;
		count++;
	}

	i=0;
	count=0;
	while(isGood && count<650){
		int value;
		isGood=table1copy.find(keys[i],value);
		if(!isGood){
			error="Error 8g: find returned false for a record that should exist in the table created with copy constructor";
		}
		else{
			if(value!=data[i]){
				isGood=false;				
				error="Error 8h: value associated with key: ";
				error+=keys[i];
				error+= " should be: ";
				error+=std::to_string(data[i]);
				error+="\nyour find passed back: ";
				error+=std::to_string(value);
				error+="\nperhaps a deep copy was not made";

			}
		}
		i++;
		count++;
	}
	count=0;
	while(isGood && count<10000){
		int value;
		isGood=table2.find(keys[i],value);
		if(!isGood){
			error="Error 8i: find returned false for a record that should exist in the table created with copy constructor";
		}
		else{
			if(value!=data[i]){
				isGood=false;								
				error="Error 8j: value associated with key: ";
				error+=keys[i];
				error+= " should be: ";
				error+=std::to_string(data[i]);
				error+="\nyour find passed back: ";
				error+=std::to_string(value);
				error+="\nperhaps a deep copy was not made";

			}
		}
		i++;
		count++;
	}
	count=0;
	while(isGood && count<20000){
		int value;
		isGood=table3.find(keys[i],value);
		if(!isGood){
			error="Error 8k: find returned false for a record that should exist in the table created with copy constructor";
		}
		else{
			if(value!=data[i]){
				isGood=false;				
				error="Error 8l: value associated with key: ";
				error+=keys[i];
				error+= " should be: ";
				error+=std::to_string(data[i]);
				error+="\nyour find passed back: ";
				error+=std::to_string(value);
				error+="\nperhaps a deep copy was not made";
			}
		}
		i++;
		count++;
	}


	return isGood;



}

/*Test 9: Check that deep copy was created with assignment operator*/
bool test9(std::string keys[], int data[], int max, std::string& error){
	ChainingTable<int> table1(1000);
	ChainingTable<int> table2(10000);
	ChainingTable<int> table3(200000);
	bool isGood=true;
	int i=0;
	int count=0;
	while(count<650){
		table1.insert(keys[i],data[i]);
		i++;
		count++;
	}
	count=0;
	while(count<10000){
		table2.insert(keys[i],data[i]);
		i++;
		count++;
	}
	count=0;
	while(count<1000000){
		table3.insert(keys[i],data[i]);
		i++;
		count++;
	}

	//duplicate table1
	table2=table1;

	count=0;
	i=0;
	while(count<650){
		table1.modify(keys[i],data[i]+2);
		i++;
		count++;
	}

	count=0;
	i=0;
	if(table2.numRecords() != 650){
		error="Error 9a: number of records was not correct.\n Correct number of records: 650";
		error+="\nYour function returns: ";
		error+=std::to_string(table2.numRecords());
		isGood=false;
	} 
	if(isGood && table2.capacity() != 1000){
		error="Error 9b: copy's capacity was not correct.\n Correct capacity: 1000 ";
		error+="\nYour function returns: ";
		error+=std::to_string(table2.capacity());
		isGood=false;
	}
	while(isGood && count<650){
		int value;
		isGood=table2.find(keys[i],value);
		if(!isGood){
			error="Error 9c: find returned false for a record that should be in the table";
		}
		else{
			if(value!=data[i]){
				isGood=false;				
				error="Error 9d: value associated with key: ";
				error+=keys[i];
				error+= " should be: ";
				error+=std::to_string(data[i]);
				error+="\nyour find() passed back: ";
				error+=std::to_string(value);
				error+="\nperhaps a deep copy was not made";

			}
		}
		i++;
		count++;
	}
	int correctCap=1000;
	table2.insert(keys[i],data[i]);
	if(isGood && table2.capacity() != correctCap){
		error="Error 9e: copy's capacity was not correct.\n Correct capacity: ";
		error+=std::to_string(correctCap);
		error+="\nYour function returns: ";
		error+=std::to_string(table2.capacity());
		isGood=false;
	}
	if(isGood && table2.numRecords() != 651){
		error="Error 9f: number of records was not correct.\n Correct number of records: 651";
		error+="\nYour function returns: ";
		error+=std::to_string(table2.numRecords());
		isGood=false;
	}

	table2=table3;
	correctCap = table3.capacity();
	if(table2.numRecords() != 1000000){
		error="Error 9g: number of records was not correct.\n Correct number of records: 650";
		error+="\nYour function returns: ";
		error+=std::to_string(table2.numRecords());
		isGood=false;
	} 
	if(isGood && table2.capacity() != correctCap){
		error="Error 9h: copy's capacity was not correct.\n Correct capacity: ";
		error+=std::to_string(correctCap);
		error+="\nYour function returns: ";
		error+=std::to_string(table2.capacity());
		isGood=false;
	}

	i=10650;
	count=0;
	while(count<1000000){
		table2.modify(keys[i],data[i]+2);
		i++;
		count++;
	}

	count=0;
	i=10650;
	while(isGood && count<1000000){
		int value;
		isGood=table3.find(keys[i],value);
		if(!isGood){
			error="Error 9i: find returned false for a record that should be in the table";
		}
		else{
			if(value!=data[i]){
				isGood=false;				
				error="Error 9j: value associated with key: ";
				error+=keys[i];
				error+= " should be: ";
				error+=std::to_string(data[i]);
				error+="\nyour find() passed back: ";
				error+=std::to_string(value);
				error+="\nperhaps a deep copy was not made";

			}
		}
		i++;
		count++;
	}


	return isGood;
}


/*Test 10: Test move constructor*/
bool test10(std::string keys[], int data[], int max, std::string& error){
	ChainingTable<int> table(10000);
	bool isGood=true;
	int i=0;
	int count=0;
	while(count<6500){
		table.insert(keys[i],data[i]);
		i++;
		count++;
	}
	count=0;

	int correctCap=table.capacity();

	ChainingTable<int> moved1=std::move(table);
	if(isGood && moved1.capacity() != correctCap){
		error="Error 10a: copy's capacity was not correct.\n Correct capacity: ";
		error+=std::to_string(correctCap);
		error+="\nYour function returns: ";
		error+=std::to_string(moved1.capacity());
		isGood=false;
	}
	if(isGood && moved1.numRecords() != 6500){
		error="Error 10b: number of records was not correct.\n Correct number of records: 6500";
		error+="\nYour function returns: ";
		error+=std::to_string(moved1.numRecords());
		isGood=false;
	}
	i=0;
	count=0;
	while(isGood && count<6500){
		int value;
		isGood=moved1.find(keys[i],value);
		if(!isGood){
			error="Error 10c: find returned false for a record that should exist in the table created with copy constructor";
		}
		else{
			if(value!=data[i]){
				isGood=false;				
				error="Error 10d: value associated with key: ";
				error+=keys[i];
				error+= " should be: ";
				error+=std::to_string(data[i]);
				error+="\nyour find passed back: ";
				error+=std::to_string(value);
				error+="\nperhaps a deep copy was not made";
			}
		}
		i++;
		count++;
	}
	moved1.insert(keys[i],data[i]);
	if(isGood && moved1.capacity() != correctCap){
		error="Error 10e: copy's capacity was not correct.\n Correct capacity: ";
		error+=std::to_string(correctCap);
		error+="\nYour function returns: ";
		error+=std::to_string(moved1.capacity());
		isGood=false;
	}
	if(isGood && moved1.numRecords() != 6501){
		error="Error 10f: number of records was not correct.\n Correct number of records: 6501";
		error+="\nYour function returns: ";
		error+=std::to_string(moved1.numRecords());
		isGood=false;
	}
	return isGood;


}
/*Test 11: move assignment*/
bool test11(std::string keys[], int data[], int max, std::string& error){
	ChainingTable<int> table1(1000);
	ChainingTable<int> table2(10000);
	ChainingTable<int> table3(100000);
	bool isGood=true;
	int i=0;
	int count=0;
	while(count<650){
		table1.insert(keys[i],data[i]);
		i++;
		count++;
	}
	count=0;
	while(count<7000){
		table2.insert(keys[i],data[i]);
		i++;
		count++;
	}
	count=0;
	while(count<60000){
		table3.insert(keys[i],data[i]);
		i++;
		count++;
	}

	//duplicate table2
	table2=std::move(table1);
	int correctCap=1000;

	if(isGood && table2.capacity() != correctCap){
		error="Error 11a: copy's capacity was not correct.\n Correct capacity: ";
		error+=std::to_string(correctCap);
		error+="\nYour function returns: ";
		error+=std::to_string(table2.capacity());
		isGood=false;
	}
	if(isGood && table2.numRecords() != 650){
		error="Error 11b: number of records was not correct.\n Correct number of records: 650";
		error+="\nYour function returns: ";
		error+=std::to_string(table2.numRecords());
		isGood=false;
	}

	count=0;
	i=0;
	while(isGood && count<650){
		int value;
		isGood=table2.find(keys[i],value);
		if(!isGood){
			error="Error 11c: find returned false for a record that should be in the table";
		}
		else{
			if(value!=data[i]){
				isGood=false;				
				error="Error 11d: value associated with key: ";
				error+=keys[i];
				error+= " should be: ";
				error+=std::to_string(data[i]);
				error+="\nyour find() passed back: ";
				error+=std::to_string(value);
				error+="\nperhaps a deep copy was not made";

			}
		}
		i++;
		count++;
	}

	table2.insert(keys[i],data[i]);
	if(isGood && table2.capacity() != correctCap){
		error="Error 11e: copy's capacity was not correct.\n Correct capacity: ";
		error+=std::to_string(correctCap);
		error+="\nYour function returns: ";
		error+=std::to_string(table2.capacity());
		isGood=false;
	}
	if(isGood && table2.numRecords() != 651){
		error="Error 11f: number of records was not correct.\n Correct number of records: 651";
		error+="\nYour function returns: ";
		error+=std::to_string(table2.numRecords());
		isGood=false;
	}
    
    correctCap=100000;
	table2=std::move(table3);

	if(isGood && table2.capacity() != correctCap){
		error="Error 11g: copy's capacity was not correct.\n Correct capacity: ";
		error+=std::to_string(correctCap);
		error+="\nYour function returns: ";
		error+=std::to_string(table2.capacity());
		isGood=false;
	}
	if(isGood && table2.numRecords() != 60000){
		error="Error 11h: number of records was not correct.\n Correct number of records: 60000";
		error+="\nYour function returns: ";
		error+=std::to_string(table2.numRecords());
		isGood=false;
	}


	i=7650;
	count=0;
	while(isGood && count<60000){
		int value;
		isGood=table2.find(keys[i],value);
		if(!isGood){
			error="Error 11i: find returned false for a record that should be in the table";
		}
		else{
			if(value!=data[i]){
				isGood=false;				
				error="Error 11j: value associated with key: ";
				error+=keys[i];
				error+= " should be: ";
				error+=std::to_string(data[i]);
				error+="\nyour find() passed back: ";
				error+=std::to_string(value);
				error+="\nperhaps a deep copy was not made";

			}
		}
		i++;
		count++;
	}


	table2.insert(keys[i],data[i]);
	if(isGood && table2.capacity() != correctCap){
		error="Error 11k: copy's capacity was not correct.\n Correct capacity: ";
		error+=std::to_string(correctCap);
		error+="\nYour function returns: ";
		error+=std::to_string(table2.capacity());
		isGood=false;
	}
	if(isGood && table2.numRecords() != 60001){
		error="Error 11l: number of records was not correct.\n Correct number of records: 60001";
		error+="\nYour function returns: ";
		error+=std::to_string(table2.numRecords());
		isGood=false;
	}
	return isGood;
}



/* test12: Initialization, numRecords(),  isEmpty()
*/
bool test12(std::string keys[], int data[], int max, std::string& error){
	LPTable<int> table1(1429);
	LPTable<int> table2(14286);
	LPTable<int> table3(28572);
	bool isGood=true;
	if(table1.numRecords()!=0 || table2.numRecords()!=0 || table3.numRecords() != 0){
		isGood=false;
		error="Error 12a: numRecords() should return 0 when table is empty";
	}
	else if(!table1.isEmpty() || !table2.isEmpty() || !table3.isEmpty()){
		isGood=false;
		error="Error 12b: isEmpty() should return true when table is empty";
	}
	else if(table1.capacity()!=1429){
		isGood=false;
		error="Error 12c: capacity() should return ";
		error+= std::to_string(1429);
		error+=" records, your capacity() returned: ";
		error+=std::to_string(table1.capacity());				
	}
	else if(table2.capacity()!=14286){
		isGood=false;
		error="Error 12d: capacity() should return ";
		error+= std::to_string(14286);
		error+=" records, your capacity() returned: ";
		error+=std::to_string(table2.capacity());				

	}
	else if(table3.capacity()!=28572){
		isGood=false;
		error="Error 12e: capacity() should return ";
		error+= std::to_string(28572);
		error+=" records, your capacity() returned: ";
		error+=std::to_string(table3.capacity());				
	}
	else if(table1.loadFactor()!=0){
		isGood=false;
		error="Error 12c: loadFactor() should return ";
		error+= std::to_string(0);
		error+=" records, your loadFactor() returned: ";
		error+=std::to_string(table1.loadFactor());				
	}
	else if(table2.loadFactor()!=0){
		isGood=false;
		error="Error 12d: capacity() should return ";
		error+= std::to_string(0);
		error+=" records, your loadFactor() returned: ";
		error+=std::to_string(table2.loadFactor());				

	}
	return isGood;
}

/*test13: use insert() with new records.  capacity should not change in these cases*/
bool test13(std::string keys[], int data[], int max, std::string& error){
	LPTable<int> table1(1429);
	LPTable<int> table2(14286);
	LPTable<int> table3(28572);

	bool isGood=true;
	int i=0;
	int count=0;
	bool rc;
	while(isGood && count<1000){
		rc=table1.insert(keys[i],data[i]);
		if(table1.isEmpty()){
			isGood=false;
			error="Error 13a: table is not empty, isEmpty() should return false, your isEmpty() returns true";
		}
		if(isGood && !rc){
			isGood=false;
			error="Error 13b: insert() returned false.  it should have returned true";
		}
		if(isGood && table1.numRecords()!=count+1){
			isGood=false;
			error="Error 13c: table should have ";
			error+= std::to_string(count+1);
			error+=" records, your numRecords() returned: ";
			error+=std::to_string(table1.numRecords());				
		}
		if(isGood && table1.capacity()!= 1429){
			isGood=false;
			error="Error 13d: table capacity should be 1429";
		}
		i++;
		count++;
	}


	count=0;
	while(isGood && count<10000){
		rc=table2.insert(keys[i],data[i]);

		if(table2.isEmpty()){
			isGood=false;
			error="Error 13e: table is not empty, isEmpty() should return false, your isEmpty() returns true";
		}
		if(isGood && !rc){
			isGood=false;
			error="Error 13f: insert() returned false.  it should have returned true";
		}
		if(isGood && table2.numRecords()!=count+1){
			isGood=false;
			error="Error 13g: table should have ";
			error+= std::to_string(count+1);
			error+=" records, your numRecords() returned: ";
			error+=std::to_string(table2.numRecords());				
		}		
		if(isGood && table2.capacity()!= 14286){
			isGood=false;
			error="Error 13h: table capacity should be 14286";
		}
	
		i++;
		count++;
	}


	count=0;
	while(isGood && count<20000){
		rc=table3.insert(keys[i],data[i]);
		if(table3.isEmpty()){
			isGood=false;
			error="Error 13i: table is not empty, isEmpty() should return false, your isEmpty() returns true";
		}
		if(isGood && !rc){
			isGood=false;
			error="Error 13j: insert() returned false.  it should have returned true";
		}
		if(isGood && table3.numRecords()!=count+1){
			isGood=false;
			error="Error 13k: table should have ";
			error+= std::to_string(count+1);
			error+=" records, your numRecords() returned: ";
			error+=std::to_string(table3.numRecords());				
		}		
		if(isGood && table3.capacity()!= 28572){
			isGood=false;
			error="Error 13l: table capacity should be 28572";
		}

		i++;
		count++;
	}


	//try to add the same records again.  This should not be allowed.
	i=0;
	count = table1.numRecords();

	while(isGood && i<1000){
		rc=table1.insert(keys[i],data[i]+10);
		if(isGood && rc){
			isGood=false;
			error="Error 13m: insert() returned true.  it should have returned false";
		}
		if(isGood && table1.numRecords()!=count){
			isGood=false;
			error="Error 13n: table should have ";
			error+= std::to_string(count+1);
			error+=" records, your numRecords() returned: ";
			error+=std::to_string(table1.numRecords());				
		}
		if(isGood && table1.capacity()!= 1429){
			isGood=false;
			error="Error 13o: table capacity should be 1429";
		}
		i++;
	}


	return isGood;

}

/*test14: testing find() and insert()
*/
bool test14(std::string keys[], int data[], int max, std::string& error){
	LPTable<int> table1(1429);
	LPTable<int> table2(14286);
	LPTable<int> table3(28572);
	bool isGood=true;
	int i=0;
	int count=0;
	while(count<1000){
		table1.insert(keys[i],data[i]);
		i++;
		count++;
	}
	count=0;
	while(count<10000){
		table2.insert(keys[i],data[i]);
		i++;
		count++;
	}
	count=0;
	while(count<20000){
		table3.insert(keys[i],data[i]);
		i++;
		count++;
	}

	i=0;
	count=0;
	while(isGood && count<1000){
		int value;
		isGood=table1.find(keys[i],value);
		if(!isGood){
			error="Error 14a: find returned false for a record that should exist in the table";
		}
		else{
			if(value!=data[i]){
				isGood=false;				
				error="Error 14b: value associated with key: ";
				error+=keys[i];
				error+= " should be: ";
				error+=std::to_string(data[i]);
				error+="\nyour find passed back: ";
				error+=std::to_string(value);
			}
		}
		i++;
		count++;
	}
	count=0;
	while(isGood && count<10000){
		int value;
		isGood=table2.find(keys[i],value);
		if(!isGood){
			error="Error 14c: find returned false for a record that should exist in the table";
		}
		else{
			if(value!=data[i]){
				isGood=false;								
				error="Error 14d: value associated with key: ";
				error+=keys[i];
				error+= " should be: ";
				error+=std::to_string(data[i]);
				error+="\nyour find passed back: ";
				error+=std::to_string(value);
			}
		}
		i++;
		count++;
	}
	count=0;
	while(isGood && count<20000){
		int value;
		isGood=table3.find(keys[i],value);
		if(!isGood){
			error="Error 14e: find returned false for a record that should exist in the table";
		}
		else{
			if(value!=data[i]){
				isGood=false;				
				error="Error 14f: value associated with key: ";
				error+=keys[i];
				error+= " should be: ";
				error+=std::to_string(data[i]);
				error+="\nyour find passed back: ";
				error+=std::to_string(value);
			}
		}
		i++;
		count++;
	}
	count=0;
	bool rc;
	while(isGood && count<1000){
		int value;
		rc=table1.find(keys[i],value);
		if(rc){
			error="Error 14g: find returned true for a record that does not exist in the table";
			isGood=false;
		}
		i++;
		count++;
	}
	count=0;
	while(isGood && count<10000){
		int value;
		rc=table2.find(keys[i],value);
		if(rc){
			error="Error 14h: find returned true for a record that does not exist in the table";
			isGood=false;
		}
		i++;
		count++;
	}
	count=0;
	while(isGood && count<20000){
		int value;
		rc=table3.find(keys[i],value);
		if(rc){
			error="Error 14i: find returned true for a record that does not exist in the table";
			isGood=false;
		}
		i++;
		count++;
	}
	i=0;
	while(count<1000){
		table1.insert(keys[i],data[i] + 10);
		i++;
		count++;
	}
	i=0;
	while(isGood && i<1000){
		int value;
		isGood=table1.find(keys[i],value);
		if(!isGood){
			error="Error 14j: find returned false for a record that should exist in the table";
		}
		else{
			if(value!=data[i]){
				isGood=false;				
				error="Error 14k: value associated with key: ";
				error+=keys[i];
				error+= " should be: ";
				error+=std::to_string(data[i]);
				error+="\nyour find passed back: ";
				error+=std::to_string(value);
			}
		}
		i++;
	}

	return isGood;
}

/*test 15: modify records, ensure numRecords() is returning the correct value.
  number of slots should not incrase during this process
*/
bool test15(std::string keys[], int data[], int max, std::string& error){

	LPTable<int> table1(1429);
	LPTable<int> table2(14286);
	LPTable<int> table3(28572);
	bool isGood=true;
	int i=0;
	int count=0;
	bool rc;

	while(isGood && count<650){
		rc = table1.modify(keys[i],data[i]);
		if(rc){
			isGood=false;
			error="Error 15a: modify() returned true.  it should have returned false as record does not yet exist";
		}
		i++;
		count++;
	}
	count=0;
	while(isGood && count<10000){
		rc=table2.modify(keys[i],data[i]);
		if(rc){
			isGood=false;
			error="Error 15b: modify() returned true.  it should have returned false as record does not yet exist";
		}
		i++;
		count++;
	}
	count=0;
	while(isGood && count<20000){
		rc=table3.modify(keys[i],data[i]);
		if(rc){
			isGood=false;
			error="Error 15c: modify() returned true.  it should have returned false as record does not yet exist";
		}
		i++;
		count++;
	}

	if(isGood && table1.numRecords() != 0 || table2.numRecords() != 0 || table3.numRecords()!=0 ){
			isGood=false;
			error="Error 15d: numRecords() should return 0 as tables should be empty";		
	}
	if(isGood && table1.capacity() != 1429 || table2.capacity() != 14286 || table3.capacity()!=28572 ){
			isGood=false;
			error="Error 15e: capacity() should not have changed as records were not added";		
	}

	i = 0;
	count = 0;
	while(isGood && count<650){
		table1.insert(keys[i],data[i]);
		i++;
		count++;
	}
	count=0;
	while(isGood && count<10000){
		table2.insert(keys[i],data[i]);
		i++;
		count++;
	}
	count=0;
	while(isGood && count<20000){
		table3.insert(keys[i],data[i]);
		i++;
		count++;
	}

	i=0;
	count=0;
	while(isGood && count<650){
		if(count%2){
			rc=table1.modify(keys[i],data[i]+1);
			if(!rc){
				isGood=false;
				error="Error 15a: modify() returned false.  it should have returned true";
			}
		}
		if(isGood && table1.numRecords()!=650){
			isGood=false;
			error="Error 15b: table should have ";
			error+= std::to_string(650);
			error+=" records, your numRecords() returned: ";
			error+=std::to_string(table1.numRecords());				
		}

		if(isGood && table1.capacity()!= 1429){
			isGood=false;
			error="Error 15c: table capacity should be 1429";
		}
		i++;
		count++;
	}
	count=0;
	while(isGood && count<10000){
		if(count%2){
			rc=table2.modify(keys[i],data[i]+2);
			if(!rc){
				isGood=false;
				error="Error 15d: modify() returned false.  it should have returned true";
			}
		}
		if(isGood && table2.numRecords()!=10000){
			isGood=false;
			error="Error 15e: table should have ";
			error+= std::to_string(10000);
			error+=" records, your numRecords() returned: ";
			error+=std::to_string(table2.numRecords());				
		}		
		if(isGood && table2.capacity()!= 14286){
			isGood=false;
			error="Error 15f: table capacity should be 14286";
		}
		i++;
		count++;
	}
	count=0;
	while(isGood && count<20000){
		if(count%2){
			rc=table3.modify(keys[i],data[i]+3);
			if(!rc){
				isGood=false;
				error="Error 15g: modify() returned false.  it should have returned true";
			}
		}
		if(isGood && table3.numRecords()!=20000){
			isGood=false;
			error="Error 15h: table should have ";
			error+= std::to_string(20000);
			error+=" records, your numRecords() returned: ";
			error+=std::to_string(table3.numRecords());				
		}		
		if(isGood && table3.capacity()!= 28572){
			isGood=false;
			error="Error 15i: table capacity should be 28572";
		}
		i++;
		count++;
	}
	return isGood;
}
/*test 16: Modify records and test find, ensure that find returns true 
for all records and that the values are modified
*/

bool test16(std::string keys[], int data[], int max, std::string& error){
	LPTable<int> table1(1429);
	LPTable<int> table2(14286);
	LPTable<int> table3(28572);
	bool isGood=true;
	int i=0;
	int count=0;
	while(count<650){
		table1.insert(keys[i],data[i]);
		i++;
		count++;
	}
	count=0;
	while(count<10000){
		table2.insert(keys[i],data[i]);
		i++;
		count++;
	}
	count=0;
	while(count<20000){
		table3.insert(keys[i],data[i]);
		i++;
		count++;
	}

	i=0;
	count=0;
	while(count<650){
		if(count%2){
			table1.modify(keys[i],data[i]+1);
		}
		i++;
		count++;
	}
	count=0;
	while(count<10000){
		if(count%2){
			table2.modify(keys[i],data[i]+2);
		}
		i++;
		count++;
	}
	count=0;
	while(count<20000){
		if(count%2){
			table3.modify(keys[i],data[i]+3);
		}
		i++;
		count++;
	}


	i=0;
	count=0;
	int value;
	int correct;

	while(isGood && count<650){
		isGood=table1.find(keys[i],value);
		if(!isGood){
			error="Error 16a: find returned false for a record that should exist in the table";
		}
		else{
			correct=data[i]+(count%2);
			if(value!=correct){
				isGood=false;				
				error="Error 16b: value associated with key: ";
				error+=keys[i];
				error+= " should be: ";
				error+=std::to_string(correct);
				error+="\nyour find passed back: ";
				error+=std::to_string(value);
			}
		}
		i++;
		count++;
	}
	count=0;
	while(isGood && count<10000){
		isGood=table2.find(keys[i],value);
		if(!isGood){
			error="Error 16c: find returned false for a record that should exist in the table";
		}
		else{
			correct=data[i]+(count%2)*2;

			if(value!=correct){

				isGood=false;								
				error="Error 16d: value associated with key: ";
				error+=keys[i];
				error+= " should be: ";
				error+=std::to_string(correct);
				error+="\nyour find passed back: ";
				error+=std::to_string(value);
			}
		}
		i++;
		count++;
	}
	count=0;
	while(isGood && count<20000){
		int value;
		isGood=table3.find(keys[i],value);
		if(!isGood){
			error="Error 16e: find returned false for a record that should exist in the table";
		}
		else{
			correct=data[i]+(count%2)*3;
			if(value!=correct){
				isGood=false;				
				error="Error 16f: value associated with key: ";
				error+=keys[i];
				error+= " should be: ";
				error+=std::to_string(correct);
				error+="\nyour find passed back: ";
				error+=std::to_string(value);
			}
		}
		i++;
		count++;
	}
	return isGood;

}
/*Test 17: Test that table grows appropriately()*/
bool test17(std::string keys[], int data[], int max, std::string& error){
	LPTable<int> table1(10);
	bool isGood=true;
	int i=0;
	int count=0;
	int currCapacity = 10;
	int currMax=7;
	while(isGood && count<1281){
		table1.insert(keys[i],data[i]);
		i++;
		if(count == currMax-1 && table1.capacity() != currCapacity){
			isGood=false;
			error="Error 17a: capacity was modified before it should have been modified";
		}
		if(count == currMax){
			currCapacity*=2;
			currMax*=2;
			if( table1.capacity() != currCapacity){
				isGood=false;
				error="Error 17b: capacity has not changed even though load factor is at limit";
			}
		}
		count++;
	}
	i=0;
	int result;
	while(isGood && i <1281){
		if(!table1.find(keys[i],result)){
				isGood=false;
				error="Error 17c: after growing the table, a record that should have been found was not";			
		}		
		else if (result != data[i]){
				isGood=false;
				error="Error 17d: after growing the table, the data associated with a key is not correct";			
		}
		i++;		
	}
	i=0;
	while(isGood && i<1281){
		table1.modify(keys[i],data[i]+10);
		i++;
		if(table1.capacity() != currCapacity){
			isGood=false;
			error="Error 17e: capacity should not change when modifying table";
		}
	}
	i=0;
	while(isGood && i <1281){
		if(!table1.find(keys[i],result)){
				isGood=false;
				error="Error 17f: after growing the table, a modified record that should have been found was not";			
		}		
		else if (result != data[i]+10){
				isGood=false;
				error="Error 17g: after growing the table, the data associated with a modified record not correct";			
		}
		i++;		
	}
	return isGood;
}

/*Test 18: Test remove()*/
bool test18(std::string keys[], int data[], int max, std::string& error){
	LPTable<int> table(500000);
	bool isGood=true;

	for(int i=0;i<350000;i++){
		table.insert(keys[i],data[i]);
	}
	for(int i=0;isGood && i<350000;i+=2){
		isGood=table.remove(keys[i]);
		if(!isGood){
			error="Error 18a: remove() should have returned true, function returned falsed";
		}
		if(table.capacity() != 500000){
			error="Error 18b: capacity() should return 500000, it returned: ";
			error+=std::to_string(table.capacity());
		}
	}
	bool rc;
	for(int i=0;isGood && i<350000;i+=2){
		rc=table.remove(keys[i]);
		if(rc){
			error="Error 18c: remove() should have returned false, function returned true";
			isGood=false;
		}
		if(table.capacity() != 500000){
			error="Error 18d: capacity() should return 500000, it returned: ";
			error+=std::to_string(table.capacity());
		}
	}

	int value;
	int result;
	for(int i=0;isGood && i<350000;i++){
		result=table.find(keys[i],value);
		if(i%2){
			if(!result){
				isGood=false;
				error="Error 18e: finding key (";
				error+=keys[i];
				error+=") that was not removed but find() is returning false";
			}
			else{
				if(value != data[i]){
					isGood=false;
					error="Error 18f: value passed back from find is not correct after a remove operation";
				}
			}
		}
		else {
			if(result){
				isGood=false;
				error="Error 18g: key (";
				error+=keys[i];
				error+=") was removed but find() is returning true";			
			}
		}
	}
	return isGood;
}




/*Test 19: Test Copy Constructor, ensure that copy is same as original*/
bool test19(std::string keys[], int data[], int max, std::string& error){
	LPTable<int> table1(1000);
	LPTable<int> table2(10000);
	LPTable<int> table3(20000);
	bool isGood=true;
	int i=0;
	int count=0;
	while(count<650){
		table1.insert(keys[i],data[i]);
		i++;
		count++;
	}
	count=0;
	while(count<10000){
		table2.insert(keys[i],data[i]);
		i++;
		count++;
	}
	count=0;
	while(count<20000){
		table3.insert(keys[i],data[i]);
		i++;
		count++;
	}

	LPTable<int> table1copy=table1;
	LPTable<int> table2copy=table2;
	LPTable<int> table3copy=table3;

	if(isGood && table1copy.numRecords() != table1.numRecords()){
		error="Error 19a: number of records was not correct.\n Correct number of records: ";
		error+=std::to_string(table1.numRecords());
		error+="\nYour function returns: ";
		error+=std::to_string(table1copy.numRecords());
		isGood=false;
	}
	if(isGood && table2copy.numRecords() != table2.numRecords()){
		error="Error 19b: number of records was not correct.\n Correct number of records: ";
		error+=std::to_string(table2.numRecords());
		error+="\nYour function returns: ";
		error+=std::to_string(table2copy.numRecords());
		isGood=false;

	}
	if(isGood && table3copy.numRecords() != table3.numRecords() ){
		error="Error 19c: number of records was not correct.\n Correct number of records: ";
		error+=std::to_string(table3.numRecords());
		error+="\nYour function returns: ";
		error+=std::to_string(table3copy.numRecords());
		isGood=false;
	}

	if(isGood && table1copy.capacity() != table1.capacity()){
		error="Error 19d: copy's capacity was not correct.\n Correct capacity: ";
		error+=std::to_string(table1.capacity());
		error+="\nYour function returns: ";
		error+=std::to_string(table1copy.capacity());
		isGood=false;
	}
	if(isGood && table2copy.capacity() != table2.capacity()){
		error="Error 19e: copy's capacity was not correct.\n Correct capacity: ";
		error+=std::to_string(table2.capacity());
		error+="\nYour function returns: ";
		error+=std::to_string(table2copy.capacity());
		isGood=false;

	}
	if(isGood && table3copy.capacity() != table3.capacity()){
		error="Error 19f: copy's capacity was not correct.\n Correct capacity: ";
		error+=std::to_string(table3.capacity());
		error+="\nYour function returns: ";
		error+=std::to_string(table3copy.capacity());
		isGood=false;
	}


    //alter original record's data
	while(count<650){
		table1.insert(keys[i],data[i]+1);
		i++;
		count++;
	}
	count=0;
	while(count<10000){
		table2.insert(keys[i],data[i]+1);
		i++;
		count++;
	}
	count=0;
	while(count<20000){
		table3.insert(keys[i],data[i]+1);
		i++;
		count++;
	}

	i=0;
	count=0;
	while(isGood && count<650){
		int value;
		isGood=table1copy.find(keys[i],value);
		if(!isGood){
			error="Error 19g: find returned false for a record that should exist in the table created with copy constructor";
		}
		else{
			if(value!=data[i]){
				isGood=false;				
				error="Error 19h: value associated with key: ";
				error+=keys[i];
				error+= " should be: ";
				error+=std::to_string(data[i]);
				error+="\nyour find passed back: ";
				error+=std::to_string(value);
				error+="\nperhaps a deep copy was not made";

			}
		}
		i++;
		count++;
	}
	count=0;
	while(isGood && count<10000){
		int value;
		isGood=table2.find(keys[i],value);
		if(!isGood){
			error="Error 19i: find returned false for a record that should exist in the table created with copy constructor";
		}
		else{
			if(value!=data[i]){
				isGood=false;								
				error="Error 19j: value associated with key: ";
				error+=keys[i];
				error+= " should be: ";
				error+=std::to_string(data[i]);
				error+="\nyour find passed back: ";
				error+=std::to_string(value);
				error+="\nperhaps a deep copy was not made";

			}
		}
		i++;
		count++;
	}
	count=0;
	while(isGood && count<20000){
		int value;
		isGood=table3.find(keys[i],value);
		if(!isGood){
			error="Error 19k: find returned false for a record that should exist in the table created with copy constructor";
		}
		else{
			if(value!=data[i]){
				isGood=false;				
				error="Error 19l: value associated with key: ";
				error+=keys[i];
				error+= " should be: ";
				error+=std::to_string(data[i]);
				error+="\nyour find passed back: ";
				error+=std::to_string(value);
				error+="\nperhaps a deep copy was not made";
			}
		}
		i++;
		count++;
	}


	return isGood;



}

/*Test 20: Check that deep copy was created with assignment operator*/
bool test20(std::string keys[], int data[], int max, std::string& error){
	LPTable<int> table1(1000);
	LPTable<int> table2(10000);
	LPTable<int> table3(200000);
	bool isGood=true;
	int i=0;
	int count=0;
	while(count<650){
		table1.insert(keys[i],data[i]);
		i++;
		count++;
	}
	count=0;
	while(count<10000){
		table2.insert(keys[i],data[i]);
		i++;
		count++;
	}
	count=0;
	while(count<1000000){
		table3.insert(keys[i],data[i]);
		i++;
		count++;
	}

	//duplicate table1
	table2=table1;

	count=0;
	while(count<650){
		table1.modify(keys[i],data[i]+2);
		i++;
		count++;
	}

	count=0;
	i=0;
	if(table2.numRecords() != 650){
		error="Error 20a: number of records was not correct.\n Correct number of records: 650";
		error+="\nYour function returns: ";
		error+=std::to_string(table2.numRecords());
		isGood=false;
	} 
	if(isGood && table2.capacity() != 1000){
		error="Error 20b: copy's capacity was not correct.\n Correct capacity: 1000 ";
		error+="\nYour function returns: ";
		error+=std::to_string(table2.capacity());
		isGood=false;
	}
	while(isGood && count<650){
		int value;
		isGood=table2.find(keys[i],value);
		if(!isGood){
			error="Error 20c: find returned false for a record that should be in the table";
		}
		else{
			if(value!=data[i]){
				isGood=false;				
				error="Error 20d: value associated with key: ";
				error+=keys[i];
				error+= " should be: ";
				error+=std::to_string(data[i]);
				error+="\nyour find() passed back: ";
				error+=std::to_string(value);
				error+="\nperhaps a deep copy was not made";

			}
		}
		i++;
		count++;
	}
	int correctCap=1000;
	table2.insert(keys[i],data[i]);
	if(isGood && table2.capacity() != correctCap){
		error="Error 20e: copy's capacity was not correct.\n Correct capacity: ";
		error+=std::to_string(correctCap);
		error+="\nYour function returns: ";
		error+=std::to_string(table2.capacity());
		isGood=false;
	}
	if(isGood && table2.numRecords() != 651){
		error="Error 20f: number of records was not correct.\n Correct number of records: 651";
		error+="\nYour function returns: ";
		error+=std::to_string(table2.numRecords());
		isGood=false;
	}

	table2=table3;
	correctCap = table3.capacity();
	if(table2.numRecords() != 1000000){
		error="Error 20g: number of records was not correct.\n Correct number of records: 650";
		error+="\nYour function returns: ";
		error+=std::to_string(table2.numRecords());
		isGood=false;
	} 
	if(isGood && table2.capacity() != correctCap){
		error="Error 20h: copy's capacity was not correct.\n Correct capacity: ";
		error+=std::to_string(correctCap);
		error+="\nYour function returns: ";
		error+=std::to_string(table2.capacity());
		isGood=false;
	}

	i=10650;
	count=0;
	while(count<1000000){
		table2.modify(keys[i],data[i]+2);
		i++;
		count++;
	}

	count=0;
	i=10650;
	while(isGood && count<1000000){
		int value;
		isGood=table3.find(keys[i],value);
		if(!isGood){
			error="Error 20i: find returned false for a record that should be in the table";
		}
		else{
			if(value!=data[i]){
				isGood=false;				
				error="Error 20j: value associated with key: ";
				error+=keys[i];
				error+= " should be: ";
				error+=std::to_string(data[i]);
				error+="\nyour find() passed back: ";
				error+=std::to_string(value);
				error+="\nperhaps a deep copy was not made";

			}
		}
		i++;
		count++;
	}


	return isGood;
}


/*Test 21: Test move constructor*/
bool test21(std::string keys[], int data[], int max, std::string& error){
	LPTable<int> table(10000);
	bool isGood=true;
	int i=0;
	int count=0;
	while(count<6500){
		table.insert(keys[i],data[i]);
		i++;
		count++;
	}
	count=0;

	int correctCap=table.capacity();

	LPTable<int> moved1=std::move(table);
	if(isGood && moved1.capacity() != correctCap){
		error="Error 21a: copy's capacity was not correct.\n Correct capacity: ";
		error+=std::to_string(correctCap);
		error+="\nYour function returns: ";
		error+=std::to_string(moved1.capacity());
		isGood=false;
	}
	if(isGood && moved1.numRecords() != 6500){
		error="Error 21b: number of records was not correct.\n Correct number of records: 6500";
		error+="\nYour function returns: ";
		error+=std::to_string(moved1.numRecords());
		isGood=false;
	}
	i=0;
	count=0;
	while(isGood && count<6500){
		int value;
		isGood=moved1.find(keys[i],value);
		if(!isGood){
			error="Error 21c: find returned false for a record that should exist in the table created with copy constructor";
		}
		else{
			if(value!=data[i]){
				isGood=false;				
				error="Error 21d: value associated with key: ";
				error+=keys[i];
				error+= " should be: ";
				error+=std::to_string(data[i]);
				error+="\nyour find passed back: ";
				error+=std::to_string(value);
				error+="\nperhaps a deep copy was not made";
			}
		}
		i++;
		count++;
	}
	moved1.insert(keys[i],data[i]);
	if(isGood && moved1.capacity() != correctCap){
		error="Error 21e: copy's capacity was not correct.\n Correct capacity: ";
		error+=std::to_string(correctCap);
		error+="\nYour function returns: ";
		error+=std::to_string(moved1.capacity());
		isGood=false;
	}
	if(isGood && moved1.numRecords() != 6501){
		error="Error 21f: number of records was not correct.\n Correct number of records: 6501";
		error+="\nYour function returns: ";
		error+=std::to_string(moved1.numRecords());
		isGood=false;
	}
	return isGood;


}
/*Test 22: move assignment*/
bool test22(std::string keys[], int data[], int max, std::string& error){
	LPTable<int> table1(1000);
	LPTable<int> table2(10000);
	LPTable<int> table3(100000);
	bool isGood=true;
	int i=0;
	int count=0;
	while(count<650){
		table1.insert(keys[i],data[i]);
		i++;
		count++;
	}
	count=0;
	while(count<7000){
		table2.insert(keys[i],data[i]);
		i++;
		count++;
	}
	count=0;
	while(count<60000){
		table3.insert(keys[i],data[i]);
		i++;
		count++;
	}

	//duplicate table2
	table2=std::move(table1);
	int correctCap=1000;

	if(isGood && table2.capacity() != correctCap){
		error="Error 22a: copy's capacity was not correct.\n Correct capacity: ";
		error+=std::to_string(correctCap);
		error+="\nYour function returns: ";
		error+=std::to_string(table2.capacity());
		isGood=false;
	}
	if(isGood && table2.numRecords() != 650){
		error="Error 22b: number of records was not correct.\n Correct number of records: 650";
		error+="\nYour function returns: ";
		error+=std::to_string(table2.numRecords());
		isGood=false;
	}

	count=0;
	i=0;
	while(isGood && count<650){
		int value;
		isGood=table2.find(keys[i],value);
		if(!isGood){
			error="Error 22c: find returned false for a record that should be in the table";
		}
		else{
			if(value!=data[i]){
				isGood=false;				
				error="Error 22d: value associated with key: ";
				error+=keys[i];
				error+= " should be: ";
				error+=std::to_string(data[i]);
				error+="\nyour find() passed back: ";
				error+=std::to_string(value);
				error+="\nperhaps a deep copy was not made";

			}
		}
		i++;
		count++;
	}

	table2.insert(keys[i],data[i]);
	if(isGood && table2.capacity() != correctCap){
		error="Error 22e: copy's capacity was not correct.\n Correct capacity: ";
		error+=std::to_string(correctCap);
		error+="\nYour function returns: ";
		error+=std::to_string(table2.capacity());
		isGood=false;
	}
	if(isGood && table2.numRecords() != 651){
		error="Error 22f: number of records was not correct.\n Correct number of records: 651";
		error+="\nYour function returns: ";
		error+=std::to_string(table2.numRecords());
		isGood=false;
	}
    
    correctCap=100000;
	table2=std::move(table3);

	if(isGood && table2.capacity() != correctCap){
		error="Error 22g: copy's capacity was not correct.\n Correct capacity: ";
		error+=std::to_string(correctCap);
		error+="\nYour function returns: ";
		error+=std::to_string(table2.capacity());
		isGood=false;
	}
	if(isGood && table2.numRecords() != 60000){
		error="Error 22h: number of records was not correct.\n Correct number of records: 60000";
		error+="\nYour function returns: ";
		error+=std::to_string(table2.numRecords());
		isGood=false;
	}


	i=7650;
	count=0;
	while(isGood && count<60000){
		int value;
		isGood=table2.find(keys[i],value);
		if(!isGood){
			error="Error 22i: find returned false for a record that should be in the table";
		}
		else{
			if(value!=data[i]){
				isGood=false;				
				error="Error 22j: value associated with key: ";
				error+=keys[i];
				error+= " should be: ";
				error+=std::to_string(data[i]);
				error+="\nyour find() passed back: ";
				error+=std::to_string(value);
				error+="\nperhaps a deep copy was not made";

			}
		}
		i++;
		count++;
	}


	table2.insert(keys[i],data[i]);
	if(isGood && table2.capacity() != correctCap){
		error="Error 22k: copy's capacity was not correct.\n Correct capacity: ";
		error+=std::to_string(correctCap);
		error+="\nYour function returns: ";
		error+=std::to_string(table2.capacity());
		isGood=false;
	}
	if(isGood && table2.numRecords() != 60001){
		error="Error 22l: number of records was not correct.\n Correct number of records: 60001";
		error+="\nYour function returns: ";
		error+=std::to_string(table2.numRecords());
		isGood=false;
	}
	return isGood;
}




void createData(std::string keys[],int data[],int max){
	FILE* fp=fopen("dictionary.txt","r");
	if(!fp){
		std::cout << "You need dictionary.txt in your current directory" << std::endl;
		exit(0);
	}
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

