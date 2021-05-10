#include <iostream>
#include <vector>
#include <string>
using namespace std;

//Class qna
class Question_Answer
{
    string question;
    string answer;
    bool answered;

public:
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

    friend class topic;
};

class topics
{
    string topic;

    vector<Question_Answer> data;

    void accept_questions_wrt_topic();

    void display_by_topic(string subject)
    {
        cout << topic << endl;
        for (int i = 0; i < data.size(); i++)
        {
            data[i].display();
        }
    }

    void display_by_topic_questions(string subject);

    void display_by_topic_answered(string subject);

    friend class question_answer_data;
};

class question_answer_data
{
    vector<topics> database;

    void accept_question_by_topic();

    void display_all();
    void display_all_questions();
    void display_all_answered();

    void accept_answer(int index, Question_Answer qna);
};

void question_answer_data ::display_all()
{
    for (int i = 0; i < database.size(); i++)
    {
        //for (int j = 0; j < database[i].size(); j++)
        {
        }
    }
}
