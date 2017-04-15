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
    float average;
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
    }
    void clr()
    {
        roll = 0;
        strcpy(name,"");
        for(int i=0;i<5;i++)
            marks[i] = 0;
        total = 0;
        average = 0;
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
    cout<<"\n\nRoll \t: "<<roll;
    cout<<"\nName \t: "<<name;
    cout<<"\nMarks\t: ";
    for(int i=0;i<5;i++)
        cout<<marks[i]<<"\t";
    cout<<"\nTotal\t: "<<total;
    cout<<"\nAvg. \t: "<<average;
}

void Student::calculate()                                                   //Calculate
{
    total = 0;
    for(int i=0;i<5;i++)
        total += marks[i];
    average = total/5;
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
    int search();
    void delete_logical();
    void delete_physical();
};

void StudentFile::create()                                              //Create
{
    cout<<"\nEnter File Name : ";
    cin>>fileName;
}

void StudentFile::insert()                                                  //Insert
{
    fObj.open(fileName,ios::ate|ios::in|ios::out|ios::app|ios::binary);
    if(fObj.fail())
    {
        cout<<"\nFile opening Error!";
        return;
    }
    int i=0;
    while(fObj.read((char *)&obj,sizeof(obj)))
        i++;
    
    fObj.clear();
    obj.read();
    fObj.write((char *)&obj,sizeof(obj));
    fObj.close();
    cout<<"\nRecord Inserted Successfully.";
}

void StudentFile::update()                                                  //Update
{
    int pos,offset;
    pos = search();
    if(pos == -1)
        return;
    
    
    fObj.open(fileName,ios::in|ios::out|ios::binary);
    if(fObj.fail())
    {
        cout<<"\nFile opening Error!";
        return;
    }
    offset = pos * sizeof(obj);
    
    cout<<"\nEnter new data :- \n";
    obj.read();
    fObj.seekp(offset,ios::beg);
    fObj.write((char *)&obj, sizeof(obj));
    fObj.close();
}

int StudentFile::search()                                                  //Search
{
    int roll,i;
    fObj.open(fileName,ios::in|ios::binary);
    if(fObj.fail())
    {
        cout<<"\nFile opening Error!";
        return -1;
    }
    cout<<"\nEnter Roll No. to Search : ";
    cin>>roll;
    i = 0;
    while(!fObj.eof())
    {
        fObj.read((char *)&obj,sizeof(obj));
        if(obj.retRoll()==roll)
        {
            cout<<"\nRecord Found!";
            obj.display();
            fObj.close();
            return i;
        }
        i++;
    }
    fObj.close();
    cout << "\nRecord NOT found!";
    return -1;
}

void StudentFile::display_all()                                                 //Display All
{
    fObj.open(fileName,ios::in|ios::out|ios::binary);
    if(fObj.fail())
    {
        cout<<"\nFile opening Error!";
        return;
    }
    while(fObj.read((char *)&obj,sizeof(obj)))
    {
        if(obj.retRoll()!=0)
            obj.display();
    }
    fObj.close();
}

void StudentFile::delete_logical()
{
    int found,roll,pos;
    fObj.open(fileName,ios::in|ios::out|ios::binary);
    if(fObj.fail())
    {
        cout<<"\nFile opening Error!";
        return;
    }
    cout<<"\nEnter Roll No. to Delete : ";
    cin>>roll;
    found = 0;
    while(fObj.read((char *)&obj,sizeof(obj)))
    {
        if(obj.retRoll()==roll)
        {
            found = 1;
            obj.clr();
            pos = -1 * sizeof(obj);
            fObj.seekp(pos,ios::cur);
            fObj.write((char *)&obj,sizeof(obj));
            cout<<"\nRecord Successfully Deleted!";
            break;
        }
    }
    if(found==0)
        cout<<"\nRecord NOT found!";
    fObj.close();
}

void StudentFile::delete_physical()
{
    fstream fObj2;
    fObj.open(fileName,ios::in|ios::out|ios::binary);
    fObj2.open("temp.txt",ios::in|ios::out|ios::binary);
    if(fObj.fail())
    {
        cout<<"\nFile opening Error!";
        return;
    }
    if(fObj2.fail())
    {
        cout<<"\nFile opening Error!";
        return;
    }
    int found,roll;
    cout<<"\nEnter Roll No. to Delete : ";
    cin>>roll;
    found = 0;
    while(fObj.read((char *)&obj,sizeof(obj)))
    {
        if(obj.retRoll()!=roll)
            fObj2.write((char *)&obj,sizeof(obj));
        else
            found = 1;
    }
    fObj.close();
    fObj2.close();
    
    fObj.open(fileName,ios::in|ios::out|ios::binary);
    fObj2.open("temp.txt",ios::in|ios::out|ios::binary);
    while(fObj2.read((char *)&obj,sizeof(obj)))
    {
        fObj.write((char *)&obj,sizeof(obj));
    }
    fObj.close();
    fObj2.close();
    
    if(found==0)
        cout<<"\nRecord NOT found!";
    else
        cout<<"\nRecord Successfully Deleted!";
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
        cout<<"\n 5 to Delete Logically";
        cout<<"\n 6 to Delete Physically";
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
            case 6: obj.delete_physical();
                    break;
            case 0: break;
            default:cout<<"\nInvalid Option!";
        }
    }while(ch!=0);

    cout<<"\nThank you for using this program :)";
    return 0;
}