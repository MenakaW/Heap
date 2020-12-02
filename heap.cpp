#include <iostream>
#include <cstring>
#include <tgmath.h>
#include <fstream>

using namespace std;

//function prototypes
void sort(int index, int size, int* &heap);
void printInOrder(int* &heap, int &size);
void visualPrint(int* heap, int index, int size);
int numOfDigits(int num);

int main(){

  //setting up heap and size
  int* heap = new int[101];
  char input[20];
  int numnums = 0;
  cout << "input from file or console, type file/console" << endl;
  cin >> input;
  cin.get();
  //if user decides to input from file
  if(input[0]=='f'||input[0]=='F'){
    //open a input file stream
    ifstream file;
    char filename[20];
    cout << "enter file name correctly" << endl;
    cin >> filename;
    cin.get();
    file.open(filename);
    //cycle through for a max of 100 times or until the text is over
    for(int a = 1; a < 101; a++){
      if(file.eof()){
	break;
      }
      int in;
      file >> in;
      cout << in << endl;
      heap[a] = in;
      numnums++;
    }
    //get rid of the extra number at the end of the array and close the program
    heap[numnums]=0;
    numnums--;
    file.close();
  }
  //if the user chooses to enter input through console
  else{
    //ask for the size and set it
    cout << "enter the number of numbers you are inputting" << endl;
    cin >> numnums;
    cin.get();
    cout << "enter your numbers, pressing the ENTER key between each one." << end;
    //cycle through the array and add numbers for size number of times
    for(int a = 1; a <= numnums; a++){
      int input;
      cin >> input;
      cin.get();
      heap[a] = input;
    }
  }
  //heapify the tree, starting at the first non leaf node
  int beginningindex = numnums/2;
  for(int count = beginningindex; count > 0; count--){
    sort(count, numnums, heap);
  }
  cout << endl;
  cout << endl;
  cout << "visual representation: " << endl;
  cout << endl;
  //print out the data in a tree
  visualPrint(heap, 1, numnums);
  cout << endl;
  cout << endl;
  cout << "ordered output: " << endl;
  cout << endl;
  //print out the data as an array
  printInOrder(heap, numnums);
}

void printInOrder(int* &heap, int &size){
  int num = size;
  //cycle through this logic enough times to output all the numbers in the heap
  for(int a = 0; a<num; a++){
    //after printing out the root, remove it and bring the last element up to the root
    cout << heap[1] << endl;
    heap[1]=heap[size];
    heap[size] = 0;
    size--;
    //reheapify the heap by starting at the first non-leaf node and continuing up to the root
    for(int b = size/2; b > 0; b--){
      sort(b, size, heap);
    }
  }
}

void sort(int index, int size, int* &heap){
  //first make sure there is a left leaf
  if(size>=2*index){
    int current = heap[index];
    int largest = current;
    int left = heap[2*index];
    //then determine if there is a right leaf
    if(size>=(2*index+1)){
      //compare the parent with the left and right and swap it with the largest value
      //check to see if there is another level of leafs after the swap and sort them by recursively calling sort
      int right = heap[2*index+1];
      if(left>largest){
	largest = left;
      }
      if(right>largest){
	largest = right;
      }
      if(largest==left){
	int temp = heap[2*index];
	heap[2*index] = heap[index];
	heap[index]=temp;
	sort(2*index, size, heap);
      }
      else if(largest==right){
	int temp = heap[2*index+1];
	heap[2*index+1] = heap[index];
	heap[index] = temp;
	sort(2*index+1, size, heap);
      }
    }
    //if there's only a left, just compare the parent with the left
    else{
      if(left>largest){
	largest = left;
	int temp = heap[2*index];
	heap[2*index] = heap[index];
	heap[index]=temp;
	sort(2*index, size, heap);
      }
    }
  }
}

void visualPrint(int* heap, int index, int size){
  //calculate height, outputsections(nodes+slash sections)
  int height = log2(size)+1;
  int outputSections = height*2-1;
  int log = log2(size);
  int width = 4*(pow(2,log))-3;
  int lines = 0;
  int indexCount = 1;
  //cycle through the output sections
  for(int a = 0; a < outputSections; a++){
    //if the output section is even, print out numbers
    if(a%2==0){
      //calculate spacing, which is the number of spaces between each number
      //also calculate spaceleft which is how much that line should be indented
      int spacing = outputSections-a;
      spacing = spacing/2;
      spacing = spacing+2;
      spacing = pow(2,spacing)-1;
      int spaceLeft = width/2-lines;
      //print out the indent
      for(int b = 0; b < spaceLeft; b++){
	cout << " ";
      }
      //cycle through the array for the amount of numbers on that line
      int numNumbers = pow(2,a/2);
      for(int b = 0; b < numNumbers; b++){
	//based on the number of digits, adjust the spacing if need be
	int digits = numOfDigits(heap[index]);
	if(digits==3){
	  spacing--;
	  spacing--;
	}
	if(digits==2){
	  spacing--;
	}
	//break if you reach the end of the array
	if(heap[index]==0){
	  break;
	}
	//print out the number and then the spacing
	cout << heap[index];
	for(int c = 0; c <  spacing; c++){
	  cout << " ";
	}
	//change spacing back to its original value
	if(digits==3){
	  spacing++;
	  spacing++;
	}
	if(digits==2){
	  spacing++;
	}
	
	index++;
      }
      cout << endl;
      lines++;
    }
    //if the output section is odd, print out the slashes
    else{
      //figure out the number of lines in this section
      int numslash = (outputSections-a)/2;
      numslash = pow(2,numslash)-1;
      //start with one in between each pair of slashes
      int inbetween = 1;
      //the inital number of spaces between sets of slashes
      int betweensets = pow(2,(outputSections-a)/2+2)-3;
      //cycle through the lines
      for(int b = 0; b < numslash; b++){
	//calculate the indent and the number of sets of slashes
	int spaceLeft = width/2-lines;
	int sets = pow(2,(a-1)/2);
	//print out indent
	for(int c = 0; c < spaceLeft; c++){
	  cout << " ";
	  }
	for(int c = 0; c < sets; c++){
	  cout << "/";
	  //space in between front and back slashes
	  for(int d = 0; d < inbetween; d++){
	    cout << " ";
	  }
	  cout << "\\";
	  //print out space between sets
	  for(int d = 0; d < betweensets; d++){
	    if(c==sets-1){
	      break;
	    }
	    cout << " ";
	  }
	}
	//adjust values after each line
	inbetween += 2;
	betweensets -= 2;
	cout << endl;
	lines++;  
      }
    }
  }
}

//return a the number of digits of a number to aid with proper formatting
int numOfDigits(int num){
  if(num/100>0){
    return 3;
  }
  else if(num/10>0){
    return 2;
  }
  else{
    return 1;
  }
}

