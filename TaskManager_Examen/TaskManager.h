//паттерны Observer, FactoryMethod
#pragma once
#include<iostream>
#include<string>
#include<vector>
#include<iterator>
#include<conio.h>
#include<map>
#include<fstream>
#include <algorithm>
#include"Color.h"
using namespace std;

string getPassword()
{
	char buf1[100] = "";
	char buf2[100] = "";
	int i = 0;
	unsigned char c;
	do
	{
		cout << '\r' << buf2;
		c = _getch();
		buf1[i] = c;
		buf2[i++] = '*';
		buf1[i] = '\0';
		buf2[i] = '\0';
	} while (c != '\r');
	cout << endl;
	return buf1;
}

class Date
{
	int dd=1;
	int mm=1;
	int yyyy=2020;
public:
	Date() {}
	Date(int d, int m, int y)
	{
		if ((d > 0 && d <= 31 && (m == 1 || m == 3 || m == 5 || m == 7 || m == 8 || m == 10 || m == 12)) ||
			(d > 0 && d <= 30 && (m == 4 || m == 6 || m == 9 || m == 11)) ||
			(d > 0 && d <= 29 && m == 2 && y % 4 == 0) || (d > 0 && d <= 2 && m == 2 && y % 4 != 0))
		{
			dd = d;
			mm = m;
			yyyy = y;
		}
		else
		{
			dd = 1;
			mm = 1;
			yyyy = 2021;
		}
	};
	Date(const Date& data)
	{
		dd = data.dd;
		mm = data.mm;
		yyyy = data.yyyy;
	}
	Date operator=(const Date& data)
	{
		dd = data.dd;
		mm = data.mm;
		yyyy = data.yyyy;
		return *this;
	}
	bool operator>(const Date& data)
	{
		return (yyyy > data.yyyy) || (yyyy == data.yyyy && mm > data.mm) ||
			(yyyy == data.yyyy && mm == data.mm && dd > data.dd);
	}
	bool operator==(const Date& data)
	{
		return yyyy == data.yyyy && mm == data.mm && dd == data.dd;
	}
	bool operator==(const Date* data)
	{
		return (yyyy == data->yyyy && mm == data->mm && dd == data->dd);
	}
	void setDate(int d, int m, int y) { dd = d; mm = m; yyyy = y; }
	friend ostream& operator<<(ostream& out, Date& date);
	friend ostream& operator<<(ostream& out, Date* date);
	friend istream& operator>>(istream& in, Date& date);
	friend istream& operator>>(istream& in, Date* date);
	Date operator+=(int d)
	{
		dd += d;
		if (dd > 31 && (mm == 1 || mm == 3 || mm == 5 || mm == 7 || mm == 8 || mm == 10))
		{
			dd = dd % 31;
			mm++;
		}
		else if (dd > 31 && mm == 12)
		{
			dd = dd % 31;
			mm = 1;
			yyyy++;
		}
		else if (dd > 30 && (mm == 4 || mm == 6 || mm == 9 || mm == 11))
		{
			dd = dd % 30;
			mm++;
		}
		else if (dd > 29 && mm == 2 && yyyy % 4 == 0)
		{
			dd = dd % 29;
			mm == 3;
		}
		else if (dd > 28 && mm == 2 && yyyy % 4 != 0)
		{
			dd = dd % 28;
			mm == 3;
		}
	}
	int getDD() { return dd; }
	int getMM() { return mm; }
	int getYY() { return yyyy; }
};

ostream& operator<<(ostream& out, Date& date)
{
	if (date.dd < 10) 	out << "0";
	out << date.dd << ".";
	if (date.mm < 10) 	out << "0";
	out << date.mm << "." << date.yyyy;
	return out;
}

ostream& operator<<(ostream& out, Date* date)
{
	if (date->dd < 10) 	out << "0";
	out << date->dd << ".";
	if (date->mm < 10) 	out << "0";
	out<< date->mm << "." << date->yyyy;
	return out;
}

inline istream& operator>>(istream& in, Date& date)
{
	int d, m, y;
	do
	{		
		do {
			cout << "Введите день: ";
			cin >> d;
		} while (d < 0 || d > 31);
		do {
			cout << "месяц: ";
			cin >> m;
		} while (m < 0 || m > 12);
		do {
			cout << "год: ";
			cin >> y;
		} while (y < 2020);
		if (!((d > 0 && d <= 31 && (m == 1 || m == 3 || m == 5 || m == 7 || m == 8 || m == 10 || m == 12)) ||
			(d > 0 && d <= 30 && (m == 4 || m == 6 || m == 9 || m == 11)) ||
			(d > 0 && d <= 29 && m == 2 && y % 4 == 0) || (d > 0 && d <= 2 && m == 2 && y % 4 != 0)))
			cout << "Неверная дата" << endl;
	} while (!((d > 0 && d <= 31 && (m == 1 || m == 3 || m == 5 || m == 7 || m == 8 || m == 10 || m == 12)) ||
		(d > 0 && d <= 30 && (m == 4 || m == 6 || m == 9 || m == 11)) ||
		(d > 0 && d <= 29 && m == 2 && y % 4 == 0) || (d > 0 && d <= 2 && m == 2 && y % 4 != 0)));
	date.dd = d;
	date.mm = m;
	date.yyyy = y;
	return in;
}

inline istream& operator>>(istream& in, Date* date)
{
	int d, m, y;
	do
	{
		do {
			cout << "Введите день: ";
			cin >> d;
		} while (d < 0 || d > 31);
		do {
			cout << "месяц: ";
			cin >> m;
		} while (m < 0 || m > 12);
		do {
			cout << "год: ";
			cin >> y;
		} while (y < 2020);
		if (!((d > 0 && d <= 31 && (m == 1 || m == 3 || m == 5 || m == 7 || m == 8 || m == 10 || m == 12)) ||
			(d > 0 && d <= 30 && (m == 4 || m == 6 || m == 9 || m == 11)) ||
			(d > 0 && d <= 29 && m == 2 && y % 4 == 0) || (d > 0 && d <= 2 && m == 2 && y % 4 != 0)))
			cout << "Неверная дата" << endl;
	} while (!((d > 0 && d <= 31 && (m == 1 || m == 3 || m == 5 || m == 7 || m == 8 || m == 10 || m == 12)) ||
		(d > 0 && d <= 30 && (m == 4 || m == 6 || m == 9 || m == 11)) ||
		(d > 0 && d <= 29 && m == 2 && y % 4 == 0) || (d > 0 && d <= 2 && m == 2 && y % 4 != 0)));
	date->dd = d;
	date->mm = m;
	date->yyyy = y;
	return in;
}


class User;
class Task
{
protected:
	string name;
	Date deadline;
	int prior;
	string teg;
public:
	Task() {}
	Task(string n, Date dl, int pr, string tg) : name(n), deadline(dl), prior(pr), teg(tg) {}
	virtual void notify(User* us, ostream& out) = 0;
	virtual void print(ostream& out) = 0;
	virtual void save(ostream& out) = 0;
	Date getDate() { return deadline; }	
	string getTeg() { return teg; }
	string getName() { return name; }
	int getPrior() { return prior; }
	void setDate(Date d) { deadline = d; }
	void setName(string n) { name = n; }
	void setTag(string t) { teg = t; }
	void setPrior(int p) { prior = p; }	
};

class UsualTask : public Task
{
public:
	UsualTask()
	{
		prior = 0;
	}  
	UsualTask(string n, Date dl, int pr, string tg) : Task(n, dl, pr, tg) {}
	friend istream& operator>>(istream& in, UsualTask* task);
	void notify(User* us, ostream& out) override;	
	Date getDate() { return deadline; }
	void print(ostream& out) override
	{
		out <<setw(35)<< name << setw(13) << deadline << setw(8) << prior <<  setw(30) << teg << endl;
	}
	void save(ostream& out) override
	{
		out << name << endl;
		out << deadline.getDD() << endl;
		out << deadline.getMM() << endl;
		out << deadline.getYY() << endl;
		out << prior << endl;
		out << teg << endl;
	}
};

istream& operator>>(istream& in, UsualTask* task)
{
	system("cls");
	cout << "  Новая задача" << endl;
	cout << "Название: ";
	in.ignore();
	getline(in, task->name);
	int d, m, y, p;
	do {
		cout << "Дата выполнения: день - ";
		in >> d;
	} while (d < 0 || d > 31);
	do {
		cout << "месяц - ";
		in >> m;
	} while (m < 0 || m > 12);
	do {
		cout << "год - ";
		in >> y;
	} while (y < 2020);
	task->deadline.setDate(d, m, y);
	do {
		cout << "Приоритет: 1 - обычный, 2 - высокий: ";
		in >> p;
	} while (p != 1 && p != 2);
	if (p == 1)
		task->prior = 0;
	else task->prior = 1;
	in.ignore();
	cout << "Тег: ";
	getline(in, task->teg);
	return in;
}

class User
{
protected:
	string name;
	vector<Task*> tasks;
	string status;
public:
	 ~User() 
	 {
		 if (tasks.size())
		 {
			 for (size_t i = 0; i < tasks.size(); i++)
			 {
				 delete(tasks[i]);
			 }
			 tasks.clear();
		 }
	}
	User() {};
	User(string n): name(n){}
	void addTask(Task* task)
	{
		tasks.push_back(task);
	}
	virtual void delTask(int numberTask) = 0;
	void editTask(int numberTask)
	{		
		cout << "название задачи: " << tasks[numberTask - 1]->getName() << endl;
		cout << "Изменить? 1 - да  2 - нет: ";
		int vibor;
		cin >> vibor;
		if (vibor == 1)
		{
			cout << "Введите новое название: ";
			string name;
			cin.ignore();
			getline(cin, name);
			tasks[numberTask - 1]->setName(name);
		}
		cout << "срок выполнения: ";
		Date d = tasks[numberTask - 1]->getDate();
		cout << d << endl;
		cout << "Изменить? 1 - да  2 - нет: ";		
		cin >> vibor;
		if (vibor == 1)
		{
			cout << "Введите новую дату: ";
			cin >> d;
			tasks[numberTask - 1]->setDate(d);
		}
		cout << "Приоритет: " << tasks[numberTask - 1]->getPrior() << endl;
		cout << "Изменить? 1 - да  2 - нет: ";		
		cin >> vibor;
		if (vibor == 1)
		{
			int pr;
			if (tasks[numberTask - 1]->getPrior() == 0)
				pr = 1;
			else pr = 0;
			tasks[numberTask - 1]->setPrior(pr);
		}
		cout << "теги: " << tasks[numberTask - 1]->getTeg() << endl;
		cout << "1 - изменить  2 - добавить тег  3 - оставить без изменений: ";		
		cin >> vibor;
		if (vibor == 1)
		{
			cout << "Введите новый тег: ";
			string teg;
			cin.ignore();
			getline(cin, teg);
			tasks[numberTask - 1]->setTag(teg);
		}
		else if (vibor == 2)
		{
			cout << "Введите дополнительный тег: ";
			string teg;
			cin.ignore();
			getline(cin, teg);
			teg = tasks[numberTask - 1]->getTeg() + " " + teg;
			tasks[numberTask - 1]->setTag(teg);
		}
	}
	virtual void edit(int numberTask) = 0;
	void findTask()
	{
		system("cls");
		cout << "                        Поиск  запланированных задач для " << name << endl;
		cout << "----------------------------------------------------------------------------------------------------" << endl;
		cout << "1 - по дате" << endl;
		cout << "2 - по тегам" << endl;
		cout << "3 - по приоритету" << endl;
		cout << "0 - выход в предыдущее меню" << endl;
		int vibor;
		cin >> vibor;
		do {
			if (vibor != 1 && vibor != 2 && vibor != 3 && vibor != 0)
			{
				cout << "ошибка, повторите ввод: ";
				cin >> vibor;
			}
		} while (vibor != 1 && vibor != 2 && vibor != 3 && vibor != 0);
		switch (vibor)
		{
		case 1: findDate(); break;
		case 2: findTag(); break;
		case 3: findPrior(); break;
		case 0: return; break;		
		}
	}
	void findDate()
	{
		cout << "Введите дату: ";
		Date* date = new Date();
		cin >> date;
		int kol = 0;
		for (auto& x:tasks)
			if (x->getDate() == date)
			{
				x->print(cout);
				kol++;
			}
		if (kol == 0)
			cout << "Нет запланированных задач на дату" << date << endl;
		system("pause");
	}
	void findTag()
	{
		cout << "Введите тег для поиска: ";
		string tfind, teg;
		cin >> tfind;
		int kol=0;
		for (auto& x : tasks)
		{
			teg = x->getTeg();
			transform(teg.begin(), teg.end(), teg.begin(), ::tolower);
			transform(tfind.begin(), tfind.end(), tfind.begin(), ::tolower);
			if (teg.find(tfind) != -1)
			{
				x->print(cout);
				kol++;
			}
		}
		if (kol == 0)
			cout << "Нет запланированных задач с данным тегом" << endl;
		system("pause");
	}
	void findPrior()
	{
		cout << "Выберите приоритет для поиска: 1 - обычный, 2 - высокий: ";
		int vibor;
		cin >> vibor;
		do
		{
			if (vibor != 1 && vibor != 2)
			{
				cout << "ошибка, повторите ввод: ";
				cin >> vibor;
			}
		} while (vibor != 1 && vibor != 2);
		int kol=0;
		for (auto& x : tasks)
		{				
		  if (x->getPrior() == vibor-1)
		  {
				x->print(cout);
				kol++;
		  }
		}
		if (kol == 0)
				cout << "Нет запланированных задач с данным приоритетом" << endl;
		system("pause");	
	}
	virtual void print(ostream& out) = 0;
	void saveTask(ostream& out)
	{
		for (auto& i : tasks)
			i->save(out);
	}
	void save()
	{
		cout << "Введите имя файла: ";
		string namef;
		cin >> namef;
		if (namef.find(".txt") == -1)
			namef += ".txt";
		ofstream fout(namef);
		print(fout);
		fout.close();
		cout << "Данные сохранены в файл " << namef << endl;
		system("pause");
	}
	virtual void reminder(Date* datenow, ostream& out) = 0;
	virtual string getName() { return name; }		
	virtual const string getStatus() { return status; }	
	int getKolTask() { return tasks.size(); }	
};

class AdultUser : public User //взрослый пользователь
{
	string password;
	
public:
	AdultUser() { status = "AdultUser"; }

	AdultUser(string n)  {name = n; status = "AdultUser";}

	AdultUser(string n, string p) { name = n; password = p; status = "AdultUser";	}

	AdultUser(const AdultUser& us)
	{
		this->name = us.name;
		this->tasks = us.tasks;			
		this->password = us.password;
	}

	AdultUser operator=(const AdultUser& us)
	{
		this->name = us.name;
		this->tasks = us.tasks;
		Date* d = new Date;		
		this->password = us.password;
		return *this;
	}	
	
	void setPassword(string pas)
	{
		password = pas;
	}	
	
	void delTask(int numberTask) override
	{
		auto del = tasks.begin();
		advance(del, numberTask - 1);
		tasks.erase(del);
		cout << "Задача удалена!" << endl;
		system("pause");
	}
	
	string getPassword() { return password; }	

	void edit(int numberTask) override
	{
		editTask(numberTask);
	}	
		
	void print(ostream& out) override
	{
		if (tasks.size() == 0)
			out << "нет запланированных задач" << endl;
		else
		{
			out << "----------------------------------------------------------------------------------------------------" << endl;
			out << "                          Список запланированных задач для " << name << endl;
			out << "----------------------------------------------------------------------------------------------------" << endl;
			out << " № |               задача                | срок выполнения | приоритет |            тег        " << endl;
			out << "----------------------------------------------------------------------------------------------------" << endl;

			int i = 1;
			for (auto& x : tasks)
			{
				out << i++ << ". ";
				x->print(out);
			}
		}
	}
	void reminder(Date* datenow, ostream& out) override
	{
		for (auto& x : tasks)
			if (x->getPrior() == 1)
				x->notify(this,out);
		for (auto& x : tasks)
			if (x->getDate() == datenow && x->getPrior() != 1)
				x->notify(this,out);
	}	
};

class ChildUser : public User //ребенок
{		
	AdultUser* parent;
	
public:
	ChildUser() { status = "ChildUser"; }
	ChildUser(string n)  {name = n; status = "ChildUser";	}
	ChildUser(const ChildUser& us)
	{
		this->name = us.name;
		this->parent = new AdultUser(us.parent->getName(), us.parent->getPassword());
		vector<Task*> t;
		for (auto& x : us.tasks)
		{
			Task* task = new UsualTask;
			task = x;
			t.push_back(task);
		}
		this->tasks = t;
	}	
	string getParentName() { return parent->getName(); }
	string getParentPassword() { return parent->getPassword(); }	
	void delTask(int numberTask) override
	{					
		cout << "Необходимо подтверждение родителей: логин родителя: ";
		string namePar;
		cin >> namePar;
		if (namePar == getParentName())
		{
			cout << "пароль родителя: " << endl;
			string pas = getPassword();
			hash<string> encrypt;
			pas = to_string(encrypt(pas));
			if (pas == parent->getPassword())
			{
				auto del = tasks.begin();
				advance(del, numberTask - 1);
				tasks.erase(del);
				cout << "Задача удалена!" << endl;
			}
			else cout << "Неверный пароль" << endl;
		}
		else cout << "Неверное имя" << endl;
		system("pause");
	}	
	void edit(int numberTask) override
	{
		cout << "Необходимо подтверждение родителей: логин родителя: ";
		string namePar;
		cin >> namePar;
		if (namePar == getParentName())
		{
			cout << "пароль родителя: "<<endl;
			string pas = getPassword();
			hash<string> encrypt;
			pas = to_string(encrypt(pas));
			if (pas == parent->getPassword())
			{
				editTask(numberTask);
			}
			else cout << "Неверный пароль" << endl;
		}
		else cout << "Неверное имя" << endl;
		system("pause");
	}	
	void setParent(AdultUser* p) 
	{				
		parent = p;
	}
	void print(ostream& out) override
	{
		if (tasks.size() == 0)
			out << "нет запланированных задач" << endl;
		else
		{
			out << "----------------------------------------------------------------------------------------------------" << endl;
			out << "Список запланированных задач для ребенка " << name << " родители: " << parent->getName() << endl;
			out << "----------------------------------------------------------------------------------------------------" << endl;
			out << " № |                 задача              | срок выполнения | приоритет |            тег        " << endl;
			out << "----------------------------------------------------------------------------------------------------" << endl;

			int i = 1;
			for (auto& x : tasks)
			{
				out << i++ << ". ";
				x->print(out);
			}
		}
	}
	void reminder(Date* datenow, ostream& out) override
	{
		for (auto& x : tasks)
			if (x->getPrior() == 1)
			{
				x->notify(this,out);
				x->notify(this->parent,out);
			}
		for (auto& x : tasks)
			if (x->getDate() == datenow && x->getPrior() != 1)
			{
				x->notify(this,out);
				x->notify(this->parent,out);
			}

	}	
};  

void UsualTask::notify(User* us, ostream& out)
{
	SetColor(10, 0);
	out << "Напоминание для: " << us->getName() << " задача " << name << " должна быть выполнена " << deadline <<"    Приоритет - " << prior <<  endl;
	out << "----------------------------------------------------------------------------------------------------" << endl;
	SetColor(15, 0);
}

class Creator
{
public:
	virtual ~Creator() {}
	virtual User* createUser(string n) = 0;
	User* create(string n)
	{
		User* user = this->createUser(n);
		return user;
	}
};

class AdultCreator : public Creator
{
public:
	User* createUser(string n) override
	{
		return new AdultUser(n);
	}
};

class ChildCreator : public Creator
{
public:
	User* createUser(string n) override
	{
		return new ChildUser(n);
	}
};
class TaskManager
{
	map<string, AdultUser*> adults;
	map<string, ChildUser*> childs;
	Date* datenow;
public:
	TaskManager() { datenow = new Date(1, 1, 2020); }
	void addUser()
	{
		system("cls");
		cout << "----------------------------------------------------" << endl;
		cout << "Добавление нового пользователя " << endl;
		cout << "----------------------------------------------------" << endl;
		int k;
		do {
			cout << "Определите категорию пользователя  1 - взрослый, 2 - ребенок:    ";
			cin >> k;
		} while (k != 1 && k != 2);
		if (k == 1)
		{
			string n, p;
			cout << "Имя (логин): ";
			cin >> n;
			do {
				if (adults.count(n) || childs.count(n))
				{
					cout << "Пользователь с таким именем существует, придумайте другое имя:   ";
					cin >> n;
				}
			} while (adults.count(n) || childs.count(n));
			cout << "Пароль: " << endl;
			p = getPassword();			
			hash<string>encrypt;
			p = to_string(encrypt(p));
			AdultUser* us = new AdultUser(n, p);			
			adults.insert(make_pair(n, us));
			cout << "Пользователь " << n << " успешно добавлен!" << endl;;
		}
		else
		{
			string n, namePar, p;
			cout << "Имя (логин): ";
			cin >> n;
			do {
				if (adults.count(n) || childs.count(n))
				{
					cout << "Пользователь с таким именем существует, придумайте другое имя:  ";
					cin >> n;
				}
			} while (adults.count(n) || childs.count(n));
			cout << "Необходимо подтверждение родителей, введите имя родителя:   ";
			cin >> namePar;
			if (adults.count(namePar))
			{				
				cout << "Пароль: "<<endl;
				p = getPassword();
				hash<string>encrypt;
				p = to_string(encrypt(p));
				if (adults[namePar]->getPassword() == p)
				{
					ChildUser* us = new ChildUser(n);
					AdultUser* parent = new AdultUser(namePar, adults[namePar]->getPassword());					
					us->setParent(parent);
					childs.insert(make_pair(n, us));
					cout << "Пользователь " << n << " успешно добавлен!" << endl;;
				}
				else cout << "Неверный пароль" << endl;
			}
			else cout << "Пользователя с таким именем нет" << endl;
		}
		system("pause");
	}
	void delUser()
	{

	}
	void shapka()
	{
		system("cls");
		cout << "----------------------------------------------------------------------------------------------------" << endl;
		cout << "                  Планировщик задач TaskManager" ;
		SetColor(10, 0);
		cout<<setw(35)<<"Сегодня: "<<datenow<<endl;
		SetColor(15, 0);
		cout << "----------------------------------------------------------------------------------------------------" << endl;
	}
	void reminderALL(Date* date)
	{
		ofstream fout("reminderALL.txt");
		for (auto& x:adults)
		{
			x.second->reminder(date,fout);
		}
		for (auto& x : childs)
			x.second->reminder(date, fout);
		fout.close();
		cout << "Напоминания отправлены" << endl;
		cout << "Хотите просмотреть файл рассылки? 1 - да, 2 - нет:  ";
		int vibor;
		cin >> vibor;
		do
		{
			if (vibor != 1 && vibor != 2)
			{
				cout << endl << "ошибка, введите 1 или 2:  ";
				cin >> vibor;
			}
		} while (vibor != 1 && vibor != 2);
		if (vibor == 1)
		{
			system("cls");
			ifstream fin("reminderALL.txt");
			if (fin.is_open())
			{
				string st;
				while (!fin.eof())
				{
					getline(fin, st);
					cout << st << endl;
				}
				system("pause");
			}
			fin.close();
		}
	}
	void vhod()
	{
		shapka();
		cout << "имя (логин): ";
		string name;
		cin >> name;
		if (adults.count(name) || childs.count(name))
			menu(name);
		else cout << "Пользователь с таким именем не найден" << endl;
		system("pause");
	}
	void menu()
	{
		loadAll();
		shapka();
		reminderALL(datenow);
		while (true)
		{
			system("cls");
			shapka();
			cout << "1 - Вход" << endl;
			cout << "2 - Регистрация" << endl;
			cout << "3 - Установить дату" << endl;
			cout << "0 - Закрыть программу" << endl;			
			int vibor;
			cin >> vibor;
			do {
				if (vibor != 1 && vibor != 2 && vibor != 3 && vibor != 0)
				{
					cout << "ошибка, повторите ввод: ";
					cin >> vibor;
				}
			} while (vibor != 1 && vibor != 2 && vibor != 3 && vibor != 0);
			switch (vibor)
			{
			case 1: vhod(); break;
			case 2: addUser(); saveAll(); break;
			case 3: setDate(); break;
			case 0: saveAll(); exit(0); break;			
			}
		}
	}
	void setDate()
	{		
		cin >> datenow;
		cout << "Дата установлена!" << endl;		
		system("pause");
		reminderALL(datenow);
	}
	void menu(string nameUser)
	{
		while (true)
		{
			//shapka;
			system("cls");
			cout << "----------------------------------------------------------------------------------------------------" << endl;
			cout << "                  Планировщик задач TaskManager";
			SetColor(10, 0);
			cout << setw(30) << "Сегодня: " << datenow << endl;
			SetColor(15, 0);			
			cout << "----------------------------------------------------------------------------------------------------" << endl;
			Creator* creator;
			User* us;
			if (adults.count(nameUser))
				creator = new AdultCreator;
			else creator = new ChildCreator;
			us = creator->create(nameUser);
			if (adults.count(nameUser))				
				us = adults[nameUser];			
			else				
				us = childs[nameUser];			
			cout << "Вы вошли под именем " << nameUser << "  Статус: " << us->getStatus() << endl;
			cout << "----------------------------------------------------------------------------------------------------" << endl;
			us->reminder(datenow,cout);
			cout << "1 - Добавить задачу" << endl;
			cout << "2 - Удалить задачу" << endl;
			cout << "3 - Редактировать задачу" << endl;
			cout << "4 - Просмотр всех задач" << endl;
			cout << "5 - Поиск" << endl;
			cout << "6 - Сохранить в файл" << endl;
			cout << "7 - Установить дату" << endl;
			cout << "0 - Выход в предыдущее меню" << endl;
			cout << "----------------------------------------------------------------------------------------------------" << endl;
			if (datenow == new Date(1, 1, 2020))
			{				
				cout << "Дата не установлена! Планировщик может работать некорректно!" << endl;
				cout << "----------------------------------------------------------------------------------------------------" << endl;
			}
			int vibor;
			cin >> vibor;
			do {
				if (vibor != 1 && vibor != 2 && vibor != 3 && vibor != 4 && vibor != 5 && vibor != 6 && vibor != 7 && vibor != 0)
				{
					cout << "ошибка, повторите ввод: ";
					cin >> vibor;
				}
			} while (vibor != 1 && vibor != 2 && vibor != 3 && vibor != 4 && vibor != 5 && vibor != 6 && vibor != 7 && vibor != 0);
			switch (vibor)
			{
			case 1:
			{
				UsualTask* task = new UsualTask;
				cin >> task;
				us->addTask(task);
				saveAll();
				break;
			}
			case 2:
			{
				int numberTask = getNumberTask(us);
				if (numberTask !=-1)
					us->delTask(numberTask);
				saveAll();
				break;
			}
			case 3:
			{
				int numberTask = getNumberTask(us);
				if (numberTask != -1)
					us->edit(numberTask); 
				saveAll(); 
				break;
			}
			case 4: system("cls"); us->print(cout); system("pause"); break;
			case 5: us->findTask(); break;
			case 6: us->save();
				break;
			case 7: setDate(); saveAll(); break;
			case 0: saveAll(); return; break;
			}
		}
	}
	void printAll()
	{
		system("cls");		
		for (auto& x : adults)
		{
			cout << x.first << "  AdultUser  " << x.second->getPassword() << endl;
			x.second->print(cout);
		}
		for (auto& x : childs)
		{
			cout << x.first << "  ChildUser  " << x.second->getParentName() << "  "<<x.second->getParentPassword()<<endl;
			x.second->print(cout);
		}
		system("pause");
	}
	int getNumberTask(User* us)
	{
		system("cls");
		us->print(cout);
		cout << "Выберите номер задачи: ";
		int number;
		cin >> number;
		if (number > 0 && number <= us->getKolTask())
			return number;
		else
		{
			cout << "Неверный номер" << endl;
			system("pause");
			return -1;
		}
	}
	void saveAll()
	{
		ofstream fout("taskManager.txt");
		fout << datenow->getDD() << endl;
		fout << datenow->getMM() << endl;
		fout << datenow->getYY() << endl;
		fout << adults.size() << endl;
		for (auto& x : adults)
		{
			fout << x.first << endl;
			fout << x.second->getPassword() << endl;
			fout << x.second->getKolTask() << endl;
			if (x.second->getKolTask())
				x.second->saveTask(fout);
		};
		fout << childs.size() << endl;
		for (auto& x:childs)
		{
			fout << x.first << endl;
			fout << x.second->getParentName() << endl;
			fout << x.second->getParentPassword() << endl;
			fout << x.second->getKolTask() << endl;
			if (x.second->getKolTask())
				x.second->saveTask(fout);
		}
		fout.close();
	}
	void loadAll()
	{
		ifstream fin("taskManager.txt");
		if (fin.is_open())
		{
			int d, m, y;
			fin >> d;
			fin >> m;
			fin >> y;
			datenow = new Date(d, m, y);
			int kolAdultUsers;
			fin >> kolAdultUsers;
			for (size_t i = 0; i < kolAdultUsers; i++)
			{
				string name, pas;
				int kolTask;
				fin >> name;
				fin >> pas;
				AdultUser* us = new AdultUser(name, pas);
				fin >> kolTask;
				for (size_t j = 0; j < kolTask; j++)
				{
					string nameTask, tegTask;
					int d, m, y, pr;
					if (j==0) fin.get();
					getline(fin, nameTask);
					fin >> d;
					fin >> m;
					fin >> y;
					Date dateTask(d, m, y);
					fin >> pr;
					fin.get();
					getline(fin, tegTask);
					UsualTask* task = new UsualTask(nameTask, dateTask, pr, tegTask);
					us->addTask(task);
				}
				adults.insert(make_pair(name, us));
			}
			int kolChildUsers;
			fin >> kolChildUsers;
			for (size_t i = 0; i < kolChildUsers; i++)
			{
				string name, nameParent, passwordParent;
				int kolTask;
				fin >> name;
				fin >> nameParent;
				fin >> passwordParent;
				ChildUser* us = new ChildUser(name);
				AdultUser* parent = new AdultUser(nameParent, passwordParent);
				us->setParent(parent);
				fin >> kolTask;
				for (size_t j = 0; j < kolTask; j++)
				{
					string nameTask, tegTask;
					int d, m, y, pr;
					if (j==0) fin.get();
					getline(fin, nameTask);
					fin >> d;
					fin >> m;
					fin >> y;
					Date dateTask(d, m, y);
					fin >> pr;
					fin.get();
					getline(fin, tegTask);
					UsualTask* task = new UsualTask(nameTask, dateTask, pr, tegTask);
					us->addTask(task);
				}
				childs.insert(make_pair(name, us));
			}
				
		}
		fin.close();				
	}
};
