#include<iostream>
#include<fstream>
#include<string>

using namespace std;
void write_fun(string fileName)
{
  int count = 1;
  ofstream write_obj;
  string str;
  while (1)
  {
    write_obj.open(fileName, ios::app);
    getline(cin, str);
    if (str == "exit")
    {
      break;
    }
    else
    {
    if (count == 1)
    {
      write_obj << str;
    }
    else
    {
      write_obj << endl << str;
    }
    
      count ++;
    }
    write_obj.close();
  }
}

int main()
{
  system("clear");
  system(" chmod +x ./welcomenotepad.sh");
  system("./welcomenotepad.sh");
  string str;
  string fileName;
  int choice;
  cout << "\t\tEnter 'exit' anytime to quit notepad" << endl;
  cout << "\t\t\tEnter The File Name: ";
  cin >> fileName;
  if(fileName != "exit")
  {
    //checking if its a text file
    
    if(fileName[fileName.length()-4] != '.' || fileName[fileName.length()-3] != 't' || fileName[fileName.length()-2] != 'x' || fileName[fileName.length()-1] != 't' )
    {
      fileName = fileName + ".txt";
    }

    ifstream read_obj;

    read_obj.open(fileName, ios:: in);

    if (read_obj.fail())
    {
      cout << "\t\t\tSorry, No file exist" << endl
      << "\t\t\tDo you want to Create One ?" << endl
      << "\t\t\tChoice (1/0): ";
      cin >> choice;
      if (choice == 1)
      {
       cout << "File Created Successfully" <<endl;
       write_fun(fileName);
      }
    }
    
    else
    {
      system("clear");
      //reading the file before
      while (!read_obj.eof())
      {
        getline(read_obj, str);
        //obj >> str;
        cout << "\t\t\t" << str << endl;

      }
      //now appending the file afterwards
      read_obj.close();
      write_fun(fileName);
      
    }
  }
  cin.ignore();
  cout <<"\t\t\t" << "Press any key to Exit..." << endl;
  cin.get();
  system("./dealloc_resource NOTEPAD");
  return 0;
}
