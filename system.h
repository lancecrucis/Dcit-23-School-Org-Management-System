#include <iostream>     // used to perform the input and output operations
#include <fstream>      // used to create files, read from files, and write to files
#include <sstream>      // used to extract string from files
#include <string>       // used to find a word from a set of strings
#include <time.h>       // used for time related functions
#include <iomanip>      // used for style and formatting input and output operations
#include <vector>       // used for when elements are added or removed
#include <dirent.h>     // substitute to #include <filesystem>. Used for directories
#include <algorithm>    //used with vectors and used with removing spaces in files

using namespace std;

void line();            // for styling the ui
void line2();           // for styling the ui(2)
void line3();           // for styling the ui(3)
void clearscreen();     // reset the screen 
bool loggedin();        // login
string orgregister();   // register
void insidelogin();     // after login 
void addmembers();      // add members
void deletemembers();   // delete members
void assignmembers();   // assign members
void vieworg();         // view all created organizations
void deleteorg();       // delete existing organizations

string username, studentnum, password;  //my global variables

void menu(){    // MAIN MENU
clearscreen();
    line();
    cout<<"Cavite State University - Silang Campus"<<endl;
    line();
    cout<<"\tCurrent Date: "<<__DATE__<<endl;
    cout<<endl;
    cout<<endl;
    line2();
    cout<<"|Student Organization|";
    cout<<"--------";
    cout<<endl;
    cout<<"\n1. Login"<<endl;
    cout<<"2. Register"<<endl;
    cout<<"3. View Organization"<<endl;
    cout<<"4. Exit"<<endl;
    cout<<endl;

    int choice;
    cout<<"Enter you choice: ";
    cin>>choice;
    
    switch(choice){
        case 1:             
            loggedin();         //LOGIN    
            break;
        case 2: 
            orgregister();      //REGISTER
            break;
        case 3:
            vieworg();          //VIEW ALL CREATED ORGANIAZTION
            break;
        case 4:
            clearscreen();      //EXIT THE SYSTEM
            cout<<"Exiting the program...";
            exit(0);
            break;
        default:
            clearscreen();
            menu();
            break;
    }

}

void line(){                      //PRINT EQUAL SIGN  
    for(int i=1;i<40;i++){
        cout<<"=";
    }
    cout<<endl;
}

void line2(){                    //PRINT LINE 1
    for(int i=1; i<10; i++){
        cout<<"-";
    }
}

void line3(){                   //PRINT LINE 2
    for(int i=1;i<35;i++){
        cout<<"-";
    }
}
void pausescreen(){             //PAUSE AND WAIT FOR ENTER
    cout<<"Press Enter to continue..";
    cin.ignore();
    cin.get();
}

void clearscreen() {            //CLEAR/RESET THE SCREEN
    system("clear");
}

//login system
bool loggedin(){                //LOGIN FUNCTION
    clearscreen();
    line();
    cout<<"\t Login to an Organization"<<endl;
    line();
    
    string password;
    string un, pw;

    cout<<"\nEnter your organization name: ";
    cin>>username;
    cout<<"Enter your password: ";
    cin>>password;

    ifstream read(username + ".txt");    //OPEN FILE

     if (!read.is_open()) {     //CHECK IF FILE EXIST OR CREATED
        clearscreen();
        cout<< endl;
        
        cerr<< "\033[1;31mInvalid. Organization is not found nor created\033[0m\n";
        cout<<"\033[1;31m-----------------------------------------------\033[0m";
        cout<<endl;
        cout<<"\n0. Return to main menu"<<endl;
        cerr<<"1. Try again"<<endl;
        cout<<"2. Register an organization"<<endl;
        int logchoice;
        cout<<"\nEnter your choice: ";
        cin>>logchoice;

        if(logchoice==1){
            clearscreen();
            loggedin();
        }
        else if(logchoice==2){
            clearscreen();
            orgregister();
        }
        else{
            clearscreen();
            menu();
        }
    }

    getline(read,un);     //READ THE USERNAME
    getline(read,pw);     //READ THE PASSWORD
    read.close();         //CLOSE THE FILE

    if(un == username && pw == password)
    {
        insidelogin();
        return true;
    }
    else
    {
        cerr<<"\n\033[1;31mIncorrect Password.\033[0m"<<endl;
        cout<<"0. Return to main menu"<<endl;
        cerr<<"1. Try again"<<endl;
        cout<<"2. Register an organization"<<endl;
        int logchoice;
        cout<<"\nEnter your choice: ";
        cin>>logchoice;

        if(logchoice==1){
            clearscreen();
            loggedin();
        }
        else if(logchoice==2){
            clearscreen();
            orgregister();
        }
        else{
            clearscreen();
            menu();
        }
        return false;
    }
}


string orgregister() {      //REGISTER
    clearscreen();
    string name,course;
    line();
    cout<<"\tRegister an Organization"<<endl;
    line();
    cin.ignore();

    cout<<"\nName of the person registering: ";
    getline(cin,name);
    cout<<"Year and Course (e.g., 1st BSCS): ";
    getline(cin,course);

    while(true){         //VALIDATION OF ORGANIZATION NAME
        cout<<"Name of the organization: ";
        getline(cin,username);
        if(username.length() >= 3){
        break;
        }
        cerr<< "\n\033[1;31mInvalid: Username must be at least 3 characters.\033[0m"<<endl;
    }

    while (true) {      //VALIDATION FOR PASSWORD
        cout << "Password for the organization: ";
        getline(cin, password);
        if (password.length() >= 6) {
            break;
        }
        cerr << "\n\033[1;31mInvalid: Password must be at least 6 characters\033[0m" << endl;
    }
                        //VALIDATION IF INPUT IS NOT EMPTY
    if(name.empty()||course.empty()||username.empty()||password.empty()){
        cerr<<"\n\033[1;31mAll fields are required. Please restart the registration process.\033[0m"<<endl;
        cout<<"1. Try again. "<<endl;
        cout<<"2. Go back to main menu"<<endl;
        int choice1;
        cout<<"\nEnter your choice: ";
        cin>>choice1;
        if(choice1==1){
            clearscreen();
            orgregister();
        }
        else{
            clearscreen();
            menu();
        }

    }

    ofstream file;      //CREATE A TXT FILE TO STORE USERNAME AND PASSWORD
    file.open(username+".txt");
    file<<username<<endl<<password;
    file.close();

                        //CREATE CSV FILE TO STORE THE MEMBERS INFORMATION
    ofstream orgmembers(username + "_members.csv");
    if(orgmembers.is_open()){
        orgmembers.close();
    }

    clearscreen();
    cout << "\tRegistered Successfully!" << endl;
    cout<<"------------------------------------";
    cout<<"\nOrganization Details:"<<endl;
    cout << "\nOrganization Name: " << "\t"<<username << endl;
    cout << "Registered By: " <<"\t\t"<< name << endl;
    cout << "Registration Date: " <<"\t"<<__DATE__ << endl;
    char n;
    cout<<"\nWould you like to go to login page? (Y/N): ";
    cin>>n;
    
    if(n=='y'||n=='Y'){
    clearscreen();
    loggedin(); 
    }else if(n=='N'||n=='n'){
        char option;
    cout << "Would you like to register another organization? (Y/N): ";
    cin >> option;

         if (option == 'y' || option == 'Y') {
        clearscreen();
        orgregister();  
    } else {
        cout << "Returning to the main menu..." << endl;
        clearscreen();
        menu();  
    }
} else {
    cerr << "\033[1;31mInvalid input. Returning to main menu...\033[0m" << endl;
    clearscreen();
    menu();  
}
    return username;
    }


void insidelogin(){         //AFTER LOGIN
    int choice;
    clearscreen();
    line();
    cout << "Welcome to " << username << "'s Organization" << endl;
    line();
    cout<<"1. Add Members"<<endl;
    cout<<"2. Assign Members"<<endl;
    cout<<"3. Delete Members"<<endl;
    cout<<"4. Delete Organization"<<endl;
    cout<<"5. Main Menu"<<endl;
    cout<<"Enter your choice: ";
    cin>>choice;

    if(choice==1){          // ADD MEMBERS
        clearscreen();
        addmembers();
    }
    else if(choice==3){     // DELETE MEMBERS
        clearscreen();
        deletemembers();
    }
    else if(choice==2){     // ASSIGN MEMBERS
        clearscreen();
        assignmembers();
    }
    else if(choice==4){     //DELETE ORGANIZATION
        clearscreen();
        deleteorg();
    }
    else if(choice==5){     // MAIN MENU
        clearscreen();
        menu();
    }
    else{
        clearscreen();
        insidelogin();
    }
}

void addmembers(){          //ADD MEMBERS
    clearscreen();
    fstream file(username+"_members.csv", ios::out|ios::app); 

    if(!file){
        cerr<<"\033[1;31mFailed to find members.cvs\033[0m";
        return;
    }

    string name, year, course, section, email, contactnum, role;
    
    cout<<"\tData Add members\n";
    line3();
    cout<<"---";
    cout<<endl;
    cout<<endl;
    
    cin.ignore();

    while(true){                //STUDENT NUMBER VALIDATION
    cout<<"Student Number: "; 
    getline(cin,studentnum);
    if(all_of(studentnum.begin(), studentnum.end(), ::isdigit)){
        break;
    }
    cerr<<"\033[1;31mInvalid student number (must be 'all numbers') \033[0m"<<endl;
    }

    while(true){                //FULL NAME VALIDATION
    cout<<"Student Full name: "; 
    getline(cin,name);
        if(name.find(",") == string::npos && !name.empty()){
        break;  
    }
    cerr<<"\033[1;31mInvalid Full name (must have first name at the start.\033[0m"<<endl;
    }

    cout<<"Year (e.g, 1st year): ";         
    getline(cin,year);
    cout<<"Course (e.g., BSCS): ";
    getline(cin,course);

    if(name.empty()||year.empty()||course.empty()){  //IF INPUT IS EMPTY
        cout<<"\n-------------------------------------";
        cerr<<"\n\033[1;31mAll fields are required. Please restart the registration process.\033[0m\n";
        cout<<"1. Try again. "<<endl;
        cout<<"2. Go back to menu"<<endl;
        int choice1;
        cout<<"\nEnter your choice: ";
        cin>>choice1;
        if(choice1==1){
            clearscreen();
            addmembers();
        }
        else{
            clearscreen();
            insidelogin();
        }
    }


    while(true){                    // SECTION VALIDATION
        cout<<"Section (e.g., 1a): ";
        getline(cin,section);
            if(section.length()==2 && isdigit(section[0]) && isalpha(section[1])){
            break;
            }
    cerr<<"\033[1;31mInvalid section. (must start with a number and ends with a letter)\033[0m"<<endl;
    }
 
    while(true){                    //SCHOO EMAIL VALIDATION
        cout<<"School email: ";
        getline(cin,email);
            if(email.find("@cvsu.edu.ph")!= string::npos){
            break;
            }
    cerr<<"\033[1;31mInvalid School email (must have '@cvsu.edu.ph')at the end.\033[0m"<<endl;
    }
 
    while(true){                    // PHONE N0. VALIDATION
    cout << "Contact number (+63): ";
    getline(cin, contactnum);
    if(contactnum.length()==11 && all_of(contactnum.begin(), contactnum.end(), ::isdigit )){
        break;
    }
    cerr<<"\033[1;31mInvalid contact number. (must have '11 digits').\033[0m"<<endl;
    }

    file <<","<< studentnum << "," << name << "," << year << "," << course << ","       //INPUT INFORMATION TO THE CSV FILE
    << section << "," << email << "," << contactnum << endl;

    file.close(); 

    char choice;
    cout<<"Add another member? (Y/N): ";
    cin>>choice;
    if(choice=='Y'||choice=='y'){
        clearscreen();
        addmembers();
    }
    else if(choice=='n'||choice=='N'){
        clearscreen();
        insidelogin();
    }


}
void deletemembers(){
    clearscreen();
    
    ifstream file(username +"_members.csv");
    if(!file.is_open()){
        cout<<"Error opening member file\n";
        pausescreen();
        clearscreen();
        insidelogin();
    }

    vector<string>lines;            //GET AND STORE LINES FROM THE FILE
    string line;
    while(getline(file, line)){
        lines.push_back(line);
    }
    file.close();

    string delete_members;
    cout<<"\nEnter the student number of the member you want to delete: ";
    cin>>delete_members;
    

    bool found = false;                     //PROCESS INFORMATION LINE BY LINE
    vector<string>::iterator it;
    for(it = lines.begin(); it != lines.end(); ++it){
            stringstream ss(*it);           //GIVE ACCESS TO THE LINE IT POINTS TO
            string studentnum_in_file;

            getline(ss, studentnum_in_file, ',');
            getline(ss, studentnum_in_file, ',');
            
            cout << "\nFound student number in file: '" << studentnum_in_file << "'" << endl;

            studentnum_in_file.erase(remove(studentnum_in_file.begin(), 
            studentnum_in_file.end(), ' '), studentnum_in_file.end());

            if(studentnum_in_file==delete_members){       //CHECK AND DELETE INFORMATION OF THE MEMBER
                lines.erase(it);
                found = true;
                break;
            }
        }
    if (!found){
        cerr<<"\033[1;31mStudent number is not found.\n\033[0m";
        pausescreen();
        clearscreen();
        insidelogin();
    }

    ofstream outfile(username+"_members.csv");           //UPDATE THE FILE
    if(!outfile.is_open()){
        cout<<"Error writing to members file.\n";
        pausescreen();
        clearscreen();
        insidelogin();
    }

   for (size_t i = 0; i < lines.size(); ++i) {          //WRITE EACH REMAINING FILE TO THE LINE
    outfile << lines[i] << '\n';
    }

    outfile.close();
    cout<<"\n----------------------------------";
    cout<<"\nMember deleted successfully.\n";
    pausescreen();
    clearscreen();
    insidelogin();

}

void vieworg(){                  //VIEW ALL CREATED ORGANIZATIONS AND ITS MEMBERS
    clearscreen();

    vector<string> orgs;        //STORES THE NAME OF THE ORGANIZATION

    DIR* dir = opendir(".");    //OPENS THE DIRECTORY
    if(dir == nullptr){
        cout<<"error opening"<<endl;
        return;
    }
    struct dirent*entry;
    while((entry = readdir(dir))!=nullptr){
        string filename=entry->d_name;
         if (filename.find("_members.csv") != string::npos) {
            string orgname = filename.substr(0, filename.find("_members.csv")); //EXTRACT ORG NAME FROM "_MEMBERS"
            orgs.push_back(orgname);
    }
    }

    closedir(dir);

    if(orgs.empty()){
        cout<<endl;
        cout<<"No organization found"<<endl;
        pausescreen();
        clearscreen();
        menu();
        return;
    }

    line();
    cout<<"\tAvailable Organizations"<<endl;
    line();
    cout<<endl;

    for(size_t i=0;i<orgs.size();++i){
        cout<<i+1<<". "<<orgs[i]<<endl;
    }
    cout<<endl;
    

    int choice;
    cout<<endl;
    cout << "\nEnter the number of the organization you want to view: ";
    cin >> choice;

    if(choice < 1 || choice > orgs.size()){
        cerr<<"\033[1;31m Invalid choice. Returning to main menu..\033[0m\n";
        pausescreen();
        clearscreen();
        menu();
        return;
    }

    string chosenorg = orgs[choice - 1];
    string filename = chosenorg + "_members.csv";

    fstream file(filename, ios::in);

    if(!file){
        cout<<"Failed to open members.csv";
        pausescreen();
        clearscreen();
        menu();
        return;
    }
    
    clearscreen();              //PRINTS THE MEMBERS INFORMATION
    cout<<"\n\t\t\t\t\t\t\t|Students Record| \n\n";;
    cout<<"------------------------------------------------------------------------------------------------------------------------------------------";
    cout<<endl;
    cout << left << setw(15)<<"Role";
    cout<< setw(18) << "|Student Number";
    cout<< setw(28) << "|Student Name";
    cout<< setw(12) << "|Year";
    cout<< setw(13) << "|Course";
    cout<< setw(10) << "|Section";
    cout<< setw(28) << "|School Email";
    cout<< setw(15) << "|Contact Number"<<endl;
    cout<<endl;
    string role,studentnum,studentname,year,course,section,email,contactnum;

    while (getline(file, role, ',')){
        getline(file, studentnum, ',');
        getline(file, studentname, ',');
        getline(file, year, ',');
        getline(file, course, ',');
        getline(file, section, ',');
        getline(file, email, ',');
        getline(file, contactnum, '\n');

        cout<<left<<setw(15)<<(role.empty() ?"Unassigned" : role);
        cout<< setw(18) << studentnum;
        cout<< setw(28) << studentname;           
        cout<< setw(12) << year;
        cout<< setw(13) << course;
        cout<< setw(10) << section;
        cout<< setw(28) << email;
        cout<< setw(15) << contactnum<<endl; 
    }

    file.close();
    cout<<endl;
    pausescreen();
    clearscreen();
    menu();
}

void assignmembers(){                     //ASSIGN MEMBERS INTO THEIR ROLES
    clearscreen();
    
    string filename = username + "_members.csv";

    fstream file(filename, ios::in);      //LOAD MEMBERS INTO THE VECTOR
    if (!file) {
        cout << "Failed to open members.csv";
        pausescreen();
        clearscreen();
        insidelogin();
        return;
    }

    vector<vector<string> >members;       // Vector to store member records
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        vector<string> record;
        string field;

        while (getline(ss, field, ',')) {
            record.push_back(field);
        }

        members.push_back(record);
    }
    file.close();

    if (members.empty()) {
        cerr << "\033[1;31mNo members found in the organization. \033[0m" << endl;
        pausescreen();
        clearscreen();
        menu();
        return;
    }

    clearscreen();                        // DISPLAY MEMBERS ROLE
    cout << "\n\t\t\t| Members List of " << username << " |" << endl;
    cout<<"------------------------------------------\n";
    cout << left << setw(5) << "No.";
    cout << setw(15) << "Role";
    cout << setw(18) << "|Student Number";
    cout << setw(28) << "|Student Name" << endl;

    for (size_t i = 0; i < members.size(); ++i) {
        cout << left << setw(5) << i + 1;
        cout << setw(15) << (members[i][0].empty() ? "(Unassigned)" : members[i][0]);
        cout << setw(18) << members[i][1];
        cout << setw(28) << members[i][2] << endl;
    }

    int member_choice;
    cout << "\nEnter the number of the member to assign a role: ";
    cin >> member_choice;

    if (member_choice < 1 || member_choice > members.size()) {
        cerr << "\033[1;31mInvalid choice. Returning to main menu... \033[0m\n";
        pausescreen();
        clearscreen();
        menu();
        return;
    }

    
    cin.ignore(); 
    cout << "Enter the role for " << members[member_choice - 1][2] << ": ";       // ASSIGN A ROLE TO A MEMBER
    string new_role;
    getline(cin, new_role);

    
    members[member_choice - 1][0] = new_role;

    
    ofstream outfile(filename, ios::out | ios::trunc);          // UPDATE THE INFORMATION IN THE FILE
    if (!outfile) {
        cout << "Error writing to members file." << endl;
        pausescreen();
        clearscreen();
        menu();
        return;
    }

   for (size_t j = 0; j < members.size(); ++j) {
    for (size_t i = 0; i < members[j].size(); ++i) {
        outfile << members[j][i];
        if (i != members[j].size() - 1) {
            outfile << ",";
        }
    }
    outfile << endl;
    }

    outfile.close();

    cout << "\nRole assigned successfully!" << endl;
    pausescreen();
    clearscreen();
    menu();
}

void deleteorg(){
    char choice;
    string pass;
    ifstream file(username +".txt");
    if(!file.is_open()){
        cout<<"Error opening txt file\n";
        pausescreen();
        menu();
    }
    file.close();
    cout<<"Do you want to delete the organization? (Y/N): ";
    cin>>choice;

   if(choice == 'Y' || choice == 'y') {
    cout << "Are you sure you want to delete it? This action cannot be undone. (Y/N): ";
    cin >> choice;

    if(choice == 'Y' || choice == 'y') {
        cout << "Enter your password to delete the organization: ";
        cin >> pass;

        if (pass == password) {
            remove((username + ".txt").c_str());                    //REMOVE .TXT AND .CSV FILES FOR THE ORGANIZATION
            remove((username + "_members.csv").c_str());
            cout << "\nOrganization successfully deleted.\n";
            } else {
                cerr << "\033[1;31mIncorrect password: Could not delete the organization file.\033[0m\n";
                pausescreen();
                insidelogin();
            }
            pausescreen();
            menu(); 
         }else {
            cout << "The deletion is canceled.\n";
            pausescreen();
            insidelogin();  
        }
    } else {
        cout << "The deletion is canceled.\n";
        pausescreen();
        insidelogin();  
    }
}

//HI SIR ;>