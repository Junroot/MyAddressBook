﻿#include <iostream>
#include <stdlib.h>
#include <conio.h>
#include <Windows.h>
#include "AddressBook.h"
#include "sms.h"
#include "call.h"

#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77
#define ENTER 13
#define ESC 27

using namespace std;

void setcolor(int color, int bgcolor)
{
		color &= 0xf;
		bgcolor &= 0xf;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (bgcolor << 4) | color);
}

int MainPrint()
{
	setcolor(15, 0);
	int key;
	int sel = 1;
	while (1)
	{
		system("cls");
		cout << "■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■" << endl;
		cout << "\tMy number : 01035123546" << endl << endl;
		if (sel == 1) cout << "\t▶1. AddressBook" << endl;
		else cout << "\t1. AddressBook" << endl;
		if (sel == 2) cout << "\t▶2. Call" << endl;
		else cout << "\t2. Call" << endl;
		if (sel == 3) cout << "\t▶3. Message" << endl;
		else cout << "\t3. Message" << endl;
		if (sel == 4) cout << "\t▶4. Exit" << endl;
		else cout << "\t4. Exit" << endl;
		cout << "■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■" << endl;
		key = getch();
		if (key == UP && sel>1)	sel--;
		else if (key == DOWN && sel < 4) sel++;
		else if (key == ENTER) return sel;
	}
}

void AddressBookPrint(AddressBook* book)
{
	int key;
	int sel = 1;
	while (1)
	{
		system("cls");
		cout << "■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■" << endl;
		setcolor(10,0);
		cout << "\t\t\tAddressBook" << endl;
		setcolor(2, 0);
		cout << "\tENTER : Search"<< endl;
		cout << "\tESC : Back" << endl;
		cout << "\t ← : Delete, → : Add" << endl << endl;
		setcolor(15, 0);
		book->Print(sel);
		cout << "■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■" << endl;
		key = getch();
		if (key == UP && sel>1)	sel--;
		else if (key == DOWN && sel < book->Size()) sel++;
		else if (key == LEFT)
		{
			book->DeletePerson(sel);
			if (sel == book->Size()+1) sel--;
		}
		else if (key == RIGHT)
		{
			person per;
			cout << "\tName : ";
			cin >> per.first;
			cout << "\tNumber : ";
			cin >> per.second;
			book->AddPerson(per);
			sel = 1;
		}
		else if (key == ENTER)
		{
			string search;
			cout << "\tSearch : ";
			cin >> search;
			system("cls");
			cout << "■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■" << endl;
			setcolor(10, 0);
			cout << "\t\t\tAddressBook" << endl;
			setcolor(2, 0);
			cout << "\tESC : Back" << endl;
			cout << "\tSearch : ";
			setcolor(15, 0);
			cout << search << endl << endl;
			cout << "■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■" << endl;
			book->SearchByName(search);
			book->SearchByNum(search);
			while (key = getch() != ESC);
		}
		else if (key == ESC) break;
	}
}

void CallPrint(Call* call, AddressBook* book)
{
	int key;
	system("cls");
	cout << "■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■" << endl;
	setcolor(10, 0);
	cout << "\t\t\tCall" << endl;
	setcolor(2, 0);
	cout << "\tESC : Back" << endl << endl;
	setcolor(15, 0);
	call->Print(book);
	cout << "■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■" << endl;
	while (key = getch() != ESC);
}

void SMSPrint(SMS* sms, AddressBook* book)
{
	int key;
	int sel = 1;
	while (1)
	{
		system("cls");
		cout << "■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■" << endl;
		setcolor(10, 0);
		cout << "\t\t\tSMS" << endl;
		setcolor(2, 0);
		cout << "\tENTER : Select" << endl;
		cout << "\tESC : Back" << endl << endl;
		setcolor(15, 0);
		if (sel == 1) cout << "\t▶1. Sent" << endl;
		else cout << "\t1. Sent" << endl;
		if (sel == 2) cout << "\t▶2. Received" << endl;
		else cout << "\t2. Received" << endl;
		cout << "■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■" << endl;
		key = getch();
		if (key == UP && sel > 1)	sel--;
		else if (key == DOWN && sel < 2) sel++;
		else if (key == ENTER)
		{
			if (sel == 1)
			{
				int inp = 1;
				while (1)
				{
					system("cls");
					cout << "■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■" << endl;
					setcolor(10, 0);
					cout << "\t\t\tSMS" << endl;
					setcolor(2, 0);
					cout << "\tESC : Back" << endl << endl;
					setcolor(15, 0);
					sms->print_outboxlists(*book, inp);
					cout << "■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■" << endl;
					sms->print_outsms(*book, inp);
					key = getch();
					if (key == UP && inp > 1)	inp--;
					else if (key == DOWN && inp < sms->outSize()) inp++;
					else if (key == ESC) break;
				}
			}
			else
			{
				int inp = 1;
				while (1)
				{
					system("cls");
					cout << "■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■" << endl;
					setcolor(10, 0);
					cout << "\t\t\tSMS" << endl;
					setcolor(2, 0);
					cout << "\tESC : Back" << endl << endl;
					setcolor(15, 0);
					sms->print_inboxlists(*book, inp);
					cout << "■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■" << endl;
					sms->print_insms(*book, inp);
					key = getch();
					if (key == UP && inp > 1)	inp--;
					else if (key == DOWN && inp < sms->inSize()) inp++;
					else if (key == ESC) break;
				}
			}
		}
		else if (key == ESC) break;
	}
}

int main(void)
{
	int input;
	AddressBook* book = new AddressBook;
	Call* call = new Call;
	SMS* sms = new SMS;
	while (1)
	{
		input = MainPrint();
		if (input == 1)
		{
			AddressBookPrint(book);
		}
		else if (input == 2)
		{
			CallPrint(call,book);
		}
		else if (input == 3)
		{
			SMSPrint(sms,book);
		}
		else if (input == 4) break;
	}
	return 0;
}