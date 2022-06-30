#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OK			0
#define ERROR			1
#define PHONE_NUMBER_LENGTH	9
#define MAX_NAME_LENGTH		32
#define NUMBER_OF_MONTHS	12
#define DAYS_PER_MONTH		30


struct contact {
	char* name;
	char phoneNumber[PHONE_NUMBER_LENGTH];
	unsigned short bDay;	
	unsigned short bMonth;	
};

typedef struct contact contact;

int loadContactByData(char* name,
	       		char phoneNumber[PHONE_NUMBER_LENGTH],
	       		unsigned short bDay,
			unsigned short bMonth,
			contact* c)
{
	c->name = (char*) malloc(sizeof(char) * MAX_NAME_LENGTH);

	strncpy(c->name, name, MAX_NAME_LENGTH);

	if (strlen(phoneNumber) != PHONE_NUMBER_LENGTH )
	{
		puts("Invalid phone number length.");
		return ERROR;	
	}

	strcpy(c->phoneNumber, phoneNumber);

	if (bDay > DAYS_PER_MONTH)
	{
		puts("Invalid bDay.");
		return ERROR;	
	}
	
	c->bDay = bDay;

	if (bMonth > NUMBER_OF_MONTHS)
	{
		puts("Invalid bMonth.");
		return ERROR;	
	}

	c->bMonth = bMonth;

	return OK;
}

int loadContacts(char* filename, contact** contacts)
{
	char buff[255];
	int rc;
	char* token;
	int phoneBookRows = 1;
	FILE* fp;
	unsigned char columnCount = 1;

	
	fp = fopen(filename, "r");

	if (fp == NULL) {
		puts("The specified file does not exist.");
		return ERROR;
	}



	while (fscanf(fp, "%s", buff) != EOF)
	{
		contact c;
		c.name = (char*) malloc(sizeof(char) * MAX_NAME_LENGTH);
		
		printf("Line read: %s\n", buff);

		token = strtok(buff, ",");
		strncpy(c.name, token, MAX_NAME_LENGTH);
		while (token != NULL)
		{
			token = strtok(NULL, ",");
			switch(columnCount)
			{
				case 1:
					printf("c.name: %s\n", c.name);
					strcpy(c.phoneNumber, token);
					printf("c.phoneNumber: %s\n", c.phoneNumber);
					break;
				case 2:
					c.bDay = atoi(token);
					printf("c.bDay: %hu\n", c.bDay);
					break;
				case 3:
					c.bMonth = atoi(token);
					printf("c.bMonth: %hu\n", c.bMonth);
					break;
			}
			columnCount++;
		}

		puts("---");
		free(c.name);
		
		columnCount = 1;

		/*printf("Loading contact...\nName: %s\nPhone Number: %s\nBirthday: %s/%s\n\n", 
				buff[0],
				buff[1],
				buff[2],
				buff[3]);*/
	}
	fclose(fp);

	/* Successfully loaded contact into matrix
	loadContactByData("Artur", "999328951", 4, 5, &c);	
	printf("Loading contact...\nName: %s\nPhone Number: %s\nBirthday: %u/%u\n\n", 
			c.name,
			c.phoneNumber,
			c.bDay,
			c.bMonth);

	contacts = (contact**) realloc(contacts, sizeof(contact) * phoneBookRows);

	printf("sizeof(contacts): %lu\n", sizeof(contact) * phoneBookRows );

	contacts[0] = &c;
	*/
	return OK;
}

int main()
{

/*	---- TEST LOAD CONTACT ----
 *
	contact c;
	int rc;

	rc = loadContactByData("Artur", "999328951", 4, 5, &c);

	if (rc != OK){
		puts("Fatal error at loadContactByData() - Aborting program.");
		exit(1);
	}

	printf("Loading contact...\nName: %s\nPhone Number: %s\nBirthday: %u/%u\n\n", 
			c.name,
			c.phoneNumber,
			c.bDay,
			c.bMonth);

*/

	/* Testando preenchimento de array de structs. Sucesso. Sem handling de arquivos ainda.
	contact** contacts;
	char* phoneBookFileName = "data/phonebook.txt";
	int rc;
	
	contacts = (contact**) malloc(sizeof(contact)); 
	rc = loadContacts(phoneBookFileName, contacts);
	
	if (rc != OK) {
		puts("Fatal error at loadContacts() - Aborting program.");
		exit(1);
	}

	printf("Loading contact...\nName: %s\nPhone Number: %s\nBirthday: %u/%u\n\n", 
			contacts[0][0].name,
			contacts[0][0].phoneNumber,
			contacts[0][0].bDay,
			contacts[0][0].bMonth);*/

	contact** contacts;
	char* phoneBookFileName = "./data/mock.txt";
	int rc;

	contacts = (contact**) malloc(sizeof(contact)); 
	rc = loadContacts(phoneBookFileName, contacts);
	
	if (rc != OK) {
		puts("Fatal error at loadContacts() - Aborting program.");
		exit(1);
	}

	return OK;
}

