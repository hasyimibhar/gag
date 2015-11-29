#ifndef COMMON_H_INCLUDED
#define COMMON_H_INCLUDED

#include <curses.h>
#include <algorithm>
#include <string>

using namespace std;

#define FOREACH(ContType,ElemType,Iterator,Container) for(std::ContType<ElemType>::iterator Iterator = Container.begin(); Iterator != Container.end(); Iterator++)

template <class C, class T> void remove_element(C &container, const T &value)
{
	container.erase(std::remove(container.begin(), container.end(), value), container.end());
}

#define MIN_CONFIRM_COLS    20
#define MAX_CONFIRM_COLS    60

#define MIN_MESSAGEBOX_COLS    20
#define MAX_MESSAGEBOX_COLS    80

bool ConfirmBox(WINDOW*, string, string);
void MessageBox(WINDOW*, string, string);
std::string StringBox(WINDOW*, string, string, int);

void         PackInteger16(unsigned char*, unsigned int);
void         PackInteger32(unsigned char*, unsigned int);
void         PackInteger64(unsigned char*, uint64_t);
unsigned int UnpackInteger16(unsigned char*);
unsigned int UnpackInteger32(unsigned char*);
uint64_t     UnpackInteger64(unsigned char*);

#define Pack754_32(f)   (Pack754((f), 32, 8))
#define Pack754_64(f)   (Pack754((f), 64, 11))
#define Unpack754_32(i) (Unpack754((i), 32, 8))
#define Unpack754_64(i) (Unpack754((i), 64, 11))

long long   Pack754  (long double, unsigned, unsigned);
long double Unpack754(long long, unsigned, unsigned);

#endif // COMMON_H_INCLUDED
