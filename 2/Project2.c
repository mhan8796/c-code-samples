#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct Act
{
	char name[31]; //Name of Act
	char descri[251]; //Description of Act
	int len; //Length of Time for the Act
	int ord; //Current order of Act within the show
};

typedef struct nodeStruct //define a LLNode structure
{
	struct Act act;
	struct nodeStruct *next;
}LLNode;

void add(LLNode **head);
void move(LLNode **head);
void delete(LLNode **head);
void print(LLNode *head);
void save(LLNode *head);
void read(LLNode **head);

int main()
{
	int choice=0, flag=0;
	LLNode *head=NULL;
	printf("Greeting!Please enter number(number only):\n"); //start the program with a greeting
	while (flag == 0)
	{
		printf("\n1. Add a new act\n2. Delete an act\n3. Move an act\n4. Print the current schedule\n5. Save the current list to a file\n6. Read the list from a file\n7. Quit\n");
		scanf("%d", &choice); //then print the menu
		switch (choice) //Your program will be menu driven
		{
		case 1:
		{
				  add(&head); //Add a new act
				  break;
		}
		case 2:
		{
				  delete(&head); //Delete an act
				  break;
		}
		case 3:
		{
				  move(&head); //Move an act
				  break;
		}
		case 4:
		{
				  print(head); //Print the current schedule
				  break;
		}
		case 5:
		{
				  save(head);
				  break;
		}
		case 6:
		{
				  read(&head);
				  break;
		}
		case 7: //Quit
		{
				  flag = 1;
				  exit(0);
				  break;
		}
		default:
		{
				   printf("Please enter again\n");
				   break;
		}
		}
	}
	return 0;
}

void add(LLNode **head) //Add a new act
{
	struct Act act;
	LLNode *newnode;
	int choice=0;
	printf("Please enter the name of act:\n"); //you will prompt them for information about the act and use that information to initialize an Act structure.
	getchar();
	fgets(act.name, 30, stdin);
	printf("Please enter the description of act:\n");
	fgets(act.descri, 250, stdin);
	printf("Please enter the length of the act:\n");
	scanf("%d",&act.len);
	printf("where do you wanna add?\n1)at the beginning.\n2)in the middle.\n3)at the end.\n");
 //To insert the new LLNode into the list, you will first prompt the user regarding where they wish to insert the new act
	scanf("%d", &choice);
	switch (choice)
	{
	case 1:
f1:	{
	 		  int i = 0;
			  LLNode *ptr;
			  newnode = malloc(sizeof(LLNode));
			  if (newnode== NULL)
			  {
				  printf("Error allocating memory!\n");
				  exit(1);
			  }

			  newnode->act = act; //create an LLNode, and store the newly created Act structure within it.
			  newnode->next = *head;
			  *head = newnode;
			  ptr = *head;
			  while (ptr!= NULL)
			  {
				  ptr->act.ord = i + 1;
				  ptr = ptr->next;
				  i++;
			  }
			  break;
	}
	case 2:
	{
			  LLNode *pt, *ptr;
			  int num = 0, i = 0;
			  newnode = malloc(sizeof(LLNode));
			  if (newnode == NULL)
			  {
				  printf("Error allocating memory!\n");
				  exit(1);
			  }
			  newnode->act = act;
			  print(*head); //If the user chooses the middle, prompt the user for the Show Order value before which the new LLNode should be inserted
			  printf("Which one you want to add before?:\n");
			  scanf("%d", &num);
			  if (num == 1)
			  {
				  goto f1;
			  }
			  else
			  {
			  pt = *head;
			  while (pt->next != NULL&&pt->next->act.ord != num)
			  {
				  pt = pt->next;
			  }
			  newnode->next = pt->next;
			  pt->next = newnode;
			  ptr = *head;
			  while (ptr != NULL)
			  {
				  ptr->act.ord = i + 1;
				  ptr = ptr->next;
				  i++;
			  }
			 }
			  break;
	}
	case 3:
	{
			  if (*head == NULL)
			  {
				  goto f1;
			  }
			  else
			  {
				  LLNode *ptr = *head;
				  int i = 0;
				  newnode = malloc(sizeof(LLNode));
				  if (newnode == NULL)
				  {
					  printf("Error allocating memory!\n");
					  exit(1);
				  }
				  newnode->act = act;
				  while (ptr->next != NULL)
				  {
					  ptr = ptr->next;
				  }
				  ptr->next = newnode;
				  newnode->next = NULL;
				  ptr = *head;
				  while (ptr != NULL)
				  {
					  ptr->act.ord = i + 1;
					  ptr = ptr->next;
					  i++;
				  }
			  }
			  break;
	}
	default:
	{
			   printf("Please enter again\n");
			   break;
	}
	}
}

void move(LLNode **head)
{
	int num=0, numm=0,i=0;
	LLNode *ptr,*temp,*pre,*p;
	printf("Enter a order you want to move:\n"); //the user is prompted to enter the Show Order value of the node to be moved
	scanf("%d", &num);
	printf("Enter a order you want to insert before:\n"); //Then the user is prompted to enter the Show Order value before which the node should be inserted
	scanf("%d", &numm);
	if (num == 1&&numm!=1)
	{
		p = *head;
		ptr = *head;
		while (ptr != NULL&&ptr->act.ord != numm)
		{
			pre = ptr;
			ptr = ptr->next;
		}
		if (ptr != NULL)
		{
			*head = p->next;
			p->next = ptr;
			pre->next = p;
		}
		else
printf("no match found"); //If either the node to be moved or the node with the entered Show Order cannot be found, an error message is displayed for the user and the list is left intact.
	}
	else if (numm == 1&&num!=1)
	{
		int i = 0;
		ptr=*head;
		while (ptr != NULL&&ptr->act.ord != num)
		{
			pre = ptr;
			ptr = ptr->next;
		}
		if (ptr != NULL)
		{
			pre->next = ptr->next;
			ptr->next = *head;
			*head = ptr;
		}
		else
printf("no match found"); //If either the node to be moved or the node with the entered Show Order cannot be found, an error message is displayed for the user and the list is left intact.
		ptr = *head;
		while (ptr != NULL)
		{
			ptr->act.ord = i + 1;
			ptr = ptr->next;
			i++;
		}
	}
	else if (num == 1 && numm == 1)
	{}
	else
	{
		ptr = *head;
		while (ptr != NULL&&ptr->act.ord != num)
		{
			pre = ptr;
			ptr = ptr->next;
		}
		if (ptr != NULL)
		{
			temp = ptr;
			pre->next = temp->next;
		}
		else
printf("no match found"); //If either the node to be moved or the node with the entered Show Order cannot be found, an error message is displayed for the user	and the list is left intact.
		ptr = *head;
		while (ptr != NULL&&ptr->act.ord != numm)
		{
			pre = ptr;
			ptr = ptr->next;
		}
		if (ptr != NULL)
		{
			temp->next = ptr;
			pre->next = temp;
		}
		else
			printf("no match found");
	}
	ptr = *head;
	while (ptr!= NULL) 
	{
		ptr->act.ord = i+1;
		ptr = ptr->next;
		i++;
	}
}

void delete(LLNode **head) //Delete an act
{
	int num = 0, i=0;
	LLNode *ptr = *head;
	printf("Please enter a show order to delete:\n"); //the user is prompted to enter the Show Order value
	scanf("%d", &num);
	if (num == 1)
	{
		*head = ptr->next;
		free(ptr);
		ptr = *head;
		while (ptr != NULL) //Show Order refresh
		{
			ptr->act.ord = i + 1;
			ptr = ptr->next;
			i++;
		}
	}
	else
	{
		while (ptr->next != NULL&&ptr->next->act.ord != num)
		{
			ptr = ptr->next;
		}
		if (ptr->next != NULL)
		{
			LLNode *temp = ptr->next;
			ptr->next = temp->next;
			free(temp);
			ptr = *head;
			while (ptr != NULL) ////Show Order refresh
			{
				ptr->act.ord = i + 1;
				ptr = ptr->next;
				i++;
			}
		}
		else
			printf("no match found"); //If the LLNode is not found with that Show Order, an error message is printed for the user
	}
}

void print(LLNode *head) //Print the current schedule
{
	LLNode *ptr = head;
	while (ptr != NULL)
	{ //all the data in each Act strucure is printed to the screen in an easy to read manner
		printf("\nAct name: %s",ptr->act.name);
		printf("Act description: %s",ptr->act.descri);
		printf("Act length: %d\n",ptr->act.len);
		printf("Act order: %d\n",ptr->act.ord);
		ptr = ptr->next;
	}
}

void save(LLNode *head) //save the current list of acts to a binary file
{
	FILE *fp;
	LLNode *ptr;
	char filename[50];
	int i = 0;
	ptr = head;
	printf("Please enter a file name to save:\n");
	scanf("%s", &filename);
	getchar();
	fp = fopen(filename, "wb");
	if (!fp)
	{
		printf("Unable to open file!");
		exit(1);
	}
	while (ptr != NULL)
	{
		fwrite(ptr, sizeof(LLNode), 1, fp);
		ptr = ptr->next;
	}
	fclose(fp);
}

void read(LLNode **head) //read a list from a binary file
{
	FILE *fp;
	char filename[50];
	LLNode *ptr;
	int i = 0, si = 0, size = 0;
	printf("Please enter a file name to read:\n");
	scanf("%s", &filename);
	getchar();
	fp = fopen(filename, "rb");
	if (!fp)
	{
		printf("Unable to open file!\n");
		exit(1);
	}
	fseek(fp, 0, SEEK_END);
	si=ftell(fp);
	fseek(fp, 0, SEEK_SET);
	size = si / sizeof(LLNode);
	ptr = malloc(size*sizeof(LLNode));
	if (ptr == NULL)
	{
		printf("Error allocating memory!\n");
		exit(1);
	}
	for (i = 0; i < size; i++)
		fread(&ptr[i], sizeof(LLNode), 1, fp);
	*head = &ptr[0];
	for (i = 0; i < size; i++)
		ptr[i].next = &ptr[i + 1];
	ptr[i-1].next = NULL;
	fclose(fp);
}
