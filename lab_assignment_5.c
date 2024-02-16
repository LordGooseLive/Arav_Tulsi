#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	char letter;
	struct node* next;
} node;

// Returns number of nodes in the linkedList.
int length(node* head)
{	
	//Var declaration
	int len = 0; //length of list

	//counts nodes
	if (head != NULL) //ensures list exists
	{
		//itterates through list
		for (len; head-> next != NULL; len++) // local <<head>> safe to increment
		{
			head = head -> next; //itterates <<head>>
		}
	}
	return len; //returns length of list
}

// parses the string in the linkedList
//  if the linked list is head -> |a|->|b|->|c|
//  then toCString function wil return "abc"
char* toCString(node* head)
{
	//Var declaration
	int len = length (head); //gets length of list	
	node * temp = head; //traversial variable
	char * string = (char *) malloc (sizeof (char ) * (++len)); //dynamic string
	/* Incrementing <<len>> above 
	allows for null char and reduces 
	operations in string traversal 
	and manipulation in following 
	lines of code*/
	
	//Parses string
	if (string != NULL)	//ensures malloc successful
	{
		//traverses lists and array
		for (int i = 0; i < len; i++)
		{
			string[i] = temp->letter; //copies list to array
			temp = temp->next; //travels to next node
		}
		string [len] = '\0'; //initialises last element to NULL
	}
	return string;
}

// inserts character to the linkedlist
// f the linked list is head -> |a|->|b|->|c|
// then insertChar(&head, 'x') will update the linked list as foolows:
// head -> |a|->|b|->|c|->|x|
void insertChar(node** pHead, char c)
{
	//creates and initialises newnode
	node * newNode = (node*) malloc (sizeof (node));
	newNode-> letter = c; //stores passby-char
	newNode-> next = NULL; //marks as list end

	//inserts node to empty list
	if ( *pHead == NULL)
	{
		*pHead = newNode; //links new node
	}

	//inserts node to existing list
	else
	{
		node *temp = *pHead; //temporary variable improves readability
		for (temp; temp->next != NULL; temp = temp->next); //traverses to tail
		temp->next = newNode; //links new node
	}
}

// deletes all nodes in the linkedList.
void deleteList(node** pHead)
{
	//Var declaration
	node * current = *pHead;
	node * temp = NULL;

	//deallocation process
	while (current != NULL) //traverses through list
	{
		temp = current;
		current = current->next; //itterates current
		free (temp); //frees node
	}

	//clears head pointer in main
	*pHead = NULL; 
}

int main(void)
{
	int i, strLen, numInputs;
	node* head = NULL;
	char* str;
	char c;
	FILE* inFile = fopen("input.txt","r");

	fscanf(inFile, " %d\n", &numInputs);
	
	while (numInputs-- > 0)
	{
		fscanf(inFile, " %d\n", &strLen);
		for (i = 0; i < strLen; i++)
		{
			fscanf(inFile," %c", &c);
			insertChar(&head, c);
		}

		str = toCString(head);
		printf("String is : %s\n", str);

		free(str);
		deleteList(&head);

		if (head != NULL)
		{
			printf("deleteList is not correct!");
			break;
		}
	}

	fclose(inFile);
}