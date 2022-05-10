#pragma once
#include <iostream>
#include <iomanip>


using namespace std;

string statement;

template <typename dataType>


class List
{
private:

	size_t size_of_list; //Number of items in the list

	class Element
	{

	public:

		Element* Next, * Previous; //Pointers to the next and previous element.

		dataType member;

		Element(dataType member, Element* Next = NULL, Element* Previous = NULL)
		{
			this->member = member;
			this->Next = Next;
			this->Previous = Previous;
		}
	};




	Element* Head; //Pointer to the beginning
	Element* Tail; //Pointer to the end


public:


	List()  //Constructor for creating an empty list
	{

		Head = Tail = NULL;
		size_of_list = 0;

	};

	List(dataType member) //Constructor for creating a list with an element
	{

		Element* newNode = new Element(member);

		Head = Tail = newNode;

		size_of_list = 1;

	};

	~List() //Destructor
	{

		clear();

	};

	void clear()
	{ //Deleting all list members

		Element* temp = Head; // Create temporary node

		while (Head != NULL) //Deleting members
		{
			Element* temp = Head->Next;
			delete Head;
			Head = temp;
		}

		Tail = Head = NULL;

		size_of_list = 0;

	};

	size_t get_size()  //Getting the number of items in the list
	{
		return size_of_list;
	}



	void push_back(dataType member) {          //Adding an item to the end of the list

		Element* newNode = new Element(member);


		if (isEmpty()) {                       //If the list is empty

			Head = Tail = newNode;
		}


		else {                                //If the list is not empty

			newNode->Previous = Tail;
			Tail->Next = newNode;
			Tail = newNode;

		}

		size_of_list++;
	};

	void push_front(dataType newMember)                 //Add a new element forward
	{
		Element* temp = new Element(newMember);

		if (Head != NULL)                             //If List is not empty
		{
			temp->Next = Head;
			Head->Previous = temp;
			Head = temp;
			size_of_list++;
		}

		else                                          //If List is empty
		{
			Head = Tail = temp;
			size_of_list++;
		}
	}


	bool isEmpty()    //Checking for emptiness
	{
		if (Head == NULL)
			return true;
		else
			return false;
	}


	void push_back(List& newList)
	{
		Element* temp = newList.Head;

		for (int i = 0; i < (int)newList.get_size(); i++)
		{

			this->push_back(temp->member);
			temp = temp->Next;

		}
	};




	dataType at(size_t elem)                                                 //Getting an element by index
	{

		if (elem < get_size()) // If index is in List range
		{
			Element* temp = Head; // Create temporary node
			for (int i = 0; i < elem; i++) {
				temp = temp->Next;
			}
			return temp->member;
		}

		else {
			throw out_of_range("Out of range");
		}


	}
		
	dataType headValue() 
	{
		if (size_of_list != 0)

			return Head->member;

		else

			throw out_of_range("No elements");
	}

	
	void goNext() 
	{
		if (Head != NULL)

			Head = Head->Next;

		else
			throw out_of_range("No elements");
	}

	
	void insert(dataType value, size_t elem)                                //Inserting before an element that was previously available by this index
	{

		if (elem > get_size() - 1)
			throw out_of_range("Out of range");

		else
		{
			if ((elem == 0) || (elem = get_size() - 1))                         //Adding to extreme points
			{
				if (elem == 0)
					push_front(value);
				if (elem = get_size() - 1)
					push_back(value);
			}

			else                                                             //Adding to the middle
			{
				Element* temp = Head, * save;

				for (int i = 0; i < elem - 1; i++)
					temp = temp->Next;

				Element* newElement = new Element(value, NULL, NULL);

				newElement->member = value;
				save = temp->Next;
				temp->Next;
				temp->Next = newElement;
				newElement->Next = save;

				size_of_list++;
			}

		}
	}



	friend std::ostream& operator << (std::ostream& out, List& currentList) //Redefining output
	{
		size_t current_size_of_list = currentList.get_size();

		for (size_t i = 0; i < current_size_of_list; i++)
		{
			cout << currentList.at(i) << endl;
		}
		return out;
	}
};

template<typename dataTypeForKey, typename dataTypeForValue>


class MyMap
{
private:

	class Element
	{
	public:

		bool color;					    // Black is 0| Red is 1
		dataTypeForKey key;
		dataTypeForValue value;
		Element* leftChild;
		Element* rightChild;
		Element* parent;

		Element(dataTypeForKey key, dataTypeForValue value, Element* parent, bool color, Element* leftChild = NULL, Element* rightChild = NULL)
		{

			this->key = key;
			this->value = value;
			this->parent = parent;
			this->color = color;
			this->leftChild = leftChild;
			this->rightChild = rightChild;

		}
	};

	Element* root;
	Element* nil;

	void leftTurn(Element* first) //Making a left turn
	{
		Element* second = first->rightChild;
		first->rightChild = second->leftChild;

		if (second->leftChild != nil)
			second->leftChild->parent = first;

		second->parent = first->parent;

		if (first->parent == NULL)
			this->root = second;

		else
		{

			if (first == first->parent->leftChild)
				first->parent->leftChild = second;

			else
				first->parent->rightChild = second;
		}

		second->leftChild = first;
		first->parent = second;
	}

	void rightTurn(Element* first) //Making a right turn
	{
		Element* second = first->leftChild;
		first->leftChild = second->rightChild;

		if (second->rightChild != nil)
			second->rightChild->parent = first;

		second->parent = first->parent;

		if (first->parent == NULL)
			this->root = second;

		else
		{
			if (first == first->parent->rightChild)
				first->parent->rightChild = second;
			else
				first->parent->leftChild = second;
		}

		second->rightChild = first;
		first->parent = second;
	}

	void outputOfTreeElement(Element* element) //Output of tree's element

	{
		if (element != nil)
		{
			if (element->rightChild != NULL && element->rightChild != nil)
				outputOfTreeElement(element->rightChild);

			if (element->leftChild != NULL && element->leftChild != nil)
				outputOfTreeElement(element->leftChild);

			if (element->parent != NULL) //If the element is not the root
				cout << "Êëþ÷: " << element->key << "|Çíà÷åíèå: " << element->value << "|Öâåò: " << element->color << "|Ðîäèòåëü: " << element->parent->key << endl;
			else //If the element is the root
				cout << "Êëþ÷: " << element->key << "|Çíà÷åíèå: " << element->value << "|Öâåò: " << element->color << "|Êîðåíü" << endl;

		}
	}


	void getValues(Element* member, List<dataTypeForValue>* value) //Getting the value of an element and adding it to the list
	{
		if (member != nil)
		{
			getValues(member->leftChild, value);

			value->push_back(member->value);

			getValues(member->rightChild, value);
		}
	}

	void getKeys(Element* memeber, List<dataTypeForKey>* key) //Getting the element key and adding it to the list
	{
		if (memeber != nil)
		{
			getKeys(memeber->leftChild, key);

			key->push_back(memeber->key);

			getKeys(memeber->rightChild, key);
		}
	}

public:

	MyMap() //Empty Tree Constructor
	{

		nil = new Element(NULL, NULL, NULL, 0); //Leaves and root are always black
		root = nil;

	};

	~MyMap() //Destructor
	{
		this->root == nil;
	};

	void insert(dataTypeForKey key, dataTypeForValue value)
	{
		Element* temp = new Element(key, value, NULL, 1, nil, nil); //Creating a new red element whose descendants are empty leaves

		if (this->root == nil) //If the tree is empty
		{
			root = temp;
			temp->color = 0; //Repaint the element in black
			return;
		}

		else //If the tree is empty
		{
			Element* parent = NULL;
			Element* newNode = this->root;

			while (newNode != nil) //Until we reached the leaves
			{
				parent = newNode;

				if (temp->key < newNode->key) //If the key of the element is smaller, then go to the left
				{
					newNode = newNode->leftChild;
				}

				else //If the key of the element is bigger, then go to the right
				{
					newNode = newNode->rightChild;
				}
			}

			temp->parent = parent;

			if (temp->key < parent->key) //If the key of the parent is bigger, then the current element becomes its left child
				parent->leftChild = temp;

			else //If the key of the parent is smaller, then the current element becomes its right child
				parent->rightChild = temp;
		}
		if (temp->parent->parent == NULL)
			return;
		//We are starting to restore the structure of the red-black tree
		Element* grandPerent;

		while (temp->parent->color == 1) //While perent is Red

		{
			bool whatPosition = temp->parent->parent->rightChild == temp->parent;//Initializing a variable

			grandPerent = whatPosition ? (temp->parent->parent->leftChild) : (temp->parent->parent->rightChild);

			if (grandPerent->color == 1) //If the color is red
			{
				grandPerent->color = 0;

				temp->parent->color = 0;

				temp->parent->parent->color = 1;

				temp = temp->parent->parent;
			}

			else
			{
				if (temp == (whatPosition ? (temp->parent->leftChild) : (temp->parent->rightChild)))
				{
					temp = temp->parent;
					whatPosition ? rightTurn(temp) : leftTurn(temp);
				}
				temp->parent->color = 0;

				temp->parent->parent->color = 1;

				whatPosition ? leftTurn(temp->parent->parent) : rightTurn(temp->parent->parent);//Making rigth or left turn
			}

			if (temp == root)
			{
				break;
			}
		}

		root->color = 0;

	};

	void remove(dataTypeForKey key)
	{
		Element* nodeToBeDeleted = find(key);//Getting the address of the desired element

		Element* first = NULL;
		Element* second = NULL;

		int originalColor = nodeToBeDeleted->color;

		second = nodeToBeDeleted;
		//Moving the right descendant of the deleted element to its place
		if (nodeToBeDeleted->leftChild == nil)
		{
			first = nodeToBeDeleted->rightChild;

			if (nodeToBeDeleted->parent == NULL)
				root = nodeToBeDeleted->rightChild;

			else
			{

				if (nodeToBeDeleted == nodeToBeDeleted->parent->leftChild)
					nodeToBeDeleted->parent->leftChild = nodeToBeDeleted->rightChild;

				else
					nodeToBeDeleted->parent->rightChild = nodeToBeDeleted->rightChild;
			}

			nodeToBeDeleted->rightChild->parent = nodeToBeDeleted->parent;
		}
		else
		{
			if (nodeToBeDeleted->rightChild == nil)
			{
				first = nodeToBeDeleted->leftChild;

				if (nodeToBeDeleted->parent == NULL)
					root = nodeToBeDeleted->leftChild;

				else
				{

					if (nodeToBeDeleted == nodeToBeDeleted->parent->leftChild)
						nodeToBeDeleted->parent->leftChild = nodeToBeDeleted->leftChild;

					else
						nodeToBeDeleted->parent->rightChild = nodeToBeDeleted->leftChild;
				}

				nodeToBeDeleted->leftChild->parent = nodeToBeDeleted->parent;
			}

			else
			{
				second = nodeToBeDeleted->rightChild;

				while (second->leftChild != nil)
				{
					second = second->leftChild;
				}

				originalColor = second->color; //Saving the color
				first = second->rightChild;

				if (second->parent == nodeToBeDeleted)
					first->parent = second;

				else
				{
					if (second->parent == NULL)
						root = second->rightChild;

					else
					{
						if (second == second->parent->leftChild)
							second->parent->leftChild = second->rightChild;

						else
							second->parent->rightChild = second->rightChild;
					}
					second->rightChild->parent = second->parent;

					second->rightChild = nodeToBeDeleted->rightChild;
					second->rightChild->parent = second;
				}


				if (nodeToBeDeleted->parent == NULL)
					root = second;

				else
					if (nodeToBeDeleted == nodeToBeDeleted->parent->leftChild)
						nodeToBeDeleted->parent->leftChild = second;

					else
						nodeToBeDeleted->parent->rightChild = second;

				second->parent = nodeToBeDeleted->parent;

				second->leftChild = nodeToBeDeleted->leftChild;

				second->leftChild->parent = second;

				second->color = nodeToBeDeleted->color;
			}
		}

		//We are starting to restore the structure of the red-black tree
		if (originalColor == 0)
		{
			Element* sibling;

			while (first != root && first->color == 0)
			{
				if (first == first->parent->leftChild)
				{
					sibling = first->parent->rightChild;

					if (sibling->color == 1) //if color of the sibling is Red
					{
						sibling->color = 0; //Making color of simbling black

						first->parent->color = 1;//Making parent red

						leftTurn(first->parent); //Making left tern 

						sibling = first->parent->rightChild;
					}

					if (sibling->leftChild->color == 0 && sibling->rightChild->color == 0) //If the color of both descendants is black
					{
						sibling->color = 1;
						first = first->parent;
					}
					else
					{
						if (sibling->rightChild->color == 0)
						{
							sibling->leftChild->color = 0;//Left child becomes black

							sibling->color = 1;// Changing color to red

							rightTurn(sibling);//Making right tern

							sibling = first->parent->rightChild;
						}
						sibling->color = first->parent->color;//Changing color to the color of its perent

						first->parent->color = 0; //Changing perents color to black

						sibling->rightChild->color = 0;//Changing right child's color to black

						leftTurn(first->parent);//Making left tern 

						first = root;
					}
				}
				//We repeat the same algorithm, but change the direction of turns to the opposite
				else
				{
					sibling = first->parent->leftChild;

					if (sibling->color == 1)
					{
						sibling->color = 0;

						first->parent->color = 1;

						rightTurn(first->parent); //Making right tern

						sibling = first->parent->leftChild;
					}

					if (sibling->rightChild->color == 0 && sibling->rightChild->color == 0)
					{
						sibling->color = 1;
						first = first->parent;
					}

					else
					{
						if (sibling->leftChild->color == 0)
						{
							sibling->rightChild->color = 0;

							sibling->color = 1;

							leftTurn(sibling); //Making left tern 

							sibling = first->parent->leftChild;
						}

						sibling->color = first->parent->color;

						first->parent->color = 0;

						sibling->leftChild->color = 0;

						rightTurn(first->parent);//Making right tern

						first = root;
					}
				}
			}
			first->color = 0;//Changing color to black
		}

	}

	void print() //Tree output
	{
		if (this->root != nil)
			outputOfTreeElement(this->root);
		else
			throw invalid_argument("Map is empty");
	};
	

	List <dataTypeForKey> get_keys()  //Getting the keys of all tree elements
	{
		List<dataTypeForKey>* keys = new List<dataTypeForKey>;

		getKeys(root, keys);

		return *keys;
	}


	List <dataTypeForValue> get_values() //Getting the values of all tree elements
	{
		List<dataTypeForValue>* values = new List<dataTypeForValue>;

		getValues(root, values);

		return *values;
	}



	Element* find(dataTypeForKey key)
	{
		Element* searchable = NULL;
		Element* temp = this->root;

		while (temp != nil) //Until they reached the leaves
		{
			if (temp->key == key) //If this is the right element
			{
				searchable = temp;
				break;
			}

			if (temp->key > key) //If the key of the current element is bigger than the key you are looking for
				temp = temp->leftChild;

			else //If the key of the current element is smaller than the key you are looking for
				temp = temp->rightChild;
		}

		if (searchable == NULL)
		{
			throw invalid_argument("This element is not in the tree");
		}

		else
		{
			//Return the address of the desired item
			return searchable;

		}

	}

	int findForValue(dataTypeForKey key)
	{
		Element* searchable = NULL;
		Element* temp = this->root;

		while (temp != nil) //Until they reached the leaves
		{
			if (temp->key == key) //If this is the right element
			{
				searchable = temp;
				break;
			}

			if (temp->key > key) //If the key of the current element is bigger than the key you are looking for
				temp = temp->leftChild;

			else //If the key of the current element is smaller than the key you are looking for
				temp = temp->rightChild;
		}

		if (searchable == NULL)
		{
			throw invalid_argument("This element is not in the tree");
		}

		else
		{
			//Return the value of the desired item
			return searchable->value;

		}

	}

	bool isInMap(dataTypeForKey key)  //Checking for the presence of an element with a specified key
	{
		Element* searchable = NULL;
		Element* temp = this->root;

		while (temp != nil) //Until they reached the leaves
		{
			if (temp->key == key) //If this is the right element
			{
				searchable = temp;
				break;
			}

			if (temp->key > key) //If the key of the current element is bigger than the key you are looking for
				temp = temp->leftChild;

			else //If the key of the current element is smaller than the key you are looking for
				temp = temp->rightChild;
		}

		if (searchable == NULL)
		{
			return false;
		}

		else
		{

			return true;
		}
	}

};



class Coding //The main class that ensures the operation of the algorithm
{
	private:

		char* charBuff;

		int* numberOfSymbols; //Saving the number of each unique symbols
		
		int powerOfLanguage; //Saving number of unique symbols

		string* encoding; //Saving encodings of each symbol

	
		

	
	
	bool contains(string tempString) {
		for (int i = 0; i < powerOfLanguage; i++)
		{
			if (encoding[i] == tempString) 
				return true;
		}
		return false;
	}

	public:
	
		Coding(MyMap<char, int>& currentMap, int languagePower, string newStatement)    //Constructor
		{
			List<char> currentKeys = currentMap.get_keys();
			List<int> currentValues = currentMap.get_values();

			charBuff = new char[languagePower];

			numberOfSymbols = new int[languagePower];

			encoding = new string[languagePower];

			powerOfLanguage = languagePower;

			statement = newStatement;



			for (int i = 0; i < powerOfLanguage; i++)
			{
				encoding[i] = "";

				charBuff[i] = currentKeys.headValue();

				numberOfSymbols[i] = currentValues.headValue();
				encoding[i] = "";
				currentKeys.goNext();
				currentValues.goNext();
			}


			BubbleSort();
		}

		
	void encodingTheStatement(int start, int finish)//The main encode algorithm
	{
		if (start == finish)
			return;

		else
		{
			int first = start;
			int last = finish;
		 	int firstSumm = 0;
			int lastSumm = 0;
			
			/*Finding the optimal index to split the array so that 
			the sum of both parts of the array are approximately equal*/

			while (first <= last) 
			{
				if (firstSumm <= lastSumm) 
				{
					firstSumm += numberOfSymbols[first];
					first++;
				}

				else 
				{
					lastSumm += numberOfSymbols[last];
					last--;
				}
			}
			
			/*We put zeros in the codes of the elements of the left part of the 
			array, and ones in the codes of the elements of the last part of the array*/

			for (int i = start; i < first; i++) 
			{
				encoding[i] += "0";
			}
			
			for (int i = first; i <= finish; i++)
			{
				encoding[i] += "1";
			}
			
			/*Recursively repeat the algorithm until each element 
			of the original array has its own unique code*/

			encodingTheStatement(start, first - 1);
			encodingTheStatement(first, finish);


		}
		
	}

	
	string encodeTheStatement()//Encoding the original statement
	{
		int temp = 0;

		string encodedStetement = "";

		for (int i = 0 ; i < statement.size(); i++)
		{
			for (int j = 0; j < powerOfLanguage; j++)
			{
				if (charBuff[j] == statement.at(i))
				{
					temp = j;
					break;
				}
				
			}
			encodedStetement += encoding[temp];
		}

		return encodedStetement;
	
	}
	
	
	
	
	string decodeTheStatement() //Decoding the original statement
	{
		string decodedTheStatement = "";

		string currentEncodedStatement = encodeTheStatement();

		int temp = 0;

		int max_code_lenght = 0;

		for (int i = 0; i < powerOfLanguage; i++) 
		{
			if (encoding[i].size() > max_code_lenght) max_code_lenght = encoding[i].size();
		}

		while (currentEncodedStatement.size() > 0)
		{
			for (int i = 0; i <= (max_code_lenght < currentEncodedStatement.size()) ? max_code_lenght: currentEncodedStatement.size(); i++)
			{
				string substring = currentEncodedStatement.substr(0, i);

				if (contains(substring)) 
				{
					for (int j = 0; j < powerOfLanguage; j++)
					{
						if (encoding[j] == substring)
						{
							temp = j;
							break;
						}
												
					}
				
					decodedTheStatement += charBuff[temp];

					currentEncodedStatement.erase(0, i);

					break;
				}
			}
		}
		return decodedTheStatement;
	}

	
	

	void printResults()
	{
		for (int i = 0; i < powerOfLanguage; i++) //Output of characters and their encodings
		{
			cout << "| Symbol: " << charBuff[i] << " | " << "Frequency: " << (float)((float)numberOfSymbols[i]/(float)statement.size()) << " | Code: "<< encoding[i]<<" |" << endl;;
		}

		cout <<"| "<< statement << " | " << encodeTheStatement() << " | " << decodeTheStatement()<< " |" << endl;  //Output of encoded and decoded statements 
		
		int amountOfStatenet = 0; //Computing of compression ratio
		int amountOfEncoding = 0;

		float compressionRatio;

		for (int i = 0; i < powerOfLanguage; i++)
		{
			amountOfStatenet += 8 * numberOfSymbols[i];
		}

		for (int i = 0; i < powerOfLanguage; i++)
		{
			amountOfEncoding += encoding[i].size() * numberOfSymbols[i];
		}
		
		compressionRatio = (float)amountOfStatenet / (float)amountOfEncoding;

		cout << "| Before: " << amountOfStatenet << " bites | " << "After: " << amountOfEncoding << " bites |" << endl; //Output of the volume of the original and encoded phrases

		cout << "| Compression Ratio: " << compressionRatio << " |" << endl; //Outputing of compression ratio
		 
		
	}
	
	void BubbleSort() //Bubble sorting algorithm from 2 lab of the last semester
	{
		for (int i = 0; i < powerOfLanguage; i++) 
		{
			for (int j = 0; j < powerOfLanguage - 1; j++) 
			{
				if (numberOfSymbols[j] < numberOfSymbols[j + 1])
				{
					int int_temporary = numberOfSymbols[j];

					char char_temporary = charBuff[j];

					numberOfSymbols[j] = numberOfSymbols[j + 1];

					charBuff[j] = charBuff[j + 1];

					numberOfSymbols[j + 1] = int_temporary;

					charBuff[j + 1] = char_temporary;
				}
			}
		}
	}
}; 
