#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

enum Spec { COMPUTERSCIENCE, IT, ECONOMY, PHYSICS, ART };

string specStr[] = { "комп'ютерні науки", "інформатика", "математика та економіка", "фізика та інформатика", "трудове навчання" };
struct Student
{
    string prizv;
    unsigned kurs;
    Spec spec;
    unsigned physicsGrades;
    unsigned mathsGrades;
    union
    {
        unsigned programGrades;
        unsigned methodGrades;
        unsigned pedagogGrades;
    };
};

void Create(Student* s, const int N);
void Sort(Student* s, const int N);
void Print(Student* s, const int N);
int BinSearch(Student* s, const int N, const string prizv, unsigned programGrades, unsigned pedagogGrades, unsigned methodGrades);
int* IndexSort(Student* s, const int N);
void PrintIndexSorted(Student* s, int* I, const int N);

int main()
{
    int N;
    cout << "Введіть к-сть студентів: "; cin >> N;

    Student* s = new Student[N];

    int ThirdGrade;
    string prizv;
    int found;
    unsigned physicsGrades;
    unsigned mathsGrades;
    unsigned programGrades;
    unsigned methodGrades;
    unsigned pedagogGrades;

    int menuItem;
    do {
        cout << endl << endl << endl;
        cout << "Виберіть дію:" << endl << endl;
        cout << " [1] - введення даних з клавіатури" << endl;
        cout << " [2] - вивід даних на екран" << endl;
        cout << " [3] - фізичне впорядкування даних" << endl;
        cout << " [4] - індексне впорядкування та вивід даних" << endl << endl;
        cout << " [5] - бінарний пошук студента" << endl;
        cout << " [0] - вихід та завершення роботи програми" << endl << endl;
        cout << "Введіть значення: "; cin >> menuItem;
        cout << endl << endl << endl;
        switch (menuItem)
        {
            case 1:
                Create(s, N);
                break;
            case 2:
                Print(s, N);
                break;
            case 3:
                Sort(s, N);
                break;
            case 4:
                PrintIndexSorted(s, IndexSort(s, N), N);
                break;
            case 5:
                cout << "Введіть ключі пошуку:" << endl;
                cout << " Бал з математики: ";
                switch (s->spec)
                {
                    case COMPUTERSCIENCE:
                        cin >> s->mathsGrades;
                        break;
                    case IT:
                        cin >> s->methodGrades;
                        break;
                    case ECONOMY:
                    case ART:
                    case PHYSICS:
                        cin >> s->pedagogGrades;
                        break;
                }

                cin.get();
                cin.sync();
                cout << " прізвище: "; getline(cin, prizv);
                cout << endl;
                if ((found = BinSearch(s, N, prizv, s->programGrades, s->pedagogGrades, s->methodGrades)) != -1)
                    cout << "Знайдено студента в позиції " << found + 1 << endl;
                else
                    cout << "Шуканого студента не знайдено" << endl;
                break;
            case 0:
                break;
            default:
                cout << "Ви ввели помилкове значення! "
                        "Слід ввести число - номер вибраного пункту меню" << endl;
        }
    } while (menuItem != 0);

    Create(s, N);
    Sort(s, N);
    Print(s, N);
    return 0;
}

void Create(Student* s, const int N)
{
    int spec;
    for (int i = 0; i < N; i++)
    {
        cout << "Студент No " << i + 1 << ":" << endl;
        cin.get();
        cin.sync();

        cout << " прізвище: "; getline(cin, s[i].prizv);
        cout << " курс: "; cin >> s[i].kurs;
        cout << " спеціальність (0 - комп'ютерні науки, 1 - інформатика, 2 - математика та економіка, 3 - фізика та інформатика, 4 - трудове навчання): ";
        cin >> spec;
        cout << " оцінки з фізики: "; cin >> s[i].physicsGrades;
        cout << " оцінки з математики: "; cin >> s[i].mathsGrades;
        s[i].spec = (Spec)spec;
        switch (s[i].spec)
        {
            case COMPUTERSCIENCE:
                cout << " оцінки з програмування: "; cin >> s[i].programGrades;
                break;
            case IT:
                s[i].methodGrades;
                cout << " оцінки з чисельних методів: "; cin >> s[i].methodGrades;
                break;
            case ECONOMY:
            case ART:
            case PHYSICS:
                cout << " оцінки з педагогіки: "; cin >> s[i].pedagogGrades;
                break;
        }

        cout << endl;
    }
}
void Print(Student* s, const int N)
{
    cout << "============================================================================ ============================================================================= ==============" << endl;
    cout << "| No | Прізвище | курс |     спеціальність     | оцінка з фізики | оцінка з математики | оцінка з програмування | оцінка з чисельних методів | оцінка з педагогіки |" << endl;
    cout << "---------------------------------------------------------------------------- ----------------------------------------------------------------------------- --------------" << endl;
    for (int i = 0; i < N; i++)
    {
        cout << "|" << setw(2) << right << i + 1 << " ";
        cout << " |" << setw(10) << left << s[i].prizv
             << "     |" << setw(3) << right << s[i].kurs << " "
             << " |" << setw(23) << left << specStr[s[i].spec]
             << "       |" << setw(17) << right << s[i].physicsGrades << " "
             << "|" << setw(21) << right << s[i].mathsGrades << " ";

        switch (s[i].spec)
        {
            case COMPUTERSCIENCE:
                cout << "| " << setw(24) << right << s[i].programGrades << " |                            |" << "                     |"
                     << endl;
                break;
            case IT:
                cout << "|                        | " << setw(28) << s[i].methodGrades << " |                     |"
                     << endl;
                break;
            case ECONOMY:
            case ART:
            case PHYSICS:
                cout << "|                        |                            | " << setw(15) << s[i].pedagogGrades << " |"
                     << endl;
                break;
        }
    }
    cout << "======================================================================================================================================================================="
         << endl;
    cout << endl;
}

void Sort(Student* s, const int N)
{
    Student tmp;
    for (int i0 = 0; i0 < N - 1; i0++)
        for (int i1 = 0; i1 < N - i0 - 1; i1++)
            switch (s[i1].spec)
            {
                case COMPUTERSCIENCE:
                    if  ((s[i1].spec > s[i1 + 1].spec)
                        ||
                        ((s[i1].spec == s[i1 + 1].spec) &&
                        (s[i1].mathsGrades > s[i1 + 1].mathsGrades))
                        ||
                        (s[i1].spec == s[i1 + 1].spec) &&
                        (s[i1].mathsGrades == s[i1 + 1].mathsGrades) &&
                        (s[i1].prizv > s[i1 + 1].prizv))
                    {
                        tmp = s[i1];
                        s[i1] = s[i1 + 1];
                        s[i1 + 1] = tmp;
                    }
                    break;

                case IT:
                    if ((s[i1].methodGrades > s[i1 + 1].methodGrades)
                        ||
                        (s[i1].methodGrades == s[i1 + 1].methodGrades &&
                        (s[i1].mathsGrades > s[i1 + 1].mathsGrades))
                        ||
                        (s[i1].methodGrades == s[i1 + 1].methodGrades &&
                        (s[i1].mathsGrades == s[i1 + 1].mathsGrades) &&
                        (s[i1].prizv > s[i1 + 1].prizv)))
                    {
                        tmp = s[i1];
                        s[i1] = s[i1 + 1];
                        s[i1 + 1] = tmp;
                    }
                    break;

                case ECONOMY:
                case ART:
                case PHYSICS:
                    if ((s[i1].pedagogGrades > s[i1 + 1].pedagogGrades)
                        ||
                        (s[i1].pedagogGrades == s[i1 + 1].pedagogGrades &&
                        (s[i1].mathsGrades > s[i1 + 1].mathsGrades))
                        ||
                        ((s[i1].pedagogGrades == s[i1 + 1].pedagogGrades) &&
                        (s[i1].mathsGrades == s[i1 + 1].mathsGrades) &&
                        (s[i1].prizv > s[i1 + 1].prizv)))
                    {
                        tmp = s[i1];
                        s[i1] = s[i1 + 1];
                        s[i1 + 1] = tmp;
                    }
                    break;
            }

}

int* IndexSort(Student* s, const int N)
{

    int* I = new int[N];
    for (int i = 0; i < N; i++)
        I[i] = i;
    int i, j, value;
    for (i = 1; i < N; i++)
    {
        switch (s[i].spec)
        {
            case COMPUTERSCIENCE:
                value = I[i];
                for (j = i - 1;
                     j >= 0 && ((s[I[j]].spec > s[value].spec)
                                ||
                                (s[I[j]].spec == s[value].spec) &&
                                (s[I[j]].mathsGrades > s[value].mathsGrades)
                                ||
                                (s[I[j]].spec == s[value].spec) &&
                                (s[I[j]].mathsGrades == s[value].mathsGrades) &&
                                (s[I[j]].prizv > s[value].prizv));
                     j--)
                {
                    I[j + 1] = I[j];
                }
                I[j + 1] = value;
                break;

            case IT:
                value = I[i];
                for (j = i - 1;
                     j >= 0 && ((s[I[j]].methodGrades > s[value].methodGrades)
                                ||
                                (s[I[j]].methodGrades == s[value].methodGrades &&
                                (s[I[j]].mathsGrades > s[value].mathsGrades)
                                ||
                                (s[I[j]].methodGrades == s[value].methodGrades &&
                                (s[I[j]].mathsGrades == s[value].mathsGrades) &&
                                (s[I[j]].prizv > s[value].prizv))));
                     j--)
                {
                    I[j + 1] = I[j];
                }
                I[j + 1] = value;
                break;

            case ART:
            case ECONOMY:
            case PHYSICS:
                value = I[i];
                for (j = i - 1;
                     j >= 0 && ((s[I[j]].pedagogGrades > s[value].pedagogGrades)
                                ||
                                (s[I[j]].pedagogGrades == s[value].pedagogGrades &&
                                (s[I[j]].mathsGrades > s[value].mathsGrades)
                                ||
                                (s[I[j]].pedagogGrades == s[value].pedagogGrades &&
                                (s[I[j]].mathsGrades == s[value].mathsGrades) &&
                                (s[I[j]].prizv > s[value].prizv))));
                     j--)
                {
                    I[j + 1] = I[j];
                }
                I[j + 1] = value;
                break;

        }
        return I;

    };
}

void PrintIndexSorted(Student* s, int* I, const int N)
{
    cout << "============================================================================ ======================================" << endl;
    cout << "| No | Прізвище | курс| спеціальність | оцінка з фізики | оцінка з математики | оцінка з інформатики |" << endl;
    cout << "---------------------------------------------------------------------------- --------------------------------------" << endl;
    for (int i = 0; i < N; i++)
    {
        cout << "| " << setw(2) << right << i + 1 << " ";
        cout << "| " << setw(12) << left << s[I[i]].prizv
             << "| " << setw(3) << right << s[I[i]].kurs << " "
             << "| " << setw(23) << left << specStr[s[I[i]].spec]
             << "| " << setw(15) << right << s[I[i]].physicsGrades << " "
             << "| " << setw(19) << left << s[I[i]].mathsGrades << " ";
        switch (s[i].spec)
        {
            case COMPUTERSCIENCE:
                cout << "| " << setw(22) << right << s[I[i]] .programGrades << " |                            |" << "                     |"
                     << endl;
                break;
            case IT:
                cout << "|                        | " << setw(26) << s[I[i]].methodGrades << " |                     |"
                     << endl;
                break;
            case ECONOMY:
            case ART:
            case PHYSICS:
                cout << "|                        |                            | " << setw(19) << s[I[i]].pedagogGrades << " |"
                     << endl;
                break;
        }
        cout << endl;
    }
    cout << "================================================================================================================="
         << endl;
    cout << endl;
}

int BinSearch(Student* s, const int N, const string prizv, unsigned mathsGrades, unsigned pedagogGrades, unsigned methodGrades)
{
    int L = 0, R = N - 1, m;
    do {

        switch (s->spec)
        {
            case COMPUTERSCIENCE:
                m = (L + R) / 2;
                if (s[m].prizv == prizv && s[m].mathsGrades == mathsGrades)
                    return m;
                if ((s[m].prizv < prizv)
                    ||
                    (s[m].prizv == prizv &&
                    (s[m].mathsGrades < mathsGrades)))
                {
                    L = m + 1;
                }
                else
                {
                    R = m - 1;
                }
                break;

            case IT:
                m = (L + R) / 2;
                if (s[m].prizv == prizv && s[m].methodGrades == methodGrades)
                    return m;
                if ((s[m].prizv < prizv)
                    ||
                    (s[m].prizv == prizv &&
                     s[m].methodGrades < methodGrades)
                    ||
                    (s[m].prizv == prizv && s[m].methodGrades == methodGrades)
                        )
                {
                    L = m + 1;
                }
                else
                {
                    R = m - 1;
                }
                break;

            case ECONOMY:
            case ART:
            case PHYSICS:
                m = (L + R) / 2;
                if (s[m].prizv == prizv && s[m].pedagogGrades == pedagogGrades)
                    return m;
                if ((s[m].prizv < prizv)
                    ||
                    (s[m].prizv == prizv &&
                     s[m].pedagogGrades < pedagogGrades)
                    ||
                    (s[m].prizv == prizv && s[m].pedagogGrades == pedagogGrades)
                        )
                {
                    L = m + 1;
                }
                else
                {
                    R = m - 1;
                }
                break;
        }

    } while (L <= R);
    return -1;
}