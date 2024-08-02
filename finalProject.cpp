#include <iostream>
#include <cstdlib> //for system("clear") command
#include <ctime>   //to use time function while seeding
#include <map>
#include <string> //for string manipulation
using namespace std;

struct Node
{
    int patientID;
    string name;
    int age;
    int weight;
    char sex;
    Node *next;

    Node(int id, const string &n, int a, int w, char s) : patientID(id), name(n), age(a), weight(w), sex(s), next(NULL) {}
};

class DiabetesDetectionSystem
{
private:
    Node *head;
    map<int, int> riskScores; // Map to store risk scores (patientID -> riskScore)

public:
    DiabetesDetectionSystem() : head(NULL) {}

    ~DiabetesDetectionSystem(); // to free memory allocated to linked list at last

    void welcomeScreen();
    void fixAppointment();
    void proceedWithTestings();
    void generatePreReport();
    void generateFinalReport();
    void patientLogin();
    void generateTips();
    void adminLogin();
    void patientDataManagement();
    void viewPatientList();
    void editPatientDetails();
    void removePatient();
};

DiabetesDetectionSystem::~DiabetesDetectionSystem()
{
    Node *current = head;
    while (current != NULL)
    {
        Node *nextNode = current->next;
        delete current;
        current = nextNode;
    }
}

void DiabetesDetectionSystem::welcomeScreen()
{
    system("clear");

    cout << "==============================================================================\n";
    cout << "    W E L C O M E   T O   D I A B E T E S   D E T E C T I O N   S Y S T E M\n";
    cout << "==============================================================================\n\n";

    cout << "This program will help determine whether a person may have diabetes based on tests.\n";
    cout << "You can fix appointments, proceed with tests, generate reports, and more.\n\n";

    cout << "Press any key to continue...\n";

    // Wait for user input before proceeding
    cin.ignore(); // clear space from buffer
    cin.get();    // read single character and waits till user gives input
}

void DiabetesDetectionSystem::fixAppointment()
{
    system("clear"); // Clear the console screen

    cout << "=============================================\n";
    cout << "             F I X   A P P O I N T M E N T\n";
    cout << "=============================================\n\n";

    // Gather appointment details
    string name;
    int age;
    int weight;
    char sex;

    cout << "Enter your name: ";
    cin.ignore(); // Clear the newline character from the buffer
    getline(cin, name);

    cout << "Enter your age: ";
    cin >> age;

    cout << "Enter your weight: ";
    cin >> weight;

    cout << "Enter your sex (M/F): ";
    cin >> sex;
    sex = toupper(sex); // Convert to uppercase

    // Generate a unique ID (you can implement your own logic)
    srand(static_cast<unsigned int>(time(NULL))); // Seed for random number generation
    // to insure that whenever we run program difference seed is formed

    int uniqueID = rand() % 1000 + 1000;

    // Create a new node for the linked list
    Node *newNode = new Node(uniqueID, name, age, weight, sex);

    // Add the new node to the linked list
    newNode->next = head; // insertion at head
    head = newNode;

    // Display appointment details
    cout << "\nAppointment fixed successfully!\n";
    cout << "Your unique ID: " << uniqueID << "\n";
    cout << "Appointment Details:\n";
    cout << "Name: " << name << "\n";
    cout << "Age: " << age << "\n";
    cout << "Weight: " << weight << " kg\n";
    cout << "Sex: " << sex << "\n";

    cout << "\nPress any key to continue...\n";
    cin.ignore(); // Clear the newline character from the buffer
    cin.get();    // Wait for user input
}

void DiabetesDetectionSystem::proceedWithTestings()
{
    system("clear");

    cout << "=============================================\n";
    cout << "   P R O C E E D   W I T H   T E S T I N G S\n";
    cout << "=============================================\n\n";

    if (head == NULL)
    {
        cout << "No patients available. Please fix an appointment first.\n";
        cout << "\nPress any key to continue...\n";
        cin.ignore();
        cin.get();
        return;
    }

    int patientID;
    cout << "Enter your unique ID: ";
    cin >> patientID;

    Node *current = head;
    while (current != NULL && current->patientID != patientID)
    {
        current = current->next;
    }

    if (current == NULL)
    {
        cout << "Patient not found. Please check the unique ID.\n";
        cout << "\nPress any key to continue...\n";
        cin.ignore();
        cin.get();
        return;
    }

    char answer;
    int riskScore = 0;

    cout << "\nAnswer the following questions (Y for Yes, N for No):\n";

    cout << "1. Do you experience frequent thirst? ";
    cin >> answer;
    riskScore += (answer == 'Y' || answer == 'y') ? 1 : 0;

    cout << "2. Do you have a family history of diabetes? ";
    cin >> answer;
    riskScore += (answer == 'Y' || answer == 'y') ? 1 : 0;

    if (riskScores.find(patientID) == riskScores.end())
    {
        // If the patient is not in the map, add them
        riskScores[patientID] = riskScore;
    }
    else
    {
        // If the patient is already in the map, update their test score
        riskScores[patientID] += riskScore;
    }

    // Analyze the test results
    if (riskScores[patientID] >= 2)
        cout << "You need to go through the diabetes testing \n";
    else
        cout << "You have no major risk of having diabetes \n";
    cout << "\nPress any key to continue...\n";
    cin.ignore();
    cin.get();
}

void DiabetesDetectionSystem::generatePreReport()
{
    system("clear");

    cout << "=============================================\n";
    cout << "       G E N E R A T E   P R E - R E P O R T\n";
    cout << "=============================================\n\n";

    if (head == NULL)
    {
        cout << "No patients available. Please fix an appointment first.\n";
        cout << "\nPress any key to continue...\n";
        cin.ignore();
        cin.get();
        return;
    }

    int patientID;
    cout << "Enter your unique ID: ";
    cin >> patientID;

    Node *current = head;
    while (current != NULL && current->patientID != patientID)
    {
        current = current->next;
    }

    if (current == NULL)
    {
        cout << "Patient not found. Please check the unique ID.\n";
        cout << "\nPress any key to continue...\n";
        cin.ignore(); // to clear buffer
        cin.get();    // wait for user input
        return;
    }

    // Display patient details
    cout << "\nPatient Details:\n";
    cout << "Name: " << current->name << "\n";
    cout << "Age: " << current->age << "\n";
    cout << "Weight: " << current->weight << " kg\n";
    cout << "Sex: " << current->sex << "\n\n";

    // Display pre-report based on pre-testing questions
    cout << "Preliminary Report:\n";
    if (riskScores.find(patientID) != riskScores.end())
    {
        int preTestScore = riskScores[patientID];

        if (preTestScore >= 2)
        {
            cout << "High likelihood of diabetes based on pre-testing questions.\n";
        }
        else
        {
            cout << "Low likelihood of diabetes based on pre-testing questions.\n";
        }
    }
    else
    {
        cout << "No pre-testing data available for this patient.\n";
    }

    cout << "\nPress any key to continue...\n";
    cin.ignore();
    cin.get();
}

void DiabetesDetectionSystem::generateFinalReport()
{
    system("clear");

    cout << "=============================================\n";
    cout << "         G E N E R A T E   F I N A L   R E P O R T\n";
    cout << "=============================================\n\n";

    if (head == NULL)
    {
        cout << "No patients available. Please fix an appointment first.\n";
        cout << "\nPress any key to continue...\n";
        cin.ignore();
        cin.get();
        return;
    }

    int patientID;
    cout << "Enter your unique ID: ";
    cin >> patientID;

    Node *current = head;
    while (current != NULL && current->patientID != patientID)
    {
        current = current->next;
    }

    if (current == NULL)
    {
        cout << "Patient not found. Please check the unique ID.\n";
        cout << "\nPress any key to continue...\n";
        cin.ignore();
        cin.get();
        return;
    }

    // Display patient details
    cout << "\nPatient Details:\n";
    cout << "Name: " << current->name << "\n";
    cout << "Age: " << current->age << "\n";
    cout << "Weight: " << current->weight << " kg\n";
    cout << "Sex: " << current->sex << "\n\n";

    // Gather additional information for the final report
    char answer;
    int additionalScore = 0;

    cout << "Answer the following questions (Y for Yes, N for No):\n";

    // Additional questions
    cout << "1. Do you have a family history of diabetes? ";
    cin >> answer;
    if (answer == 'Y' || answer == 'y')
    {
        additionalScore += 2; // Adjust the score based on the answer
    }

    cout << "2. How often do you engage in physical exercise? (Low/Moderate/High) ";
    string exerciseLevel;
    cin >> exerciseLevel;
    if (exerciseLevel == "Low" || exerciseLevel == "low")
    {
        additionalScore += 1; // Adjust the score based on the answer
    }
    else if (exerciseLevel == "High" || exerciseLevel == "high")
    {
        additionalScore -= 1; // Adjust the score based on the answer
    }

    // Comprehensive testing based on pre-test score and additional information
    int finalTestScore = riskScores[patientID] + additionalScore;

    // Display final report based on comprehensive testing
    cout << "\nFinal Report:\n";
    cout << "Total Comprehensive Test Score: " << finalTestScore << "\n";

    if (finalTestScore >= 8)
    {
        cout << "High likelihood of diabetes. Consult a doctor for further evaluation.\n";
    }
    else if (finalTestScore >= 5)
    {
        cout << "Moderate risk of diabetes. Follow a healthy lifestyle and monitor your health.\n";
    }
    else
    {
        cout << "Low likelihood of diabetes. Maintain a healthy lifestyle to prevent risks.\n";
    }

    // Additional recommendations based on the test results
    if (finalTestScore >= 5)
    {
        cout << "\nAdditional Recommendations:\n";
        cout << "1. Consult with a healthcare professional for a detailed examination.\n";
        cout << "2. Adopt a balanced diet and engage in regular physical activity.\n";
        // Add more recommendations based on the test results
    }

    cout << "\nPress any key to continue...\n";
    cin.ignore(); // to clear buffer
    cin.get();    // wait for user input
}

void DiabetesDetectionSystem::patientLogin()
{
    system("clear");

    cout << "=====================================\n";
    cout << "        P A T I E N T   L O G I N\n";
    cout << "=====================================\n\n";

    if (head == NULL)
    {
        cout << "No patients available. Please fix an appointment first.\n";
        cout << "\nPress any key to continue...\n";
        cin.ignore();
        cin.get();
        return;
    }

    int patientID;
    cout << "Enter your unique ID: ";
    cin >> patientID;

    Node *current = head;
    while (current != NULL && current->patientID != patientID)
    {
        current = current->next;
    }

    if (current == NULL)
    {
        cout << "Patient not found. Please check the unique ID.\n";
        cout << "\nPress any key to continue...\n";
        cin.ignore();
        cin.get();
        return;
    }

    // Display patient details
    cout << "\nPatient Details:\n";
    cout << "Name: " << current->name << "\n";
    cout << "Age: " << current->age << "\n";
    cout << "Weight: " << current->weight << " kg\n";
    cout << "Sex: " << current->sex << "\n\n";

    // Display test reports (assuming you have stored them)
    if (riskScores.find(patientID) != riskScores.end())
    {
        int patientScore = riskScores[patientID];

        cout << "Test Report:\n";
        cout << "Comprehensive Test Score: " << patientScore << "\n";

        // Determine the risk level based on the test score
        cout << "Risk Level: ";
        if (patientScore > 10)
        {
            cout << "High risk of diabetes. Consult a doctor as soon as possible.\n";
        }
        else if (patientScore >= 5 && patientScore <= 10)
        {
            cout << "Low risk of diabetes. Monitor your health.\n";
        }
        else
        {
            cout << "No risk of diabetes. Maintain a healthy lifestyle.\n";
        }
    }
    else
    {
        cout << "No test report available for this patient.\n";
    }

    cout << "\nPress any key to continue...\n";
    cin.ignore();
    cin.get();
}

void DiabetesDetectionSystem::generateTips()
{
    system("clear");

    cout << "=====================================\n";
    cout << "           G E N E R A T E   T I P S\n";
    cout << "=====================================\n\n";

    // Seed for random tip generation
    srand(static_cast<unsigned>(std::time(NULL)));

    // Generate a random number to select a tip
    int tipNumber = std::rand() % 10; // Change 10 to the total number of tips

    cout << "Tips for Diabetes Prevention and Management:\n";

    switch (tipNumber)
    {
    case 0:
        cout << "1. Maintain a healthy diet rich in fruits, vegetables, and whole grains.\n";
        cout << "2.Cut sugar and refined carbohydrates from your diet.\n";
        cout << "3.Avoiding large portion sizes can help reduce insulin and blood sugar levels and decrease the risk of diabetes.\n";
        break;
    case 1:
        cout << "1. Monitor your blood sugar levels regularly as advised by your doctor.\n";
        cout << "2.Try to be intentionally active by taking a walk, dancing, lifting weights or swimming for 30 minutes, five days per week.\n";
        cout << "3.rinking water instead of other beverages may help control blood sugar and insulin levels, thereby reducing the risk of diabetes.\n";
        break;
    case 2:
        cout << "1. Regular physical activity is key; aim for at least 30 minutes a day.\n";
        cout << "2.Getting plenty of fiber is beneficial for gut health and weight management.\n";
        cout << "3.Consuming a good fiber source at each meal can help prevent spikes in blood sugar and insulin levels.\n";
        break;
    case 3:
        cout << "1. Stay hydrated by drinking plenty of water throughout the day.\n";
        cout << "2.Diabetes raises your risk of infection and slows healing, so treat even simple cuts and scrapes quickly. \n";
        cout << "3.Xpect to see your doctor two to four times a year.\n";
        break;
    case 4:
        cout << "1.Smoking is a risk factor for type 2 diabetes. Quitting smoking can improve overall health and reduce diabetes risk.\n";
        cout << "2.A1c blood tests to find out your average blood sugar for the past 2 to 3 months. \n";
        cout << "3.Managing your carbs can help keep your blood sugar under control. \n";
        break;
    case 5:
        cout << "1.Stay informed about diabetes prevention strategies and healthy lifestyle choices.\n";
        cout << "2.Choose high-fiber carbs, such as green vegetables, fruit, beans, and whole grains.\n";
        cout << "3.Diabetes makes heart disease more likely, so keep a close eye on your blood pressure and cholesterol. \n";
        break;
    case 6:
        cout << "1.Attend educational programs or consult with healthcare professionals for personalized advice.\n";
        cout << "2.Regular exercise can help you reach or maintain a healthy weight. \n";
        cout << "3.Try at least 30 minutes a day of aerobic exercise 5 days a week.\n";
        break;
    case 7:
        cout << "1.Be aware of your family history of diabetes. Genetics can play a role in diabetes risk.\n";
        cout << "2.Include strength training and stretching on some days.\n";
        cout << "3.When you’re sleep-deprived, you tend to eat more, and you can put on weight, which leads to health problems.\n";
        break;
    case 8:
        cout << "1.Use healthy oils in moderation, such as olive oil or canola oil.\n";
        cout << "2.People with diabetes who get enough sleep often have healthier eating habits and improved blood sugar levels.\n";
        cout << "3.tress and diabetes don't mix. Excess stress can elevate blood sugar levels. \n";
        break;
    case 9:
        cout << "1.If you choose to consume alcohol, do so in moderation. Limiting alcohol intake is beneficial for overall health.\n";
        cout << "2.t your annual physical, make sure you get a dilated eye exam, blood pressure check, foot exam, and screenings for other complications such as kidney damage, nerve damage, and heart disease.\n";
        cout << "3.Feeling more tired than usual may be a sign Diabetes level-2\n";
        break;
    default:
        cout << "1. Consult with your healthcare provider for personalized advice.\n";
        break;
    }

    cout << "\nPress any key to continue...\n";
    cin.ignore();
    cin.get();
}

void DiabetesDetectionSystem::viewPatientList()
{
    system("clear");
    cout << "=====================================\n";
    cout << "       V I E W   P A T I E N T   L I S T\n";
    cout << "=====================================\n\n";

    if (head == NULL)
    {
        cout << "No patients available.\n";
    }
    else
    {
        Node *current = head;
        while (current != NULL)
        {
            cout << "Patient ID: " << current->patientID << "\n";
            cout << "Name: " << current->name << "\n";
            cout << "Age: " << current->age << "\n";
            cout << "Weight: " << current->weight << " kg\n";
            cout << "Sex: " << current->sex << "\n\n";
            current = current->next;
        }
    }

    cout << "\nPress any key to continue...\n";
    cin.ignore();
    cin.get();
}

void DiabetesDetectionSystem::editPatientDetails()
{
    system("clear");
    cout << "=====================================\n";
    cout << "      E D I T   P A T I E N T   D E T A I L S\n";
    cout << "=====================================\n\n";

    int patientID;
    cout << "Enter the Patient ID to edit details: ";
    cin >> patientID;

    Node *current = head;
    while (current != NULL && current->patientID != patientID)
    {
        current = current->next;
    }

    if (current == NULL)
    {
        cout << "Patient not found. Please check the Patient ID.\n";
    }
    else
    {
        // Display current details
        cout << "Current Details:\n";
        cout << "Name: " << current->name << "\n";
        cout << "Age: " << current->age << "\n";
        cout << "Weight: " << current->weight << " kg\n";
        cout << "Sex: " << current->sex << "\n\n";

        // Update details
        cout << "Enter new details:\n";
        cout << "Name: ";
        cin >> current->name;
        cout << "Age: ";
        cin >> current->age;
        cout << "Weight: ";
        cin >> current->weight;
        cout << "Sex: ";
        cin >> current->sex;

        cout << "Details updated successfully.\n";
    }

    cout << "\nPress any key to continue...\n";
    cin.ignore();
    cin.get();
}

void DiabetesDetectionSystem::removePatient()
{
    system("clear");
    cout << "=====================================\n";
    cout << "          R E M O V E   P A T I E N T\n";
    cout << "=====================================\n\n";

    int patientID;
    cout << "Enter the Patient ID to remove: ";
    cin >> patientID;

    Node *current = head;
    Node *prev = NULL;

    while (current != NULL && current->patientID != patientID)
    {
        prev = current;
        current = current->next;
    }

    if (current == NULL)
    {
        cout << "Patient not found. Please check the Patient ID.\n";
    }
    else
    {
        if (prev == NULL)
        {
            // Removing the first node
            head = current->next;
        }
        else
        {
            prev->next = current->next;
        }

        delete current;
        cout << "Patient removed successfully.\n";
    }

    cout << "\nPress any key to continue...\n";
    cin.ignore();
    cin.get();
}

void DiabetesDetectionSystem::patientDataManagement()
{
    int option;
    do
    {
        system("clear");
        cout << "=====================================\n";
        cout << "     P A T I E N T   D A T A   M A N A G E M E N T\n";
        cout << "=====================================\n\n";

        cout << "1. View Patient List\n";
        cout << "2. Edit Patient Details\n";
        cout << "3. Remove Patient\n";
        cout << "4. Back to Admin Menu\n\n";

        cout << "Enter your choice: ";
        cin >> option;

        switch (option)
        {
        case 1:
            // View Patient List
            viewPatientList();
            break;
        case 2:
            // Edit Patient Details
            editPatientDetails();
            break;
        case 3:
            // Remove Patient
            removePatient();
            break;
        case 4:
            // Back to Admin Menu
            break;
        default:
            cout << "Invalid choice. Try again.\n";
            break;
        }

    } while (option != 4);
}

void DiabetesDetectionSystem::adminLogin()
{
    system("clear");

    cout << "=====================================\n";
    cout << "            A D M I N   L O G I N\n";
    cout << "=====================================\n\n";

    char username[20];
    char password[20];

    // admin credentials
    const char *adminUsername = "admin";
    const char *adminPassword = "admin123";

    cout << "Enter username: ";
    cin >> username;

    cout << "Enter password: ";
    cin >> password;

    if (strcmp(username, adminUsername) == 0 && strcmp(password, adminPassword) == 0)
    {
        // Admin authentication successful
        cout << "\nAdmin login successful.\n";
        int choice;
        do
        {
            cout << "\nAdmin Menu:\n";
            cout << "1. View Patient Data\n";
            cout << "2. Remove Patient\n";
            cout << "3. Logout\n";
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice)
            {
            case 1:
            {
                patientDataManagement();
                break;
            }
            case 2:
            {
                removePatient();
                break;
            }
            break;
            case 3:
                cout << "Logging out...\n";
                break;
            default:
                cout << "Invalid choice. Try again.\n";
                break;
            }

        } while (choice != 3);
    }
    else
    {
        cout << "\nInvalid username or password. Access denied.\n";
    }

    cout << "\nPress any key to continue...\n";
    cin.ignore();
    cin.get();
}

int main()
{
    cout << "\n\n\n\n\n--------JAYPEE INSTITUE OF INFORMATION AND TECHNOLOGY--------------\n\n\n";
    cout << "GROUP MEMBERS:\n";
    cout << "DEV CHAUDHARY 9922103069\n";
    cout << "KUSHAL KUMAR SHARMA 9922103070\n";
    cout << "RASENDRA KAUSHIK 9922103075\n";
    cout << "TUSHAR MANISHI 9922103086\n";
    cout << "Press any key to continue...\n";
    cin.ignore();
    cin.get();
    DiabetesDetectionSystem diabetesSystem;

    int choice;
    do
    {
        system("clear");
        cout << "=====================================\n";
        cout << " D I A B E T E S   D E T E C T I O N   S Y S T E M\n";
        cout << "=====================================\n\n";
        cout << "1. Patient Login\n";
        cout << "2. Admin Login\n";
        cout << "3.Fix Appointment\n";
        cout << "4.Proceed with Testing\n";
        cout << "5.Generate Pre Report\n";
        cout << "6.Generate Final Report\n";
        cout << "7.Generate Tips\n";
        cout << "8. Exit\n\n";

        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            // Call patient login function
            diabetesSystem.patientLogin();
            break;
        case 2:
            diabetesSystem.adminLogin();
            break;
        case 3:
            diabetesSystem.fixAppointment();
            break;
        case 4:
            diabetesSystem.proceedWithTestings();
            break;
        case 5:
            diabetesSystem.generatePreReport();
            break;
        case 6:
            diabetesSystem.generateFinalReport();
            break;
        case 7:
            diabetesSystem.generateTips();
            break;
        case 8:
            cout << "Exiting the Diabetes Detection System. Goodbye!\n";
            break;
        default:
           cout << "Invalid choice. Try again.\n";
            break;
        }

    } while (choice != 8);

    return 0;
}