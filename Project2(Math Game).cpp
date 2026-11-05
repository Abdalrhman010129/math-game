#include<iostream>
#include<cstdlib>
#include <ctime>

using namespace std;

enum enQuestionsLevel { EasyLevel = 1, MedLevel = 2, HardLevel = 3, Mix = 4 };

enum enOperationType {Add=1,Sub=2,Mult=3,Div=4,MixOp=5 };


struct stQuestion
{
	int Number1 = 0;
	int Number2 = 0;
	enOperationType OperationType;
	enQuestionsLevel QuestionLevel;
	int CorrectAnswer = 0;
	int PlayerAnswer = 0;
	bool AnswerResult = false;
};

struct stQuizz
{
	stQuestion QuestionList[100];
	short NumberOfQuestions;
	enQuestionsLevel QuestionsLevel;
	enOperationType OpType;
	short NumberOfWrongAnswers = 0;
	short NumberOfRightAnswers = 0;
	bool isPass = false;
};

short ReadHowManyQuestions()
{
	short NumberOfQuestions;
	do
	{
		cout << "How Many Questions do you want to answer ? ";
		cin >> NumberOfQuestions;
	} while (NumberOfQuestions < 1 || NumberOfQuestions>10);

	return NumberOfQuestions;
}


enQuestionsLevel ReadQuestionsLevel()
{
	short QuestionsLevel = 0;
	do
	{
		cout << "Enter Questions Level [1] Easy, [2] Med, [3] Hard, [4] Mix ? ";
		cin >> QuestionsLevel;
	} while (QuestionsLevel < 1 || QuestionsLevel>4);

	return (enQuestionsLevel)QuestionsLevel;
}


string GetQuestionsLevelText(enQuestionsLevel QuestionLevel)
{
	string arrQuestionLevelText[4] = { "Easy","Med","Hard","Mix" };
	return arrQuestionLevelText[QuestionLevel - 1];
}

enOperationType ReadOpType()
{
	short OpType;
	do
	{
		cout << "Enter Operation Type [1] Add, [2] Sub, [3] Mul, [4] Div, [5] Mix ? ";
		cin >> OpType;
	} while (OpType < 1 || OpType>5);

	return (enOperationType)OpType;
}


string GetOpTypeSymbol(enOperationType OpType)
{
	switch (OpType)
	{
	case enOperationType::Add:
		return "+";
	case enOperationType::Sub:
		return "-";
	case enOperationType::Mult:
		return "*";
	case enOperationType::Div:
		return "/";
	default:
		return "Mix";
	}
}

void SetScreenColor(bool Right)
{
	if (Right)
		system("color 2F"); // Green for correct answers.
	else
	{
		system("color 4F"); // Red for incorrect answers.
		cout << "\a"; // Plays an alert sound.
	}
}

int RandomNumber(int From, int To)
{
	int RandomNumber = rand() % (To - From + 1) + From;
	return RandomNumber;
}



enOperationType GetRandomOperationType()
{
	int Op = RandomNumber(1, 4);
	return (enOperationType)Op;
}


int SimpleCalculator(int Number1, int Number2, enOperationType OpType)
{
	switch (OpType)
	{
	case enOperationType::Add:
		return Number1 + Number2;
	case enOperationType::Sub:
		return Number1 - Number2;
	case enOperationType::Mult:
			return Number1 * Number2; 
	case enOperationType::Div:
				return Number1 / Number2;
	default:
		return Number1 + Number2;

	}
}

stQuestion GenerateQuestion(enQuestionsLevel QuestionLevel, enOperationType OpType)
{
	stQuestion Question;
	if (QuestionLevel == enQuestionsLevel::Mix)
	{
		QuestionLevel = (enQuestionsLevel)RandomNumber(1, 3);
	}
	if (OpType == enOperationType::MixOp)
	{
		OpType = GetRandomOperationType();

	}
	Question.OperationType = OpType;

	switch (QuestionLevel)
	{
	case enQuestionsLevel::EasyLevel:
		Question.Number1 = RandomNumber(1, 10);
		Question.Number2 = RandomNumber(1, 10);

		Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, Question.OperationType);
		Question.QuestionLevel = QuestionLevel;
		return Question;

	case enQuestionsLevel::MedLevel:
		Question.Number1 = RandomNumber(10, 50);
		Question.Number2 = RandomNumber(10, 50);

		Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, Question.OperationType);
		Question.QuestionLevel = QuestionLevel;
		return Question;

	case enQuestionsLevel::HardLevel:
		Question.Number1 = RandomNumber(50, 100);
		Question.Number2 = RandomNumber(50, 100);

		Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, Question.OperationType);
		Question.QuestionLevel = QuestionLevel;
		return Question;
	
	}
	return Question;
}

void GenerateQuizzQuestions(stQuizz& Quizz)
{
	for (short Question = 0; Question < Quizz.NumberOfQuestions; Question++)
	{
		Quizz.QuestionList[Question] = GenerateQuestion(Quizz.QuestionsLevel, Quizz.OpType);
	}
}

int ReadQuestionAnswer()
{
	int Answer=0;
	cin >> Answer;
	return Answer;
}

void PrintTheQuestion(stQuizz& Quizz, short QuestionNumber)
{
	cout << "\n";
	cout << "Question [" << QuestionNumber + 1 << "/" << Quizz.NumberOfQuestions << "] \n\n";
	cout << Quizz.QuestionList[QuestionNumber].Number1 << endl;
	cout << Quizz.QuestionList[QuestionNumber].Number2 << endl;
	cout << GetOpTypeSymbol(Quizz.QuestionList[QuestionNumber].OperationType);
	cout << "\n___________" << endl;
}

void CorrectTheQuestionAnswer(stQuizz& Quizz, short QuestionNubmer)
{
	if (Quizz.QuestionList[QuestionNubmer].PlayerAnswer != Quizz.QuestionList[QuestionNubmer].CorrectAnswer)
	{
		Quizz.QuestionList[QuestionNubmer].AnswerResult = false;
		Quizz.NumberOfWrongAnswers++;
		cout << "Wront Answer :-( \n";
		cout << "The right answer is: "; 
		cout << Quizz.QuestionList[QuestionNubmer].CorrectAnswer;
		cout << "\n";

	}
	else
	{
		Quizz.QuestionList[QuestionNubmer].AnswerResult = true;
		Quizz.NumberOfRightAnswers++;
		cout << "Right Answer :-) \n";

	}
	cout << endl;
	SetScreenColor(Quizz.QuestionList[QuestionNubmer].AnswerResult);
}

void AskAndCorrectQuestionListAnswers(stQuizz& Quizz)
{
	for (short QuestionNumber = 0; QuestionNumber < Quizz.NumberOfQuestions; QuestionNumber++)
	{
		PrintTheQuestion(Quizz, QuestionNumber);
		Quizz.QuestionList[QuestionNumber].PlayerAnswer = ReadQuestionAnswer();
		CorrectTheQuestionAnswer(Quizz, QuestionNumber);
	}
	Quizz.isPass = (Quizz.NumberOfRightAnswers >= Quizz.NumberOfWrongAnswers);
}

string GetFinalResultsText(bool Pass)
{
	if (Pass)
		return "Pass :-)";
	else
		return "Fail :-(";

}


void PrintQuizzResults(stQuizz Quizz)
{
	cout << "\n";
	cout << "___________________________________\n\n";
	cout << "Final Results is " << GetFinalResultsText(Quizz.isPass);
	cout << "\n_________________________________\n\n";




	cout << "Number of Questions: " << Quizz.NumberOfQuestions << endl;
	cout << "Questions Level    : " << GetQuestionsLevelText(Quizz.QuestionsLevel) << endl;
	cout << "OpType             : " << GetOpTypeSymbol(Quizz.OpType) << endl;
	cout << "Number of Right Answers: " << Quizz.NumberOfRightAnswers << endl;
	cout << "Number of Wrong Answers: " << Quizz.NumberOfWrongAnswers << endl;
	cout << "____________________________________\n";



}

void PlayMathGame()
{
	stQuizz Quizz;

	Quizz.NumberOfQuestions = ReadHowManyQuestions();
	Quizz.QuestionsLevel = ReadQuestionsLevel();
	Quizz.OpType = ReadOpType();

	GenerateQuizzQuestions(Quizz);

	AskAndCorrectQuestionListAnswers(Quizz);
	PrintQuizzResults(Quizz);

}

void ResetScreen()
{
	system("cls");
	system("color 0F");
}

void StartGame()
{
	char PlayAgain = 'Y';
	do
	{
		ResetScreen();
		PlayMathGame();
		cout << endl << "Do you want to play again? Y/N? ";
		cin >> PlayAgain;
	} while (PlayAgain == 'Y' || PlayAgain == 'y');
}

int main()
{
	srand((unsigned)time(NULL));
	StartGame();
	return 0;
}


	







//My sol:

//write a program represent a math Game

//#include <iostream>
//#include<cstdlib>
//#include<ctime>
//using namespace std;
//enum enQuestionsLevel {Easy=1,Med=2,Hard=3,Mix=4};
//enum enOperationType  {Add=1,Sub=2,Mul=3,Div=4,mix=5};
//int ReadHowManyQuestions()
//{
//    int NumberOfQuestions;
//    do {
//        cout << "How Many Questions do you want to answer ? ";
//        cin >> NumberOfQuestions;
//    } while (NumberOfQuestions <0);
//    return NumberOfQuestions;
//}  
//int RandomNumber(int From, int To)
//{
//    int RandomNumber = rand() % (To - From + 1) + From;
//    return RandomNumber;
//}
//int GetQuestionLevelIndex()
//{
//    int QuestionLevelIndex;
//    do
//    {
//        cout << "Enter QuestionsLevel [1] Easy, [2] Med, [3] Hard, [4] Mix ? ";
//        cin >> QuestionLevelIndex;
//    } while (QuestionLevelIndex > 4 || QuestionLevelIndex < 1);
//    return QuestionLevelIndex;
//}
//enQuestionsLevel QuestionLevelChoice(int QuestionLevelIndex)
//{
//   
//    return (enQuestionsLevel)QuestionLevelIndex;
//}
//int GetOperationTypeIndex()
//{
//    int OperationTypeIndex;
//    do
//    {
//        cout << "Enter Operation Type [1] Add, [2] Sub, [3] Mul, [4] Div, [5] Mix ? ";
//        cin >> OperationTypeIndex;
//    } while (OperationTypeIndex > 5 || OperationTypeIndex < 1);
//    return OperationTypeIndex;
//}
//enOperationType OperationTypeChoice(int OperationTypeIndex)
//{
//  
//    return (enOperationType)OperationTypeIndex;
//}
//struct stQuizResult
//{
//    int NumberOfQuestions;
//    enQuestionsLevel QuestionsLevel;
//    enOperationType  OperationType;
//    int NumberOFRightAnswers;
//    int NumberOfWrongAnswers;
//
//};
//struct stQuestionParts
//{
//    int FirstNumber,SecondNumber,Result;
//    char Sign;
//
//};
//int GetQuestionNumbers(enQuestionsLevel QuestionLevel)
//{
//    switch (QuestionLevel)
//    {
//    case enQuestionsLevel::Easy:
//        return RandomNumber(0, 10);
//        break;
//    case enQuestionsLevel::Med:
//        return RandomNumber(10, 99);
//        break;
//    case enQuestionsLevel::Hard:
//        return RandomNumber(100, 999);
//        break;
//    case enQuestionsLevel::Mix:
//        return RandomNumber(RandomNumber(0,1000), RandomNumber(0,1000));
//        break;
//    }
//}
//char GetRandomSign()
//{
//    int RandomSign = RandomNumber(1, 4);
//    switch (RandomSign)
//    {
//    case 1:
//        return '+';
//        break;
//    case 2:
//        return '-';
//        break;
//    case 3:
//        return '*';
//        break;
//    case 4:
//        return '/';
//        break;
//
//    }
//}
//char GetQuestionSign(enOperationType OperationType)
//{
//    switch (OperationType)
//    {
//    case enOperationType::Add :
//        return '+';
//        break;
//    case enOperationType::Sub:
//        return '-';
//        break;
//    case enOperationType::Mul:
//        return '*';
//        break;
//    case enOperationType::Div:
//        return '/';
//        break;
//    case enOperationType::mix:
//        return GetRandomSign();
//        break;
//    }
//}
//stQuestionParts FormQuestion(int QuestionoLeveIndex,int OperationLevelIndex)
//{
//    stQuestionParts QuestionParts;
//    QuestionParts. FirstNumber = GetQuestionNumbers(QuestionLevelChoice(QuestionoLeveIndex));
//    QuestionParts. SecondNumber = GetQuestionNumbers(QuestionLevelChoice(QuestionoLeveIndex));
//    QuestionParts. Sign = GetQuestionSign(OperationTypeChoice(OperationLevelIndex));
//    cout << QuestionParts.FirstNumber << endl;
//    cout << QuestionParts. SecondNumber <<" "<< QuestionParts.Sign << endl;
//    cout << "_______________"<<endl;
//    return QuestionParts;
//}
//int GetUserAnswer()
//{
//    int Answer;
//    cin >> Answer;
//    return Answer;
//}
//int GetCorrectAnswerFromComputer(stQuestionParts QuestionParts)
//{
//    int CorrectAnswer;
//    switch (QuestionParts.Sign)
//    {
//    case '+':
//        CorrectAnswer = QuestionParts.FirstNumber + QuestionParts.SecondNumber;
//        break;
//    case '-':
//        CorrectAnswer = QuestionParts.FirstNumber - QuestionParts.SecondNumber;
//        break; 
//    case '*':
//        CorrectAnswer = QuestionParts.FirstNumber * QuestionParts.SecondNumber;
//        break;
//    case '/':
//        CorrectAnswer = QuestionParts.FirstNumber / QuestionParts.SecondNumber;
//        break;
//
//    }
//    return CorrectAnswer;
//
//}
//void ResetScreen()
//{
//    system("cls");
//    system("color 0F");
//}
//bool PrintIsCorrect(int UserAnswer, int CorrctAnswer)
//{
//    if (UserAnswer == CorrctAnswer)
//    {
//        cout << "Right Answer :-)\n" << endl;
//        system("color 2F");
//        return true;
//    }
//    else
//    {
//        system("color 4F");
//        cout << "\a";
//        cout << "Wrong Answer :-(\n";
//        cout << "Right Answer is : " << CorrctAnswer << endl << endl;
//        return false;
//    }
//}
//stQuizResult FillQuizResults(int NumberOfQuestions,int  NumberOFRightAnswers,int NumberOfWrongAnswers,int QuestionLevelIndex,int  OperationTypeIndex)
//{
//    stQuizResult QuizResults;
//    QuizResults.NumberOfQuestions = NumberOfQuestions;
//    QuizResults.NumberOFRightAnswers = NumberOFRightAnswers;
//    QuizResults.NumberOfWrongAnswers = NumberOfWrongAnswers;
//    QuizResults.OperationType = OperationTypeChoice(OperationTypeIndex);
//    QuizResults.QuestionsLevel = QuestionLevelChoice(QuestionLevelIndex);
//    return QuizResults;
//}
//stQuizResult PlayQuiz(int HowManyQuestions)
//{
//    stQuizResult QuizResults;
//    int QuestironLevelIndex = GetQuestionLevelIndex();
//    int OperationTypeIndex = GetOperationTypeIndex();
//    int RightAnswer = 0, WrongAnswer = 0;
//    for (int QuestionNumber = 1; QuestionNumber <= HowManyQuestions; QuestionNumber++)
//    {
//        cout << "Question [" << QuestionNumber << "/" << HowManyQuestions << "]\n"<<endl;
//       
//        if (PrintIsCorrect(GetUserAnswer(),
//     GetCorrectAnswerFromComputer(FormQuestion(QuestironLevelIndex,OperationTypeIndex))))
//            RightAnswer++;
//        else
//            WrongAnswer++;
//    }
//   QuizResults= FillQuizResults(HowManyQuestions, RightAnswer, WrongAnswer, QuestironLevelIndex, OperationTypeIndex);
//   return QuizResults;
//
//}
//void ShowFinalResultSentense(stQuizResult QuizResults)
//{
//    cout << "\n\n________________________________\n\n";
//    if (QuizResults.NumberOFRightAnswers >= QuizResults.NumberOfWrongAnswers)
//    {
//        cout << " Final Results is Pass :-)\n\n";
//        system("color 2F");
//    }
//    else
//    {
//        cout << " Final Results is Fail :-(\n\n";
//        system("color 4F");
//        cout << "\a";
//    }
//    cout << "________________________________\n";
//
//}
//string QuestiosLeveName(stQuizResult QuizResults)
//{
//    string arrQuestionLevelName[4] = { "Easy","Med","Hard","Mix" };
//    return arrQuestionLevelName[QuizResults.QuestionsLevel - 1];
//}
//string OperationTypeName(stQuizResult QuizResults)
//{
//    string arrOperationTypeName[5] = { "+","-","*","/","Mix" };
//    return arrOperationTypeName[QuizResults.OperationType - 1];
//}
//
//void PrintFinalResults(stQuizResult QuizResults)
//{
//    cout << "Number of Questions    : " << QuizResults.NumberOfQuestions << endl;
//    cout << "Questions Level        : " <<QuestiosLeveName( QuizResults) << endl;
//    cout << "Op Type                : " << OperationTypeName(QuizResults) << endl;
//    cout << "Number of Right Answers: " << QuizResults.NumberOFRightAnswers << endl;
//    cout << "Number of Wrong Answers: " << QuizResults.NumberOfWrongAnswers << endl;
//    cout << "_________________________________________\n" << endl;
//
//}
//void StartGame()
//{
//    char PlayAgain = 'Y';
//    do
//    {
//        ResetScreen();
//        stQuizResult QuizResults = PlayQuiz(ReadHowManyQuestions());
//        ShowFinalResultSentense(QuizResults);
//        PrintFinalResults(QuizResults);
//        cout << "Do you want to play again? Y/N?";
//        cin >> PlayAgain;
//
//    } while (PlayAgain == 'y' || PlayAgain == 'Y');
//
//}
//int main()
//{
//    srand((unsigned)time(NULL));
//    StartGame();
//    return 0;
//}