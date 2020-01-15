#include <iostream>
#include "MiniFw_Modified.h"
#include "randgen.h"
#include "Robots_Modified.h"

void go (Robot & emre, int & hp);
void smallerTen (Robot & emre, int bag);
void biggerTen (Robot & emre, int bag );
bool checkHP (Robot & emre, int & hp);
void corners(Robot & emre, int & hp);

void RandomWalk(Robot & murat, Robot & huso, Robot & osikey, Robot & rabis) // this function makes robot move randomly
{	
		RandGen rbt;
		int RandSelect = rbt.RandInt(1,4);

		if ( RandSelect == 1 )
		{
		murat.TurnRandom();
		murat.Move();
		murat.Resurrect();
		murat.TurnRandom();
		}
		else if ( RandSelect == 2 )
		{
		huso.TurnRandom();
		huso.Move();
		huso.Resurrect();
		huso.TurnRandom();
		}
		else if ( RandSelect == 3 )
		{
		osikey.TurnRandom();
		osikey.Move();
		osikey.Resurrect();
		osikey.TurnRandom();
		}
		else if ( RandSelect == 4 )
		{
		rabis.TurnRandom();
		rabis.Move();
		rabis.Resurrect();
		rabis.TurnRandom();
		}
}

void go (Robot & emre, int & hp) //this function makes user move by arrow keys
{
	if (emre.GetBagCount() > 30) // this statement activates super mode
	{

		if( IsPressed(keyDownArrow ))
		{
			emre.Teleport(emre.GetXCoordinate() , emre.GetYCoordinate() - 1 , south) ;
			emre.Resurrect();
			emre.PickAllThings();
		}
		else if( IsPressed(keyUpArrow))
		{
			emre.Teleport(emre.GetXCoordinate() , emre.GetYCoordinate() + 1 , north) ;
			emre.Resurrect();
			emre.PickAllThings();
		}
		else if( IsPressed(keyLeftArrow) )
		{
			emre.Teleport(emre.GetXCoordinate() - 1 , emre.GetYCoordinate() , west) ;
			emre.Resurrect();
			emre.PickAllThings();
		}
		else if (IsPressed(keyRightArrow)) 
		{
			emre.Teleport(emre.GetXCoordinate() + 1 , emre.GetYCoordinate() , east) ;
			emre.Resurrect();
			emre.PickAllThings();
		}

	}
	else if (emre.GetBagCount() <= 30) // this statement works when there are below the 30 balls on bag
	{
		if (IsPressed(keyDownArrow))
		{
			emre.TurnFace(south);
			emre.Move();
			if (emre.GetXCoordinate() != 0 && emre.GetYCoordinate() != 0 || emre.GetXCoordinate() != 12 && emre.GetYCoordinate() != 0 )
			{ emre.PickAllThings(); }
		}
		else if (IsPressed(keyUpArrow))
		{
			emre.TurnFace(north);
			emre.Move();
			if (emre.GetXCoordinate() != 0 && emre.GetYCoordinate() != 12 || emre.GetXCoordinate() != 12 && emre.GetYCoordinate() != 12 )
			{ emre.PickAllThings(); }
		}
		else if (IsPressed(keyLeftArrow))
		{
			emre.TurnFace(west);
			emre.Move();
			if (emre.GetXCoordinate() != 0 && emre.GetYCoordinate() != 0 || emre.GetXCoordinate() != 0 && emre.GetYCoordinate() != 12 )
			{ emre.PickAllThings();}
		}
		else if (IsPressed(keyRightArrow))
		{
			emre.TurnFace(east);
			emre.Move();
			if (emre.GetXCoordinate() != 12 && emre.GetYCoordinate() != 0 || emre.GetXCoordinate() != 12 && emre.GetYCoordinate() != 12 )
			{ emre.PickAllThings(); }
		}
	}	checkHP(emre, hp);
}

void corners(Robot & emre, int & hp) //this function let you put the things to the corners
{
	int x  = GetCellCount(0,0), y  = GetCellCount(12,0), z  = GetCellCount(0,12), t  = GetCellCount(12,12);
	int PlayerX =  emre.GetXCoordinate() , PlayerY = emre.GetYCoordinate();
	int bag = emre.GetBagCount();


	if ( x + bag <= 10 && PlayerX == 0 && PlayerY == 0 )
	{
		smallerTen(emre,bag);
	}
	else if ( x + bag > 10 && PlayerX == 0 && PlayerY == 0)
	{ 
		biggerTen(emre,x);
	}
	else if ( y + bag <= 10 && PlayerX == 12 && PlayerY == 0 )
	{ 
		smallerTen(emre,bag); 
	}
	else if ( y + bag > 10 && PlayerX == 12 && PlayerY == 0  )
	{ 
		biggerTen(emre,y);
	}
	else if ( z + bag <= 10 && PlayerX == 0 && PlayerY == 12 )
	{ 
		smallerTen(emre,bag); 
	}
	else if ( z + bag > 10 && PlayerX == 0 && PlayerY == 12 )
	{ 
		biggerTen(emre,z); 
	}
	else if ( t + bag <= 10 && PlayerX == 12 && PlayerY == 12 )
	{ 
		smallerTen(emre,bag); 
	}
	else if ( t + bag > 10 && PlayerX == 12 && PlayerY == 12 )
	{ 
		biggerTen(emre,t); 
	}	
	checkHP(emre, hp);
}
	
void smallerTen (Robot & emre, int bag) //this function checks if bag + corner <=10
{
	for (int i = 0 ; i < bag ; i++)
	{
		emre.PutThing(); 
	}
}

void biggerTen (Robot & emre, int bag )//this function checks if bag + corner > 10
{
	for ( int i = 0 ; i < 10 - bag ; i++)
	{
		emre.PutThing(); 
	}
}

bool checkHP(Robot & emre, int & hp) //this function returns a value if user robot alive
{
	if(emre.isAlive())
	{
		return true;
	}
	else if(!emre.isAlive())
	{
		return false;
	}
}
int controllerHP ( Robot & emre, int & hp ) // this function supposed to update hp for robot but it doesnt please tell me why...
{

	if(hp == 3)
	{
		ShowMessage("You have 2 lives left!");
		emre.Resurrect();
		hp--;
	}
	if(checkHP(emre,hp) == 2)
	{
		ShowMessage("You have 1 lives left!");
		emre.Resurrect();
		hp--;
	}
	if(checkHP(emre,hp) == 1)
	{
		ShowMessage("You have no lives left");
		ShowMessage("You lost the game!");
	} return hp;
}
	
int main () 
{
	Robot emre (6,6); //calling robots

	Robot murat (6,2);
	murat.SetColor(red);

	Robot huso (2,6);
	huso.SetColor(red);

	Robot osikey (6,10);
	osikey.SetColor(red);

	Robot rabis(10,6);
	rabis.SetColor(red);


	RandGen xPos, yPos, thing, nmbrCell; 
	int PutCell = nmbrCell.RandInt(40,169);
	

	for ( int i = 0 ; i <= PutCell ; i++ ) //this statement put balls to the environment between 40 and 169(13x13)
	{
		int a = xPos.RandInt(0,12);
		int b = yPos.RandInt(0,12);
		int c = thing.RandInt(1,4);	
		
		if ( !GetCellCount(a,b) )
		{
			PutThingsOnCell(a,b,c);
		}	
	}

	
	int LeftDown = GetCellCount(0,0), RightDown = GetCellCount(12,0), LeftUp = GetCellCount(0,12), RightUp = GetCellCount(12,12); //number of balls on the corners
	
	if ( LeftDown + RightDown + LeftUp + RightUp != 40  ) // if this statement is true code will let you play the game until you die
	{
	int hp = 3;
	while( hp > 0)
	{
			if(checkHP(emre,hp) && hp > 0)
			{
				RandomWalk(murat,huso,osikey,rabis);
				go(emre,hp);
				corners(emre, hp);
			}
			else if(!checkHP(emre,hp) && hp <= 3) //if the user dies it will call controller function which gives an error
			{
				controllerHP(emre,hp);
			}
				
	}
	}
	else if( LeftDown + RightDown + LeftUp + RightUp == 40 ) // this statement represents the wining conditions
		{
			ShowMessage("Congratulations! You win the game!");
			return 0;
		}
		
	
	return 0;
}

			
		
	
		












