#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fstream>
#include <math.h>

using namespace std;

const int SURRENDER= 0;
const int MADBEAR = 1;
const int BANDIT = 2;
const int LORDLUPIN= 3;
const int ELF= 4;
const int TROLL= 5;
const int SHAMAN= 6;
const int VAJSH= 7;
const int EXCALIBUR= 8;
const int MYTHRIL= 9;
const int EXCALIPOOR= 10;
const int MUSHMARIO= 11;
const int MUSHFIB= 12;
const int MUSHGHOST= 13;
const int MUSHKNIGHT= 14;
const int REMEDY= 15; 
const int MAIDENKISS= 16;
const int PHOENIXDOWN= 17;
const int MERLIN= 18;
const int ABYSS= 19;
const int GUINEVERSE= 20;
const int LIGHTWING= 21;
const int ODIN= 22;
const int DRAGON_SWORD= 22;
const int BOWSER=99;

const int ROUND_TABLE_WARRIOR= 0;
const int ARTHUR= 1;
const int LANCELOT= 2;
const int PALADIN= 3;
const int DRAGON_WARRIOR=4;

const int EVENT_SIZE = 100;
const int MAX_CHARACTER_EACH_LINE = 250;

struct knight
{
   int HP;
   int level;
   int remedy;
   int maidenkiss;
   int phoenixdown;
};

// read data from input file to corresponding variables
// return 1 if successfully done, otherwise return 0
int readFile(const char* filename, knight& theKnight, int& nEvent, int* arrEvent)
{
	const char* file_name = filename;
	FILE* f = 0;
	char* str = new char[MAX_CHARACTER_EACH_LINE];
	int num;

	f = fopen(file_name, "r");
	if (f == NULL)	//file not found || cannot read
		return 0;

	fgets(str, MAX_CHARACTER_EACH_LINE, f);
	if (feof(f))
		return 0;

	int start = 0;
	int len = strlen(str);
	// read HP
	while (start < len && str[start] == ' ')
		start ++;
	num = 0;
	while (start < len && str[start] <= '9' && str[start] >= '0'){
		num = num * 10 + str[start] - '0';
		start++;
	}
	theKnight.HP = num;
	if (theKnight.HP < 1 || theKnight.HP > 999)
		return 0;

	// read level
	while (start < len && (str[start] > '9' || str[start] < '0'))
		start ++;
	num = 0;
	while (start < len && str[start] <= '9' && str[start] >= '0'){
		num = num * 10 + str[start] - '0';
		start++;
	}
	theKnight.level = num;
	if (theKnight.level < 1 || theKnight.level > 10)
		return 0;

	// read remedy
	while (start < len && (str[start] > '9' || str[start] < '0'))
		start ++;
	num = 0;
	while (start < len && str[start] <= '9' && str[start] >= '0'){
		num = num * 10 + str[start] - '0';
		start++;
	}
	theKnight.remedy = num;
	if (theKnight.remedy < 0 || theKnight.remedy > 99)
		return 0;

	// read maidenkiss
	while (start < len && (str[start] > '9' || str[start] < '0'))
		start ++;
	num = 0;
	while (start < len && str[start] <= '9' && str[start] >= '0'){
		num = num * 10 + str[start] - '0';
		start++;
	}
	theKnight.maidenkiss = num;
	if (theKnight.maidenkiss < 0 || theKnight.maidenkiss > 99)
		return 0;

	// read phoenixdown
	while (start < len && (str[start] > '9' || str[start] < '0'))
		start ++;
	num = 0;
	while (start < len && str[start] <= '9' && str[start] >= '0'){
		num = num * 10 + str[start] - '0';
		start++;
	}
	theKnight.phoenixdown = num;
	if (theKnight.phoenixdown < 0 || theKnight.phoenixdown > 99)
		return 0;

	// read events
	nEvent = 0;
	while (1){
		if (feof(f))
			break;
		fgets(str, MAX_CHARACTER_EACH_LINE, f);
		if (str == NULL)
			break;
		start = 0;
		len = strlen(str);
    // cout << "\'" << str << "\'" << "\t" << len << endl;
		while (start < len){
			while (start < len && (str[start] > '9' || str[start] < '0'))
				start++;
			if (start >= len)
				break;
			arrEvent[nEvent] = 0;
			while (start < len && str[start] <= '9' && str[start] >= '0'){
				arrEvent[nEvent] = arrEvent[nEvent] * 10 + str[start] - '0';
				start++;
			}
			nEvent++;
		}
    delete[] str;
	}
	fclose(f);
	return 1;
}

void display(int* nOut)
{
  if (nOut)
    cout << *nOut;
  else
    cout << "Error!";
}

void caculateResult(int *nOut, int HP, int level, int remedy, int maidenkiss, int phoenixdown, bool isCompleteMission)
{
	if (isCompleteMission)
	{
		*nOut=HP+level+maidenkiss+phoenixdown;
	} else
	{
		*nOut=1;
	}
	
}

bool isPrimeNumber(int HP)
{
	for (int i=2; i<HP;i++)
	{
		if (HP % i==0) return(false);
	}
	return(true);
}

bool isArthur(int HP)
{
	if (HP==999) return(true);
	else return(false);
}

bool isLancelot(int HP)
{
	if (HP==888) return(true);
	else return(false);
}

bool isPaladin(int HP)
{
	if (isPrimeNumber(HP)) return(true);
	else return(false);
}

bool isDragonWarrior(int HP)
{
	if (HP==888) return(false);
	int x,y,z;
	for (x=1; x<=HP-2; x++)
		for(y=1; y<=(HP-x)/2+1; y++)
		{
			z=HP-x-y;
			if (pow(x,2)==pow(y,2)+pow(z,2)) return(true);
		}
	return(false);
}

int typeOfCharacter(int HP)
{
	if (isArthur(HP)) return(ARTHUR);
	if (isLancelot(HP)) return(LANCELOT);
	if (isPaladin(HP)) return(PALADIN);
	if (isDragonWarrior(HP)) return(DRAGON_WARRIOR);
	return(ROUND_TABLE_WARRIOR);
}

int main(int argc, char** argv)
{
    //if (argc < 2) return 1;
    const char* filename = "input.txt";

   struct knight theKnight;
   int nEvent; //number of events
   int* arrEvent = new int[EVENT_SIZE]; // array of events
   int* nOut;                           // final result
   int i;

   bool isCompleteMission=1;
   int typeCharacter=ROUND_TABLE_WARRIOR;

	readFile(filename, theKnight, nEvent, arrEvent);
	//cout << theKnight.HP << ' ' << theKnight.level << ' ' << theKnight.remedy << ' ' << theKnight.maidenkiss << ' ' << theKnight.phoenixdown << endl;

	typeCharacter=typeOfCharacter(theKnight.HP);
	for (i = 0; i < nEvent; i++)
	{
		int theEvent = arrEvent[i];
		cout << theEvent << endl;
		//Add code here
		switch (theEvent)
		{
		case SURRENDER:
			caculateResult(nOut, theKnight.HP, theKnight.level, theKnight.remedy, theKnight.maidenkiss, theKnight.phoenixdown, isCompleteMission);
			display(nOut);
			return(1);
		break;
		
		case MADBEAR:
			//deal with MadBear here
		break;

		case BANDIT:
			//deal with Bandit here
		break;
		}
	}
	caculateResult(nOut, theKnight.HP, theKnight.level, theKnight.remedy, theKnight.maidenkiss, theKnight.phoenixdown, isCompleteMission);
    display(nOut);
	return 0;
}

