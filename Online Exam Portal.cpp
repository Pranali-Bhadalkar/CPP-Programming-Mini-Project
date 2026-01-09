#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Person
{
public:
string username;
string password;
Person()
{
username="";
password="";
}
virtual void displayRole()
{
cout<<"Generic Person\n";
}
};

class Student : public Person
{
public:
Student()
{
cout<<"\n[Student Object Created]\n";
}
~Student()
{
cout<<"[Student Object Destroyed]\n";
}
void registerUser()
{
cout<<"\nEnter username: ";
cin>>username;
cout<<"Enter password: ";
cin>>password;
ofstream fout("users.txt",ios::app);
if(fout.is_open())
{
fout<<username<<" "<<password<<endl;
fout.close();
cout<<"Registration Successful!\n";
}
else
{
cout<<"Error opening users.txt file!\n";
}
}
bool loginUser()
{
cout<<"\nEnter username: ";
cin>>username;
cout<<"Enter password: ";
cin>>password;
ifstream fin("users.txt");
string u,p;
int found=0;
while(fin>>u>>p)
{
if(u==username && p==password)
{
found=1;
break;
}
}
fin.close();
if(found)
{
cout<<"\nLogin Successful!\n";
return true;
}
else
{
cout<<"Invalid Username or Password!\n";
return false;
}
}
void displayRole()
{
cout<<"Role: Student\n";
}
};

class Admin : public Person
{
public:
Admin()
{
cout<<"\n[Admin Object Created]\n";
}
~Admin()
{
cout<<"[Admin Object Destroyed]\n";
}
bool adminLogin()
{
cout<<"\nEnter admin username: ";
cin>>username;
cout<<"Enter admin password: ";
cin>>password;
if(username=="admin" && password=="admin123")
{
cout<<"Admin Login Successful!\n";
return true;
}
else
{
cout<<"Invalid Admin Credentials!\n";
return false;
}
}
void addQuestion()
{
string question,option1,option2,option3,option4;
int correct;
cout<<"\nEnter Question: ";
cin.ignore();
getline(cin,question);
cout<<"Option 1: ";
getline(cin,option1);
cout<<"Option 2: ";
getline(cin,option2);
cout<<"Option 3: ";
getline(cin,option3);
cout<<"Option 4: ";
getline(cin,option4);
cout<<"Enter Correct Option Number (1-4): ";
cin>>correct;
ofstream fout("questions.txt",ios::app);
if(fout.is_open())
{
fout<<question<<endl;
fout<<option1<<endl;
fout<<option2<<endl;
fout<<option3<<endl;
fout<<option4<<endl;
fout<<correct<<endl;
fout.close();
cout<<"Question Added Successfully!\n";
}
else
{
cout<<"Error writing to questions.txt\n";
}
}
void viewAllResults()
{
ifstream fin("results.txt");
string name,percent;
int score;
if(!fin.is_open())
{
cout<<"No results available yet.\n";
return;
}
cout<<"\n---- All Results ----\n";
while(fin>>name>>score>>percent)
{
cout<<"User: "<<name<<" | Score: "<<score<<" | Percent: "<<percent<<endl;
}
fin.close();
}
void displayRole()
{
cout<<"Role: Admin\n";
}
};

class ExamSystem : public Student
{
public:
ExamSystem()
{
cout<<"\n[Exam System Activated]\n";
}
void startExam(Student s)
{
ifstream fin("questions.txt");
if(!fin.is_open())
{
cout<<"No questions available. Contact admin!\n";
return;
}
string question,opt[4];
int correct,ans;
int score=0,total=0;
cout<<"\n===== Exam Started =====\n";
while(getline(fin,question))
{
for(int i=0;i<4;i++)
{
getline(fin,opt[i]);
}
fin>>correct;
fin.ignore();
total++;
cout<<"\nQ"<<total<<". "<<question<<endl;
for(int i=0;i<4;i++)
{
cout<<i+1<<") "<<opt[i]<<endl;
}
cout<<"Your Answer: ";
cin>>ans;
if(ans==correct)
{
score++;
}
}
fin.close();
cout<<"\n===== Exam Completed =====\n";
cout<<"You scored "<<score<<" out of "<<total<<endl;
float percent=(score*100.0f)/total;
cout<<"Percentage: "<<percent<<"%"<<endl;
if(percent>=80)
cout<<"Excellent Performance!\n";
else if(percent>=50)
cout<<"Good Performance!\n";
else
cout<<"Needs Improvement!\n";
ofstream fout("results.txt",ios::app);
if(fout.is_open())
{
fout<<s.username<<""<<score<<""<<percent<<"%"<<endl;
fout.close();
}
else
{
cout<<"Error saving result!\n";
}
}
void viewMyResults(Student s)
{
ifstream fin("results.txt");
string uname,percent;
int score;
int found=0;
cout<<"\n===== Your Result History =====\n";
while(fin>>uname>>score>>percent)
{
if(uname==s.username)
{
cout<<"Score: "<<score<<" | Percent: "<<percent<<endl;
found=1;
}
}
if(!found)
cout<<"No records found for you!\n";
fin.close();
}
};

int main()
{
Student s;
Admin a;
ExamSystem exam;
int choice;
bool loggedIn=false;
bool isAdmin=false;
do
{
cout<<"\n===== Online Exam Portal =====\n";
cout<<"1. Register Student\n";
cout<<"2. Student Login\n";
cout<<"3. Admin Login\n";
cout<<"4. Take Exam\n";
cout<<"5. View My Results\n";
cout<<"0. Exit\n";
cout<<"Enter your choice: ";
cin>>choice;
switch(choice)
{
case 1:
s.registerUser();
break;
case 2:
if(s.loginUser())
{
loggedIn=true;
isAdmin=false;
}
break;
case 3:
if(a.adminLogin())
{
isAdmin=true;
loggedIn=true;
int c;
do
{
cout<<"\n--- Admin Menu ---\n";
cout<<"1. Add Question\n";
cout<<"2. View All Results\n";
cout<<"0. Logout\n";
cout<<"Enter choice: ";
cin>>c;
if(c==1)
a.addQuestion();
else if(c==2)
a.viewAllResults();
}while(c!=0);
}
break;
case 4:
if(loggedIn && !isAdmin)
exam.startExam(s);
else if(isAdmin)
cout<<"Admin cannot take exam!\n";
else
cout<<"Please login as Student first!\n";
break;
case 5:
if(loggedIn && !isAdmin)
exam.viewMyResults(s);
else
cout<<"Please login as Student first!\n";
break;
case 0:
cout<<"Exiting Program...\n";
break;
default:
cout<<"Invalid choice!\n";
}
}while(choice!=0);
return 0;
}

