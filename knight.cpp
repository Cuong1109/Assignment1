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
const int DRAGON_SWORD= 23;
const int BOWSER=99;

const int ROUND_TABLE_WARRIOR= 0;
const int ARTHUR= 1;
const int LANCELOT= 2;
const int PALADIN= 3;
const int DRAGON_WARRIOR_NO_SWORD=4;
const int DRAGON_WARRIOR_HAVE_SWORD=5;

const int EVENT_SIZE = 100;
const int MAX_CHARACTER_EACH_LINE = 250;

const int BASE_DAMAGE_MADBEAR=10;
const int BASE_DAMAGE_BANDIT=15;
const int BASE_DAMAGE_LORDLUPIN=45;
const int BASE_DAMAGE_ELF= 65;
const int BASE_DAMAGE_TROLL=85;

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

int caculateResult(int HP, int level, int remedy, int maidenkiss, int phoenixdown, bool isCompleteMission)
{
	if (isCompleteMission)
	{
		return(HP+level+remedy+maidenkiss+phoenixdown);
	} else
	{
		return(-1);
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
	if (isDragonWarrior(HP)) return(DRAGON_WARRIOR_NO_SWORD);
	return(ROUND_TABLE_WARRIOR);
}

void increseNotPass(int &now, int max, int temp)
{
	now+=temp;
	if (now>max) now=max;
}

bool isPerfectSquare(int x) 
{ 
    int s = sqrt(x); 
    return (s*s == x); 
} 

bool isFibonacci(int n) 
{ 
    return isPerfectSquare(5*n*n + 4) || 
           isPerfectSquare(5*n*n - 4); 
} 

int mushFib(int HP, int maxHP)
{
	bool kt=0;
	while (kt==0)
	{
		if (isFibonacci(++HP)) kt=1;
	}
	if (HP>maxHP) HP=maxHP;
	return(HP);
}
void decreaseNotOver(int &now, int min, int temp)
{
	now-=temp;
	if (now<min) now=min;
}

int levelO(int i)
{
	i++;
	int b=i%10;
	int c=i>6?(b>5?b:5):b;
	return(c);
}

int damage(int baseDamage, int levelO)
{
	return(baseDamage*levelO);
}

void usePhoenixDown(int &phoenixdown, bool &isTiny, bool &isFrog,int &HP, int maxHP)
{
	phoenixdown--;
	isTiny=false;
	isFrog=false;
	HP=maxHP;
}

void tinyStage(bool &isTiny, int &tinyCount)
{
	if (isTiny)
	{
		tinyCount--;
	}
}

void frogStage(bool &isFrog, int &frogCount)
{
	if (isFrog)
	{
		frogCount--;
	}
}

void odinStage(bool &isOdin, int &odinCount, bool &isOdinActive)
{
	if (isOdin)
	{
		if (odinCount==0)
		isOdin=0;
		odinCount--;	
	}
}

void lightwingStage(bool &isLightwing, int &lightwingtCount)
{
	if (isLightwing)
	{
		if (lightwingtCount==0)
		isLightwing=0;
		lightwingtCount--;
	}
}

int main(int argc, char** argv)
{
    if (argc < 2) return 1;
    const char* filename = argv[1];;
	
   struct knight theKnight;
   int nEvent; //number of events
   int* arrEvent = new int[EVENT_SIZE]; // array of events
   int* nOut;                           // final result
   int i;

	readFile(filename, theKnight, nEvent, arrEvent);
	//cout << theKnight.HP << ' ' << theKnight.level << ' ' << theKnight.remedy << ' ' << theKnight.maidenkiss << ' ' << theKnight.phoenixdown << endl;
	bool isLancelot=0;
	bool isCompleteMission=1;
	int characterType=typeOfCharacter(theKnight.HP);
	if (characterType==LANCELOT) isLancelot=1;

	int backLevel,dem;
	int HP=theKnight.HP;
	int level=theKnight.level;
	int remedy=theKnight.remedy;
	int maidenkiss=theKnight.maidenkiss;
	int phoenixdown=theKnight.phoenixdown;

	int frogCount=0;
	int tinyCount=0;
	int odinCount=0;
	int lighwingtCount=0;
	int nEventNew=nEvent;

	bool isExcalibur=0;
	bool isExcalipoor=0;
	bool isMythril=0;
	bool isOdin=0;
	bool isOdinActive=0;
	bool isFrog=0;
	bool isTiny=0;
	bool isLightwing=0;
	
	for (i = 0; i < nEvent; i++)
	{
		if (i==nEventNew) break;
		int theEvent = arrEvent[i];
		//cout << theEvent << endl;
		if (isLancelot==1 && level%2==1) characterType=ARTHUR;
		if (isLancelot==1 && level%2==0) characterType=LANCELOT;
		tinyStage(isTiny, tinyCount);
		frogStage(isFrog, frogCount);
		odinStage(isOdin, odinCount, isOdinActive);
		lightwingStage(isLightwing, lighwingtCount);

		switch (theEvent)
		{
		case SURRENDER:
			goto FINISH;
		break;

		case MADBEAR:
			if (isLightwing) break;
			if (isExcalibur || isOdin || characterType==ARTHUR || characterType==PALADIN || characterType==DRAGON_WARRIOR_HAVE_SWORD) 
			{
				increseNotPass(level,10,1);
				break;
			}
			
			if (level>levelO(i) && !isExcalipoor)
			{
				increseNotPass(level,10,1);
				break;
			}

			if (level<levelO(i) || isExcalipoor)
			{
				if(isMythril==0) HP=HP-damage(BASE_DAMAGE_MADBEAR, levelO(i));
				if (HP<=0)
				{
					if (phoenixdown<=0)
					{
						isCompleteMission=0;
						goto FINISH;
					} else
					usePhoenixDown(phoenixdown, isTiny, isFrog, HP, theKnight.HP);
				}
			}
			if (tinyCount==0 && isTiny)
			{
				isTiny=false;
				HP*=5;
				if (HP>theKnight.HP) HP=theKnight.HP;
			}
			if (frogCount==0 && isFrog)
			{
				isFrog=false;
				level=backLevel;
			}
		break;

		case BANDIT:
			if (isLightwing) break;
			if (isExcalibur || isOdin || characterType==ARTHUR || characterType==PALADIN || characterType==DRAGON_WARRIOR_HAVE_SWORD)
			{
				increseNotPass(level,10,1);
				break;
			}

			if (level>levelO(i) && !isExcalipoor)
			{
				increseNotPass(level,10,1);
				break;
			}

			if (level<levelO(i) || isExcalipoor)
			{
				if(isMythril==0) HP=HP-damage(BASE_DAMAGE_BANDIT, levelO(i));
				if (HP<=0)
				{
					if (phoenixdown<=0)
					{
						isCompleteMission=0;
						goto FINISH;
					} else
					usePhoenixDown(phoenixdown, isTiny, isFrog, HP, theKnight.HP);
				}
			}
			if (tinyCount==0 && isTiny)
			{
				isTiny=false;
				HP*=5;
				if (HP>theKnight.HP) HP=theKnight.HP;
			}
			if (frogCount==0 && isFrog)
			{
				isFrog=false;
				level=backLevel;
			}
		break;

		case LORDLUPIN:
			if (isLightwing) break;
			if (isExcalibur || isOdin || characterType==ARTHUR || characterType==PALADIN || characterType==DRAGON_WARRIOR_HAVE_SWORD)
			{
				increseNotPass(level,10,1);
				break;
			}

			if (level>levelO(i) && !isExcalipoor)
			{
				increseNotPass(level,10,1);
				break;
			}

				if (level<levelO(i) || isExcalipoor)
			{
				if(isMythril==0) HP=HP-damage(BASE_DAMAGE_LORDLUPIN, levelO(i));
				if (HP<=0)
				{
					if (phoenixdown<=0)
					{
						isCompleteMission=0;
						goto FINISH;
					} else
					usePhoenixDown(phoenixdown, isTiny, isFrog, HP, theKnight.HP);
				}
			}
			if (tinyCount==0 && isTiny)
			{
				isTiny=false;
				HP*=5;
				if (HP>theKnight.HP) HP=theKnight.HP;
			}
			if (frogCount==0 && isFrog)
			{
				isFrog=false;
				level=backLevel;
			}
		break;

		case ELF:
			if (isLightwing) break;
			if (isExcalibur || isOdin || characterType==ARTHUR || characterType==PALADIN || characterType==DRAGON_WARRIOR_HAVE_SWORD)
			{
				increseNotPass(level,10,1);
				break;
			}

			if (level>levelO(i) && !isExcalipoor)
			{
				increseNotPass(level,10,1);
				break;
			}

			if (level<levelO(i) || isExcalipoor)
			{
				if(isMythril==0) HP=HP-damage(BASE_DAMAGE_ELF, levelO(i));
				if (HP<=0)
				{
					if (phoenixdown<=0)
					{
						isCompleteMission=0;
						goto FINISH;
					} else
					usePhoenixDown(phoenixdown, isTiny, isFrog, HP, theKnight.HP);
				}
			}
			if (tinyCount==0 && isTiny)
			{
				isTiny=false;
				HP*=5;
				if (HP>theKnight.HP) HP=theKnight.HP;
			}
			if (frogCount==0 && isFrog)
			{
				isFrog=false;
				level=backLevel;
			}
		break;

		case TROLL:
			if (isLightwing) break;
			if (isExcalibur || isOdin || characterType==ARTHUR || characterType==PALADIN || characterType==DRAGON_WARRIOR_HAVE_SWORD)
			{
				increseNotPass(level,10,1);
				break;
			}

			if (level>levelO(i) && !isExcalipoor)
			{
				increseNotPass(level,10,1);
				break;
			}

				if (level<levelO(i) || isExcalipoor)
			{
				if(isMythril==0) HP=HP-damage(BASE_DAMAGE_TROLL, levelO(i));
				if (HP<=0)
				{
					if (phoenixdown<=0)
					{
						isCompleteMission=0;
						goto FINISH;
					} else
					usePhoenixDown(phoenixdown, isTiny, isFrog, HP, theKnight.HP);
				}
			}
			if (tinyCount==0 && isTiny)
			{
				isTiny=false;
				HP*=5;
				if (HP>theKnight.HP) HP=theKnight.HP;
			}
			if (frogCount==0 && isFrog)
			{
				isFrog=false;
				level=backLevel;
			}
		break;

		case SHAMAN:
			if (isLightwing) break;
			if (isOdin || characterType==ARTHUR || characterType==PALADIN || characterType==DRAGON_WARRIOR_HAVE_SWORD)
			{
				increseNotPass(level,10,2);
				break;
			}

			if (isTiny || isFrog) break;

			if (level>levelO(i) && !isExcalipoor)
			{
				increseNotPass(level,10,2);
				break;
			}

			if (level<levelO(i) || isExcalipoor)
			{
				if (HP<5) HP=1;
				else HP=HP/5;
				if (remedy>=1) 
				{
					remedy--;
					HP*=5;
				}
				else
				{
					isTiny=true;
					tinyCount=3;
				}
			}
		break;

		case VAJSH:
			if (isLightwing) break;
			if (isOdin || characterType==ARTHUR || characterType==PALADIN || characterType==DRAGON_WARRIOR_HAVE_SWORD)
			{
				increseNotPass(level,10,2);
				break;
			}

			if (isTiny || isFrog) break;

			if (level>levelO(i) && !isExcalipoor)
			{
				increseNotPass(level,10,2);
				break;
			}

			if (level<levelO(i) || isExcalipoor)
			{
				backLevel=level;
				level=1;
				if (maidenkiss>=1) 
				{
					maidenkiss--;
					level=backLevel;
				}
				else
				{
					isFrog=true;
					frogCount=3;
				}
			}
		break;

		case EXCALIBUR:
			if (isLightwing) break;
			if (characterType==DRAGON_WARRIOR_HAVE_SWORD) break;
			isExcalibur=true;
		break;

		case MYTHRIL:
			if (isLightwing) break;
			isMythril=true;
		break;

		case EXCALIPOOR:
			if (isLightwing) break;
			if (characterType==PALADIN) break;
			if (characterType==DRAGON_WARRIOR_HAVE_SWORD) break;
			if (characterType==DRAGON_WARRIOR_NO_SWORD) break;
			if (characterType==ARTHUR) break;
			if (level<5) isExcalipoor=true;
			isExcalibur=false;
		break;
		

		case MUSHMARIO:
			if (isLightwing) break;
			increseNotPass(HP,theKnight.HP,50);
		break;

		case MUSHFIB:
			if (isLightwing) break;
			HP=mushFib(HP, theKnight.HP);
		break;

		case MUSHGHOST:
			if (isLightwing) break;
			if (characterType==PALADIN) break;
			if (characterType==DRAGON_WARRIOR_HAVE_SWORD) break;
			decreaseNotOver(HP,1,50);
		break;

		case MUSHKNIGHT:
			if (isLightwing) break;
			increseNotPass(theKnight.HP,999,50);
			HP=theKnight.HP;
		break;

		case REMEDY:
			if (isLightwing) break;
			increseNotPass(remedy,99,1);
			if (isTiny)
			{
				remedy--;
				HP=HP*5;
				isTiny=false;
			}
		break;

		case MAIDENKISS:
			if (isLightwing) break;
			increseNotPass(maidenkiss,99,1);
			if (isFrog)
			{
				maidenkiss--;
				level=backLevel;
				isFrog=false;
			}
		break;

		case PHOENIXDOWN:
			if (isLightwing) break;
			increseNotPass(phoenixdown,99,1);
		break;

		case MERLIN:
			if (isLightwing) break;
			if (isTiny)
			{
				isTiny=false;
				HP*=5;
			}
			if(isFrog)
			{
				isFrog=false;
				level=backLevel;
			}
			increseNotPass(level,10,1);
			HP=theKnight.HP;
		break;

		case ABYSS:
			if (isLightwing) break;
			if (characterType==DRAGON_WARRIOR_HAVE_SWORD) break;
			if (level<7) 
			{
				isCompleteMission=0;
				goto FINISH;
			}
		break;

		case GUINEVERSE:
			if (isLightwing)
			{
				goto FINISH;
				break;
			}
			dem=0;
			nEventNew=i*2+1;
			while (dem!=i)
			{
				dem++;
				arrEvent[i+dem]=arrEvent[i-dem];
			}
		break;

		case LIGHTWING:
			if (isLightwing) break;
			isLightwing=1;
			lighwingtCount=3;
		break;

		case ODIN:
			if (isLightwing) break;
			if (isOdinActive==0) 
			{
				isOdinActive=1;
				isOdin=1;
				odinCount=3;
			}
		break;

		case DRAGON_SWORD:
			if (isLightwing) break;
			if(characterType==DRAGON_WARRIOR_NO_SWORD)
			characterType=DRAGON_WARRIOR_HAVE_SWORD;
		break;

		case BOWSER:
			if (isLightwing) break;
			if (isOdin)
			{
				level=10;
				break;
			}
			if (characterType==ARTHUR || characterType==LANCELOT || characterType==DRAGON_WARRIOR_HAVE_SWORD) 
			{
				level=10;
				break;
			} 
			if (characterType==PALADIN && level>=8)
			{
				level=10;
				break;
			}
			if(level==10)
			{
				break;
			}
			isCompleteMission=0;
			goto FINISH;
		break;
		}
	}

	FINISH: 
	int result=caculateResult(HP,level,remedy,maidenkiss,phoenixdown,isCompleteMission);
	nOut=&result;
    display(nOut);
	return 0;
}

