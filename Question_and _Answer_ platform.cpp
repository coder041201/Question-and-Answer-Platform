/*
*DSA Mini Project

*Problem Statement:
    To implement an interactive Question and Answer platform where anyone can Ask and Answer 
    Questions anonymously.

*Contribuitors:
    Roll no.    Name
    2303        Aparna Agrawal
    2312        Hardiki Sonchhatra
    2317        Khushbu Bora
    2326        Sudha Chintake
*/

#include <iostream>
#include <vector>
#include <string>

using namespace std;

//Passwpord for Admin mode
#define password "H15k"

#define questions_per_page 5

//Class question and answer
class Question_Answer
{
    string question;
    //Taking question input
    void accept_question()
    {
        cout << endl;

        cout << "Enter question (End with '?')" << endl;

        cin.ignore();
        //using getline to input line and using '?' as delimenator
        getline(cin, question, '?');

        //setting answered to false
        answered = false;
    }

    //Displaying question and answer
    void display()
    {
        cout << question << '?' << endl;
        if (answered)
        {
            cout << "Ans: " << answer << endl;
        }
        else
        {
            cout << "This question is not answered" << endl;
        }
        cout << endl;
    }

    //Inputting answer
    void accept_answer()
    {
        cout << question << '?' << endl;
        cout << "Enter answer (press enter 2 times when you are done)" << endl;

        cin.ignore(); //Extra '\n'

        string line;
        do
        {
            getline(cin, line);
            answer += line;
        } while (line != "");
        answered = true;
    }

public:
    //boolean variable to check whether question is answered or not
    string answer;
    bool answered;

    //making question_answer_data as a friend
    friend class question_answer_data;
};

//class for storing actual QnA data
class question_answer_data
{
    //vector of topics
    vector<string> topic;

    //matrix of Question_Answer object
    vector<vector<Question_Answer>> database;

public:
    //Accepting topicwise questions
    void accept_question_by_topic(string subject)
    {

        //Asking user to check database , so no repeated questions
        cout << "Check whether your question has been added before:)" << endl;
        cout << endl;

        if (display_by_topic(subject) != 0)
        {
            char already_added;
            cout << endl;
            cout << "Enter 'y' if your question was present in displayed list (else enter any other character to continue)" << endl;
            cin >> already_added;

            //returning if question already present
            if (already_added == 'y' || already_added == 'Y')
                return;
        }

        //iterator variable
        int i = 0;

        //boolean variable to check topic is already present or not
        bool found = false;

        for (i = 0; i < topic.size(); i++)
        {

            //If topic found, simply adding question to the vector
            if (topic[i] == subject)
            {
                found = true;
                Question_Answer temp;
                temp.accept_question();
                database[i].push_back(temp);
                return;
            }
        }

        //if topic not found
        if (!found)
        {
            //Adding new topic
            topic.push_back(subject);

            //Adding new question to given topic
            Question_Answer temp;
            temp.accept_question();

            //creating temprory vector to push in database
            vector<Question_Answer> t;
            t.push_back(temp);
            database.push_back(t);

            return;
        }
    }

    //Displaying questions by topic
    int display_by_topic(string subject)
    {
        //Displaying topic name
        cout << endl;
        cout << "Topic: " << subject << endl;
        cout << endl;

        //if there are no questions present
        if (topic.size() == 0)
        {
            cout << "Nothing to display" << endl;
            return 0;
        }

        int i = 0;
        int count = 0;

        //Iterating topic vector till given topic is found
        for (i = 0; i < topic.size(); i++)
        {
            if (topic[i] == subject)
                break;
        }

        //When given topic is not present in vector
        if (i == topic.size())
        {
            cout << "Nothing to display" << endl;
            return 0;
        }

        //Displaying QnA for given topic
        for (int j = database[i].size() - 1; j >= 0; j--)
        {
            //calling Question_Answer display method
            database[i][j].display();

            //Keeping count of displayed questions
            count++;

            //Displaying only previously defined number of QnA at a time
            if (count % questions_per_page == 0 && j > 0)
            {
                cout << endl;

                //Asking user whether he want to see more
                cout << "For more questions type y (else type any other char)" << endl;
                char x;
                cin >> x;

                if (x == 'y' || x == 'Y')
                {
                    continue;
                }
                else
                    break;
            }
        }
        return 1;
    }

    //Displaying all QnA
    void display_all()
    {
        //Keeping count of displayed questions
        int count = 0;

        //Traversing through matrix
        for (int i = 0; i < database.size(); i++)
        {
            for (int j = database[i].size() - 1; j >= 0; j--)
            {

                //calling Question_Answer display method
                database[i][j].display();

                count++;

                //Displaying only previously defined no. of QnA at a time
                if (count % questions_per_page == 0 && i > 0 && j > 0)
                {
                    cout << endl;

                    //Asking user whether he want to see more
                    cout << "For more questions type y (else type any other char)" << endl;
                    char x;
                    cin >> x;

                    if (x == 'y' || x == 'Y')
                    {
                        continue;
                    }
                    else
                    {
                        break;
                    }
                }
            }
        }
    }

    //Displaying all unanswered questions and asking user for answers
    void display_all_unanswered()
    {

        //question no. input from user to which he/she wants to answer
        int question_number;

        char x;

        //Variable for keeping track of displayed questions
        int number_of_unanswerd = 0;

        //Vector to store indices
        vector<int> unanswerd_j_index;
        vector<int> unanswerd_i_index;

        //Traversing through QnA matrix
        for (int i = database.size() - 1; i >= 0; i--)
        {
            for (int j = database[i].size() - 1; j >= 0; j--)
            {
                //checking whether answered or not
                if (!database[i][j].answered)
                {
                    //Adding indices of unanswered question
                    unanswerd_j_index.push_back(j);
                    unanswerd_i_index.push_back(i);

                    //Updating count
                    number_of_unanswerd++;

                    //Displaying questions
                    cout << "Q." << number_of_unanswerd << " " << database[i][j].question << '?' << endl;

                    //Displaying only previously defined no. of questions at a time
                    if (number_of_unanswerd % questions_per_page == 0)
                    {
                        cout << endl;

                        //Asking user whether he wants to add answer to any question
                        cout << "If you want to answer any of these question type y (else type any other char)";
                        cin >> x;

                        //Accepting answer
                        if (x == 'y' || x == 'Y')
                        {
                            cout << "Enter question number" << endl;
                            cin >> question_number;

                            cout << endl;

                            //Accessing particular QnA through question no. and size and accepting ans
                            database[unanswerd_i_index[question_number - 1]][unanswerd_j_index[question_number - 1]].accept_answer();
                        }

                        //Asking user whether he want to see more
                        if (i != 0 || j != 0)
                        {
                            cout << "For more questions type y (else type any other char)" << endl;
                            cin >> x;

                            cout << endl;
                        }

                        //If user wants to see more Questions
                        if (x == 'y' || x == 'Y')
                        {
                            continue;
                        }

                        else
                            break;
                    }
                }
            }
        }
        //For last questions if any
        if (number_of_unanswerd % questions_per_page != 0)
        {
            cout << endl;
            cout << "If you want to answer any of these question type y (else type any other char)";
            cin >> x;

            if (x == 'y' || x == 'Y')
            {
                cout << "Enter question number" << endl;
                cin >> question_number;

                database[0][unanswerd_j_index[question_number - 1]].accept_answer();
            }
        }

        //When all questions are answered
        if (number_of_unanswerd == 0)
        {
            cout << "No unanswered questions!!" << endl;
        }
    }

    //Displaying all answered questions
    void display_all_answered()
    {
        //Keeping count
        int count = 0;
        char x;

        //Traversing through Qna matrix
        for (int i = database.size() - 1; i >= 0; i--)
        {
            for (int j = database[i].size() - 1; j >= 0; j--)
            {
                cout << endl;

                //Displaying if answered
                if (database[i][j].answered)
                {
                    database[i][j].display();
                    count++;

                    //Displaying only previously defined no. of questions at a time
                    if (count % questions_per_page == 0)
                    {
                        //Asking user whether he want to see more
                        cout << "For more questions type y (else type any other char)";
                        cin >> x;
                        if (x == 'y' || 'Y')
                        {
                            continue;
                        }
                        else
                        {
                            break;
                        }
                    }
                }
            }
        }
    }

    //Removing particular element from matrix
    void remove_ques()
    {
        string subject;
        int index;

        //Asking for topic
        cout << "Enter the topic " << endl;
        cin >> subject;

        //When topic vector is empty
        if (topic.size() == 0)
        {
            cout << "Nothing to display" << endl;
            return;
        }

        int i = 0;

        cout << endl;

        //Displaying topic name
        cout << "Topic: " << subject << endl;

        cout << endl;

        //Iterating topic vector till given topic is found
        for (i = 0; i < topic.size(); i++)
        {
            if (topic[i] == subject)
                break;
        }

        //When given topic is not found
        if (i == topic.size())
        {
            cout << "Nothing to display" << endl;
            return;
        }

        //if given topic found
        for (int j = 0; j < database[i].size(); j++)
        {
            //Displaying all questions of that topic with index
            cout << "Q." << j << " ";
            database[i][j].display();
        }

        //Accepting index for which QnA to be removed
        cout << "Enter the index of the Question you want to delete" << endl;
        cin >> index;

        //Using inbuilt vector function to remove element
        database[i].erase(database[i].begin() + index);
        cout << "Question successfully Removed" << endl;
    }

    //Removing answer of particular question of specific topic
    void remove_ans()
    {

        int index;

        string subject;

        // Asking for topic
        cout << "Enter the Topic" << endl;
        cin >> subject;

        //When topic vector is empty
        if (topic.size() == 0)
        {
            cout << "Nothing to display" << endl;
            return;
        }

        int i = 0;

        cout << endl;

        //Displying topic
        cout << "Topic: " << subject << endl;

        cout << endl;

        //Iterating topic vector till given topic is found
        for (i = 0; i < topic.size(); i++)
        {
            if (topic[i] == subject)
                break;
        }

        //When given topic is not found
        if (i == topic.size())
        {
            cout << "Nothing to display" << endl;
            return;
        }

        //if given topic found
        for (int j = 0; j < database[i].size(); j++)
        {
            //Displaying all answered questions
            if (database[i][j].answered = true)
            {
                cout << "Q." << j << " ";
                database[i][j].display();
            }
        }

        //Asking admin to enter the index for which answer to be removed
        cout << "Enter index of the question of which you want to delete the answer" << endl;
        cin >> index;

        //Setting answer to null of given index
        database[i][index].answer = "\0";

        //Swetting boolean value of given index to false
        database[i][index].answered = false;

        cout << "Answer Successfully Removed" << endl;
    }
};

int main()
{
    //Creating object of main database
    question_answer_data Q;

    //outer do while loop
    int choice;
    do
    {
        //Displaying outer MENU
        cout << endl;
        cout << "====================================================================================" << endl;
        cout << "Enter 0 if you are user" << endl;
        cout << "OR 1 if you want to access admin function" << endl;
        cout << "(type any no. key to exit)" << endl;
        cout << "=====================================================================================" << endl;
        cout << endl;

        cin >> choice;

        //User mode
        if (choice == 0)
        {
            //Inner do while loop 1
            int ch;
            do
            {
                cout << endl;
                //Displaying user MENU
                cout << "==============================================================================" << endl;
                cout << "************MENU************" << endl;
                cout << "1.Add new question of particular topic" << endl;
                cout << "2.Display questions and answers of specific topic" << endl;
                cout << "3.Display all questions and answers" << endl;
                cout << "4.Display all answered questions (with their answers)" << endl;
                cout << "5.Display all unanswered questions (also add their answers if you want to)" << endl;
                cout << "6.Exit" << endl;
                cout << "==============================================================================" << endl;
                cout << endl;
                cout << "Enter your choice" << endl;

                cin >> ch;

                //Inner switch case1 (User)
                switch (ch)
                {
                case 1:
                {
                    cout << endl;
                    //Accepting topic from user
                    cout << "Enter Topic" << endl;
                    string topic;
                    cin >> topic;

                    Q.accept_question_by_topic(topic);
                }
                break;
                case 2:
                {
                    //Accepting topic from user
                    cout << "Enter Topic" << endl;
                    string topic;
                    cin >> topic;

                    Q.display_by_topic(topic);
                }
                break;
                case 3:
                {
                    Q.display_all();
                }
                break;
                case 4:
                {
                    Q.display_all_answered();
                }
                break;
                case 5:
                {
                    Q.display_all_unanswered();
                }
                break;
                case 6:
                {
                    cout << "Exiting" << endl;
                    cout << endl;
                }
                break;
                default:
                    cout << "Invalid choice" << endl;
                }

            } while (ch != 6);
        }

        //Admin mode
        else if (choice == 1)
        {
            string pass;
            cout << endl;

            //Asking user to enter password
            cout << "Enter password to access admin functions (you only have one chance)" << endl;

            cin >> pass;

            //Providing access only if password is correct
            if (pass == password)
            {

                //Inner do while loop 2
                int ch;

                do
                {
                    cout << endl;
                    //Displaying admin menu
                    cout << "=====================================================================================" << endl;
                    cout << "Press 1 to remove question by topic" << endl;
                    cout << "Press 2 to remove answer of question of specific topic" << endl;
                    cout << "Press 3 to exit" << endl;
                    cout << "=====================================================================================" << endl;
                    cout << endl;

                    cout << "Enter choice" << endl;

                    cin >> ch;

                    //Inner switch case 2 (Admin mode)
                    switch (ch)
                    {
                    case 1:
                    {
                        Q.remove_ques();
                    }
                    break;
                    case 2:
                    {
                        Q.remove_ans();
                    }
                    break;
                    case 3:
                    {
                        cout << "Exiting" << endl;
                        cout << endl;
                    }
                    break;
                    default:
                        cout << "Invalid choice" << endl;
                    }

                } while (ch != 3);
            }

            //When password is wrong...(no multiple chance for correct password)
            else
            {
                cout << "Wrong password... access denied!!" << endl;
            }
        }
        else
        {
            cout << "Exiting" << endl;
        }

    } while (choice == 0 || choice == 1);
}

/*
OUTPUT
*/
