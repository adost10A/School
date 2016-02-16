//As the title suggest this is a WIP of Craps.

#include <stdio.h>
#include <stdlib.h>

void bet_path(int *choice)
{
	
	printf("-------------------------------------------\n");
	printf("Pass Line: 1\nDon't pass Line: 2\n");
	scanf("%d",&(*choice));
	printf("-------------------------------------------\n");
}

void introduction()
{
	printf("-------------------------------------------\n");
	printf("Welcome to the game of Craps, please begin by\n");
	printf("entering a seed for the random number generator\n");
	printf("Seed\t");
}

int die_roll()
{
	char choice;
	int die_1,die_2;
	printf("Would you like to roll the dice? Y or N?: ");
	scanf(" %c",&choice);
	if(choice == 'Y' || choice == 'y')
	{
		printf("\n\nRolling the dice!!!!\n");
		die_1 = (rand()%6) + 1;
		die_2 = (rand()%6) + 1;
		printf("Dice 1: \t%d \nDice 2: \t%d\n",die_1,die_2);	
		printf("-------------------------------------------\n");
		return (die_1 + die_2);
	}
	else{
		printf("Dice will not roll\n");
		return 0;
	}
	
}

void print_sum(int sum)
{
	if (sum ==0){
		printf("No Sum available to print\n");
		return;
	}
	printf("The Sum of the dice is %d\n",sum);
}

double bet(double *winnings,double *bankroll)
{
	double bet_value;
	printf("How much would you like to bet? (Min of $5.00 is required\n\n$");
	scanf("%lf",&bet_value);
	if (bet_value > (*bankroll))
	{
		printf("Your bet is too high so we will be betting all of your money\n");
		bet_value = (*bankroll);
		(*bankroll)=0;
	}
	while(bet_value<5)
	{
		printf("Your bet value is below the minimum requirement, please try again\n$");
		scanf("%lf",&bet_value);
	}
	printf("-------------------------------------------\n");
	(*bankroll)-=bet_value;
	return bet_value;
}

void double_question(double *current_bet,double bankroll)
{
	char c;
	printf("Would you like to double/press your bet? Y or N\t");
	scanf(" %c",&c);
	double curr_bankroll = (double)(bankroll-(*current_bet));
	if(c == 'Y' ||c == 'y')
	{
		if((double)((*current_bet)*2)>curr_bankroll)
		{
			(*current_bet) = (double)(bankroll+(*current_bet));
		}
		else
		{
			(*current_bet) = (double)((*current_bet)*2);
		}
	}
	return;
}

void Pass_Line(int sum_die,double *winnings,double *current_bet,double bankroll)
{
	int point;
	(*current_bet) = bet(&(*winnings),&bankroll);
	sum_die = die_roll();
	switch(sum_die)
	{
		case 7:case 11:
			printf("Congrats!! You just won %.2f\n",*current_bet);
			(*winnings) = (double)((*winnings)+(*current_bet));
			break;
		case 2: case 3: case 12:
			printf("Sadly you lost %.2f\n!",*current_bet);
			(*winnings) = (double)((*winnings)-(*current_bet));
			break;
		//case 4:case 5:case 6:case 8:case 9:case 10:
		default:
			double_question(&(*current_bet),bankroll);
			printf("Your current bet is %.2f\n",(*current_bet));
			point = sum_die;
			sum_die = 0;
			printf("Your point is %d\n",point);
			printf("Let us now continue.\n");
			sum_die = die_roll();
			printf("The value of the die roll is %d\n",sum_die);
			while(1)
			{
				if(sum_die==point)
				{
					printf("You have just won %.2f!!!!\n",(*current_bet));
					(*winnings) = (double)((*winnings)+(*current_bet));
					break;
				}
				else if(sum_die == 7)
				{
					printf("You've seven-out, the following will be deducted %.2f\n",(*current_bet));
					(*winnings) = (double)((*winnings)-(*current_bet));
					break;
				}
				else
					printf("Reminder, your point is %d\n",point);
					sum_die = die_roll();
					printf("The value of the die roll is %d\n",sum_die);
			}
	}
}

void No_Pass(int sum_die,double *winnings,double *current_bet,double bankroll)
{
	int point;
	(*current_bet) = bet(&(*winnings),&bankroll);
	sum_die = die_roll();
	switch(sum_die)
	{
		case 2: case 3: case 12:
			printf("Congrats!! You just won %.2f\n",*current_bet);
			(*winnings) = (double)((*winnings)+(*current_bet));
			break;
		case 7:case 11:	
			printf("Sadly you lost %.2f\n!",*current_bet);
			(*winnings) = (double)((*winnings)-(*current_bet));
			break;
		//case 4:case 5:case 6:case 8:case 9:case 10:
		default:
			double_question(&(*current_bet),bankroll);
			printf("Your current bet is %.2f\n",(*current_bet));
			point = sum_die;
			sum_die = 0;
			printf("Your point is %d\n",point);
			printf("Let us now continue.\n");
			sum_die = die_roll();
			printf("The value of the die roll is %d\n",sum_die);
			while(1)
			{
				if(sum_die==point)
				{
					printf("You've seven-out, the following will be deducted %.2f\n",(*current_bet));
					(*winnings) = (double)((*winnings)-(*current_bet));
					break;
				}
				else if(sum_die == 7)
				{
					
					printf("You have just won %.2f!!!!\n",(*current_bet));
					(*winnings) = (double)((*winnings)+(*current_bet));
					break;
				}
				else
					printf("Reminder, your point is %d\n",point);
					sum_die = die_roll();
					printf("The value of the die roll is %d\n",sum_die);
			}
	}
}
void main()
{
	int choice,sum_die,seed;
	char c;
	introduction();
	double bankroll = 100.00,current_bet,winnings=0;
	scanf("%d",&seed);
	srand(seed);
	bet_path(&choice);
	printf("Bets have been set! Let's play some craps!!\n");
	
	while(1){
		if(choice == 1){
			Pass_Line(sum_die,&winnings,&current_bet,bankroll);
			printf("Your current winnings are %.2f\nWould you like to continue? ",winnings);
			scanf(" %c",&c);
			if(c == 'N'||c =='n'){break;}}
		else if(choice == 2)
			No_Pass(sum_die,&winnings,&current_bet,bankroll);
			printf("Your current winnings are %.2f\nWould you like to continue? ",winnings);
			scanf(" %c",&c);
			if(c == 'N'||c =='n'){break;}
			
	}
	bankroll = (double)(bankroll+winnings);
	printf("My bankroll is %.2f",bankroll);
}
