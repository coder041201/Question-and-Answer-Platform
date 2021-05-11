#include <iostream>
#include <vector>
#include <string>
using namespace std;

//Class qna
class Question_Answer
{
    string question;
    string answer;

public:
    bool answered;

    void accept_question()
    {
        cout << "Enter question (End with '?')" << endl;
        getline(cin, question, '?');
        answered = false;
    }
    void display()
    {
        cout << question << endl;
        if (answered)
        {
            cout << answer << endl;
        }
        else
        {
            cout << "This question is not answered" << endl;
        }
    };

    friend class question_answer_data;
};

// class topics
// {
//     string topic;

//     vector<Question_Answer> data;

//     void accept_questions_wrt_topic();

//     void display_topic(string subject)
//     {
//         cout << topic << endl;
//         for (int i = 0; i < data.size(); i++)
//         {
//             data[i].display();
//         }
//     }

//     void display_by_topic_questions(string subject);

//     void display_by_topic_answered(string subject);

//     friend class question_answer_data;
// };

class question_answer_data
{
    vector<string> topic;
    vector<vector<Question_Answer>> database;

public:
    void accept_question_by_topic(string subject)
    {

        int i = 0;
        bool found = false;

        for (i = 0; i < topic.size(); i++)
        {
            cout << " in outer loop" << endl;
            if (topic[i] == subject)
            {

                found = true;
                Question_Answer temp;
                temp.accept_question();
                database[i].push_back(temp);
                return;
            }
        }

        if (!found)
        {
            topic.push_back(subject);
            Question_Answer temp;
            temp.accept_question();

            vector<Question_Answer> t;
            t.push_back(temp);

            database.push_back(t);

            return;
        }
    }


    void display_by_topic(string subject)
    {
        int i = 0;
        int count = 0;

        for (i = 0; i < topic.size(); i++)
        {
            if (topic[i] == subject)
                break;
        }
        for (int j = database[i].size() - 1; j >= 0; j--)
        {
            database[i][j].display();
            count++;
            if (count % 5 == 0)
            {
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
    }

    void display_all()
    {
        int count = 0;
        for (int i = 0; i < database.size(); i++)
        {
            for (int j = database[i].size() - 1; j >= 0; j--)
            {
                database[i][j].display();

                count++;

                if (count % 5 == 0)
                {
                    cout << "For more database type y(else type any other char)" << endl;
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

    void display_all_unanswered()
    {
        int count = 0;
        char x;
        for (int i = database.size() - 1; i >= 0; i--)
        {
            for (int j = database[i].size() - 1; j >= 0; j--)
            {

                if (!database[i][j].answered)
                {
                    cout << database[i][j].question << endl;
                    count++;
                    if (count % 5 == 0)
                    {
                        cout << "For more database type y(else type any other char)" << endl;
                        cin >> x;
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
    }

    void display_all_answered()
    {
        int count = 0;
        char x;
        for (int i = database.size() - 1; i >= 0; i--)
        {
            for (int j = database[i].size() - 1; j >= 0; j--)
            {
                if (database[i][j].answered)
                {
                    database[i][j].display();
                    count++;
                    if (count % 5 == 0)
                    {
                        cout << "For more type y";
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
};

// void display_all_answered();

// void accept_answer(int index, Question_Answer qna);
// void question_answer_data ::display_all()
// {
//     for (int i = 0; i < database.size(); i++)
//     {
//         //for (int j = 0; j < database[i].size(); j++)
//         {
//         }
//     }
// }

int main()
{
    question_answer_data Q;
    for (int i = 0; i < 3; i++)
    {
        cout << i << endl;
        Q.accept_question_by_topic("Maths");
        Q.accept_question_by_topic("Science");
    }
    Q.display_all();
    Q.display_all_unanswered();
    Q.display_by_topic("Maths");
}
