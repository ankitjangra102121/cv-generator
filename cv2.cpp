#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <regex>

using namespace std;

void registerUser (const string &username, const string &password)
{
    ifstream infile("users.csv");
    string line, storedUsername;

    while (getline(infile, line))
    {
        stringstream ss(line);
        getline(ss, storedUsername, ','); 
        if (storedUsername == username) 
        {
            cout << "Error: Username '" << username << "' already exists. Please choose a different username." << endl;
            infile.close();
            return;
        }
    }
    infile.close();

    ofstream file("users.csv", ios::app);
    file << username << "," << password << endl; 
    cout << "Registration successful!" << endl;
}

bool login(string &username, const string &password)
{
    ifstream file("users.csv");
    string line, storedUsername, storedPassword;

    while (getline(file, line))
    {
        stringstream ss(line);
        getline(ss, storedUsername, ',');
        getline(ss, storedPassword, ',');

        if (storedUsername == username && storedPassword == password)
        {
            cout << "Login Successful\n";
            return true;
        }
    }
    cout << "Login Failed\n";
    return false;
}

string generateFilename(const string &name)
{
    string formattedName = name;
    for (char &c : formattedName)
    {
        if (isspace(c))
        {
            c = '_';
        }
    }
    return formattedName + ".pdf";
}

void saveToCSV(const string &filename, const string &username, const string &name, const string &email, const string &phone,
               const string &address, const string &linkedin_username, const string &github_username)
{
    ifstream infile(filename);
    bool fileIsEmpty = infile.peek() == ifstream::traits_type::eof();
    infile.close();

    ofstream file(filename, ios::app);
    if (file.is_open())
    {
        if (fileIsEmpty)
        {
            file << "Username,Name,Email,Phone,Address,LinkedIn ID,GitHub ID";
        }
        file << username << ","
             << name << ","
             << email << ","
             << phone << ","
             << address << ","
             << linkedin_username << ","
             << github_username
             << endl;

        file.close();
    }
    else
    {
        cout << "Error: Could not open file " << filename << endl;
    }
}

void addWorkExperience(vector<string> &work_experience)
{
    int num_entries;
    cout << "How many work experience entries do you want to add? ";
    cin >> num_entries;
    cin.ignore();
    if (num_entries <= 0)
    {
        return;
    }
    else
    {
        for (int i = 0; i < num_entries; ++i)
        {
            string Job_Title, Job_CompanyName, Job_CityState, Job_Duration;
            stringstream experiences_ss;

            cout << "Enter Job Title " << (i + 1) << ": ";
            getline(cin, Job_Title);

            cout << "Enter Company Name " << (i + 1) << ": ";
            getline(cin, Job_CompanyName);

            cout << "Enter City and State " << (i + 1) << ": ";
            getline(cin, Job_CityState);

            cout << "Enter Duration: ";
            getline(cin, Job_Duration);

            experiences_ss << "\\section*{Work Experience}"
                           << "\\resitem{ Job Title - " << Job_Title << "}{" << Job_CompanyName << ", " << Job_CityState << " \\\\ "
                           << Job_Duration << "}\n"
                           << "\\begin{itemize}\n";

            for (int j = 0; j < 3; ++j)
            {
                string responsibility;
                cout << "Enter responsibility " << (j + 1) << " for " << Job_Title << ": ";
                getline(cin, responsibility);
                experiences_ss << "    \\item " << responsibility << "\n";
            }

            experiences_ss << "\\end{itemize}\n\n";
            work_experience.push_back(experiences_ss.str());
        }
    }
}

void addProjects(vector<string> &projects)
{
    int num_projects;
    cout << "How many projects do you want to add? ";
    cin >> num_projects;
    cin.ignore();
    if (num_projects <= 0)
    {
        return;
    }
    else
    {
        for (int i = 0; i < num_projects; ++i)
        {
            string project_name, project_description, project_technologies;
            stringstream project_ss;
            cout << "Enter project name for project " << (i + 1) << ": ";
            getline(cin, project_name);

            cout << "Enter project description for project " << (i + 1) << ": ";
            getline(cin, project_description);

            cout << "Enter technologies used for project " << (i + 1) << ": ";
            getline(cin, project_technologies);

            project_ss << "\\section*{Projects}"
                       << "\\vspace{0.5cm}"
                       << "\\textbf{Project Name: " << project_name << "} \n"
                       << "\\begin{itemize}\n"
                       << " \\item Description: " << project_description << "\n"
                       << " \\item Technologies: " << project_technologies << "\n"
                       << "\\end{itemize}\n";
            projects.push_back(project_ss.str());
        }
    }
}

void addCertifications(vector<string> &Exp_certifications)
{
    int num_certificates;
    cout << "How many certification entries do you want to add? ";
    cin >> num_certificates;
    cin.ignore();
    if (num_certificates <= 0)
    {
        return;
    }
    else
    {
        for (int i = 0; i < num_certificates; ++i)
        {
            string cert_name, cert_institution, cert_date;
            stringstream certification_ss;

            cout << "Enter Certification Name " << (i + 1) << ": ";
            getline(cin, cert_name);

            cout << "Enter Issuing Institution " << (i + 1) << ": ";
            getline(cin, cert_institution);

            cout << "Enter Date of Certification: ";
            getline(cin, cert_date);

            certification_ss << "\\section*{Certifications}"
                             << "\\resitem{Certification: " << cert_name << "}{" << cert_institution << " \\\\ "
                             << cert_date << "}\n";

            Exp_certifications.push_back(certification_ss.str());
        }
    }
}

void addExtracurricularActivities(vector<string> &extracurricular_activities)
{
    int num_extraCurricular;
    cout << "How many extracurricular activities do you want to add? ";
    cin >> num_extraCurricular;
    cin.ignore();
    if (num_extraCurricular <= 0)
    {
        return;
    }
    else
    {
        for (int i = 0; i < num_extraCurricular; ++i)
        {
            string Activity_Name, Role, Contribution;
            stringstream activities_ss;

            cout << "Enter Activity Name " << (i + 1) << ": ";
            getline(cin, Activity_Name);

            cout << "Enter your Role in " << Activity_Name << ": ";
            getline(cin, Role);

            cout << "Enter Contribution or Achievement in " << Activity_Name << ": ";
            getline(cin, Contribution);

            activities_ss << "\\section*{Extracurricular Activities}"
                          << "\\resitem{Activity: " << Activity_Name << "}\n"
                          << "\\begin{itemize}\n"
                          << "    \\item Role: " << Role << "\n"
                          << "    \\item Contribution: " << Contribution << "\n"
                          << "\\end{itemize}\n\n";

            extracurricular_activities.push_back(activities_ss.str());
        }
    }
}

void addInternshipExperience(vector<string> &internship_experience)
{
    int num_Intern;
    cout << "How many internship entries do you want to add? ";
    cin >> num_Intern;
    cin.ignore();
    if (num_Intern <= 0)
    {
        return;
    }
    else
    {
        for (int i = 0; i < num_Intern; ++i)
        {
            string Intern_Title, Intern_CompanyName, Intern_CityState, Intern_Duration;
            stringstream Internexperiences_ss;

            cout << "Enter Internship Title " << (i + 1) << ": ";
            getline(cin, Intern_Title);

            cout << "Enter Company Name " << (i + 1) << ": ";
            getline(cin, Intern_CompanyName);

            cout << "Enter City and State " << (i + 1) << ": ";
            getline(cin, Intern_CityState);

            cout << "Enter Duration: ";
            getline(cin, Intern_Duration);

            Internexperiences_ss << "\\section * {Internship Experience}"
                                 << "\\resitem{Internship Title - " << Intern_Title << "}{" << Intern_CompanyName << ", " << Intern_CityState << " \\\\ "
                                 << Intern_Duration << "}\n"
                                 << "\\begin{itemize}\n";

            for (int j = 0; j < 3; ++j)
            {
                string task;
                cout << "Enter task/responsibility " << (j + 1) << " for " << Intern_Title << ": ";
                getline(cin, task);
                Internexperiences_ss << "    \\item " << task << "\n";
            }

            Internexperiences_ss << "\\end{itemize}\n\n";

            internship_experience.push_back(Internexperiences_ss.str());
        }
    }
}

bool validatename(const string &name)
{
    regex namePattern("^[A-Za-z]+(?:[\\s'-][A-Za-z]+)*$");
    return regex_match(name, namePattern);
}

bool validateemail(const string &email)
{
    const regex pattern(R"((\w+)(\.?)(\w*)@gmail\.com)");
    return regex_match(email, pattern);
}

bool validatePhoneNumber(string &phone)
{
    const regex pattern(R"(^\d{10}$)");
    return regex_match(phone, pattern);
}


void replacePlaceholder(string &templateContent, const string &placeholder, const string &value)
{
    size_t pos = 0;
    while ((pos = templateContent.find(placeholder, pos)) != string::npos)
    {
        templateContent.replace(pos, placeholder.length(), value);
        pos += value.length();
    }
}

string joinVector(const vector<string> &vec, const string &delimiter)
{
    ostringstream result;
    for (size_t i = 0; i < vec.size(); ++i)
    {
        result << vec[i];
        if (i != vec.size() - 1)
            result << delimiter;
    }
    return result.str();
}


void deleteUserData(const string &filename, const string &username)
{
    ifstream infile(filename);
    if (!infile.is_open())
    {
        cerr << "Error: Could not open " << filename << endl;
        return;
    }

    string line;
    vector<string> lines;
    bool userFound = false;
    while (getline(infile, line))
    {
        string storedUsername;
        stringstream ss(line);
        getline(ss, storedUsername, ',');

        cout << "Checking username: " << storedUsername << endl;

        if (storedUsername != username)
        {
            lines.push_back(line); 
        }
        else
        {
            userFound = true;
            cout << "User  found: " << storedUsername << endl;
        }
    }
    infile.close();

    if (!userFound)
    {
        cout << "No data found for the user with username: " << username << endl;
        return;
    }

    ofstream outfile(filename);
    if (outfile.is_open())
    {
        for (const string &l : lines)
        {
            outfile << l << endl;
        }
        outfile.close();
        cout << "User  data deleted successfully from " << filename << endl;
    }
    else
    {
        cout << "Error: Could not open file " << filename << " for writing." << endl;
    }
}

int menu()
{
    cout << "1. Register\n";
    cout << "2. Login\n";
    cout << "3. Exit\n";
}

int loggingin(string &cuser)
{
    int choice;
    string username, password;

    while (true)
    {
        menu();
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "Enter a username: ";
            cin >> username;
            cuser = username;
            cout << "Enter a password: ";
            cin >> password;
            registerUser(username, password);
            break;
        case 2:
            cout << "Enter your username: ";
            cin >> username;
            cuser = username;
            cout << "Enter your password: ";
            cin >> password;
            if (login(username, password))
            {
                return 1;
            }
            else
            {
                return 0;
            }
            break;
        case 3:
            cout << "Exiting..." << endl;
            return 0;
        default:
            cout << "Invalid choice! Please try again." << endl;
        }
    }
    return 0;
}

int main()
{
    string username;
    if (!loggingin(username))
    {
        return 0;
    }
    cout << username << endl;
    

    string templateFileNames[] = {
        "template1.tex",
        "template2.tex",
        "template3.tex"};
    cout << "Resume Types:" << endl;
    cout << "1: Fresher Resume" << endl;
    cout << "2: Experienced Resume" << endl;
    cout << "3: Internship Resume" << endl;

    int templateChoice;
    cout << "Choose the type of resume (1-3): ";
    cin >> templateChoice;
    cin.ignore();

    string templateFileName;
    switch (templateChoice)
    {
    case 1:
        templateFileName = templateFileNames[0];
        break;
    case 2:
        templateFileName = templateFileNames[1];
        break;
    case 3:
        templateFileName = templateFileNames[2];
        break;
    default:
        cout << "Invalid choice. Exiting." << endl;
        return 1;
    }
    string name, email, phone, address, linkedin_username, github_username;

    do
    {
        cout << "Enter your Name: ";
        getline(cin, name);
        if (!validatename(name))
        {
            cout << "Invalid name!!!" << endl;
        }
    } while (!validatename(name));

    cout << "Enter your Address: ";
    getline(cin, address);

    cout << "Enter your LinkedIn Link: ";
    getline(cin, linkedin_username);

    cout << "Enter your Github username: ";
    getline(cin, github_username);

    do
    {
        cout << "Enter your email id: ";
        getline(cin, email);
        if (!validateemail(email))
        {
            cout << "Invalid email id. Please enter a valid email id." << endl;
        }
    } while (!validateemail(email));

    do
    {
        cout << "Enter your phone number: ";
        getline(cin, phone);
        if (!validatePhoneNumber(phone))
        {
            cout << "Invalid phone number. Please enter a valid phone number." << endl;
        }
    } while (!validatePhoneNumber(phone));

    string Prof_Summary, Prof_Achievements, objective;
    if (templateChoice == 2)
    {
        cout << "Enter your Profession in brief: ";
        getline(cin, Prof_Summary);
        cout << "Enter your Professional Achievements: ";
        getline(cin, Prof_Achievements);
    }
    else
    {
        cout << "Enter the objective: ";
        getline(cin, objective);
    }

    string edu_degree, edu_university, edu_graduationYear, edu_branch, edu_course, extracurricular_achievements;
    cout << "Enter your degree: ";
    getline(cin, edu_degree);

    cout << "Enter your university: ";
    getline(cin, edu_university);

    cout << "Enter your graduation year: ";
    getline(cin, edu_graduationYear);

    cout << "Enter your Branch: ";
    getline(cin, edu_branch);

    cout << "Enter your Relevant Coursework: ";
    getline(cin, edu_course);

    string skills_1, skills_2;
    cout << "Enter your skills(Expertise): ";
    getline(cin, skills_1);

    cout << "Enter your skills(Strong competencies): ";
    getline(cin, skills_2);

    cout << "Enter the Achievenments: ";
    getline(cin, extracurricular_achievements);

    vector<string> projects;
    addProjects(projects);

    vector<string> work_experience, Exp_certifications, extracurricular_activities, internship_experience;
    if (templateChoice == 2)
    {
        addWorkExperience(work_experience);
        addCertifications(Exp_certifications);
    }
    else
    {
        addInternshipExperience(internship_experience);
        addExtracurricularActivities(extracurricular_activities);
    }

    ifstream templateFile(templateFileName);
    if (!templateFile.is_open())
    {
        cerr << "Failed to open template file." << endl;
        return 1;
    }

    string templateContent((istreambuf_iterator<char>(templateFile)), istreambuf_iterator<char>());
    templateFile.close();

    replacePlaceholder(templateContent, "Your Name", name);
    replacePlaceholder(templateContent, "Your Address", address);
    replacePlaceholder(templateContent, "Your Email", email);
    replacePlaceholder(templateContent, "Your Phone Number", phone);
    replacePlaceholder(templateContent, "LinkedIn Profile", linkedin_username);
    replacePlaceholder(templateContent, "Github Profile", github_username);
    replacePlaceholder(templateContent, "[Your Major]", edu_branch);
    replacePlaceholder(templateContent, "Bachelor of Science", edu_degree);
    replacePlaceholder(templateContent, "University Name, City, State", edu_university);
    replacePlaceholder(templateContent, "GYear", edu_graduationYear);
    replacePlaceholder(templateContent, "[Courses]", edu_course);
    replacePlaceholder(templateContent, "objectivex", objective);
    replacePlaceholder(templateContent, "projects", joinVector(projects, ""));
    replacePlaceholder(templateContent, "work experiencess", joinVector(work_experience, ""));
    replacePlaceholder(templateContent, "certificates", joinVector(Exp_certifications, ""));
    replacePlaceholder(templateContent, "ExtraxCurricularxActivities", joinVector(extracurricular_activities, ""));
    replacePlaceholder(templateContent, "InternxExperience", joinVector(internship_experience, ""));
    replacePlaceholder(templateContent, "skills1", skills_1);
    replacePlaceholder(templateContent, "skills2", skills_2);
    replacePlaceholder(templateContent, "[Prfessionalx Summary]", Prof_Summary);
    replacePlaceholder(templateContent, "Professionalxx accomplishments, KPIs", Prof_Achievements);
    replacePlaceholder(templateContent, "Academic and extracurricular achievements", extracurricular_achievements);

    ofstream outputFile("cv2.tex");
    if (!outputFile.is_open())
    {
        cerr << "Error: Could not write to cv2.tex" << endl;
        return 1;
    }
    outputFile << templateContent;

    outputFile.close();

    saveToCSV("cv2.csv", username, name, email, phone, address, linkedin_username, github_username);

    char downloadOption;
    cout << "Do you want to generate and download the PDF? (y/n): ";
    cin >> downloadOption;

    if (downloadOption == 'y' || downloadOption == 'Y')
    {
        string filename = generateFilename(name);
        string pdflatexCommand = "pdflatex -jobname=" + filename.substr(0, filename.length() - 4) + " cv2.tex";
        int result = system(pdflatexCommand.c_str());
        if (result == 0)
        {
            cout << "PDF generated successfully." << endl;
        }
        else
        {
            cout << "Error generating PDF." << endl;
        }
    }
    else
    {
        cout << "PDF generation skipped." << endl;
    }
    char deleteOption;
    cout << "Do you want to delete your data from the system? (y/n): ";
    cin >> deleteOption;

    if (deleteOption == 'y' || deleteOption == 'Y')
    {
        deleteUserData("cv2.csv", username);
    }
    else
    {
        cout << "Data retained." << endl;
    }

    return 0;
}