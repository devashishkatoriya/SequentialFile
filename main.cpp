//Program to show working of Sequential File Access

/*
 * Created by Devashish Katoriya 1-4-2017
 */

#include <fstream>
#include <iostream>
#include <cstring>

using namespace std;

class Student                                                           //Student Class
{
    char name[30];
    int roll,marks[5],total;
    float average,percentage;
    void calculate();
public:
    Student()
    {
        roll = 0;
        strcpy(name,"");
        for(int i=0;i<5;i++)
            marks[i] = 0;
        total = 0;
        average = 0;
        percentage = 0;
    }
    void clr()
    {
        roll = 0;
        strcpy(name,"");
        for(int i=0;i<5;i++)
            marks[i] = 0;
        total = 0;
        average = 0;
        percentage = 0;
    }
    void read();
    void display();
    inline int retRoll()
    {
        return roll;
    }
};

void Student::read()                                                        //Read
{
    cout<<"\nEnter Roll\t:";
    cin>>roll;
    cout<<"Enter Name\t:";
    cin>>name;
    cout<<"Enter Marks\t:\n";
    for(int i=0;i<5;i++)
        cin>>marks[i];
    calculate();
}

void Student::display()                                                     //Display
{
    cout<<"\nRoll \t: "<<roll;
    cout<<"\nName \t: "<<name;
    cout<<"\nMarks\t: ";
    for(int i=0;i<5;i++)
        cout<<marks[i]<<"\t";
    cout<<"\nTotal\t: "<<total;
    cout<<"\nAvg. \t: "<<average;
}

void Student::calculate()                                                   //Calculate
{
    for(int i=0;i<5;i++)
        total += marks[i];
    average = total/5;
    percentage = total/5;
}

class StudentFile                                                           //File Class
{
    Student obj;
    char fileName[50];
    fstream fObj;
public:
    StudentFile()
    {
        create();
    }
    void create();
    void insert();
    void display_all();
    void update();
    void search();
    void delete_logical();
};

void StudentFile::create()                                              //Create
{
    cout<<"\nEnter File Name : ";
    cin>>fileName;
}

void StudentFile::insert()                                                  //Insert
{
    obj.read();
    fObj.open(fileName,ios::out|ios::app);
    if(fObj.fail())
    {
        cout<<"\nFile opening Error!";
        return;
    }
    fObj.write((char *)&obj,sizeof(obj));
    fObj.close();
    cout<<"\nRecord Inserted Successfully.";
}

void StudentFile::update()                                                  //Update
{
    int found,roll;
    fObj.open(fileName,ios::out|ios::app);
    if(fObj.fail())
    {
        cout<<"\nFile opening Error!";
        return;
    }
    cout<<"\nEnter Roll No. to Update : ";
    cin>>roll;
    found = 0;
    while(!fObj.eof())
    {
        fObj.read((char *)&obj,sizeof(obj));
        if(obj.retRoll()==roll)
        {
            found = 1;
            cout<<"\nEnter new Data : ";
            obj.read();
            fObj.write((char *)&obj,sizeof(obj));
        }
    }
    if(found==1)
        cout<<"\nRecord Updated Successfully.";
    else
        cout<<"\nRecord NOT found!";
    fObj.close();
}

void StudentFile::search()                                                  //Search
{
    int found,roll;
    fObj.open(fileName,ios::out|ios::app);
    if(fObj.fail())
    {
        cout<<"\nFile opening Error!";
        return;
    }
    cout<<"\nEnter Roll No. to Search : ";
    cin>>roll;
    found = 0;
    while(!fObj.eof())
    {
        fObj.read((char *)&obj,sizeof(obj));
        if(obj.retRoll()==roll)
        {
            found = 1;
            cout<<"\nRecord Found!";
            obj.display();
        }
    }
    if(found==0)
        cout<<"\nRecord NOT found!";
    fObj.close();
}

void StudentFile::display_all()                                                 //Display All
{
    fObj.open(fileName,ios::out|ios::app);
    if(fObj.fail())
    {
        cout<<"\nFile opening Error!";
        return;
    }
    while(!fObj.eof())
    {
        fObj.read((char *)&obj,sizeof(obj));
        obj.display();

    }
    fObj.close();
}

void StudentFile::delete_logical()
{
    int found,roll;
    fObj.open(fileName,ios::out|ios::app);
    if(fObj.fail())
    {
        cout<<"\nFile opening Error!";
        return;
    }
    cout<<"\nEnter Roll No. to Delete : ";
    cin>>roll;
    found = 0;
    while(!fObj.eof())
    {
        fObj.read((char *)&obj,sizeof(obj));
        if(obj.retRoll()==roll)
        {
            found = 1;
            obj.clr();
            cout<<"\nRecord Successfully Deleted!";
        }
    }
    if(found==0)
        cout<<"\nRecord NOT found!";
    fObj.close();
}

int main()
{
    int ch;
    cout<<"\nProgram for Student Records using Sequential File Access";
    StudentFile obj;
    do
    {
        ch = 0;
        cout<<"\n\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
        cout<<"\n 1 to Insert";
        cout<<"\n 2 to Display the File";
        cout<<"\n 3 to Search";
        cout<<"\n 4 to Update";
        cout<<"\n 5 to Delete";
        cout<<"\n 0 to Exit";
        cout<<"\nEnter your choice : ";
        cin>>ch;
        cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
        switch(ch)
        {
            case 1: obj.insert();
                    break;
            case 2: obj.display_all();
                    break;
            case 3: obj.search();
                    break;
            case 4: obj.update();
                    break;
            case 5: obj.delete_logical();
                    break;
            case 0: break;
            default:cout<<"\nInvalid Option!";
        }
    }while(ch!=0);

    cout<<"\nThank you for using this program :)";
    return 0;
}