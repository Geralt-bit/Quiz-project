#include <bits/stdc++.h>
using namespace std;

// Struct to represent a quiz question
struct Question {
    string questionText;
    string correctAnswer;
};

// Class to represent the question bank
class QuestionBank {
private:
    vector<Question> questions;
    string filename; // File to store questions
public:
    // Constructor to initialize the filename
    QuestionBank(const string& file) : filename(file) {}

    // Method to load questions from file
    void loadQuestions() {
        ifstream fileIn(filename);
        if (fileIn.is_open()) {
            Question q;
            while (getline(fileIn, q.questionText) && getline(fileIn, q.correctAnswer)) {
                questions.push_back(q);
            }
            fileIn.close();
        }
    }

    // Method to save questions to file
    void saveQuestions() const {
        ofstream fileOut(filename);
        if (fileOut.is_open()) {
            for (const auto& q : questions) {
                fileOut << q.questionText << "\n" << q.correctAnswer << "\n";
            }
            fileOut.close();
        }
    }

    // Method to add a question to the bank
    void addQuestion(const Question& newQuestion) {
        questions.push_back(newQuestion);
        saveQuestions(); // Save questions to file
    }

    // Method to display all questions in the bank
    void displayQuestions() const {
        cout << "Question Bank:" << endl;
        for (int i = 0; i < questions.size(); ++i) {
            cout << i + 1 << ". " << questions[i].questionText << endl;
        }
    }

    // Method to edit a question in the bank
    void editQuestion(int index, const Question& updatedQuestion) {
        if (index >= 0 && index < questions.size()) {
            questions[index] = updatedQuestion;
            saveQuestions(); // Save questions to file
            cout << "Question updated successfully!" << endl;
        }
        else {
            cout << "Invalid index!" << endl;
        }
    }

    // Method to delete a question from the bank
    void deleteQuestion(int index) {
        if (index >= 0 && index < questions.size()) {
            questions.erase(questions.begin() + index);
            saveQuestions(); // Save questions to file
            cout << "Question deleted successfully!" << endl;
        }
        else {
            cout << "Invalid index!" << endl;
        }
    }

    // Method to take a quiz
    void takeQuiz() const {
        cout << "Welcome to the Quiz!" << endl;
        int score = 0;
        for (const Question& q : questions) {
            cout << "Q: " << q.questionText << endl;
            string answer;
            cout << "Your answer: ";
            cin >> answer;
            if (answer == q.correctAnswer) {
                cout << "Correct!" << endl;
                score++;
            }
            else {
                cout << "Incorrect!" << endl;
            }
        }
        cout << "Quiz finished! Your score: " << score << "/" << questions.size() << endl;
    }
};

int main() {
    QuestionBank quizBank("questions.txt"); // Specify the file to store questions
    char choice;

    // Load questions from file
    quizBank.loadQuestions();

    while (true) {

        cout << "Choose an option:" << endl;
        cout << "1. Add a question" << endl;
        cout << "2. Edit a question" << endl;
        cout << "3. Delete a question" << endl;
        cout << "4. Display all questions" << endl;
        cout << "5. Take the quiz" << endl;
        cout << "6. Quit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case '1': {
            Question newQuestion;
            cout << "Enter the question: ";
            cin.ignore(); // to clear the input buffer
            getline(cin, newQuestion.questionText);
            cout << "Enter the correct answer: ";
            getline(cin, newQuestion.correctAnswer);
            quizBank.addQuestion(newQuestion);
            cout << "Question added successfully!" << endl;
            break;
        }
        case '2': {
            int index;
            cout << "Enter the index of the question you want to edit: ";
            cin >> index;
            Question updatedQuestion;
            cout << "Enter the updated question: ";
            cin.ignore();
            getline(cin, updatedQuestion.questionText);
            cout << "Enter the updated correct answer: ";
            getline(cin, updatedQuestion.correctAnswer);
            quizBank.editQuestion(index - 1, updatedQuestion);
            break;
        }
        case '3': {
            int index;
            cout << "Enter the index of the question you want to delete: ";
            cin >> index;
            quizBank.deleteQuestion(index - 1);
            break;
        }
        case '4':
            quizBank.displayQuestions();
            break;
        case '5':
            quizBank.takeQuiz();
            break;
        case '6':
            cout << "Goodbye!" << endl;
            return 0;
        default:
            cout << "Invalid choice. Please enter a number between 1 and 6." << endl;
        }
    }

    return 0;
}
