#include<iostream>
#include<cstdlib>
#include<string.h>
#include<sstream>
#include<fstream>
#include<iomanip>
using namespace std;

// here we will create Student Class for the system

int RollNoToBeUpdated=0;


class student
{
      private:
          char Student_Name[50];
          int Roll_no;
          int Computer_Architecure, Data_Stucture, Data_Communication, English, DataBase_Systems, Cpp_progam;       
          double Student_Percentage;
          char Student_Grade;
          bool flag;/*flag=false when input roll no does not exist in file student.dat
                    flag=true when input roll no exists in file student.dat*/
          void CalculateGrade();
              
              
      public:
          student();
          //void menu();
          void entry_menu();
          void display_all();
          void getdata();
          void CheckForDuplicationInFile();
          void showdata();// this function displays student data on the output screen
          void TabularDisplay();// is used to display the result of all students in the form of a table
          int  GetStudentRollNo();// returns the roll no. of the current student
          void Write_Student_Record_In_File();// write user input=student record in file student.dat
          void ShowStudentRecord(int);// is used to display record of a student with a particular roll no given in function argument
          void Update_Student_Record(int);//accepts rollno and update record of binary file i.e student.dat
          void Delete_Student_Record(int);// DELETES A STUDENT RECORD that belongs to rollno provided by the user from the file student.dat
          void Delete_From_Duplicate_File(int);// deletes record from file DuplicateCheckingFile.txt(that contains only roll no of all students..)
          void Show_Result_Menu();// shows the Result Menu to the user that takes choice from the user to see whether user wants to see class result or individual student result
          void Display_Class_Result();// it displays result of complete class on the output screen  
};// shows the end of class

void menu(){
    system("cls");
    char ch;
    student std_obj;
    cout.setf(ios::fixed|ios::showpoint);
    cout<<setprecision(2); // program outputs decimal number to two decimal places*/
    do
    {
    system("cls");
    
    cout<<"\n\n\n\t\t\t\tHOME SCREEN\n\n\n";
    cout<<"\n\n\t1. Result Calculation System";
    cout<<"\n\n\t2. Student Database Management System";
    cout<<"\n\n\t3. Exit";
    cout<<"\n\n\n\n\n\tPlease Select Your Option (1-3)";
    cin>>ch;
    switch(ch)
    {
          case '1':
          //shows Result Calculation System
          std_obj.Show_Result_Menu();
          break;  
          case '2':
          //shows Student Database Management System Code
          std_obj.entry_menu();
          break;
          case '3':
          //user wants to exit the system
          break;
          default: cout<<"\a";
    }
    }while(ch!='3');
        
    system("pause");// second last statement that stops the output screen till the user presses any key

}

void student::entry_menu()
{
    char ch;
    int num;
    student std;
    system("CLS");
    cout<<"\n\n\n\t\t\tSTUDENT DATABASE MANAGEMENT SYSTEM MENU";
    cout<<"\n\n\t1. CREATE STUDENT RECORD";
    cout<<"\n\n\t2. SHOW RECORDS OF ALL STUDENTS";
    cout<<"\n\n\t3. SEARCH STUDENT RECORD";
    cout<<"\n\n\t4. UPDATE STUDENT RECORD";
    cout<<"\n\n\t5. DELETE STUDENT RECORD";
    cout<<"\n\n\t6. BACK TO HOME SCREEN";
    cout<<"\n\n\n\n\tPlease Enter Your Choice (1-6) ";
    cin>>ch;
    system("cls");
    switch(ch)
    {
          case '1':
               // creates student record
               std.Write_Student_Record_In_File();
               break;
          case '2':
               display_all();// it is showing records of all students in the file
               break;
          case '3':
               cout<<"\n\n\t Please Enter The Roll No";
               cin>>num;// we are receiving roll no from the system user
               std.ShowStudentRecord(num);
               break;
          case '4':
               //gets input as the roll no of student
               cout<<"\n\n\tPlease Enter The roll number ";
               cin>>num;
               std.Update_Student_Record(num);
               break;
          case '5':
               cout<<"\n\n\tPlease Enter The roll number ";
               cin>>num;
               std.Delete_Student_Record(num);
               break;
          case '6':
               break;
          default:cout<<"\a";entry_menu();
    
    }// end of switch
}// end of entry_menu function

void student ::display_all()
{
    // declarations
    student st;
    ifstream inFile;
    //open file
    inFile.open("student.dat",ios::binary);
    //if file did not open.. print error message & return function using return statement
    if(!inFile)
    {
    cout<<"File could not be opened !! Press any Key...";
    cin.ignore();
    cin.get();
    return;
    }
    /* if file opens, we will read records of all students one by one and call
    showdata() for each record*/
    cout<<"\n\n\n\t\tDISPLAY ALL RECORDs !!!\n\n";
    while(inFile.read(reinterpret_cast<char *> (&st), sizeof(student)))
    {
        st.showdata();// st.showdata is executed for each record of student in the file
        cout<<"\n\n====================================\n";
    }
    //close file using file object & clear input buffers
    inFile.close();
    cin.ignore();
    cin.get();
}// end of display_data function

void student::getdata()
{
    flag=false;
    cout<<"\nEnter the roll no of the student = ";
    cin>>Roll_no;
    // here we will check for duplication of roll no in the file
    //for udpate..if(RollNoToBeUpdated!=Roll_no)// 1118!=1118 
    if(RollNoToBeUpdated!=Roll_no)
    CheckForDuplicationInFile();
    
    if(flag==true)
    {
    cout<<"Error duplicate record"<<endl;
    return;// function returns
    }
    //if flag==false then we will ask user to enter the remaining data of the student
    cout<<"\n\nEnter The Name of student ";
    cin.ignore();
    cin.getline(Student_Name,50);
    cout<<"\nEnter The marks in Computer Architectre out of 100 : ";
    cin>>Computer_Architecure;
    cout<<"\nEnter The marks in Data Stucture out of 100 : ";
    cin>>Data_Stucture;
    cout<<"\nEnter The marks in Data Communications out of 100 : ";
    cin>>Data_Communication;
    cout<<"\nEnter The marks in English out of 100 : ";
    cin>>English;
    cout<<"\nEnter The marks in DataBase System out of 100 : ";
    cin>>DataBase_Systems;
    cout<<"\nEnter The marks in Cpp_program out of 100 : ";
    cin>>Cpp_progam;
    CalculateGrade();// THEN CALCULATING HIS RESULT

}// getdata ends

void student::CheckForDuplicationInFile()
{
    //open File DuplicateCheckingFile.txt
    //compare the roll no that user entered with all rollno.s of file DuplicateCheckingFile.txt;    
    // if found, make flag=true othwise flag=false
    int Current_RollNo=0;
    flag=false;
    ifstream infile("DuplicateCheckingFile.txt");
    while(!infile.eof())
    {
    infile>>Current_RollNo;
    if(Current_RollNo==Roll_no)
    {
        flag=true;
    }
    }// end of while
    infile.close();
    if(flag==false)// no duplication
    {
        // we are writing the roll no in DuplicateCheckingFile.txt
        ofstream outfile("DuplicateCheckingFile.txt",ios::app);
        outfile<<"\n"<<Roll_no;
        outfile.close();  
    }// if ends
     
}// end of CheckForDuplicationInFile

void student::showdata()
{
    cout<<"\nRoll Number of student = "<<Roll_no;
    cout<<"\nName of student = "<<Student_Name;    
    cout<<"\nMarks in Computer_Architecure = "<<Computer_Architecure;
    cout<<"\nMarks in Data_Stucture = "<<Data_Stucture;
    cout<<"\nMarks in Data_Communication= "<<Data_Communication;
    cout<<"\nMarks in English = "<<English;
    cout<<"\nMarks in DataBase_Systems = "<<DataBase_Systems;
    cout<<"\nMarks in Cpp_program ="<<Cpp_progam;
    cout<<"\nPercentage of student = "<<Student_Percentage;
    cout<<"\nGrade Of student = "<<Student_Grade;
 }

student::student()
{
    //creating student.dat file
    
    ofstream outFile("student.dat",ios::binary|ios::app); //create ofstream object
    outFile.close();
    //ceating DuplicateCheckingFile.txt
    
    ofstream outDFile("DuplicateCheckingFile.txt",ios::app);
    outDFile.close();
}

/////////////////// WRITES STUDENT RECORD IN FILE STUDENT.DAT   ///// 
void student::Write_Student_Record_In_File()
 {
    //OPEN FILE STUDENT.DAT
    ofstream outFile;
    outFile.open("student.dat",ios::binary|ios::app);
    
    getdata();// to get input from user
    
    //if flag=false(no duplication of roll no).... enter student record
    if(flag==false)// no duplication
    {
        //write record in file student.dat
        outFile.write(reinterpret_cast<char *>(this),sizeof(student));
        outFile.close();
        cout<<"\n\n Student record has been created";
    }
    //if flag=true.... print... error : record not created
    if(flag==true)
    {
        cout<<"record not created due to duplication\n";
        outFile.close();
    }
    cin.ignore();
    cin.get();
    //close file      
}

void student::Update_Student_Record(int n)
{
    //declarations
    
    /*adding bool variable.. bool is true when n(roll no to be updated) is found 
    in the file student.dat& found=false when the roll no of the record we are 
    going to enter is not found in the file student.dat*/
    RollNoToBeUpdated=n;// so now RollNoToBeUpdated is holding n
    bool found=false;
    fstream File;
    //open file student.dat
    File.open("student.dat",ios::binary|ios::in|ios::out);
    //if file does not open... print error and return function
    if(!File)
    {
        cout<<"File could not be open !! Press any Key...";
        cin.ignore();
        cin.get();
        return;     
    }
    
    /*if file opens... read each record one by one till we reach to the record
    of the student having roll no. n.. by using if statement like
    (current record roll==n) 
    then 
    1. we will print student record on the output screen using showdata() function 
    
    2. further we will take input(student record) from user with changes in it 
    using getdata()
    
    3. & now if flag==false(means no duplication of roll no. exists)
    then
    we will write the updated or changed record of student in the file*/
    
    while(!File.eof()&&found==false)// as long as reading file & record not found
    {
        //File.read(reinterpret_cast<char *>(this), sizeof(student));
        File.read(reinterpret_cast<char *> (this), sizeof(student));
        /*if file opens... read each record one by one till we reach to the record
        of the student having roll no. n.. by using if statement like
        (current record roll==n) */
        if(GetStudentRollNo()==n)// we have found record to be updated
        {
        //1. we will print student record on the output screen using showdata() 
        //function 
        showdata();
        cout<<"\n\nPlease Enter The New Details of student"<<endl;
        /*2. further we will take input(student record) from user with changes 
        in it using getdata()*/
        getdata(); // get user input as updated record
        if(flag==false)// no duplication
        {
            int pos=(-1)*static_cast<int>(sizeof(*this));
            File.seekp(pos,ios::cur);
            File.write(reinterpret_cast<char *> (this), sizeof(student));
        }
        found=true;// found is a bool variable to show record found if found=true                   
        }// end of if GetStudentRollNo()==n
        }// end of while loop
        File.close();
        
    // checking for duplication using flag variable value
    if(flag==true)// duplicate roll no
    {
        cout<<"could not update because this RollNo already exists";
    } 
    if(found==false)//we could not find that roll no in the file student.dat
    {
        cout<<"\n\n Record Not Found";
    }
    cin.ignore();
    cin.get();
    
    // no duplication & Record is found in file student.dat
    if(flag==false&&found==true&&RollNoToBeUpdated!=Roll_no)//
    {
    Delete_From_Duplicate_File(n);// deleting here 111 from DuplicateCheckingFile.txt
    }
    RollNoToBeUpdated=0;
}// end of update function

void student::Delete_Student_Record(int n)
{
   //declarations
   
   ifstream inFile;
   
   //open file
   inFile.open("student.dat",ios::binary);
   // if file does not open .. print error
   if(!inFile)
   {
        cout<<"\nFile could not be opened..Press any key";
        cin.ignore();
        cin.get();
        return;
   }
   //if file opens
   //1.create & open another file temp.dat   
   ofstream outFile;
   outFile.open("Temp.dat",ios::out);
   inFile.seekg(0,ios::beg);
   //while reading each record of student.dat..
   while(inFile.read(reinterpret_cast<char *> (this), sizeof(student)))
   {
      if(GetStudentRollNo()!=n)
        {
            //2. copy records to temp.dat from student.dat file except the one we wanted to delete(e.g Omer in our example)
            outFile.write(reinterpret_cast<char *> (this), sizeof(student));
        }// end if
                                                       
    }// end of while
   
   //3. close both files
   outFile.close();
   inFile.close();   
   //remove student.dat
   remove("student.dat");
   //rename temp.dat as student.dat to make it student.dat again
   rename("Temp.dat","student.dat");
   cout<<"\n\nRecord deleted.. press any key";
   cin.ignore();
   cin.get();
   //call function delete duplicate file that delete's Omer's record from 
   //file DuplicateCheckingFile.txt  
   Delete_From_Duplicate_File(n);
  
   
}// end of delete function

void student::Delete_From_Duplicate_File(int RollNoOfRecord)
{
    int Current_RollNo;
    //open files DuplicateCheckingFile.txt & temporary file TempFile.txt
    ifstream InFile("DuplicateCheckingFile.txt");
    ofstream OutFile("TempFile.txt");
    InFile.seekg(0,ios::beg);
    /* copy contents of DuplicateCheckingFile.txt in temporary file TempFile.txt
    except the roll no of record to be deleted that was omer in our case*/
    while(!InFile.eof())
    {
        InFile>>Current_RollNo; 
        if(Current_RollNo!=RollNoOfRecord)
        {
            OutFile<<"\n"<<Current_RollNo;
        }  
    }// end of while
    
    //3. close both files
    InFile.close();
    OutFile.close();
    //remove DuplicateCheckingFile.txt
    remove("DuplicateCheckingFile.txt");
    /*rename TempFile.txt as DuplicateCheckingFile.txt to make it 
    DuplicateCheckingFile.txt again*/
    rename("TempFile.txt","DuplicateCheckingFile.txt");
    //clear input buffers
    cin.ignore();
    cin.get();
   
}//end of Delete_From_Duplicate_File(int RollNoOfRecord)

void student::CalculateGrade()
{
    Student_Percentage=(Computer_Architecure+Data_Stucture+Data_Communication+English+DataBase_Systems+Cpp_progam)/6.0;
    if(Student_Percentage>=90)
    Student_Grade='A';
    if(Student_Percentage>=80&&Student_Percentage<90)  
    Student_Grade='B';  
    if(Student_Percentage>=70&&Student_Percentage<80)
    Student_Grade='C';
    if(Student_Percentage>=60&&Student_Percentage<70)
    Student_Grade='D';
    if(Student_Percentage>=50&&Student_Percentage<60)
    Student_Grade='E';
    if(Student_Percentage<50)
    Student_Grade='F';
}// end of CalculateGrade() function

void student::TabularDisplay()
{
    cout<<left<<setw(10)<<Roll_no<<setw(10)<<Student_Name<<setw(15)<<Computer_Architecure<<setw(15)<<Data_Stucture<<setw(15)<<Data_Communication<<setw(15)<<English<<setw(15)<<DataBase_Systems<<setw(15)<<Cpp_progam<<setw(15)<<Student_Percentage<<setw(10)<<Student_Grade<<endl;    
}

int student::GetStudentRollNo()
{
    return Roll_no;
}

void student::ShowStudentRecord(int n)
{
    ifstream inFile;
    inFile.open("student.dat",ios::binary);
    if(!inFile)// file did not open
    {
                cout<<"File could not be opened !! Press any key to continue";
                cin.ignore();
                cin.get();
                return;
    }
    bool flag=false;// we used it as an indicator to know whether that roll no is found in the file or not
    //now here will take the roll no and find student record in the file "student.dat"
    while(inFile.read(reinterpret_cast<char *> (this),sizeof(student)))
    {
        if(GetStudentRollNo()==n)// the n roll no is found in the file student.dat
        {
            showdata();// prints record of current student
            flag=true;// record is found in the file student.dat
        } 
        
    }// end of while loop
    inFile.close();
    if(flag==false)
    cout<<"\n\nrecord does not exist";
    cin.ignore();
    cin.get();
}// Show Student Record function ends

//result menu is shown here
void student::Show_Result_Menu()
{
    
    // declarations & clear screen
    char ch;
    int rno;
    system("cls");
    
    //print menu using cout on the output screen
    cout<<"\n\n\n\tRESULT MENU";
    cout<<"\n\n\n\t1. Class Result";
    cout<<"\n\n\n\t2. Student Report Card";
    cout<<"\n\n\n\t3. Back to Main Menu/Home Screen";
    cout<<"\n\n\n\tEnter Choice... ";
    cin>>ch;
    system("cls");
    
    // we will add switch to add code to the options provided by the menu
    switch(ch)
    {
        case '1':Display_Class_Result();
            break;
        case '2':cout<<"\n\n\tEnter the Roll No of the Student = ";
                cin>>rno;
                ShowStudentRecord(rno);
                break;
        case '3':break;
        default: cout<<"\a";
    }// end of switch
          
}// end of show result menu function

void student::Display_Class_Result()
{
    //opens file student.dat
    ifstream inFile;
    inFile.open("student.dat",ios::binary);
    //if file does not opens, prints error on output screen and returns the function
    if(!inFile)
    {
            cout<<"File could not be opened.. Press any key..";
            cin.ignore();
            cin.get();
            return;
    }
    /*if file opens, 
    1. system will give heading of class result on output screen*/
    cout<<"\n\n\t\tALL CLASS RESULT \n\n";
    cout<<"==================================================================================================================================\n";
    cout<<left<<setw(10)<<"R.No"<<setw(10)<<"Name"<<setw(15)<<"Architecure"<<setw(15)<<"Stucture"<<setw(15)<<"Communication"<<setw(15)<<"English"<<setw(15)<<"DataBase"<<setw(15)<<"Progamming"<<setw(15)<<"%Age"<<setw(10)<<"Grade"<<endl;
    cout<<"==================================================================================================================================\n";
    
    /*2. use a while loop and it will run as long as it is reading records from the 
    file student.dat*/
    while(inFile.read(reinterpret_cast<char *> (this), sizeof(student)))
    {
        TabularDisplay();
    /*3. inside while loop... call the function Tabular Display that prints student's
    data on the output screen in the form of table
    */ 
    }// end of while
    // closes file student.dat
    inFile.close();
    //clear input buffers
    cin.ignore();
    cin.get();
     
}// end of function Display_Class_Result()

// all class functions end here

void login(){// function login
	label:
	system("cls");
    cout<<"\t\t\t========================="<<endl;
    cout<<"\t\t\t|  Login Home Page      |"<<endl;
    cout<<"\t\t\t========================="<<endl;
    cout<<endl;
    cout<<"\t\t\t--------------------------"<<endl;
	cout<<"\t\t\t|[1] .REGISTER           |"<<endl;
	cout<<"\t\t\t|[2] .LOGIN              |"<<endl;
	cout<<"\t\t\t|[3] .EXIT               |"<<endl;
    cout<<"\t\t\t--------------------------"<<endl;
    cout<<"\t\t\tPlese Enter Your Choice...";
	string p,q,w;
	int x;string s;
	cin>>x;
	if(x==1){

        system("cls");
        ofstream fout;
        cout<<"ENTER YOUR USERNAME"<<endl;
        cin>>s;
        cout<<"ENTER YOUR PASSWORD"<<endl;
        cin>>p;
        s=s+p;
        ifstream fin;
        string line;
        int offset=0;
        fin.open("myfile.txt");
        if(fin.is_open())
        {
            while(!fin.eof())
            {
                getline(fin,line);
                if(line.find(s,0)!=-1)
                {
                    cout<<"sorry! this username is not available"<<endl;
                    cout<<"Press any key to go to Home Page"<<endl;
                    char kk;
                    cin>>kk;
                    goto label;
                    //break;
                }
            }
        }
        fin.close();
        fout.open("myfile.txt",ios::app);
        fout<<s+"\n";
        fout.close();
        goto label;
	}
		else if(x==2){

			string line;
			system("cls");
  			ifstream fin;
  			int offset=0;
  			cout<<"ENTER YOUR USERNAME"<<endl;
  			cin>>q;
  			cout<<"ENTER YOUR PASSWORD"<<endl;
  			cin>>w;
  			q=q+w;
  			fin.open("myfile.txt");
  			if(fin.is_open())
  			{
  				while(!fin.eof())
  				{
  					getline(fin,line);
					if(line.find(q,0)!=-1)
					{
						cout<<"you are logged in !!"<<endl;
						offset=1;
                        menu();
						break;
                    }
				}
				if(offset==0)
				{
					cout<<"sorry you are unauthorised!!"<<endl;
					cout<<"Press 1 and enter to go to home page"<<endl;
					//getch();
					char o;
					cin>>o;
					goto label;
								  }
			}
  			fin.close();
	}
	else if(x==3){
		cout<<" ";
	}else{
	    goto label;
	}

}

int main()
{
    system("color f4");
    login();
    return 0;
}